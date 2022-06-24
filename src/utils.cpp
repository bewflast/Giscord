#include "utils.h"

char*	hostname_buff = new char[80];
char*	ip_port_buff = new char[22];

std::string	Utils::wchar_t_to_std_str(wchar_t* wch_str)
{
	std::wstring	ws(wch_str);
	std::string	ws_stdstr(ws.begin(), ws.end());

	return (ws_stdstr);
}

HWND		Utils::get_process_window_descriptor(const wchar_t* window_name)
{
	HWND	desc;

	desc = FindWindow(0, window_name);
	return (desc);
}


DWORD		Utils::get_process_id(const wchar_t* window_name, HWND winDesc)
{
	DWORD	PID(NULL);

	GetWindowThreadProcessId(winDesc, &PID);

	return (PID);
}


HANDLE		Utils::get_process_handle(DWORD pid)
{
	HANDLE	procHandle(NULL);

	procHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	return (procHandle);
}


dll			Utils::get_DLLs(const char* dll_name, DWORD pid)
{
	dll				result;
	HANDLE			SnapShot;
	MODULEENTRY32	ModuleEntry;

	SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	ModuleEntry = { 0 };
	result = { NULL, NULL, NULL };
	if (!SnapShot) return (result);

	ModuleEntry.dwSize = sizeof(ModuleEntry);
	
	if (!Module32First(SnapShot, &ModuleEntry)) return (result);

	do
	{
		
		if (Utils::wchar_t_to_std_str(ModuleEntry.szModule) == (std::string)dll_name)
		{
			CloseHandle(SnapShot);

			result.addr = (DWORD_PTR)ModuleEntry.modBaseAddr;
			result.hMod = (DWORD)ModuleEntry.hModule;
			result.size = ModuleEntry.modBaseSize;

			return(result);
		}
	} 
	while (Module32Next(SnapShot, &ModuleEntry));

	CloseHandle(SnapShot);
	return (result);
}

std::vector<int>	Utils::str_to_sig(std::string target)
{
	std::string			tmp;
	std::vector<int>	result;
	int					i(0);
	std::istringstream	a(target);
	
	while (std::getline(a, tmp, ' '))
		result.push_back(tmp == "?" ? -1 : std::stoul("0x" + tmp, nullptr, 16));
	
	return (result);
}

DWORD				Utils::sigscan::get_address(std::vector<int> signature, dll Module, HANDLE procHandle)
{

	std::vector<byte> memBuffer(Module.size);
	if (!ReadProcessMemory(procHandle, (LPCVOID)(Module.addr), memBuffer.data(), Module.size, NULL))
		return (NULL);
	for (int i = 0; i < Module.size; i++)
	{
		for (DWORD j = 0; j < signature.size(); j++)
		{
			if (signature[j] != -1 && signature[j] != memBuffer[i + j])
				break;
			if (j + 1 == signature.size())
				return (Module.hMod + i);
		}
	}
	return (NULL);
}

char*				Utils::readString(DWORD pid, DWORD_PTR address, int type)
{
	HANDLE		proc;
	std::string	result;
	
	memset((type == 1 ? hostname_buff : ip_port_buff), NULL, sizeof(char) * (type == 1 ? 80 : 22));

	proc = Utils::get_process_handle(pid);
	ReadProcessMemory(proc, (LPCVOID)address, (type == 1 ? hostname_buff : ip_port_buff), (type == 1 ? 79 : 21), 0);
	CloseHandle(proc);

	return (type == 1 ? hostname_buff : ip_port_buff);
}

