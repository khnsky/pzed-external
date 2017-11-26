#include "stdafx.h"

#include "CBhop.h"
#include "Offsets.h"

#include <chrono>
#include <thread>

extern CProcess csgo;

void bhop()
{
	if (csgo.isSetUp())
	{
		for (;;)
		{
			DWORD dwLocalBase;
			CMemory::read<DWORD>(csgo.getHandle(), csgo.getClientAddress() + signatures::dwLocalPlayer, dwLocalBase);
			DWORD dwFlags = CMemory::read<BYTE>(csgo.getHandle(), dwLocalBase + netvars::m_fFlags);
			if (ON_GROUND & dwFlags && GetAsyncKeyState(VK_SPACE))
				CMemory::write<DWORD>(csgo.getHandle(), csgo.getClientAddress() + signatures::dwForceJump, 6);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
}