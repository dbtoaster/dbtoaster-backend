#ifndef DBTOASTER_EVENT_HPP
#define DBTOASTER_EVENT_HPP

#include <cstdint>
#include "relation.hpp"
#include "message.hpp"

namespace dbtoaster {

enum class EventType : uint32_t {
  kNotDefined = 0,
  kInsertTuple,
  kDeleteTuple,
  kBatchUpdate
};

struct Event {
  Event() : relation_id(kInvalidRelationId), event_type(EventType::kNotDefined) { }

  Event(RelationId rid, EventType tp, MessageBasePtr msg)
      : relation_id(rid), event_type(tp), message(std::move(msg)) { }

  bool isEmpty() { return message == nullptr; }

  union {
    struct {
      RelationId relation_id;
      EventType event_type;
    };
    uint64_t id;
  };
  MessageBasePtr message;

  static constexpr uint64_t getId(RelationId r, EventType t) {
    return (static_cast<uint64_t>(t) << 32) | r;
  }
};

static_assert(sizeof(MessageBasePtr) + 8 == sizeof(Event), "Unexpected event type size");

}

#endif /* DBTOASTER_EVENT_HPP */