#include "stdafx.h"

#include "CBhop.h"
#include "Offsets.h"

#include <chrono>
#include <thread>

extern CProcess process;

void bhop()
{
    while (!process.isSetUp()) 
    {
        // should never be called if csgo is not set up
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    while (true)
    {
        // why use one version of read once and another other time,
        // no checks if read succeeded
        DWORD dwLocalBase = CMemory::read<DWORD>(process.getHandle(), process.getClientAddress() + signatures::dwLocalPlayer);
        // could throw, why is this set with throwing one and base with returning bool one, why read<byte> but type is dword?
        BYTE dwFlags = CMemory::read<BYTE>(process.getHandle(), dwLocalBase + netvars::m_fFlags);

        // not checking if dwMouseEnable or something - hopping while in chat etc.
        if (ON_GROUND & dwFlags && GetAsyncKeyState(VK_SPACE))
        {
            CMemory::write<DWORD>(process.getHandle(), process.getClientAddress() + signatures::dwForceJump, 6);
        }

        // less than 1000/128 (128 - highest tickrate in cs)
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

    // throw? wait and try again? (no reason unless implemented multithreading?
}