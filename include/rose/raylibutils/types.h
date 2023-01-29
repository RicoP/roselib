#pragma once

#include <raylib.h>
#include <rose/serializer.h>

// Import Raylib structs

//@Imposter Color is declared in raylib.h
/*
struct Color {
     char r;
     char g;
     char b;
     char a;
};
*/

//@Imposter vector3 is declared in raylib.h
/*
struct Vector3 {
	float x,y,z;
};
*/

//@Imposter Camera is declared in raylib.h
/*
struct Camera3D {
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fovy;
    int projection;
};
*/

namespace rose {
  namespace ecs {
    inline void serialize(Color &o, ISerializer &s) {
        unsigned long long l = 0;
        l ^= o.a;
        l <<= 8;
        l ^= o.b;
        l <<= 8;
        l ^= o.g;
        l <<= 8;
        l ^= o.r;
        
        ::rose::ecs::serialize(l, s);
    }
    inline void deserialize(Color &o, IDeserializer &s) {
        unsigned long long l = 0;
        ::rose::ecs::deserialize(l, s);

        o.r = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.g = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.b = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.a = (unsigned char)(l & 0xFF);
    }
  }
}

namespace rose {
  namespace ecs {
    inline void serialize(Vector3 &o, ISerializer &s) {
        float v[3] = {o.x, o.y, o.z};
        ::rose::ecs::serialize(v, s);
    }
    inline void deserialize(Vector3 &o, IDeserializer &s) {
        float v[3] = {0,0,0};
        ::rose::ecs::deserialize(v, s);
        o.x = v[0];
        o.y = v[1];
        o.z = v[2];
    }
  }
}

/*
static Vector3 & operator+=(Vector3 & lhs, Vector3 rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

static Vector3 & operator-=(Vector3 & lhs, Vector3 rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

static Vector3 & operator*=(Vector3 & lhs, float rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

static Vector3 operator+(Vector3 lhs, Vector3 rhs) {
    return lhs += rhs;
}

static Vector3 operator-(Vector3 lhs, Vector3 rhs) {
    return lhs -= rhs;
}

static Vector3 operator*(Vector3 lhs, float rhs) {
    return lhs *= rhs;
}
*/
