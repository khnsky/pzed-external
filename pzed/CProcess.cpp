#include "stdafx.h"

#include "CProcess.h"

#include <iostream>

bool CProcess::init(const std::wstring& processName, const std::initializer_list<std::wstring>& moduleList)
{
	m_wsProcessName = processName;

    try
    {
        m_dwPId = CMemory::getPId(processName);
        std::cout << "found PId." << std::endl;
        m_hProcess = CMemory::getPHandle(m_dwPId);
        std::cout << "opened handle to process" << std::endl;

        for (const auto& a : moduleList)
        {
            m_mModules[a] = CMemory::getModule(a, m_dwPId);
            std::wcout << L"found " << a << L" moudle" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
	assert(isSetUp() && "process not set up properly");
    return true;
}