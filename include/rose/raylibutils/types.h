#pragma once

#include <raylib.h>
#include <raymath.h>
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

//@Imposter Vector2 is declared in raylib.h
/*
struct Vector2 {
	float x,y;
};
*/

//@Imposter Vector3 is declared in raylib.h
/*
struct Vector3 {
	float x,y,z;
};
*/

//@Imposter Vector4 is declared in raylib.h
/*
struct Vector4 {
	float x,y,z,w;
};
*/

//@Imposter Matrix is declared in raylib.h
/*
struct Matrix {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
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
    inline void serialize(Color &o, ISerializer &s) {
        unsigned long long l = 0;
        l ^= o.a;
        l <<= 8;
        l ^= o.b;
        l <<= 8;
        l ^= o.g;
        l <<= 8;
        l ^= o.r;
        
        serialize(l, s);
    }
    inline void deserialize(Color &o, IDeserializer &s) {
        unsigned long long l = 0;
        deserialize(l, s);

        o.r = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.g = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.b = (unsigned char)(l & 0xFF);
        l >>= 8;
        o.a = (unsigned char)(l & 0xFF);
    }
}

namespace rose {
    inline void serialize(Vector2 &o, ISerializer &s) {
        float v[2] = {o.x, o.y};
        serialize(v, s);
    }
    inline void deserialize(Vector2 &o, IDeserializer &s) {
        float v[2] = {0,0};
        deserialize(v, s);
        o.x = v[0];
        o.y = v[1];
    }
}

namespace rose {
    inline void serialize(Vector3 &o, ISerializer &s) {
        float v[3] = {o.x, o.y, o.z};
        serialize(v, s);
    }
    inline void deserialize(Vector3 &o, IDeserializer &s) {
        float v[3] = {0,0,0};
        deserialize(v, s);
        o.x = v[0];
        o.y = v[1];
        o.z = v[2];
    }
}

namespace rose {
    inline void serialize(Vector4 &o, ISerializer &s) {
        float v[4] = {o.x, o.y, o.z, o.w};
        serialize(v, s);
    }
    inline void deserialize(Vector4 &o, IDeserializer &s) {
        float v[4] = {0,0,0,0};
        deserialize(v, s);
        o.x = v[0];
        o.y = v[1];
        o.z = v[2];
        o.w = v[3];
    }
}

namespace rose {
    inline void serialize(Matrix &o, ISerializer &s) {
        auto equals = [](Vector4 lhs, Vector4 rhs) {
            return lhs.x == rhs.x &&
                   lhs.y == rhs.y &&
                   lhs.z == rhs.z &&
                   lhs.w == rhs.w;
        };
        Vector4 rows[4] = {
            Vector4 { o.m0, o.m4, o.m8, o.m12} ,
            Vector4 { o.m1, o.m5, o.m9, o.m13} ,
            Vector4 { o.m2, o.m6, o.m10, o.m14} ,
            Vector4 { o.m3, o.m7, o.m11, o.m15} ,
        };

        // Only serialize rows that differ from the identity.
        // row[3] should always be {0,0,0,1} for affine matrices.
        std::size_t max = 4;

        if(equals(rows[3], {0,0,0,1})) {
            max--;
            if(equals(rows[2], {0,0,1,0})) {
                max--;
                if(equals(rows[1], {0,1,0,0})) {
                    max--;
                    if(equals(rows[0], {1,0,0,0})) {
                        max--;
                    }
                }
            }
        }

        serialize(rows, s, max);
    }
    inline void deserialize(Matrix &o, IDeserializer &s) {
        float rows[4][4] = {
            {1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,1}
        };
        deserialize(rows, s);

        o.m0 = rows[0][0]; o.m4 = rows[0][1]; o.m8  = rows[0][2]; o.m12 = rows[0][3];
        o.m1 = rows[1][0]; o.m5 = rows[1][1]; o.m9  = rows[1][2]; o.m13 = rows[1][3];
        o.m2 = rows[2][0]; o.m6 = rows[2][1]; o.m10 = rows[2][2]; o.m14 = rows[2][3];
        o.m3 = rows[3][0]; o.m7 = rows[3][1]; o.m11 = rows[3][2]; o.m15 = rows[3][3];
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
