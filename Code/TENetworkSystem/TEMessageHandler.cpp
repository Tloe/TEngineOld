#include "TEMessageHandler.h"
#include "TEEventManager.h"
#include "TEReliabilityControl.h"

#include <limits>

namespace
{
    U32 GetUniqueMessageId()
    {
        static U32 packetId = 0;

        if(packetId == std::numeric_limits<U32>::max())
            packetId = 0;

        return packetId++;
    }

}

TE::Network::MessageHandler::MessageHandler()
{

}

void TE::Network::MessageHandler::QueBroadcastMessage(TE::Net::Packet &packet, bool reliable)
{
    U32 messageId = ::GetUniqueMessageId();

    Outgoing::Message message { std::move(packet), 0, 0};

    for(auto & que : m_outgoing.ques)
    {
        que.second.push_back(messageId);
        ++message.queCount;
        if(reliable)
            ++message.missingAcks;
    }

    m_outgoing.messages.emplace(std::make_pair(messageId, std::move(message)));
}

void TE::Network::MessageHandler::QueMessage(TE::Net::Packet &packet, bool reliable, I32 connectionId)
{
    U32 messageId = ::GetUniqueMessageId();

    Outgoing::Message message { std::move(packet), 0, 1};

    m_outgoing.ques[connectionId].push_back(messageId);
    if(reliable)
        ++message.missingAcks;

    m_outgoing.messages.emplace(std::make_pair(messageId, std::move(message)));
}

void TE::Network::MessageHandler::AddNetworkObject(I32 objectId, TE::Network::NetworkObjectSPtr &networkObject)
{
    m_networkObjects.insert(std::make_pair(objectId, networkObject));
}

bool TE::Network::MessageHandler::HasQuedMessages(U32 connectionId)
{
    return !m_outgoing.ques[connectionId].empty();
}

TE::Net::Packet TE::Network::MessageHandler::GenerateQuePacket(U32 connectionId, U32 sequenceNo)
{
    Net::Packet packet;
    packet.BeginPacket(Net::PacketType::Packet);

    auto & que = m_outgoing.ques[connectionId];
    packet.WriteU32(que.size());

    for(U32 messageId : que)
    {
        auto & msg = m_outgoing.messages.find(messageId)->second;

        packet.WriteBinaryPacket(msg.packet);

        if(--msg.queCount == 0 && msg.missingAcks == 0)
        {
            m_outgoing.messages.erase(messageId);
        }

        m_outgoing.messageIdsInPackage.insert(std::make_pair(sequenceNo, messageId));
    }

    que.clear();

    packet.EndPacket();

    return packet;
}

void TE::Network::MessageHandler::HandleQuePacket(U32 connectionId, Net::Packet &packet, U64 time)
{
    U32 numMessages;
    packet.StartReading();
    packet.ReadU32(numMessages);
    for(U32 i = 0; i < numMessages; ++i)
    {
        TE::Net::Packet message;
        packet.ReadBinaryPacket(message);
        HandleIncoming(connectionId, message, time);
    }
}

void TE::Network::MessageHandler::GenerateObjectUpdateMessages()
{
    m_objectUpdatePackets.clear();

    for(const auto & objItr : m_networkObjects)
    {
        auto objItrSPtr = objItr.second.lock();
        if(objItrSPtr)
        {
            m_objectUpdatePackets.emplace_back(objItrSPtr->CreateUpdatePacket());
            m_objectUpdatePackets.back().WriteMessageType(MessageType::ObjectUpdate);
        }
    }
}

void TE::Network::MessageHandler::QueObjectUpdateMessages(U32 connectionId)
{
    for(Net::Packet & message : m_objectUpdatePackets)
    {
        QueMessage(message, false, connectionId);
    }
}

void TE::Network::MessageHandler::CheckAcks(U32 connectionId, std::vector<U32> & acks)
{
    auto & lastAck = m_lastAcks[connectionId];
    for(U32 ack : acks)
    {
        U32 expectedAck = lastAck + 1;
        if(ack == expectedAck)
        {
            auto msgIdRange = m_outgoing.messageIdsInPackage.equal_range(ack);
            for(auto itr = msgIdRange.first; itr != msgIdRange.second; ++itr)
            {
                if(m_outgoing.messages[itr->second].missingAcks <= 1)
                {
                    m_outgoing.messages.erase(itr->second);
                }
                else
                {
                    --m_outgoing.messages[itr->second].missingAcks;
                }
            }
        }
        else
        {
            auto msgIdRange = m_outgoing.messageIdsInPackage.equal_range(expectedAck);
            for(auto itr = msgIdRange.first; itr != msgIdRange.second; ++itr)
            {
                m_outgoing.ques[connectionId].push_back(itr->second);
                ++m_outgoing.messages[itr->second].queCount;
            }
        }
        m_outgoing.messageIdsInPackage.erase(expectedAck);
        lastAck = ack;
    }
}

void TE::Network::MessageHandler::HandleIncoming(U32 connectionId, TE::Net::Packet &packet, U64 time)
{
    assert(m_connectionObjects.find(connectionId) != m_connectionObjects.end());

    I32 messageType;
    packet.StartReading();
    packet.ReadMessageType(messageType);
    I32 objectId;
    switch(messageType)
    {
    case MessageType::ObjectUpdate:
        {
            packet.ReadI32(objectId);
            auto sPtr = m_networkObjects[objectId].lock();
            if(sPtr)
                sPtr->RemoteObjectUpdate(packet);
            break;
        }
    case MessageType::TranslationEvent:
        {
            objectId = m_connectionObjects.find(connectionId)->second;
            auto sPtr = m_networkObjects[objectId].lock();
            if(sPtr)
                sPtr->RemoteTranslationEvent(packet, time);
            break;
        }
    case MessageType::ScaleEvent:
        {
            objectId = m_connectionObjects.find(connectionId)->second;
            auto sPtr = m_networkObjects[objectId].lock();
            if(sPtr)
                sPtr->RemoteScaleEvent(packet, time);
            break;
        }
    case MessageType::OrientationEvent:
        {
            objectId = m_connectionObjects.find(connectionId)->second;
            auto sPtr = m_networkObjects[objectId].lock();
            if(sPtr)
                sPtr->RemoteOrientationEvent(packet, time);
            break;
        }
    case MessageType::AddForceEvent:
        {
            objectId = m_connectionObjects.find(connectionId)->second;
            auto sPtr = m_networkObjects[objectId].lock();
            if(sPtr)
                sPtr->RemoteAddForceEvent(packet, time);
            break;
        }
    }
}

void TE::Network::MessageHandler::MapConnectionToObjectId(I32 connectionId, I32 objectId)
{
    m_connectionObjects.insert(std::make_pair(connectionId, objectId));
}

void TE::Network::MessageHandler::AddConnection(U32 connectionId)
{
    m_outgoing.ques.insert(std::make_pair(connectionId, Outgoing::MessageIdList()));
    m_lastAcks.insert(std::make_pair(connectionId, -1));
}

void TE::Network::MessageHandler::RemoveConnection(U32 connectionId)
{
    for(U32 messageId : m_outgoing.ques[connectionId])
    {
        if(m_outgoing.messages[messageId].missingAcks)
            m_outgoing.messages.erase(messageId);
        else
            --m_outgoing.messages[messageId].missingAcks;
    }

    m_outgoing.ques.erase(connectionId);
    m_lastAcks.erase(connectionId);
}
