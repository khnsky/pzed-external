#pragma once

#include <cassert>
#include <string>
#include <type_traits>

#include <Windows.h>

// funkcja konwertuj¹ca z stringa na wstringa
// wersje funkcji przyjmuj¹ce wchar*, stringi, i char*

class CMemory
{
public:
	CMemory() = delete;

	static bool isValidHandle(HANDLE h) { return h != INVALID_HANDLE_VALUE; }
	static bool isValidProcessHandle(HANDLE h) { return isValidHandle(h) && h > 0; }
	static bool properlyCloseHandle(HANDLE h)
	{
		auto const a = CloseHandle(h);
		assert(a && "handle not closed properly");
		return a;
	}

	static DWORD getPId(const std::wstring& processName);
	static bool getPId(const std::wstring& processName, DWORD& pid);

	// jak na razie otwiera tylko z jednymi uprawnieniami, tylko tyle potrzebujemy,
	// ale mo¿e lepiej to zmieniæ, daæ mo¿liwoœæ wiêkszego manewru, enum z mo¿liwymi wartoœciami?
	static HANDLE getPHandle(DWORD pid) { return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); }
	static void getPHandle(DWORD pid, HANDLE& h) { h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); }

	static DWORD getModule(const std::wstring& moduleName, DWORD pid);
	static bool getModule(const std::wstring& moduleName, DWORD pid, DWORD& dwAddress);

	// mo¿e napisaæ wersje przyjmuj¹c¹ value by value (xD) aby unikn¹æ kopiowania primitywnych typów,
	// resztê const_castowaæ? rozwi¹zanie doœæ patologiczne
	// mo¿e const& w ogólnie niepotrzebne czy piszemy tu kiedykolwiek naprawdê du¿e rzeczy?
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

	// nie jestem pewien tej funcji, na razie zarys
	template<typename T>
	static T read(HANDLE hProcess, DWORD dwAddress)
	{
		static_assert(std::is_trivially_copyable<T>::value, "Invalid RPM/WPM type");

		if (isValidProcessHandle(hProcess))
		{
			// ?
			T value = T();
			ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(dwAddress), &value, sizeof(T), 0);
			return value;
		}
		// throw
		return false;
	}
};