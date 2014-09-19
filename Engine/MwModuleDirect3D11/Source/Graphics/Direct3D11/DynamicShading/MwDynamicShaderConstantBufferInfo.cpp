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

#include "MwDynamicShaderConstantBufferInfo.h"


MwDynamicShaderConstantBufferInfo::MwDynamicShaderConstantBufferInfo(void)
{
	this->totalSize = 0;
}


MwDynamicShaderConstantBufferInfo::~MwDynamicShaderConstantBufferInfo(void)
{
	this->Clear();

}

bool MwDynamicShaderConstantBufferInfo::Add(MwString name, int elementSize, int elementCount, int offset)
{
	int startAddress, size;
	int elementPitch = MwMaths::GetBoundary(elementSize, MwDynamicShaderConstantBufferInfo::SizeMultiplicity);

	if (elementCount > 1)
	{
		startAddress = MwMaths::GetBoundary(this->totalSize, MwDynamicShaderConstantBufferInfo::SizeMultiplicity);
		size = elementCount * elementPitch;
	}
	else
	{
		int vectorOffset = this->totalSize % MwDynamicShaderConstantBufferInfo::SizeMultiplicity;
		if ((vectorOffset != 0) && (vectorOffset + elementSize > MwDynamicShaderConstantBufferInfo::SizeMultiplicity))
			startAddress = this->totalSize + MwDynamicShaderConstantBufferInfo::SizeMultiplicity - vectorOffset;
		else
			startAddress = this->totalSize;
		size = elementCount * elementSize;
	}

	if (startAddress + size > MwDynamicShaderConstantBufferInfo::MaxSize)
		return false;

	MwDynamicShaderConstantInfo constantInfo;
	constantInfo.name = name;
	constantInfo.offset = startAddress + offset;
	constantInfo.elementSize = elementSize;
	constantInfo.elementCount = elementCount;
	constantInfo.elementPitch = elementPitch;

	this->totalSize = startAddress;

	if (offset == 0)
		this->totalSize += size;

	MwList<MwDynamicShaderConstantInfo>::Add(constantInfo);

	return true;
}

void MwDynamicShaderConstantBufferInfo::Clear()
{
	this->totalSize = 0;

	MwList<MwDynamicShaderConstantInfo>::Clear();
}
