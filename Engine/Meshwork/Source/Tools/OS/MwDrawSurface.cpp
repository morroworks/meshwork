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

#include "MwDrawSurface.h"

#include "..\..\Tools\MwMem.h"

MwDrawSurface::MwDrawSurface(void)
{
	this->pixelData = 0;
}

MwDrawSurface::~MwDrawSurface(void)
{
	this->SetSize(0, 0);
}

void MwDrawSurface::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixelDataSize = this->width * this->height * 4;

	this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->bitmapInfo.bmiHeader.biWidth = width;
	this->bitmapInfo.bmiHeader.biHeight = height;
	this->bitmapInfo.bmiHeader.biPlanes = 1;
	this->bitmapInfo.bmiHeader.biBitCount = 32;
	this->bitmapInfo.bmiHeader.biCompression = BI_RGB;
	this->bitmapInfo.bmiHeader.biSizeImage = 0;
	this->bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	this->bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	this->bitmapInfo.bmiHeader.biClrUsed = 0;
	this->bitmapInfo.bmiHeader.biClrImportant = 0;

	if (this->pixelData != 0)
	{
		VirtualFree(this->pixelData, 0, MEM_RELEASE);
		this->pixelData = 0;
	}

	if (this->pixelDataSize > 0)
	{
		this->pixelData = VirtualAlloc(0, this->pixelDataSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);	
	}
}

void MwDrawSurface::Copy(void* pixelData)
{
	MwMem::Copy(this->pixelData, pixelData, this->pixelDataSize);
}

void MwDrawSurface::Present(int x, int y, HDC deviceContext)
{
	SetDIBitsToDevice(
		deviceContext,
		x, y, this->width, this->height,
		0, 0,
		0, this->height,
		this->pixelData,
		&this->bitmapInfo,
		DIB_RGB_COLORS);
}
