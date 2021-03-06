#pragma once

namespace rose {
  struct Entity {
    enum class Status {
      Dead = 0,
      Alive
    };

    unsigned int generation; //starts at 0xFFFF and counts down
    unsigned int index;      //starts at 0 and counts up
  };

  constexpr Entity NULL_ENTITY = {0, 0};
}

namespace ros {
  inline ros::hash_value hash(const rose::Entity & e) {
    return e.generation ^ e.index;
  }
}

inline bool operator==(const rose::Entity &lhs, const rose::Entity &rhs) {
  return
    lhs.generation == rhs.generation &&
    lhs.index == rhs.index;
}

inline void serialize(rose::Entity &o, ISerializer &s) {
  if (s.node_begin("Entity", ros::hash("Entity"), &o)) {
    s.node_end();
  }
  s.end();
}

inline void deserialize(rose::Entity &o, IDeserializer &s) {
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      default: s.skip_key(); break;
    }
  }
}

inline void randomize(rose::Entity &e, ros::hash_value &h) {
}
