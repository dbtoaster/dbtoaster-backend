#ifndef DBTOASTER_EVENT_HPP
#define DBTOASTER_EVENT_HPP

#include <cstdint>
#include "source.hpp"
#include "message.hpp"

namespace dbtoaster {

enum class EventType : uint32_t {
  kNotDefined  = 0,
  kInsertTuple = 1,
  kDeleteTuple = 2,
  kBatchUpdate = 4
};

struct Event {
  Event() : source_id(kInvalidSourceId), event_type(EventType::kNotDefined) { }

  Event(SourceId sid, EventType tp, MessageBasePtr msg)
      : source_id(sid), event_type(tp), message(std::move(msg)) { }

  bool isEmpty() { return message == nullptr; }

  union {
    struct {
      SourceId source_id;
      EventType event_type;
    };
    uint64_t id;
  };
  MessageBasePtr message;

  static constexpr uint64_t getId(SourceId r, EventType t) {
    return (static_cast<uint64_t>(t) << 32) | r;
  }
};

static_assert(sizeof(MessageBasePtr) + 8 == sizeof(Event), "Unexpected event type size");

}

#endif /* DBTOASTER_EVENT_HPP */