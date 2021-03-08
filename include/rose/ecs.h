#pragma once

#include <ros/nocopy.h>

#include <vector>

namespace rose {
namespace ecs {
  struct Entity {
    enum class Status { Dead = 0, Alive };

    unsigned int generation;  // starts at 0xFFFF and counts down
    unsigned int index;       // starts at 0 and counts up
  };

  inline bool operator==(const rose::ecs::Entity &lhs, const rose::ecs::Entity &rhs) {
    return lhs.generation == rhs.generation && lhs.index == rhs.index;
  }

  constexpr Entity NULL_ENTITY = {0, 0};

  struct World : ros::nocopy {
    // entity
    std::vector<rose::ecs::Entity> entities;
    // std::vector<rose::ecs::Entity> entitiyParent; //Does this make sense?
    std::vector<unsigned int> generation;           // = fill({~0});
    std::vector<rose::ecs::Entity::Status> status;  // = fill({Stats::Dead}); fill doesnt work like that

    // utility
    [[nodiscard]] bool is_valid(const rose::ecs::Entity &entity) const {
      return generation[entity.index] == entity.generation && status[entity.index] == rose::ecs::Entity::Status::Alive;
    }

    template <class T>
    T &attach_component_to_vector(std::vector<int> &component_index, std::vector<T> &components, rose::ecs::Entity entity) {
      assert(is_valid(entity));

      if (entity.index >= component_index.size()) component_index.resize(entity.index + 1, -1);
      T *objectp = nullptr;
      if (component_index[entity.index] != -1) {
        // we already have something here.
        auto &obj = components[component_index[entity.index]];
        if (obj.entity == entity) return obj;  // nothing to do
        objectp = &obj;
      } else {
        component_index[entity.index] = components.size();
        auto &obj = components.emplace_back();
        objectp = &obj;
      }
      assert(objectp);
      T &object = *objectp;
      construct_defaults(object);
      return object;
    }


    //Camera &get_component(const std::vector<int> &is, const std::vector<Camera> &vector, const rose::ecs::Entity &entity);

    template <typename T>
    const T &get_component(const std::vector<int> &component_index,
                           const std::vector<T> &components,
                           const rose::ecs::Entity &entity) const {
      assert(entity.index >= 0);
      assert(component_index.size() < entity.index);
      assert(components.size() < component_index[entity.index]);
      assert(components[component_index[entity.index]].entity == entity);
      return components[component_index[entity.index]];
    }

    template <typename T>
    T &get_component(std::vector<int> &component_index,
                     std::vector<T> &components,
                     const rose::ecs::Entity &entity) {
      assert(entity.index >= 0);
      assert(component_index.size() < entity.index);
      assert(components.size() < component_index[entity.index]);
      assert(components[component_index[entity.index]].entity == entity);
      return components[component_index[entity.index]];
    }
  };
}  // namespace ecs
}  // namespace rose

namespace ros {
inline ros::hash_value hash(const rose::ecs::Entity &e) { return e.generation ^ e.index; }
}  // namespace ros

inline void serialize(rose::ecs::Entity &o, ISerializer &s) {
  if (s.node_begin("Entity", ros::hash("Entity"), &o)) {
    s.node_end();
  }
  s.end();
}

inline void deserialize(rose::ecs::Entity &o, IDeserializer &s) {
  // construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      default: s.skip_key(); break;
    }
  }
}

inline void randomize(rose::ecs::Entity &e, ros::hash_value &h) {}
