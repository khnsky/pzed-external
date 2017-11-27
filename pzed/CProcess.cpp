#include "stdafx.h"

#include "CProcess.h"

#include <iostream>

bool CProcess::init(const std::wstring& processName)
{
	m_wsProcessName = processName;

    // could throw here
	m_dwPId = CMemory::getPId(processName);
	m_hProcess = CMemory::getPHandle(m_dwPId);

    // could throw here
	m_dwClientAddress = CMemory::getModule(L"client.dll", m_dwPId);
	m_dwEngineAddress = CMemory::getModule(L"engine.dll", m_dwPId);

	return isSetUp();
}