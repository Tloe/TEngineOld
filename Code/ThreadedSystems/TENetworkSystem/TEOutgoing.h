#ifndef TEOUTGOING_H
#define TEOUTGOING_H

#include "TEDataTypes.h"
#include "TEPacket.h"

#include <list>
#include <map>
#include <unordered_map>

namespace TE::Network {
  typedef U32 MessageId;
  typedef I32 ConnectionId;
  typedef U32 SequenceNo;

  struct Outgoing {
    struct Message {
      Net::Packet packet;
      U32 missingAcks;
      U32 queCount;
    };

    using OutgoingMessageMap     = std::unordered_map<MessageId, Message>;
    using MessageIdList          = std::list<MessageId>;
    using OutgoingMessageQueMap  = std::map<ConnectionId, MessageIdList>;
    using MessageIdsInPackageMap = std::multimap<SequenceNo, MessageId>;

    OutgoingMessageMap messages;
    OutgoingMessageQueMap ques;
    MessageIdsInPackageMap messageIdsInPackage;
  };
}

#endif
