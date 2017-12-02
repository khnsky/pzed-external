#pragma once

#include <initializer_list>
#include <map>

#include "CMemory.h"

class CProcess
{
private:
	std::string m_sProcessName;
	DWORD m_dwPId;
	HANDLE m_hProcess;
    std::map<std::string, DWORD> m_mModules;

public:
	CProcess() :
		m_sProcessName{},
		m_dwPId{ 0 },
		m_hProcess{ INVALID_HANDLE_VALUE },
        m_mModules{}
    {}

	~CProcess() { CMemory::properlyCloseHandle(m_hProcess); }

	bool init(const std::string& processName, const std::initializer_list<std::string>& mouduleList);
    bool init(const std::string& processName) { return init(processName, {}); }

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
    const std::map<std::string, DWORD>& getModules() const { return m_mModules; }
    DWORD getModule(const std::string& moduleName) const { return m_mModules.at(moduleName); }
};