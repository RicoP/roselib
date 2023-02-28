#pragma once

#include <raylib.h>
#include <rose/handle.h>
#include <rose/singleton.h>

enum class RaylibAssetType {
    NONE = 0,

    // A image is a 2D pixelgid that lives in RAM
    Image,

    // A Texture is based on a image and lives in VRAM. It has certain Texture specific properties like MipMap level.
    Texture,

    // A Model contains meshes, animations, materials and textures
    Model,

    Video
};

struct RaylibAssetManager : RoseSingleton<RaylibAssetManager> {
    virtual rose::local_handle handle_open(const char * path, enum class RaylibAssetType &) = 0;
    virtual void handle_increment(rose::local_handle) = 0;
    virtual void handle_decrement(rose::local_handle) = 0;

    virtual bool is_valid(rose::local_handle) = 0;
    virtual bool is_ready(rose::local_handle) = 0;
    virtual Model & get_handle_model(rose::local_handle) = 0;
    virtual const char * get_handle_path(rose::local_handle) = 0;
};
