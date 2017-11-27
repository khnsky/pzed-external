#pragma once

#include "CMemory.h"

class CProcess
{
private:
	std::wstring m_wsProcessName;
	DWORD m_dwPId;
	HANDLE m_hProcess;

	// mapa? r�ne ilo�ci i nazwy modu��w?
	DWORD m_dwClientAddress;
	DWORD m_dwEngineAddress;

public:
	CProcess() :
		m_wsProcessName{},
		m_dwPId{ 0 },
		m_hProcess{ INVALID_HANDLE_VALUE },
		m_dwClientAddress{ 0 },
		m_dwEngineAddress{ 0 }
    {}

	~CProcess() { CMemory::properlyCloseHandle(m_hProcess); }

	bool init(const std::wstring& processName);
	bool isSetUp() 
	{
		return m_dwPId != 0
			&& CMemory::isValidProcessHandle(m_hProcess)
			&& m_dwClientAddress != 0
			&& m_dwEngineAddress != 0;
	}

	DWORD getId() { return m_dwPId; }
	HANDLE getHandle() { return m_hProcess; }
	// tutaj by by�o przyjemniej mie� og�ln� funkcj� do zwracania adres�w modu��w,
	// a nie oddzieln� dla ka�dego
	DWORD getClientAddress() { return m_dwClientAddress; }
	DWORD getEngineAddress() { return m_dwEngineAddress; }
};