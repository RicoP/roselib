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

    RecordingMask = 0x100,
    RecordingStart,
    Recording,
    RecordingStop,


    ReplayingMask = 0x200,
    ReplayingStart,
    Replaying,
    ReplayingSeek,
    ReplayingStop,


};
