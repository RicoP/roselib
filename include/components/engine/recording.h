#pragma once

#include <rose/hash.h>
#include <components/padevents.h>
#include <vector>

//@Flag
enum class RoseRecordingState : int {
    NONE = 0,

    Inactive,
    Paused,
    Delete,

    RecordingStart = 0x100,
    Recording,
    RecordingStop,

    RecordingMask = 0xF00,

    ReplayingStart = 0x1000,
    Replaying,
    ReplayingSeek,
    ReplayingStop,

    ReplayingMask = 0xF000,

};
