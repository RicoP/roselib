#pragma once

#include <raylib.h>
#include <rose/singleton.h>

struct RaylibAssetManager : RoseSingleton<RaylibAssetManager> {
    virtual Model model_increment(const char * path) = 0;
    virtual void  model_decrement(const char * path) = 0;
};
