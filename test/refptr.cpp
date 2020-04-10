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

static int g_systems_active = 0;

struct ISystem : noncopy {
  ISystem() { g_systems_active++; }
  virtual ~ISystem() { g_systems_active--; }
  virtual const char* name() const = 0;
};

struct GameMessangerSystem;
struct DebugSystem;
struct PhysicsSystem;
struct UISystem;

struct DebugSystem : ISystem {
  virtual const char* name() const override { return "DebugSystem"; }
  virtual ~DebugSystem() override { std::cout << name() << " destruct \n"; }
  DebugSystem() { std::cout << name() << " construct \n"; }
};

struct GameMessangerSystem : ISystem {
  ros::refptr<DebugSystem> debugSystem;

  virtual const char* name() const override { return "GameMessangerSystem"; }
  virtual ~GameMessangerSystem() override { std::cout << name() << " destruct \n"; }
  GameMessangerSystem(ros::refptr<DebugSystem> debugSystem_) : debugSystem(debugSystem_) {
    std::cout << name() << " construct \n";
  }
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

ros::refptr<UISystem> CreateUISystem(ros::refptr<DebugSystem> debugSystem = ros::refptr<DebugSystem>::make()) {
  ros::refptr<GameMessangerSystem> gameMessangerSystem = ros::refptr<GameMessangerSystem>::make(debugSystem);
  ros::refptr<PhysicsSystem> physicsSystem = ros::refptr<PhysicsSystem>::make(gameMessangerSystem, debugSystem);
  ros::refptr<UISystem> uiSystem = ros::refptr<UISystem>::make(gameMessangerSystem, debugSystem, physicsSystem);

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

  std::cout << "Active Systems " << g_systems_active << "\n";

  // game context

  ros::refptr<DebugSystem> shared_debug_system;

  {
    ros::refptr<UISystem> uiSystem = CreateUISystem();

    std::cout << "\nActive Systems " << g_systems_active << "\n";

    std::cout << "UISystem uses " << uiSystem.use_count() << "\n"
              << "physicsSystem uses " << uiSystem->physicsSystem.use_count() << "\n"
              << "debugSystem uses " << uiSystem->debugSystem.use_count() << "\n"
              << "gameMessangerSystem uses " << uiSystem->gameMessangerSystem.use_count() << "\n"
              << "\n";

    // steal old debug system and reuse it later
    shared_debug_system = uiSystem->debugSystem;
  }

  std::cout << "\nActive Systems " << g_systems_active << "\n";

  {
    ros::refptr<UISystem> uiSystem = CreateUISystem();
    ros::refptr<UISystem> uiSystem2 = uiSystem;
    uiSystem.release();

    // replace new debug messanger with old one.
    uiSystem2->physicsSystem->debugSystem = shared_debug_system;
    uiSystem2->gameMessangerSystem->debugSystem = shared_debug_system;
    uiSystem2->debugSystem = shared_debug_system;

    std::cout << "\nActive Systems " << g_systems_active << "\n";

    std::cout << "UISystem uses " << uiSystem2.use_count() << "\n"
              << "physicsSystem uses " << uiSystem2->physicsSystem.use_count() << "\n"
              << "debugSystem uses " << uiSystem2->debugSystem.use_count() << "\n"
              << "gameMessangerSystem uses " << uiSystem2->gameMessangerSystem.use_count() << "\n"
              << "\n";
  }

  std::cout << "\nActive Systems " << g_systems_active << "\n";

  {
    ros::refptr<UISystem> uiSystem = CreateUISystem(shared_debug_system);

    std::cout << "\nActive Systems " << g_systems_active << "\n";

    std::cout << "UISystem uses " << uiSystem.use_count() << "\n"
              << "physicsSystem uses " << uiSystem->physicsSystem.use_count() << "\n"
              << "debugSystem uses " << uiSystem->debugSystem.use_count() << "\n"
              << "gameMessangerSystem uses " << uiSystem->gameMessangerSystem.use_count() << "\n"
              << "\n";
  }

  std::cout << "\nActive Systems " << g_systems_active << "\n";
  shared_debug_system.release();
  std::cout << "\nActive Systems " << g_systems_active << "\n";

  assert(g_systems_active != 0);

  return 0;
}
