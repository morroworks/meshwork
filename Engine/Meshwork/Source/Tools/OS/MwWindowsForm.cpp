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

#include "MwWindowsForm.h"

#ifndef UNICODE
#	define UNICODE
#endif

#include <windowsx.h>

const wchar_t* MwWindowsForm::FormClassName = L"MyWindowsForm";

MwList<MwWindowsForm*> MwWindowsForm::instances;

LRESULT CALLBACK MwWindowsForm::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MwWindowsForm* instance = MwWindowsForm::GetInstance(hWnd);

	if (instance != NULL)
	{
		switch (uMsg)									
		{
			case WM_SYSCOMMAND:							
			{
				switch (wParam)							
				{
					case SC_SCREENSAVE:
						{
							if (instance->suppressScreenSaver)
								return 0;
						}
					case SC_MONITORPOWER:
						{
							if (instance->suppressMonitorPowerSave)
								return 0;
						}
				}
				break;									
			}

			case WM_ACTIVATE:							
			{
				// Minimization state
				if (!HIWORD(wParam))					
				{
					instance->active=TRUE;				
				}
				else
				{
					instance->active=FALSE;				
				}

				return 0;								
			}

			case WM_CLOSE:							
			{
				if (instance->Close())
				{
					PostQuitMessage(0);					
				}
				return 0;							
			}

			case WM_SIZE:								
			{
				int width = LOWORD(lParam);
				int height = HIWORD(lParam);

				instance->Resize(width, height);

				instance->width = width;
				instance->height = height;

				return 0;								
			}

			case WM_PAINT:
				{
					if (instance->Paint())
					{
						ValidateRect(instance->handle, NULL);
					}

					return 0;
				}

			case WM_KEYDOWN:						
			{
				int key = wParam;

				instance->KeyDown(key);

				if ((key >=0 ) && (key < 256))
					instance->keys[key] = TRUE;			
				return 0;							
			}

			case WM_KEYUP:								
			{
				int key = wParam;

				instance->KeyUp(key);

				if ((key >=0 ) && (key < 256))
					instance->keys[key] = FALSE;				
				return 0;								
			}

			case WM_LBUTTONDOWN:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseDown(x, y, MwWindowsForm::MouseButton_Left);
					instance->mouseButtons |= MwWindowsForm::MouseButton_Left;

					return 0;
				}

			case WM_LBUTTONUP:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseUp(x, y, MwWindowsForm::MouseButton_Left);
					instance->mouseButtons &= !MwWindowsForm::MouseButton_Left;

					return 0;
				}

			case WM_RBUTTONDOWN:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseDown(x, y, MwWindowsForm::MouseButton_Right);
					instance->mouseButtons |= MwWindowsForm::MouseButton_Right;

					return 0;
				}

			case WM_RBUTTONUP:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseUp(x, y, MwWindowsForm::MouseButton_Right);
					instance->mouseButtons &= !MwWindowsForm::MouseButton_Right;

					return 0;
				}

			case WM_MBUTTONDOWN:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseDown(x, y, MwWindowsForm::MouseButton_Middle);
					instance->mouseButtons |= MwWindowsForm::MouseButton_Middle;

					return 0;
				}

			case WM_MBUTTONUP:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseUp(x, y, MwWindowsForm::MouseButton_Middle);
					instance->mouseButtons &= !MwWindowsForm::MouseButton_Middle;

					return 0;
				}

			case WM_MOUSEMOVE:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);

					instance->MouseMove(x, y);

					if (instance->mouseMoved)
					{
						instance->mouseDeltaX = x - instance->mouseX;
						instance->mouseDeltaY = y - instance->mouseY;
					}
					else 
						instance->mouseMoved = true;
					
					instance->mouseX = x;
					instance->mouseY = y;

					return 0;
				}

			case WM_MOUSEHWHEEL:
				{
					int x = GET_X_LPARAM(lParam); 
					int y = GET_Y_LPARAM(lParam);
					int deltaFactor = GET_WHEEL_DELTA_WPARAM(wParam);

					instance->MouseWheel(x, y, deltaFactor, WHEEL_DELTA);

					return 0;
				}
		}

		int result;
		if (instance->HandleMessage(uMsg, wParam, lParam, &result))
			return result;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

MwWindowsForm* MwWindowsForm::GetInstance(HWND instanceHandle)
{
	for (int i = 0; i < MwWindowsForm::instances.count; i++)
	{
		if (MwWindowsForm::instances[i]->handle == instanceHandle)
		{
			return MwWindowsForm::instances[i];
		}
	}

	return NULL;
}

bool MwWindowsForm::ProcessMessages()
{
	bool result = false;

    MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

		result = true;
    }

	return result;
}

int MwWindowsForm::PerformFormLoop()
{
    MSG msg;

	bool done = false;
	while(!done)										
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	
		{
			if (msg.message == WM_QUIT)					
			{
				done = true;							
			}
			else										
			{
				TranslateMessage(&msg);					
				DispatchMessage(&msg);					
			}
		}

		if (!done)
		{
			for (int i = 0; i < MwWindowsForm::instances.count; i++)
			{
				MwWindowsForm::instances[i]->MainLoop();

				MwWindowsForm::instances[i]->ResetLoopVariables();
			}
		}
	}

	return (int)msg.wParam;
	
}

void MwWindowsForm::ResetLoopVariables()
{
	this->mouseDeltaX = 0;
	this->mouseDeltaY = 0;
}

MwWindowsForm::MwWindowsForm(void)
{
	this->ResetLoopVariables();

	this->applicationInstance = GetModuleHandle(NULL);
	ZeroMemory(keys, 256);

	this->left = 0;
	this->top = 0;
	this->width = 800;
	this->height = 600;
	this->caption = L"Window Title";
	this->windowMode = MwWindowsForm::WindowMode_Windowed;
	//this->windowMode = MwWindowsForm::WindowMode_FullScreen;
	this->mouseMoved = false;

	MwWindowsForm::instances.Add(this);
	//MwWindowsForm::instances.push_back(this);

	this->RegisterWindowClass();
	this->CreateFormWindow();
	this->ShowFormWindow();
}


MwWindowsForm::~MwWindowsForm(void)
{
	MwWindowsForm::instances.Remove(this);
}

bool MwWindowsForm::RegisterWindowClass()
{
	//LRESULT (CALLBACK MwWindowsForm::*memfun)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//memfun = &MwWindowsForm::WndProc;
    //this->ex.lpfnWndProc = *((WNDPROC*) (&memfun));

	this->windowClass.cbSize = sizeof(WNDCLASSEX);
    this->windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	this->windowClass.lpfnWndProc = (WNDPROC)MwWindowsForm::WndProc;
    this->windowClass.cbClsExtra = 0;
    this->windowClass.cbWndExtra = 0;
    this->windowClass.hInstance = this->applicationInstance;
    this->windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    this->windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    this->windowClass.hbrBackground = NULL;
    this->windowClass.lpszMenuName = NULL;
    this->windowClass.hIconSm = NULL;
	this->windowClass.lpszClassName = MwWindowsForm::FormClassName;

	return RegisterClassExW(&this->windowClass) != 0;
}

bool MwWindowsForm::CreateFormWindow()
{
    long wndStyle = this->windowMode == MwWindowsForm::WindowMode_FullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
	wndStyle |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	// Translate from client rect to window rect
	RECT wRect = { this->left, this->top, this->left + this->width, this->top + this->height };
	AdjustWindowRect(&wRect, wndStyle, false);

	this->handle = CreateWindowW(MwWindowsForm::FormClassName, this->caption,
								 wndStyle,
								 this->left, this->top, wRect.right - wRect.left, wRect.bottom - wRect.top,
								 NULL, NULL,
								 this->applicationInstance,
								 NULL);

	return this->handle != 0;
}

void MwWindowsForm::ShowFormWindow()
{
	ShowWindow(this->handle,SW_SHOW);
    //UpdateWindow(this->handle);
	SetForegroundWindow(this->handle);						// Slightly Higher Priority
	SetFocus(this->handle);									// Sets Keyboard Focus To The Window
}

void MwWindowsForm::SetPosition(int left, int top)
{
	this->left = left;
	this->top = top;

	SetWindowPos(this->handle, HWND_TOP, this->left, this->top, this->width, this->height, SWP_NOSIZE);
}

void MwWindowsForm::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;

	SetWindowPos(this->handle, HWND_TOP, this->left, this->top, this->width, this->height, SWP_NOMOVE);
}

void MwWindowsForm::SetStyle()
{
	SetWindowLong(this->handle, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
	SetWindowLong(this->handle, GWL_EXSTYLE, 0);
	//SetWindowLong(this->handle, GWL_STYLE, WS_POPUP);
	//SetWindowLong(this->handle, GWL_EXSTYLE, WS_EX_APPWINDOW);
}

void MwWindowsForm::CloseWindow()
{
	PostMessage(this->handle, WM_CLOSE, 0, 0);
}

void MwWindowsForm::SetActive()
{
	SetActiveWindow(this->handle);
}

void MwWindowsForm::SetCaption(const wchar_t *caption)
{
	SetWindowTextW(this->handle, caption);
}


// Virtual Methods
bool MwWindowsForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, int *result) { return false; }
void MwWindowsForm::MainLoop() { }
void MwWindowsForm::Created() { }
bool MwWindowsForm::Close() { return true; }
bool MwWindowsForm::Paint() { return true; }
void MwWindowsForm::KeyDown(int keyCode) { }
void MwWindowsForm::KeyUp(int keyCode) { }
void MwWindowsForm::Resize(int width, int height) {}
void MwWindowsForm::MouseMove(int x, int y) { }
void MwWindowsForm::MouseDown(int x, int y, int mouseButton) { }
void MwWindowsForm::MouseUp(int x, int y, int mouseButton) { }
void MwWindowsForm::MouseWheel(int x, int y, int deltaFactor, int delta) { }

