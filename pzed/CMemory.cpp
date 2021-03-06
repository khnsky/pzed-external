#include "stdafx.h"

#include "CMemory.h"

#include <tlhelp32.h>

DWORD CMemory::getPId(const std::wstring& processName)
{
    DWORD pid;
    if (getPId(processName, pid)) { return pid; }
    throw std::invalid_argument("no process with such name running.");
}

bool CMemory::getPId(const std::wstring& processName, DWORD& pid)
{
    HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry32;
    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnapshot, &processEntry32))
    {
        do
        {
            if (std::wstring(processEntry32.szExeFile) == processName)
            {
                properlyCloseHandle(hProcessSnapshot);
                pid = processEntry32.th32ProcessID;
                return true;
            }
        } while (Process32Next(hProcessSnapshot, &processEntry32));
    }
    properlyCloseHandle(hProcessSnapshot);
    return false;
}

DWORD CMemory::getModule(const std::wstring& moduleName, DWORD pid)
{
    DWORD dwAddress;
    if (getModule(moduleName, pid, dwAddress)) { return dwAddress; }
    throw std::invalid_argument("no module with such name.");
}

bool CMemory::getModule(const std::wstring& moduleName, DWORD pid, DWORD& dwAddress)
{
    HANDLE h_moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 moduleEntry32;
    moduleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(h_moduleSnapshot, &moduleEntry32))
    {
        do
        {
            if (moduleEntry32.szModule == moduleName)
            {
                properlyCloseHandle(h_moduleSnapshot);
                dwAddress = reinterpret_cast<DWORD>(moduleEntry32.modBaseAddr);
                return true;
            }
        } while (Module32Next(h_moduleSnapshot, &moduleEntry32));
    }
    properlyCloseHandle(h_moduleSnapshot);
    return false;
}