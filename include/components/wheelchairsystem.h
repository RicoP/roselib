///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>

#include <game/components/objectid.h>
struct WheelchairSystem {
  ObjectID object;

  bool equals(const WheelchairSystem & rhs) const {
    return
      object == rhs.object;
  }
};

inline void construct_defaults(WheelchairSystem & o) {
  std::memset(&o, 0, sizeof(WheelchairSystem));
  construct_defaults(o.object);
}

inline bool operator==(const WheelchairSystem &lhs, const WheelchairSystem &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const WheelchairSystem &lhs, const WheelchairSystem &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(WheelchairSystem &o, ISerializer &s) {
  if(s.node_begin("WheelchairSystem", ros::hash("WheelchairSystem"), &o)) {
    s.key("object");
    serialize(o.object, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(WheelchairSystem &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case ros::hash("object"):
        deserialize(o.object, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
namespace ros {
  inline ros::hash_value hash(WheelchairSystem &o) {
    ros::hash_value h = ros::hash(o.object);
    return h;
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(WheelchairSystem &o, ros::hash_value & h) {
  randomize(o.object, h);
}