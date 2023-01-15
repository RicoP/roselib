#pragma once

enum class RecordingState : int {
  NONE = 0,
  
  Inactive,
  
  RecordingStart,
  Recording,
  RecordingStop,
  
  ReplayingStart,
  Replaying,
  ReplayingSeek,
  ReplayingStop
};

struct RecordingEvent {
  RecordingState state = RecordingState::NONE;
  int seek = -1;
};
