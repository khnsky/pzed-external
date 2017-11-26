#include "stdafx.h"

#include "CProcess.h"

#include <iostream>

bool CProcess::init(const std::wstring& processName)
{
	m_wsProcessName = processName;

	m_dwPId = CMemory::getPId(processName);
	m_hProcess = CMemory::getPHandle(m_dwPId);

	// takiego chyba nie ma
	//m_dwBaseAddress = CMemory::getModule(L"base.dll", m_dwPId);
	m_dwClientAddress = CMemory::getModule(L"client.dll", m_dwPId);
	m_dwEngineAddress = CMemory::getModule(L"engine.dll", m_dwPId);

	std::cout << (m_dwPId != 0)
		<< CMemory::isValidProcessHandle(m_hProcess)
		<< (m_dwClientAddress != 0)
		<< (m_dwEngineAddress != 0) << std::endl;

	return isSetUp();
}