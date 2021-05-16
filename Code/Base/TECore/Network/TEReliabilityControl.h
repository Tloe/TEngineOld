#ifndef TERELIABILITYCONTROL_H
#define TERELIABILITYCONTROL_H

#include "TEDataTypes.h"

#include <limits>
#include <list>
#include <vector>

namespace TE {
namespace Net {
    struct PacketData {
        U32 sequenceNumber;
        I64 time;
        I32 size;
    };

    inline bool SequenceNumberMoreRecent(U32 s1, U32 s2, U32 maxSequenceNo = std::numeric_limits<U32>::max()) {
        return ((s1 > s2) && (s1 - s2 <= maxSequenceNo / 2)) || ((s2 > s1) && (s2 - s1 > maxSequenceNo / 2));
    }

    class ReliabilityControl {
      public:
        ReliabilityControl(U32 maxSequenceNumber = 0xffffff);

        void Reset();
        void PacketSent(I32 size);
        void PacketReceived(U32 sequenceNumber, I32 size);
        U32 GenerateAckBits();
        void ProcessAck(U32 ack, U32 ackBits);
        void Update(U64 deltaTime);

        U32 GetLocalSequence() const;
        U32 GetRemoteSequence() const;

        U32 GetSentPackets() const;
        U32 GetReceivedPackets() const;
        U32 GetLostPackets() const;
        U32 GetAckedPackets() const;

        F32 GetSentBandwidth_kbit() const;
        F32 GetAckedBandwidth_kbit() const;
        U64 GetRoundTripTime() const;

        std::vector<U32> &GetAcks();

      protected:
        void AdvanceQueueTime(U64 deltaTime);
        void UpdateQueues();
        void UpdateStats();

      private:
        U32 m_maxSequenceNumber;
        U32 m_localSequenceNumber;
        U32 m_remoteSequenceNumber;

        U32 m_sentPackets;
        U32 m_recvPackets;
        U32 m_lostPackets;
        U32 m_ackedPackets;

        F32 m_sentBandwidth;
        F32 m_ackedBandwidth;
        I64 m_rtt;
        I64 m_rttMaximum;

        std::vector<U32> m_acks;

        // TODO: optimize with circular buffers indexed by sequence % BufferSize.
        std::list<PacketData> m_sentQueue;
        std::list<PacketData> m_pendingAckQueue;
        std::list<PacketData> m_receivedQueue;
        std::list<PacketData> m_ackedQueue;
    };
}
}

#endif
