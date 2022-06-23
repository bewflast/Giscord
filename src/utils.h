#ifndef UTILS_H
# define UTILS_H

# define UNICODE
# include <Windows.h>
# include <map>
# include <string>
# include <TlHelp32.h>
# include <iostream>
# include <vector>
# include <set>
# include <stdlib.h>
# include <sstream>

typedef struct s_dll_info
{

	DWORD_PTR	addr;
	DWORD		hMod;
	DWORD		size;

} dll;

typedef	struct s_server_info
{

	const char*	hostname;
	const char*	ip_port;
	int			max_player;
	int			current_players;
	
} server;

namespace Utils
{
	namespace sigscan
	{
		namespace offsets
		{
			const DWORD	cur_players	= 	0x6AC3C4;
			const DWORD	max_players	= 	0x4E3D50;
			const DWORD	host_name	=	0x72CF10;
			const DWORD	ip_port		=	0x9FF908;
		}

		DWORD	get_address(std::vector<int> signature, dll Module, HANDLE procHandle);
	}

	std::string			wchar_t_to_std_str(wchar_t* wch_str);
	DWORD				get_process_id(const wchar_t* window_name, HWND winDesc);
	HANDLE				get_process_handle(DWORD pid);
	dll					get_DLLs(const char* dll_name, DWORD pid);
	HWND				get_process_window_descriptor(const wchar_t* window_name);
	std::vector<int>	str_to_sig(std::string target);
	char*				readString(DWORD pid, DWORD_PTR address, int type);

	template <typename T> 
	T readMem(DWORD pid, DWORD_PTR address)
	{
		T		buffer;
		HANDLE	proc;

		proc = Utils::get_process_handle(pid);
		ReadProcessMemory(proc, (LPCVOID)address, &buffer, sizeof(buffer), 0);
		CloseHandle(proc);
		return buffer;
	}
}



#endif
