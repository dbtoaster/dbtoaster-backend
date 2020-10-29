#ifndef DBTOASTER_RELATION_HPP
#define DBTOASTER_RELATION_HPP

#include <limits>

namespace dbtoaster {

typedef uint32_t RelationId;

constexpr RelationId kInvalidRelationId = std::numeric_limits<RelationId>::max();

enum class RelationType { kTable = 0, kStream };

struct Relation {
  constexpr Relation(RelationId t_id, const char* t_name, RelationType t_type)
      : id(t_id), name(t_name), type(t_type) { }

  constexpr bool isTable() const { return type == RelationType::kTable; }

  RelationId id;
  const char* name;
  RelationType type;
};

}

#endif /* DBTOASTER_RELATION_HPP */