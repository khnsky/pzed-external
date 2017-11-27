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
            // why use one version of read once and another other time,
            // no checks if read succeeded
			DWORD dwLocalBase;
			CMemory::read<DWORD>(csgo.getHandle(), csgo.getClientAddress() + signatures::dwLocalPlayer, dwLocalBase);
            // could throw, why is this set with throwing one and base with returning bool one, why read<byte> but type is dword?
			DWORD dwFlags = CMemory::read<BYTE>(csgo.getHandle(), dwLocalBase + netvars::m_fFlags);

            // not checking if dwMouseEnable or something - hopping while in chat etc.
			if (ON_GROUND & dwFlags && GetAsyncKeyState(VK_SPACE))
				CMemory::write<DWORD>(csgo.getHandle(), csgo.getClientAddress() + signatures::dwForceJump, 6);

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
    // throw? wait and try again? (no reason unless implemented multithreading?
}