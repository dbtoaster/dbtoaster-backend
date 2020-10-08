#ifndef DRIVER_ORDERED_EVENT_HPP
#define DRIVER_ORDERED_EVENT_HPP

#include <limits>
#include "event.hpp"

typedef size_t OrderType;

constexpr OrderType kInvalidOrder = std::numeric_limits<OrderType>::max();

struct OrderedEvent : Event {
  OrderedEvent() : order(kInvalidOrder) { }

  OrderedEvent(OrderType o, SourceId r, EventType t, MessageBasePtr m)
      : Event(r, t, std::move(m)), order(o) { }

  OrderType order;
};

#endif /* DRIVER_ORDERED_EVENT_HPP */