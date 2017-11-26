#pragma once

#include "CMemory.h"

class CProcess
{
private:
	std::wstring m_wsProcessName;
	DWORD m_dwPId;
	HANDLE m_hProcess;

	// mapa? ró¿ne iloœci i nazwy modu³ów?
	//DWORD m_dwBaseAddress;
	DWORD m_dwClientAddress;
	DWORD m_dwEngineAddress;

	// ustawiæ na true jak wszystko bêdzie gucci ustawione
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
	// tutaj by by³o przyjemniej mieæ ogóln¹ funkcjê do zwracania adresów modu³ów,
	// a nie oddzieln¹ dla ka¿dego
	DWORD getClientAddress() { return m_dwClientAddress; }
	DWORD getEngineAddress() { return m_dwEngineAddress; }
};