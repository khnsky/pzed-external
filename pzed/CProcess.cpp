#include "stdafx.h"

#include "CProcess.h"

#include <iostream>

bool CProcess::init(const std::string& processName, const std::initializer_list<std::string>& moduleList)
{
	m_sProcessName = processName;

    try
    {
        static DWORD pid = []
        {
            DWORD p = CMemory::getPId(processName);
            std::cout << "found PId." << std::endl;
            return p;
        }();

        static HANDLE hProcess = []
        {
            HANDLE h = CMemory::getPHandle(m_dwPId);
            std::cout << "opened handle to process" << std::endl;
            return h;
        }();

        for (const auto& a : moduleList)
        {
            m_mModules[a] = CMemory::getModule(a, m_dwPId);
            std::cout << "found " << a << " moudle" << std::endl;
        }
    }
    m_dwPId = pid;
    m_hProcess = hProcess;
    m_mModules = modules;
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
	assert(isSetUp() && "process not set up properly");
    return true;
}
