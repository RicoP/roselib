///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>


#include <serializer/serializer.h>

namespace rose {
namespace ecs {

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(ObjectID &o, ISerializer &s) {
  if(s.node_begin("ObjectID", rose::hash("ObjectID"), &o)) {
    s.key("id");
    serialize(o.id, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(ObjectID &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("id"):
        deserialize(o.id, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(ObjectID &o, rose::hash_value & h) {
  randomize(o.id, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(const ObjectID &o) {
    hash_value h = hash(o.id);
    return h;
  }
} //namespace rose
