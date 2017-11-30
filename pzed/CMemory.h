#pragma once

#include <cassert>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <Windows.h>

// TODO: add fuctions accepting wchar*,
// char* and strings

// TODO: add throws and exceptions handling

class CMemory
{
public:
    CMemory() = delete;

    static bool isValidHandle(HANDLE h) { return h != INVALID_HANDLE_VALUE; }
    static bool isValidProcessHandle(HANDLE h) { return isValidHandle(h) && h > 0; }
    static bool properlyCloseHandle(HANDLE h)
    {
        const auto a = CloseHandle(h);
        assert(a && "handle not closed properly");
        return a;
    }

    // only works for single byte characters
    // implement better solution
    static std::wstring toWstring(const std::string& s) { return std::wstring(s.cbegin(), s.end()); }

    /**
     * get process id of said process
     * @param name of a process
     * @ret process id
     */
    static DWORD getPId(const std::wstring& processName);
    static DWORD getPId(const std::string& processName) { return getPId(toWstring(processName)); }
    static bool getPId(const std::wstring& processName, DWORD& pid);
    static bool getPId(const std::string& processName, DWORD& pid) { return getPId(toWstring(processName), pid); }

    // for now opens only with one access rights, only one needed for now
    // maybe change in future, have more options, add enumerator with access rights?
    static HANDLE getPHandle(DWORD pid) { return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); }
    static void getPHandle(DWORD pid, HANDLE& h) { h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); }

    static DWORD getModule(const std::wstring& moduleName, DWORD pid);
    static DWORD getModule(const std::string& moduleName, DWORD pid) { return getModule(toWstring(moduleName), pid); }
    static bool getModule(const std::wstring& moduleName, DWORD pid, DWORD& dwAddress);
    static bool getModule(const std::string& moduleName, DWORD pid, DWORD& dwAddress) 
    { 
        return getModule(toWstring(moduleName), pid, dwAddress); 
    }

    // maybe add this function getting param value by value for primitive types,
    // all others would probably need to be const_casted (pretty patological)
    // maybe const ref not needed at all, are we passing really big things here?
    template<typename T>
    static bool write(HANDLE hProcess, DWORD dwAddress, const T& value)
    {
        static_assert(std::is_trivially_copyable<T>::value, "Invalid RPM/WPM type");

        if (isValidProcessHandle(hProcess))
            return WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(dwAddress), &value, sizeof(T), NULL);
        return false;
    }

    template<typename T>
    static bool read(HANDLE hProcess, DWORD dwAddress, T& value)
    {
        static_assert(std::is_trivially_copyable<T>::value, "Invalid RPM/WPM type");

        SIZE_T bytesRead;

        if (isValidProcessHandle(hProcess))
            return ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dwAddress), &value, sizeof(T), &bytesRead) && bytesRead == sizeof(T);
        return false;
    }

    // not sure about this one
    template<typename T>
    static T read(HANDLE hProcess, DWORD dwAddress)
    {
        T value = T();
        if (read<T>(hProcess, dwAddress, value)) { return value; }
        // throw?
    }
};