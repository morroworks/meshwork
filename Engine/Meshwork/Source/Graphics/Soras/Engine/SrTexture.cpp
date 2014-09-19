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

#include "SrTexture.h"

#include "..\..\..\Tools\MwMem.h"

SrTexture::SrTexture(void)
{
	this->data = 0;

	this->width = 0;
	this->height = 0;
}

SrTexture::SrTexture(int width, int height)
{
	this->data = 0;

	this->SetSize(width, height);
}

SrTexture::~SrTexture(void)
{
	this->SetSize(0, 0);
}

void SrTexture::SetSize(int width, int height)
{
	if ((this->width == width) && (this->height == height))
		return;
    
	this->width = width;
    this->height = height;
	this->numPixels = width * height;
	this->dataSize = this->numPixels << 2;
    this->highX = this->width - 2;
    this->highY = this->height - 2;

    if (data != 0)
		delete[] this->data;

	if (this->dataSize != 0)
		this->data = new unsigned char[this->dataSize];
	else
		this->data = 0;
}

void SrTexture::SetPixel(int X, int Y, SrARGB &color)
{
    int linear = (Y * width + X) << 2;
	unsigned char* component = data + linear;
    *(component++) = color.b;
    *(component++) = color.g;
    *(component++) = color.r;
    *(component) = color.a;
}

void SrTexture::GetPixel(int X, int Y, SrARGB &color)
{
    int linear = (Y * width + X) << 2;
	unsigned char* component = data + linear;
    color.b = *(component++);
    color.g = *(component++);
    color.r = *(component++);
    color.a = *(component);
}

void SrTexture::Clear()
{
	MwMem::Zero(this->data, this->dataSize);
}

void SrTexture::Fill(SrARGB color)
{
	unsigned int pixelColor = *(unsigned int*)&color;
	unsigned int *pixel = (unsigned int*)this->data;
	for (int i = this->numPixels; i != 0; i--)
		*pixel++ = pixelColor;

	//MwMem::Zero(pixel, numPixels * 4);
}