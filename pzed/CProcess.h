#pragma once

#include <initializer_list>
#include <map>

#include "CMemory.h"

class CProcess
{
private:
	std::wstring m_wsProcessName;
	DWORD m_dwPId;
	HANDLE m_hProcess;
    std::map<std::wstring, DWORD> m_mModules;

public:
	CProcess() :
		m_wsProcessName{},
		m_dwPId{ 0 },
		m_hProcess{ INVALID_HANDLE_VALUE },
        m_mModules{}
    {}

	~CProcess() { CMemory::properlyCloseHandle(m_hProcess); }

	bool init(const std::wstring& processName, const std::initializer_list<std::wstring>& mouduleList);
	bool isSetUp() const
	{
        return m_dwPId != 0
            && CMemory::isValidProcessHandle(m_hProcess)
            && [&] () -> bool
            {
                for (const auto& a : m_mModules) { if (a.second == 0) { return false; } }
                return true;
            }();
	}

	DWORD getId() const { return m_dwPId; }
	HANDLE getHandle() const { return m_hProcess; }
    const std::map<std::wstring, DWORD>& getModules() const { return m_mModules; }
    DWORD getModule(const std::wstring& moduleName) const { return m_mModules.at(moduleName); }
};