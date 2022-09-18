#include <rose/refptr.h>

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

void printptr(rose::refptr<vector3> ptr) { printvec(*ptr); }

rose::refptr<vector3> create_vector3(float x, float y, float z) {
  rose::refptr<vector3> p(x, y, z);
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
  rose::refptr<DebugSystem> debugSystem;

  virtual const char* name() const override { return "GameMessangerSystem"; }
  virtual ~GameMessangerSystem() override { std::cout << name() << " destruct \n"; }
  GameMessangerSystem(rose::refptr<DebugSystem> debugSystem_) : debugSystem(debugSystem_) { std::cout << name() << " construct \n"; }
};

struct PhysicsSystem : ISystem {
  rose::refptr<GameMessangerSystem> gameMessangerSystem;
  rose::refptr<DebugSystem> debugSystem;
  rose::refptr<UISystem>::refview uiSystem;

  virtual const char* name() const override { return "PhysicsSystem"; }

  virtual ~PhysicsSystem() override { std::cout << name() << " destruct \n"; }

  PhysicsSystem(rose::refptr<GameMessangerSystem> gameMessangerSystem_, rose::refptr<DebugSystem> debugSystem_)
      : gameMessangerSystem(gameMessangerSystem_), debugSystem(debugSystem_), uiSystem() {
    std::cout << name() << " construct \n";
  }
};

struct UISystem : ISystem {
  rose::refptr<GameMessangerSystem> gameMessangerSystem;
  rose::refptr<DebugSystem> debugSystem;
  rose::refptr<PhysicsSystem> physicsSystem;

  virtual const char* name() const override { return "UISystem"; }

  virtual ~UISystem() override { std::cout << name() << " destruct \n"; }

  UISystem(rose::refptr<GameMessangerSystem> gameMessangerSystem_,
           rose::refptr<DebugSystem> debugSystem_,
           rose::refptr<PhysicsSystem> physicsSystem_)
      : gameMessangerSystem(gameMessangerSystem_), debugSystem(debugSystem_), physicsSystem(physicsSystem_) {
    std::cout << name() << " construct \n";
  }
};

rose::refptr<UISystem> CreateUISystem(rose::refptr<DebugSystem> debugSystem = rose::refptr<DebugSystem>::make()) {
  rose::refptr<GameMessangerSystem> gameMessangerSystem = rose::refptr<GameMessangerSystem>::make(debugSystem);
  rose::refptr<PhysicsSystem> physicsSystem = rose::refptr<PhysicsSystem>::make(gameMessangerSystem, debugSystem);
  rose::refptr<UISystem> uiSystem = rose::refptr<UISystem>::make(gameMessangerSystem, debugSystem, physicsSystem);
  physicsSystem->uiSystem = uiSystem;

  return uiSystem;
}

int main() {
  {
    rose::refptr<vector3> ptr = create_vector3(1, 2, 3);

    printptr(ptr);

    rose::refptr<vector3> ptr2 = ptr;
    rose::refptr<vector3> ptr3 = ptr2;
    {
      rose::refptr<vector3> ptr4 = ptr3;
      printptr(*ptr2 + *ptr3);
    }
    printptr(ptr3);

    printptr(ptr2);
  }

  std::cout << "Active Systems " << g_systems_active << "\n";

  // game context

  rose::refptr<DebugSystem> shared_debug_system;
  assert(!shared_debug_system);

  {
    rose::refptr<UISystem> uiSystem = CreateUISystem();
    assert(uiSystem);

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
    rose::refptr<UISystem> uiSystem;
    uiSystem = CreateUISystem();
    {
      rose::refptr<UISystem> uiSystem2 = std::move(uiSystem);
      uiSystem = CreateUISystem();
      uiSystem = std::move(uiSystem2);
    }
    // uiSystem.release();

    // replace new debug messanger with old one.
    uiSystem->physicsSystem->debugSystem = shared_debug_system;
    uiSystem->gameMessangerSystem->debugSystem = shared_debug_system;
    uiSystem->debugSystem = shared_debug_system;

    std::cout << "\nActive Systems " << g_systems_active << "\n";

    std::cout << "UISystem uses " << uiSystem.use_count() << "\n"
              << "physicsSystem uses " << uiSystem->physicsSystem.use_count() << "\n"
              << "debugSystem uses " << uiSystem->debugSystem.use_count() << "\n"
              << "gameMessangerSystem uses " << uiSystem->gameMessangerSystem.use_count() << "\n"
              << "\n";
  }

  std::cout << "\nActive Systems " << g_systems_active << "\n";

  {
    rose::refptr<UISystem> uiSystem = CreateUISystem(shared_debug_system);

    std::cout << "\nActive Systems " << g_systems_active << "\n";

    uiSystem->physicsSystem->uiSystem->name();

    std::cout << "UISystem uses " << uiSystem.use_count() << "\n"
              << "physicsSystem uses " << uiSystem->physicsSystem.use_count() << "\n"
              << "debugSystem uses " << uiSystem->debugSystem.use_count() << "\n"
              << "gameMessangerSystem uses " << uiSystem->gameMessangerSystem.use_count() << "\n"
              << "\n";
  }

  std::cout << "\nActive Systems " << g_systems_active << "\n";
  shared_debug_system.release();
  std::cout << "\nActive Systems " << g_systems_active << "\n";

  assert(g_systems_active == 0);

  // this will correctly destroy DebugSystem but will leave a dangeling weak ptr
  // rose::refptr<DebugSystem>::refview debugSystem_null_view = rose::refptr<DebugSystem>::make();
  // assert(debugSystem_null_view.use_count() == 0);

  return 0;
}
