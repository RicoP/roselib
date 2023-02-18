#pragma once

#include <raylib.h>
#include <raymath.h>
#include <rose/hash.h>
#include <rose/assert.h>
#include <rose/handle.h>
#include <rose/singleton.h>
#include <rose/raylibutils/assetmanager.h>
#include <components/path.h>
#include <components/components.h>
#include <components/components_ser.h>
#include <utility>

namespace rose {
struct RaylibAsset {
private:
    local_handle handle = 0;

    void inc() { if(handle) RaylibAssetManager::instance().handle_increment(handle); }
    void dec() { if(handle) RaylibAssetManager::instance().handle_decrement(handle); }

protected:
    const Model & get_model() const {
        return RaylibAssetManager::instance().get_handle_model(handle);
    }

public:
    ~RaylibAsset() { dec(); }
    
    RaylibAsset(const char * path, RaylibAssetType type) { 
        handle = RaylibAssetManager::instance().handle_open(path, type);
    }

    RaylibAsset(const RaylibAsset & rhs) : handle(rhs.handle) { inc(); }

    RaylibAsset(RaylibAsset && rhs) : handle(rhs.handle) {
        rhs.handle = 0;
    }

    RaylibAsset & operator=(const RaylibAsset & rhs) {
        if(handle != rhs.handle) {
            dec();
            handle = rhs.handle;        
            inc();
        }

        return *this;
    }

    RaylibAsset & operator=(RaylibAsset && rhs) {
        if(handle != rhs.handle) {
            dec();
            handle = rhs.handle;
            rhs.handle = 0;
        }

        return *this;
    }

    const char * get_path() const {
        return RaylibAssetManager::instance().get_handle_path(handle);
    }

    local_handle get_handle() const { return handle; }
    operator bool() const { return handle != 0; }
    bool operator==(const RaylibAsset & rhs) const { return handle == rhs.handle; }
    bool operator!=(const RaylibAsset & rhs) const { return !(*this == rhs); }
};

struct RaylibAssetModel : RaylibAsset {
    RaylibAssetModel(const char * path) 
    : RaylibAsset(path, RaylibAssetType::Model) {
    }

    operator Model() {
        return get_model();
    }
};

inline void serialize(RaylibAssetModel &o, ISerializer &s) {
    Path path;
    path = o.get_path();
	serialize(path, s);
}
inline void deserialize(RaylibAssetModel &o, IDeserializer &s) {
    Path p;
	deserialize(p, s);
    o = RaylibAssetModel(p.string);
}
}

namespace rose {
inline ::rose::hash_value hash(const RaylibAssetModel &o) {
    Path path;
    path = o.get_path();
	return ::rose::hash(path);
}
}

// Operators

// Vector2
inline Vector2 & operator+=(Vector2 & lhs, Vector2 rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline Vector2 & operator-=(Vector2 & lhs, Vector2 rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline Vector2 & operator*=(Vector2 & lhs, float rhs)   { lhs.x *= rhs;   lhs.y *= rhs;   return lhs; }
inline Vector2 operator+(Vector2 lhs, Vector2 rhs)      { return lhs += rhs; }
inline Vector2 operator-(Vector2 lhs, Vector2 rhs)      { return lhs -= rhs; }
inline Vector2 operator*(Vector2 lhs, float rhs)        { return lhs *= rhs; }

// Vector3
inline Vector3 & operator+=(Vector3 & lhs, Vector3 rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
inline Vector3 & operator-=(Vector3 & lhs, Vector3 rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
inline Vector3 & operator*=(Vector3 & lhs, float rhs)   { lhs.x *= rhs;   lhs.y *= rhs;   lhs.z *= rhs;   return lhs; }
inline Vector3 operator+(Vector3 lhs, Vector3 rhs)      { return lhs += rhs; }
inline Vector3 operator-(Vector3 lhs, Vector3 rhs)      { return lhs -= rhs; }
inline Vector3 operator*(Vector3 lhs, float rhs)        { return lhs *= rhs; }

// Vector4
inline Vector4 & operator+=(Vector4 & lhs, Vector4 rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
inline Vector4 & operator-=(Vector4 & lhs, Vector4 rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
inline Vector4 & operator*=(Vector4 & lhs, float rhs)   { lhs.x *= rhs;   lhs.y *= rhs;   lhs.z *= rhs;   lhs.w *= rhs;   return lhs; }
inline Vector4 operator+(Vector4 lhs, Vector4 rhs)      { return lhs += rhs; }
inline Vector4 operator-(Vector4 lhs, Vector4 rhs)      { return lhs -= rhs; }
inline Vector4 operator*(Vector4 lhs, float rhs)        { return lhs *= rhs; }

// Matrix
inline Matrix operator+(Matrix lhs, Matrix rhs)   { return MatrixAdd(lhs, rhs); }
inline Matrix operator-(Matrix lhs, Matrix rhs)   { return MatrixSubtract(lhs, rhs); }
inline Matrix operator*(Matrix lhs, Matrix rhs)   { return MatrixMultiply(lhs, rhs); }
inline Vector3 operator*(Vector3 lhs, Matrix rhs) { return Vector3Transform(lhs, rhs); }
