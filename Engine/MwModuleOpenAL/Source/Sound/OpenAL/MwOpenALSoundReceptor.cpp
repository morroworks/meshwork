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

#include "MwOpenALSoundReceptor.h"

#include "..\..\MeshworkEngine.h"

#include <OpenAL\al.h>

//Can OpenAL have multiple listeners?
//Technically, OpenAL Soft does support it. You can't get multiple listeners in 
//a single context, but you can create multiple contexts from a single device 
//and each context will have one listener. All contexts on a given device will 
//go into a single mix, so there won't be any added latency. The contexts can 
//share buffers (as they're on the same device), but not sources (each context 
//has its own list of sources).

MwOpenALSoundReceptor::MwOpenALSoundReceptor(void)
{
}


MwOpenALSoundReceptor::~MwOpenALSoundReceptor(void)
{
}

int MwOpenALSoundReceptor::GetParameterAddress(MwString parameterName)
{
	if (parameterName.Equals("worldMatrix"))
		return 1;
	else if (parameterName.Equals("velocity"))
		return 2;

	return -1;
}

void MwOpenALSoundReceptor::SetParameter(int address, int index, void *value)
{
	if (address == -1)
		return;

	switch (address)
	{
		// World Matrix
		case 1:
		{
			if (value == 0)
				break;

			MwVector3 orientation[2];
			MwMatrix::GetAxisZ(orientation[0], *(MwMatrix*)value);
			MwMatrix::GetAxisY(orientation[1], *(MwMatrix*)value);

			alListenerfv(AL_POSITION, (ALfloat*)&((MwMatrix*)value)->_41);
			alListenerfv(AL_ORIENTATION, (ALfloat*)&orientation);

			break;
		}

		// Velocity
		case 2:
		{
			if (value != 0)
				alListenerfv(AL_VELOCITY, (ALfloat*)value);

			break;
		}
	}
}