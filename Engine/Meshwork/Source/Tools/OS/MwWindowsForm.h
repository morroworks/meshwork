#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwList.h"

#include <windows.h>

class MwWindowsForm;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwWindowsForm*>;

class MWDLLCLASS MwWindowsForm
{
private:
	bool mouseMoved;
	void ResetLoopVariables();

public:
	static const int WindowMode_Windowed = 0;
	static const int WindowMode_FullScreen = 1;
					 
	static const int MouseButton_None = 0;
	static const int MouseButton_Left = 1;
	static const int MouseButton_Right = 2;
	static const int MouseButton_Middle = 4;


	static const wchar_t* FormClassName;

	static MwList<MwWindowsForm*> instances;

	HINSTANCE applicationInstance;
	WNDCLASSEXW windowClass;
	HWND handle;

	bool keys[256]; // Left- and right-distinguishing constants are available to an application only through the GetKeyboardState, SetKeyboardState, GetAsyncKeyState, GetKeyState, and MapVirtualKey functions.
	int mouseX, mouseY,	mouseDeltaX, mouseDeltaY, mouseButtons;
	bool suppressScreenSaver, suppressMonitorPowerSave;
	
	bool active;
	int windowMode;
	int left, top, width, height;
	wchar_t *caption;


	MwWindowsForm(void);
	virtual ~MwWindowsForm(void);

	bool RegisterWindowClass();
	bool CreateFormWindow();
	void ShowFormWindow();
	void SetPosition(int left, int top);
	void SetSize(int width, int height);
	void SetStyle();
	void CloseWindow();
	void SetActive();
	void SetCaption(const wchar_t *caption);

	virtual bool HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, int *result);
	virtual void MainLoop();
	virtual void Created();
	virtual bool Close();
	virtual bool Paint();
	virtual void KeyDown(int keyCode);
	virtual void KeyUp(int keyCode);
	virtual void Resize(int width, int height);
	virtual void MouseMove(int x, int y);
	virtual void MouseDown(int x, int y, int mouseButton);
	virtual void MouseUp(int x, int y, int mouseButton);
	virtual void MouseWheel(int x, int y, int deltaFactor, int delta);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static MwWindowsForm* GetInstance(HWND instanceHandle);
	static bool ProcessMessages();
	static int PerformFormLoop();
};

