#pragma once

#include "CMemory.h"

class CProcess
{
private:
	std::wstring m_wsProcessName;
	DWORD m_dwPId;
	HANDLE m_hProcess;

	// mapa? r�ne ilo�ci i nazwy modu��w?
	//DWORD m_dwBaseAddress;
	DWORD m_dwClientAddress;
	DWORD m_dwEngineAddress;

	// ustawi� na true jak wszystko b�dzie gucci ustawione
	bool m_setUp;

public:
	CProcess() :
		m_wsProcessName{},
		m_dwPId{ 0 },
		m_hProcess{ INVALID_HANDLE_VALUE },
		//m_dwBaseAddress{ 0 },
		m_dwClientAddress{ 0 },
		m_dwEngineAddress{ 0 },
		m_setUp{ false } {}

	~CProcess() { CMemory::properlyCloseHandle(m_hProcess); }

	bool init(const std::wstring& processName);
	bool isSetUp() 
	{
		return m_dwPId != 0
			&& CMemory::isValidProcessHandle(m_hProcess)
			&& m_dwClientAddress != 0
			&& m_dwEngineAddress != 0;
	}

	// kolizja nazw
	DWORD getId() { return m_dwPId; }
	HANDLE getHandle() { return m_hProcess; }
	// tutaj by by�o przyjemniej mie� og�ln� funkcj� do zwracania adres�w modu��w,
	// a nie oddzieln� dla ka�dego
	DWORD getClientAddress() { return m_dwClientAddress; }
	DWORD getEngineAddress() { return m_dwEngineAddress; }
};