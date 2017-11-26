#pragma once

#include "CMemory.h"
#include "CProcess.h"

enum
{
	ON_GROUND = (1 << 0),
	DUCKING = (1 << 1),
	WATER_JUMP = (1 << 2),
	ON_TRAIN = (1 << 3),
	IN_RAIN = (1 << 4),
	FROZEN = (1 << 5),
	AT_CONTROLS = (1 << 6),
	CLIENT = (1 << 7),
	FAKE_CLIENT = (1 << 8),
	IN_WARTER = (1 << 9)
};

void bhop();