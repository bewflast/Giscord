#include "GmodProcInfo.h"

DWORD		GmodProcInfo::GetProcessID()
{
	return (this->pid);
}

HWND		GmodProcInfo::GetWindowDescriptor()
{
	return (this->windowDesc);
}

dll			GmodProcInfo::GetDLLBase(const char* dll_name)
{
	return (this->dlls[dll_name]);
}


HANDLE		GmodProcInfo::GetProcessHandle()
{
	return (this->handle);
}


std::string GmodProcInfo::GetProcessWindowName()
{
	return (this->proc_window_name);
}


void		GmodProcInfo::SetProcessID(DWORD pid)
{
	this->pid = pid;
}


void		GmodProcInfo::SetDLLBase(const char* dll_name, dll	module)
{
	this->dlls[dll_name] = module;
}


void		GmodProcInfo::SetProcessHandle(HANDLE procHandle)
{
	this->handle = procHandle;
}

void		GmodProcInfo::SetWindowDescriptor(HWND desc)
{
	this->windowDesc = desc;
}


void		GmodProcInfo::SetProcessWindowName(std::string windowName)
{
	this->proc_window_name = windowName;
}

bool	GmodProcInfo::IsGameStarted()
{
	HWND	temp;
	HWND	winDesc;

	temp = Utils::get_process_window_descriptor(L"Garry's Mod");
	winDesc = (!temp ? Utils::get_process_window_descriptor(L"Garry's Mod (x64)") : temp);
	
	if (winDesc != this->GetWindowDescriptor())
	{
		this->Reload();
		if (winDesc)
		{
			this->SetWindowDescriptor(winDesc);
			this->SetProcessWindowName(!temp ? "Garry's Mod (x64)" : "Garry's Mod");
			this->SetProcessID(Utils::get_process_id((!temp ? L"Garry's Mod (x64)" : L"Garry's Mod"), winDesc));
			this->SetProcessHandle(Utils::get_process_handle(this->GetProcessID()));
			for (const char* dll_name : this->required_dlls)
				this->dlls[dll_name] = Utils::get_DLLs(dll_name, this->GetProcessID());
		}
	}
	return (!!winDesc);
}


void	GmodProcInfo::Reload()
{
	this->handle = NULL;
	this->pid = NULL;
	this->windowDesc = NULL;
	this->proc_window_name = "\0";
}


GmodProcInfo::GmodProcInfo(std::set<const char*> dlls)
{
	this->required_dlls = dlls;
	this->Reload();
}