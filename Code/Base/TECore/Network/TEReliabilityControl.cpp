#include "TEReliabilityControl.h"
#include "TETime.h"

#include <assert.h>
#include <iostream>

namespace {
    const F32 bandwidthMultiplier = 0.008f;

    I32 BitIndexForSequence(U32 sequence, U32 ack, U32 maxSequenceNo) {
        assert(sequence != ack);
        assert(!TE::Net::SequenceNumberMoreRecent(sequence, ack, maxSequenceNo));
        if (sequence > ack) {
            assert(ack < 33);
            assert(maxSequenceNo >= sequence);
            return ack + (maxSequenceNo - sequence);
        } else {
            assert(ack >= 1);
            assert(sequence <= ack - 1);
            return ack - 1 - sequence;
        }
    }

    bool ListHasSequenceNo(const std::list<TE::Net::PacketData> &lst, U32 sequenceNumber) {
        for (auto &itr : lst)
            if (itr.sequenceNumber == sequenceNumber)
                return true;
        return false;
    }

    void InsertSequenceNoInList(std::list<TE::Net::PacketData> &lst,
                                const TE::Net::PacketData &p,
                                U32 maxSequenceNumber) {
        if (lst.empty()) {
            lst.push_back(p);
        } else {
            if (!TE::Net::SequenceNumberMoreRecent(p.sequenceNumber, lst.front().sequenceNumber, maxSequenceNumber)) {
                lst.push_front(p);
            } else if (TE::Net::SequenceNumberMoreRecent(p.sequenceNumber, lst.back().sequenceNumber, maxSequenceNumber)) {
                lst.push_back(p);
            } else {
                for (auto itr = lst.begin(); itr != lst.end(); ++itr) {
                    assert(itr->sequenceNumber != p.sequenceNumber);
                    if (TE::Net::SequenceNumberMoreRecent(itr->sequenceNumber, p.sequenceNumber, maxSequenceNumber)) {
                        lst.insert(itr, p);
                        break;
                    }
                }
            }
        }
    }
}

TE::Net::ReliabilityControl::ReliabilityControl(U32 maxSequenceNumber)
    : m_maxSequenceNumber(maxSequenceNumber) {
    Reset();
}

void TE::Net::ReliabilityControl::Reset() {
    m_localSequenceNumber  = 0;
    m_remoteSequenceNumber = 0;
    m_sentQueue.clear();
    m_receivedQueue.clear();
    m_pendingAckQueue.clear();
    m_ackedQueue.clear();
    m_sentPackets    = 0;
    m_recvPackets    = 0;
    m_lostPackets    = 0;
    m_ackedPackets   = 0;
    m_sentBandwidth  = 0;
    m_ackedBandwidth = 0;
    m_rtt            = 0;
    m_rttMaximum     = Time::Microseconds::Second;
}

void TE::Net::ReliabilityControl::PacketSent(I32 size) {
    assert(!::ListHasSequenceNo(m_sentQueue, m_localSequenceNumber));
    assert(!::ListHasSequenceNo(m_pendingAckQueue, m_localSequenceNumber));

    PacketData data;
    data.sequenceNumber = m_localSequenceNumber;
    data.time           = 0;
    data.size           = size;
    m_sentQueue.push_back(data);
    m_pendingAckQueue.push_back(data);

    m_sentPackets++;
    m_localSequenceNumber++;
    if (m_localSequenceNumber > m_maxSequenceNumber)
        m_localSequenceNumber = 0;
}

void TE::Net::ReliabilityControl::PacketReceived(U32 sequenceNumber, I32 size) {
    m_recvPackets++;

    if (::ListHasSequenceNo(m_receivedQueue, sequenceNumber))
        return;

    PacketData data;
    data.sequenceNumber = sequenceNumber;
    data.time           = 0;
    data.size           = size;
    m_receivedQueue.push_back(data);

    if (Net::SequenceNumberMoreRecent(sequenceNumber, m_remoteSequenceNumber, m_maxSequenceNumber))
        m_remoteSequenceNumber = sequenceNumber;
}

U32 TE::Net::ReliabilityControl::GenerateAckBits() {
    U32 ackBits = 0;

    for (auto &itr : m_receivedQueue) {
        if (itr.sequenceNumber == m_remoteSequenceNumber ||
            Net::SequenceNumberMoreRecent(itr.sequenceNumber, m_remoteSequenceNumber, m_maxSequenceNumber)) {
            break;
        }
        I32 bit_index = ::BitIndexForSequence(itr.sequenceNumber, m_remoteSequenceNumber, m_maxSequenceNumber);

        if (bit_index <= 31)
            ackBits |= 1 << bit_index;
    }

    return ackBits;
}

void TE::Net::ReliabilityControl::ProcessAck(U32 ack, U32 ackBits) {
    if (m_pendingAckQueue.empty())
        return;

    auto itr = m_pendingAckQueue.begin();
    while (itr != m_pendingAckQueue.end()) {
        bool acked = false;

        if (itr->sequenceNumber == ack) {
            acked = true;
        } else if (!SequenceNumberMoreRecent(itr->sequenceNumber, ack, m_maxSequenceNumber)) {
            I32 bitIndex = BitIndexForSequence(itr->sequenceNumber, ack, m_maxSequenceNumber);
            if (bitIndex <= 31)
                acked = (ackBits >> bitIndex) & 1;
        }
        if (acked) {
            m_rtt += static_cast<I64>((itr->time - m_rtt) * 0.1);
            // m_rtt += 7.0/8.0*m_rtt +(1.0-7.0/8.0)*(static_cast<I64>(itr->time) - m_rtt);
            InsertSequenceNoInList(m_ackedQueue, *itr, m_maxSequenceNumber);
            m_acks.push_back(itr->sequenceNumber);
            m_ackedPackets++;
            itr = m_pendingAckQueue.erase(itr);
        } else
            ++itr;
    }
}

void TE::Net::ReliabilityControl::Update(U64 deltaTime) {
    m_acks.clear();
    AdvanceQueueTime(deltaTime);
    UpdateQueues();
    UpdateStats();
}

U32 TE::Net::ReliabilityControl::GetLocalSequence() const {
    return m_localSequenceNumber;
}

U32 TE::Net::ReliabilityControl::GetRemoteSequence() const {
    return m_remoteSequenceNumber;
}

U32 TE::Net::ReliabilityControl::GetSentPackets() const {
    return m_sentPackets;
}

U32 TE::Net::ReliabilityControl::GetReceivedPackets() const {
    return m_recvPackets;
}

U32 TE::Net::ReliabilityControl::GetLostPackets() const {
    return m_lostPackets;
}

U32 TE::Net::ReliabilityControl::GetAckedPackets() const {
    return m_ackedPackets;
}

F32 TE::Net::ReliabilityControl::GetSentBandwidth_kbit() const {
    return m_sentBandwidth;
}

F32 TE::Net::ReliabilityControl::GetAckedBandwidth_kbit() const {
    return m_ackedBandwidth;
}

U64 TE::Net::ReliabilityControl::GetRoundTripTime() const {
    return m_rtt;
}

std::vector<U32> &TE::Net::ReliabilityControl::GetAcks() {
    return m_acks;
}

void TE::Net::ReliabilityControl::AdvanceQueueTime(U64 deltaTime) {
    for (auto &itr : m_sentQueue)
        itr.time += deltaTime;

    for (auto &itr : m_receivedQueue)
        itr.time += deltaTime;

    for (auto &itr : m_pendingAckQueue)
        itr.time += deltaTime;

    for (auto &itr : m_ackedQueue)
        itr.time += deltaTime;
}

void TE::Net::ReliabilityControl::UpdateQueues() {
    const U32 timeEpsilon = 1000;

    while (m_sentQueue.size() && m_sentQueue.front().time > m_rttMaximum + timeEpsilon) {
        m_sentQueue.pop_front();
    }

    if (m_receivedQueue.size()) {
        U32 latestSequenceNo = m_receivedQueue.back().sequenceNumber;
        U32 minimumSequenceNo;
        if (latestSequenceNo >= 34)
            minimumSequenceNo = (latestSequenceNo - 34);
        else
            minimumSequenceNo = m_maxSequenceNumber - (34 - latestSequenceNo);

        while (m_receivedQueue.size() && !SequenceNumberMoreRecent(m_receivedQueue.front().sequenceNumber, minimumSequenceNo, m_maxSequenceNumber)) {
            m_receivedQueue.pop_front();
        }
    }

    while (m_ackedQueue.size() && m_ackedQueue.front().time > m_rttMaximum * 2 - timeEpsilon) {
        m_ackedQueue.pop_front();
    }

    while (m_pendingAckQueue.size() && m_pendingAckQueue.front().time > m_rttMaximum + timeEpsilon) {
        m_pendingAckQueue.pop_front();
        m_lostPackets++;
    }
}

void TE::Net::ReliabilityControl::UpdateStats() {
    I64 sentBytesPerSecond = 0;
    for (auto &itr : m_sentQueue) {
        sentBytesPerSecond += itr.size;
    }
    I32 ackedPacketsPerSecond = 0;
    I64 ackedBytesPerSecond   = 0;
    for (auto &itr : m_ackedQueue) {
        if (itr.time >= m_rttMaximum) {
            ackedPacketsPerSecond++;
            ackedBytesPerSecond += itr.size;
        }
    }

    m_sentBandwidth  = sentBytesPerSecond * bandwidthMultiplier;
    m_ackedBandwidth = ackedBytesPerSecond * bandwidthMultiplier;
}
