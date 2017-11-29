#include "stdafx.h"

#include "CBhop.h"
#include "Offsets.h"

#include <chrono>
#include <thread>

extern CProcess process;

void bhop()
{
    // need to check if csgo process is still running, what happens if writting to not running process?
    while (!process.isSetUp()) 
    {
        // should never be called if csgo is not set up
        // no reason for this unless implemented multithreading
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    while (true)
    {
        // read could throw, getModule could throw
        DWORD dwLocalBase = CMemory::read<DWORD>(process.getHandle(), process.getModule(L"client.dll") + signatures::dwLocalPlayer);

        BYTE dwFlags = CMemory::read<BYTE>(process.getHandle(), dwLocalBase + netvars::m_fFlags);

        // not checking if dwMouseEnable or something - hopping while in chat etc.
        if (ON_GROUND & dwFlags && GetAsyncKeyState(VK_SPACE))
        {
            CMemory::write<DWORD>(process.getHandle(), process.getModule(L"client.dll") + signatures::dwForceJump, 6);
        }

        // less than 1000/128 (128 - highest tickrate in cs)
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}