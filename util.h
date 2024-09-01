#pragma once
#include "precomp.h"
#include "globals.h"
#include "colors.h"

void* hProc = nullptr;
DWORD pid = 0;
uintptr_t moduleBase = 0;

namespace util {

	DWORD getPid(const char* processName)
	{
		DWORD pid = 0;
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		const HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(hProc, &pe32))
		{
			do
			{
				if (!strcmp(processName, pe32.szExeFile))
				{
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hProc, &pe32));
		}

		if (!pid)
		{
			std::cout << "[+] Failed to find the process!" << std::endl;
		}

		CloseHandle(hProc);
		return pid;
	}

	std::uintptr_t getModuleBase(const char* moduleName, DWORD pid)
	{
		std::uintptr_t moduleBase = 0;
		MODULEENTRY32 me32;
		me32.dwSize = sizeof(MODULEENTRY32);

		const HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, pid);

		if (Module32First(hProc, &me32))
		{
			do
			{
				if (!strcmp(moduleName, me32.szModule))
				{
					moduleBase = (uintptr_t)me32.modBaseAddr;
					break;
				}
			} while (Module32Next(hProc, &me32));
		}

		if (!moduleBase)
		{
			std::cout << "[+] Failed to get ModuleBase!" << std::endl;
		}

		CloseHandle(hProc);
		return moduleBase;
	}

	template <typename T>
	const T Read(std::uintptr_t address) noexcept
	{
		T buffer;
		ReadProcessMemory(hProc, (BYTE*)address, &buffer, sizeof(T), FALSE);
		return buffer;
	}

	template <typename T>
	const T Read(std::uintptr_t address, std::vector<unsigned int> offset) noexcept
	{
		std::uintptr_t addr = address;
		for (unsigned int i = 0; i < offset.size(); i++)
		{
			ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(T), FALSE);
			addr += offset[i];
		}
		return addr;
	}

	template <typename T>
	bool Write(std::uintptr_t address, T value) noexcept
	{
		return WriteProcessMemory(hProc, (BYTE*)address, &value, sizeof(T), FALSE);
	}

	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc)
	{
		DWORD oldProtect;
		VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		WriteProcessMemory(hProc, dst, src, size, nullptr);
		VirtualProtectEx(hProc, dst, size, oldProtect, &oldProtect);
	}

	void NopEx(BYTE* dst, unsigned int size, HANDLE hProc)
	{
		BYTE* nopArray = new BYTE[size];
		memset(nopArray, 0x90, size);

		PatchEx(dst, nopArray, size, hProc);
		delete[] nopArray;
	}

	bool init()
	{
		pid = getPid("ac_client.exe");
		if (pid)
		{
			std::cout << "[+] Utilities initialized!" << std::endl;
			moduleBase = getModuleBase("ac_client.exe", pid);
			hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			bFound = true;

			return true;
		}
		else { 
		bool bFound = false; 
		return false; 
		}
	}

	void consoleUpdate()
	{
		system("cls");
		if (bHealth)
		{
			std::cout << color::white << "[+] Press F1 to enable Health!" << color::green << " [ON]" << std::endl;
		}
		else
		{
			std::cout << color::white << "[+] Press F1 to disable Health!" << color::red << " [OFF]" << std::endl;
		}
		if (bArmor)
		{
			std::cout << color::white << "[+] Press F2 to enable Armor!" << color::green << " [ON]" << std::endl;
		}
		else
		{
			std::cout << color::white << "[+] Press F2 to disable Armor!" << color::red << " [OFF]" << std::endl;
		}
		if (bRecoil)
		{
			std::cout << color::white << "[+] Press F3 to enable No-Recoil!" << color::green << " [ON]" << std::endl;
		}
		else
		{
			std::cout << color::white << "[+] Press F3 to disable No-Recoil!" << color::red << " [OFF]" << std::endl;
		}
		if (bKnockback)
		{
			std::cout << color::white << "[+] Press F4 to enable No-KB!" << color::green << " [ON]" << std::endl;
		}
		else
		{
			std::cout << color::white << "[+] Press F4 to disable No-KB!" << color::red << " [OFF]" << std::endl;
		}
		if (bTweaks)
		{
			std::cout << color::white << "[+] Press F5 to enable WeaponTweaks!" << color::green << " [ON]" << std::endl;
		}
		else
		{
			std::cout << color::white << "[+] Press F5 to disable WeaponTweaks!" << color::red << " [OFF]" << std::endl;
		}

		std::cout << color::white << "[+] Press END to exit!" << std::endl;

		Sleep(100);
		}
}