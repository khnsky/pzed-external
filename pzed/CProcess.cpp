#include "stdafx.h"

#include "CProcess.h"

#include <iostream>

bool CProcess::init(const std::wstring& processName)
{
	m_wsProcessName = processName;

    try
    {
        m_dwPId = CMemory::getPId(processName);
        std::cout << "found PId." << std::endl;
        m_hProcess = CMemory::getPHandle(m_dwPId);
        std::cout << "opened handle to process" << std::endl;

        m_dwClientAddress = CMemory::getModule(L"client.dll", m_dwPId);
        std::cout << "found client.dll module" << std::endl;
        m_dwEngineAddress = CMemory::getModule(L"engine.dll", m_dwPId);
        std::cout << "found engine.dll module" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
	assert(isSetUp() && "process not set up properly");
    return true;
}