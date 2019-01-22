#ifndef TEMESSAGEHANDLER_H
#define TEMESSAGEHANDLER_H

#include "TEOutgoing.h"
#include "TEPacket.h"
#include "TENetworkObject.h"

#include <vector>

namespace TE
{
    namespace Network
    {
        namespace MessageType
        {
            enum
            {
                ObjectUpdate = -120,
                TranslationEvent,
                ScaleEvent,
                OrientationEvent,
                AddForceEvent,
                NotSet = -1
            };
        }

        class MessageHandler
        {
        public:
            MessageHandler();

            void AddConnection(U32 connectionId);
            void RemoveConnection(U32 connectionId);

            void QueBroadcastMessage(Net::Packet & packet, bool reliable);
            void QueMessage(Net::Packet & packet, bool reliable, I32 connectionId);

            void AddNetworkObject(I32 objectId, TE::Network::NetworkObjectSPtr &networkObject);
            void GenerateObjectUpdateMessages();
            void QueObjectUpdateMessages(U32 connectionId);

            bool HasQuedMessages(U32 connectionId);
            Net::Packet GenerateQuePacket(U32 connectionId, U32 sequenceNo);
            void HandleQuePacket(U32 connectionId, Net::Packet & packet, U64 time);

            void CheckAcks(U32 connectionId, std::vector<U32> & acks);

            void HandleIncoming(U32 connectionId, Net::Packet & packet, U64 time);
            void MapConnectionToObjectId(I32 connectionId, I32 objectId);

        private:
            typedef std::map<U32, U32> ConnectionNetworkObjectMap;
            typedef std::map<U32, NetworkObjectWPtr> NetworkObjectWPtrMap;
            typedef std::map<U32, U32> ConnectionLastAckMap;
            typedef std::vector<Net::Packet> ObjectUpdatePacketVec;

			void QueMessage(U32 uniqueId, Net::Packet & packet, bool reliable, I32 connectionId);

            ConnectionLastAckMap m_lastAcks;
            ConnectionNetworkObjectMap m_connectionObjects;
            NetworkObjectWPtrMap m_networkObjects;
            ObjectUpdatePacketVec m_objectUpdatePackets;
            Outgoing m_outgoing;
        };
    }
}

#endif
