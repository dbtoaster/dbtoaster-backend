#ifndef DBTOASTER_MESSAGE_HPP
#define DBTOASTER_MESSAGE_HPP

#include <memory>
#include <vector>

namespace dbtoaster {

struct MessageBase {
  virtual ~MessageBase() = default;
};

typedef std::unique_ptr<MessageBase> MessageBasePtr;

template <class Key, class Value>
struct BatchMessage : MessageBase {
  typedef struct {
      Key key;
      Value value;
  } KVpair;
  std::vector<KVpair> batch;
};

};

#endif /* DBTOASTER_MESSAGE_HPP */