#pragma once

#include <rose/hash.h>
#include <components/padevents.h>
#include <vector>

//@Flag
enum class RoseRecordingState : int {
    NONE = 0,

    RecordingStart = 0x1,
    Recording,
    RecordingStop,

    RecordingMask = 0xF,

    ReplayingStart = 0x10,
    Replaying,
    ReplayingSeek,
    ReplayingStop,

    ReplayingMask = 0xF0,

    Inactive = 0x100,
};

struct RoseRecordingRequest {
  RoseRecordingState state = RoseRecordingState::NONE;
  int seek = -1;
};
