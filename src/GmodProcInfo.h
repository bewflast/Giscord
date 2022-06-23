#ifndef GMODPROCINFO_h
# define GMODPROCINFO_H

# include "utils.h"

class	GmodProcInfo 
{

private:
	DWORD								pid;
	HANDLE								handle;
	HWND								windowDesc;
	std::string							proc_window_name;
	std::set<const char*>				required_dlls;
	std::map<const char*, dll>			dlls;

public:
	GmodProcInfo(std::set<const char*> dlls);

	DWORD		GetProcessID();
	HWND		GetWindowDescriptor();
	dll			GetDLLBase(const char* dll_name);
	HANDLE		GetProcessHandle();
	std::string GetProcessWindowName();

	void		SetProcessID(DWORD pid);
	void		SetWindowDescriptor(HWND desc);
	void		SetDLLBase(const char* dll_name, dll module);
	void		SetProcessHandle(HANDLE procHandle);
	void		SetProcessWindowName(std::string windowName);

	bool		IsGameStarted();
	void		Reload();

	

};


#endif