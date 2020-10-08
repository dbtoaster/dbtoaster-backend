#ifndef DBTOASTER_MESSAGE_HPP
#define DBTOASTER_MESSAGE_HPP

#include <memory>

namespace dbtoaster {

struct MessageBase {
  virtual ~MessageBase() = default;
};

typedef std::unique_ptr<MessageBase> MessageBasePtr;

};

#endif /* DBTOASTER_MESSAGE_HPP */