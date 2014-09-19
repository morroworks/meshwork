#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwString.h"
#include "..\MwStrings.h"

class MWDLLCLASS MwOSUtils
{
public:
	MwOSUtils(void);
	~MwOSUtils(void);

	static long long MwOSUtils::GetPerformanceCounter();
	static long long MwOSUtils::GetPerformanceCounterFrequency();

	static void MwOSUtils::ShowMessage(const wchar_t *text, const wchar_t *caption, void *windowHandle = 0);

	static void GetScreenSize(int &width, int &height);
	static int GetNumberOfDisplays();
	
	static bool GetWindowClientSize(void *windowHandle, int &width, int &height);

	static int GetNumberOfProcessors();

	static void SleepX(int milliseconds);

	static MwString GetCurrentDir();

	static MwString GetApplicationName();
	static MwString GetApplicationPath();

	static void *LoadModule(MwString &fileName);
	static void UnloadModule(void **module);
	static void *GetModuleFunction(void *module, MwString &moduleName);
};

