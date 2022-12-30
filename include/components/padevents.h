#pragma once

// Check https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
// for bit masks

//@Flag
enum class PadEventButton : int {
  NONE = 0,
  // DPad
  PadUp = 1 << 0,
  PadDown = 1 << 1,
  PadLeft = 1 << 2,
  PadRight = 1 << 3,

  // Start/Back or +/-
  OptionRight = 1 << 4,
  OptionLeft = 1 << 5,

  // Stick Press
  LeftThumb = 1 << 6,
  RightThumb = 1 << 7,

  // LB/RB or L/R
  LeftFront = 1 << 8,
  RightFront = 1 << 9,

  // ABXY or BAYX
  South = 1 << 12,
  East = 1 << 13,
  West = 1 << 14,
  North = 1 << 15,

  // LT/RT or ZL/ZR
  LeftBack = 1 << 20,
  RightBack = 1 << 21,
};

struct PadEvent {
  int player = 0;

  float stick_lx = 0;
  float stick_ly = 0;
  float stick_rx = 0;
  float stick_ry = 0;

  float trigger_l = 0;
  float trigger_r = 0;

  PadEventButton buttons = PadEventButton::NONE;
};

//TODO: change to that:
/*
struct PadAnalogChangeEvent {
  float stick_lx;
  float stick_ly;
  float stick_rx;
  float stick_ry;

  float trigger_l;
  float trigger_r;
  int player;
};

struct PadButtonChangeEvent {
  PadEventButton changed;
  PadEventButton buttons;
  int player;

  bool wasPressed(PadEventButton button) {
    if(!(changed & buttons)) return false;
    return !!(buttons & button);
  }

  bool wasReleased(PadEventButton button) {
    if(!(changed & buttons)) return false;
    return !(buttons & button);
  }
};

*/
