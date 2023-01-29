#pragma once

#include <raylib.h>
#include <rose/hash.h>
#include <rose/singleton.h>
#include <rose/raylibutils/assetmanager.h>
#include <components/path.h>
#include <components/components.h>
#include <components/components_ser.h>
#include <utility>

struct RaylibAssetModel {
    path path;
    Model model;
    bool valid = false;

    ~RaylibAssetModel() {
        if(valid) RaylibAssetManager::instance().model_decrement(path.string);
        path.string[0] = 0;
        valid = false;
    }

    RaylibAssetModel(const char * path) {
        strcpy(this->path.string, path);
        model = RaylibAssetManager::instance().model_increment(path);
        valid = true;
    }

    RaylibAssetModel(const RaylibAssetModel & rhs) {
        path = rhs.path;
        valid = rhs.valid;
        if(valid)
            model = RaylibAssetManager::instance().model_increment(path.string);
    }

    RaylibAssetModel & operator=(const RaylibAssetModel & rhs) {
        if(valid) RaylibAssetManager::instance().model_decrement(path.string);
        path = rhs.path;
        valid = rhs.valid;
        model = RaylibAssetManager::instance().model_increment(path.string);
        return *this;
    }

    RaylibAssetModel(RaylibAssetModel && rhs) {
        path = rhs.path;
        valid = rhs.valid;
        model = rhs.model;

        rhs.valid = false;
    }

    RaylibAssetModel & operator=(RaylibAssetModel && rhs) {
        std::swap(valid, rhs.valid);
        std::swap(path, rhs.path);
        Model tmp = model;
        model = rhs.model;
        rhs.model = tmp;

        return *this;
    }

    operator Model() {
        assert(valid);
        return model;
    }

    bool operator==(const RaylibAssetModel & rhs) const { return path == rhs.path; }
    bool operator!=(const RaylibAssetModel & rhs) const { return !(*this == rhs); }
};

namespace rose::ecs {
inline void serialize(RaylibAssetModel &o, ISerializer &s) {
	rose::ecs::serialize(o.path, s);
}
inline void deserialize(RaylibAssetModel &o, IDeserializer &s) {
    path p;
	rose::ecs::deserialize(p, s);
    o = RaylibAssetModel(p.string);
}
}


namespace rose {
inline ::rose::hash_value hash(const RaylibAssetModel &o) {
	return ::rose::hash(o.path);
}
}
