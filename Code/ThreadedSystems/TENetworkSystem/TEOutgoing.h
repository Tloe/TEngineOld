#ifndef TEOUTGOING_H
#define TEOUTGOING_H

#include "TEDataTypes.h"
#include "TEPacket.h"

#include <unordered_map>
#include <map>
#include <list>

namespace TE
{
    namespace Network
    {
        typedef U32 MessageId;
        typedef I32 ConnectionId;
        typedef U32 SequenceNo;

        struct Outgoing
        {
            struct Message
            {
                Net::Packet packet;
                U32 missingAcks;
                U32 queCount;
            };

            typedef std::unordered_map<MessageId, Message> OutgoingMessageMap;
            typedef std::list<MessageId> MessageIdList;
            typedef std::map<ConnectionId, MessageIdList> OutgoingMessageQueMap;
            typedef std::multimap<SequenceNo, MessageId> MessageIdsInPackageMap;

            OutgoingMessageMap messages;
            OutgoingMessageQueMap ques;
            MessageIdsInPackageMap messageIdsInPackage;
        };
    }
}

#endif
