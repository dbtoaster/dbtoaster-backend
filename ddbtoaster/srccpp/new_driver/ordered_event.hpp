#ifndef DRIVER_ORDERED_EVENT_HPP
#define DRIVER_ORDERED_EVENT_HPP

#include <limits>
#include "event.hpp"

using namespace dbtoaster;

typedef size_t OrderType;

constexpr OrderType kInvalidOrder = std::numeric_limits<OrderType>::max();

struct OrderedEvent : Event {
  OrderedEvent() : Event(), order(kInvalidOrder) { }

  OrderedEvent(OrderType o, RelationId id, EventType tp, MessageBasePtr msg)
      : Event(id, tp, std::move(msg)), order(o) { }

  bool operator<(const OrderedEvent& other) const {
    return this->order > other.order;   // higher order, lower priority
  }

  OrderType order;
};

#endif /* DRIVER_ORDERED_EVENT_HPP */