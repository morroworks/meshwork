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

#include "MwOpenALAudioDevice.h"

#include "MwOpenALSound.h"
#include "MwOpenALSoundReceptor.h"

int MwOpenALAudioDevice::StreamingThreadFunction(void *parameter)
{
	MwOpenALAudioDevice *device = (MwOpenALAudioDevice*)parameter;

	while (device->processStreaming)
	{
		device->streamingThreadMutex->Lock();

		for (int i = 0; i < device->streamingSounds.count; i++)
		{
			device->streamingSounds[i]->RefillStreamingBuffers();
		}
		
		device->streamingThreadMutex->Unlock();

		MwOSUtils::SleepX(500);
	}

	return 0;
}

MwOpenALAudioDevice::MwOpenALAudioDevice(void)
{
	this->device = alcOpenDevice(0);
	if (this->device == 0)
		return;

	this->context = alcCreateContext(device, 0);
	if (this->context == 0)
		return;

	alcMakeContextCurrent(this->context);

	this->processStreaming = true;
	this->streamingThreadMutex = new MwMutex();
	this->streamingThread = new MwThread(MwOpenALAudioDevice::StreamingThreadFunction, this);
}


MwOpenALAudioDevice::~MwOpenALAudioDevice(void)
{
	this->processStreaming = false;
	delete this->streamingThread;
	delete this->streamingThreadMutex;

	alcMakeContextCurrent(0);
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

void MwOpenALAudioDevice::AddStreamingSoundEmitter(MwAudioDeviceSoundEmitter *soundEmitter)
{
	this->streamingThreadMutex->Lock();

	if (this->streamingSounds.IndexOf(soundEmitter) == -1)
		this->streamingSounds.Add(soundEmitter);

	this->streamingThreadMutex->Unlock();
}

void MwOpenALAudioDevice::RemoveStreamingSoundEmitter(MwAudioDeviceSoundEmitter *soundEmitter)
{
	this->streamingThreadMutex->Lock();

	this->streamingSounds.Remove(soundEmitter);

	this->streamingThreadMutex->Unlock();
}

MwAudioDeviceSound *MwOpenALAudioDevice::CreateSound()
{
	return new MwOpenALSound();
}

MwAudioDeviceSoundEmitter *MwOpenALAudioDevice::CreateSoundEmitter()
{
	MwOpenALSoundEmitter *result = new MwOpenALSoundEmitter();
	result->context = this;
	
	return result;
}

MwAudioDeviceSoundReceptor *MwOpenALAudioDevice::CreateSoundReceptor()
{
	return new MwOpenALSoundReceptor();
}
