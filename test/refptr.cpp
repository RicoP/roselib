#include <ros/refptr.h>

#include <iostream>

struct vector3_t {
  union {
    struct {
      float x, y, z;
    };
    float components[3];
  };
};

struct vector3 : vector3_t {
  vector3() : vector3_t({0, 0, 0}) { std::cout << "empty \n"; }
  vector3(float x_, float y_, float z_) : vector3_t({x_, y_, z_}) { std::cout << "params \n"; }
  /*implicit*/ vector3(const vector3_t& v) : vector3_t(v) { std::cout << "from base \n"; }
  /*implicit*/ vector3(const vector3& v) : vector3_t({v.x, v.y, v.z}) { std::cout << "copy \n"; }
  /*implicit*/ vector3(vector3&& v) noexcept : vector3(v.x, v.y, v.z) { std::cout << "move \n"; }
  ~vector3() { std::cout << "destructor \n"; }

  const vector3& operator+=(const vector3& rhs);

  vector3 operator+(const vector3& rhs) {
    vector3 copy(*this);
    copy += rhs;
    return copy;
  }
};

const vector3& vector3::operator+=(const vector3& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

void printvec(const vector3& v) { std::cout << v.x << " " << v.y << " " << v.z << "\n"; }

void printptr(ros::refptr<vector3> ptr) { printvec(*ptr); }

ros::refptr<vector3> create_vector3(float x, float y, float z) {
  ros::refptr<vector3> p(x, y, z);
  return p;
}

/////////////////////

struct noncopy {
  noncopy() {}
  noncopy(const noncopy&) = delete;
  noncopy& operator=(const noncopy&) = delete;
};

struct ISystem : noncopy {
  ISystem() {}
  virtual ~ISystem() {}
  virtual const char* name() const = 0;
};

struct GameMessangerSystem;
struct DebugSystem;
struct PhysicsSystem;
struct UISystem;

struct DebugSystem : ISystem {
  ros::refptr<GameMessangerSystem> gameMessangerSystem;

  virtual const char* name() const override { return "DebugSystem"; }

  virtual ~DebugSystem() override { std::cout << name() << " destruct \n"; }

  DebugSystem(ros::refptr<GameMessangerSystem> gameMessangerSystem_) : gameMessangerSystem(gameMessangerSystem_) {
    std::cout << name() << " construct \n";
  }
};

struct GameMessangerSystem : ISystem {
  // ros::refptr<DebugSystem> debugSystem;

  virtual const char* name() const override { return "GameMessangerSystem"; }

  virtual ~GameMessangerSystem() override { std::cout << name() << " destruct \n"; }

  // GameMessangerSystem(ros::refptr<DebugSystem> debugSystem_) : debugSystem(debugSystem_) {}
  GameMessangerSystem() { std::cout << name() << " construct \n"; }
};

struct PhysicsSystem : ISystem {
  ros::refptr<GameMessangerSystem> gameMessangerSystem;
  ros::refptr<DebugSystem> debugSystem;

  virtual const char* name() const override { return "PhysicsSystem"; }

  virtual ~PhysicsSystem() override { std::cout << name() << " destruct \n"; }

  PhysicsSystem(ros::refptr<GameMessangerSystem> gameMessangerSystem_, ros::refptr<DebugSystem> debugSystem_)
      : gameMessangerSystem(gameMessangerSystem_), debugSystem(debugSystem_) {
    std::cout << name() << " construct \n";
  }
};

struct UISystem : ISystem {
  ros::refptr<GameMessangerSystem> gameMessangerSystem;
  ros::refptr<DebugSystem> debugSystem;
  ros::refptr<PhysicsSystem> physicsSystem;

  virtual const char* name() const override { return "UISystem"; }

  virtual ~UISystem() override { std::cout << name() << " destruct \n"; }

  UISystem(ros::refptr<GameMessangerSystem> gameMessangerSystem_, ros::refptr<DebugSystem> debugSystem_,
           ros::refptr<PhysicsSystem> physicsSystem_)
      : gameMessangerSystem(gameMessangerSystem_), debugSystem(debugSystem_), physicsSystem(physicsSystem_) {
    std::cout << name() << " construct \n";
  }
};

ros::refptr<UISystem> CreateUISystem() {
  ros::refptr<GameMessangerSystem> gameMessangerSystem;
  ros::refptr<DebugSystem> debugSystem(gameMessangerSystem);
  ros::refptr<PhysicsSystem> physicsSystem(gameMessangerSystem, debugSystem);
  ros::refptr<UISystem> uiSystem(gameMessangerSystem, debugSystem, physicsSystem);

  return uiSystem;
} 


int main() {
  {
    ros::refptr<vector3> ptr = create_vector3(1, 2, 3);

    printptr(ptr);

    ros::refptr<vector3> ptr2 = ptr;
    ros::refptr<vector3> ptr3 = ptr2;
    {
      ros::refptr<vector3> ptr4 = ptr3;
      printptr(*ptr2 + *ptr3);
    }
    printptr(ptr3);

    printptr(ptr2);
  }

  // game context
  ros::refptr<UISystem> uiSystem = CreateUISystem();
  ros::refptr<UISystem> uiSystem2(uiSystem->gameMessangerSystem, uiSystem->debugSystem, uiSystem->physicsSystem);

  return 0;
}
