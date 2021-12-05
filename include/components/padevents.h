#pragma once

//@Flags
enum class PadEventButton : int {
	NONE = 0,
	PadUp       = 1 << 0,
	PadDown     = 1 << 1,
	PadLeft     = 1 << 2,
	PadRight    = 1 << 3,
	OptionRight = 1 << 4,
	OptionLeft  = 1 << 5,
	LeftThumb   = 1 << 6,
	RightThumb  = 1 << 7,
	LeftFront   = 1 << 8,
	RightFront  = 1 << 9,
	South       = 1 << 10,
	East        = 1 << 11,
	West        = 1 << 12,
	North       = 1 << 13,
	LeftBack    = 1 << 14,
	RightBack   = 1 << 15,
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
