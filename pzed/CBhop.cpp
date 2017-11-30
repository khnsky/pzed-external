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
        DWORD dwLocalBase = CMemory::read<DWORD>(process.getHandle(), process.getModule("client.dll") + signatures::dwLocalPlayer);

        BYTE dwFlags = CMemory::read<BYTE>(process.getHandle(), dwLocalBase + netvars::m_fFlags);

        //DWORD dwMouseEnable = CMemory::read<DWORD>(process.getHandle(), process.getModule("client.dll") + signatures::dwMouseEnable);
        //DWORD dwMouseEnablePtr = CMemory::read<DWORD>(process.getHandle(), process.getModule(L"client.dll") + signatures::dwMouseEnablePtr);

        // not checking if dwMouseEnable or something - hopping while in chat etc.
        // retarded way of checking if not in chat
        // aparently doesn't work, different value each time?
        // need to xor with something
        if (ON_GROUND & dwFlags && /*dwMouseEnable == 498533921 &&*/ GetAsyncKeyState(VK_SPACE))
        {
            // 6 - jump and release jump key in same tick
            CMemory::write<DWORD>(process.getHandle(), process.getModule("client.dll") + signatures::dwForceJump, 6);
        }

        // less than 1000/128 (128 - highest tickrate in cs)
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}