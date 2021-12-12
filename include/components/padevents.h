#pragma once

//Check https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
//for bit masks
  
//@Flags
enum class PadEventButton : int {
	NONE = 0,
  //DPad
	PadUp       = 1 << 0,
	PadDown     = 1 << 1,
	PadLeft     = 1 << 2,
	PadRight    = 1 << 3,

  //Start/Back or +/-
	OptionRight = 1 << 4,
	OptionLeft  = 1 << 5,

  //Stick Press
	LeftThumb   = 1 << 6,
	RightThumb  = 1 << 7,

  //LB/RB or L/R
	LeftFront   = 1 << 8,
	RightFront  = 1 << 9,

  //ABXY or BAYX
	South       = 1 << 13,
	East        = 1 << 14,
	West        = 1 << 15,
	North       = 1 << 16,

  //LT/RT or ZL/ZR
	LeftBack    = 1 << 20,
	RightBack   = 1 << 21,
};

struct PadEvent {
	float stick_lx;
	float stick_ly;
	float stick_rx;
	float stick_ry;
	
	float trigger_l;
	float trigger_r;
	PadEventButton buttons;
	int player;
};
