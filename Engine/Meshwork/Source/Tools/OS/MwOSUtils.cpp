//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwOSUtils.h"

#include <windows.h>
#include <direct.h>

#ifndef UNICODE
#define UNICODE
#endif

MwOSUtils::MwOSUtils(void)
{
}


MwOSUtils::~MwOSUtils(void)
{
}


long long MwOSUtils::GetPerformanceCounter()
{
	LARGE_INTEGER result;

	if (QueryPerformanceCounter(&result))
		return result.QuadPart;
	else
		return -1;
}

long long MwOSUtils::GetPerformanceCounterFrequency()
{
	LARGE_INTEGER result;

	if (QueryPerformanceFrequency(&result))
		return result.QuadPart;
	else
		return -1;
}

void MwOSUtils::ShowMessage(const wchar_t *text, const wchar_t *caption, void *windowHandle)
{
	HWND handle = windowHandle == 0 ? NULL : *(HWND*)windowHandle;

	MessageBoxW(handle, text, caption, MB_OK);
}

void MwOSUtils::GetScreenSize(int &width, int &height)
{
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
}

int MwOSUtils::GetNumberOfDisplays()
{
	return GetSystemMetrics(SM_CMONITORS);
}

bool MwOSUtils::GetWindowClientSize(void *windowHandle, int &width, int &height)
{
	HWND handle = windowHandle == 0 ? NULL : *(HWND*)windowHandle;

	RECT rect;
	bool result = GetClientRect(handle, &rect) != 0;

	width = rect.right;
	height = rect.bottom;

	return result;
}

int MwOSUtils::GetNumberOfProcessors()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
}

void MwOSUtils::SleepX(int milliseconds)
{
	Sleep(milliseconds);
}

MwString MwOSUtils::GetCurrentDir()
{
	TCHAR buffer[MAX_PATH]={0};
	int length = GetCurrentDirectory(MAX_PATH, buffer);
	return MwString(buffer, MwString::GetLength(buffer));
}

MwString MwOSUtils::GetApplicationName()
{
	TCHAR buffer[MAX_PATH]={0};
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return MwString(buffer, MwString::GetLength(buffer));
}

MwString MwOSUtils::GetApplicationPath()
{
	MwString applicationName = MwOSUtils::GetApplicationName();
	return MwString(applicationName.SubString(0, applicationName.LastIndexOf("\\")));
}

void *MwOSUtils::LoadModule(MwString &fileName)
{
	HINSTANCE dllHandle;
	dllHandle = LoadLibrary(fileName.GetCharContents());
	if (dllHandle == NULL)
		return 0;

	HINSTANCE *result = new HINSTANCE();
	*result = dllHandle;

	return result;
}

void MwOSUtils::UnloadModule(void **module)
{
	if (*module == 0)
		return;

	HINSTANCE *dllHandle = (HINSTANCE*)*module;

	if (*dllHandle == NULL)
		return;

	FreeLibrary(*dllHandle);  
	*dllHandle = NULL;

	delete *module;
	*module = 0;
}

void *MwOSUtils::GetModuleFunction(void *module, MwString &moduleName)
{
	if (module == 0)
		return 0;

	HINSTANCE *dllHandle = (HINSTANCE*)module;

	if (*dllHandle == NULL)
		return 0;
	
	return GetProcAddress(*dllHandle, moduleName.GetCharContents());
}
