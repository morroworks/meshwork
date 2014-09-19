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

#include "MwOpenALSoundEmitter.h"

#include "MwOpenALAudioDevice.h"

MwOpenALSoundEmitter::MwOpenALSoundEmitter(void)
{
	alGenSources(1, &this->handle);

	this->soundBuffer = 0;

	this->isLooping = false;
	this->isAmbient = false;
	this->isPlaying = false;

	//alDopplerFactor();
	//alSpeedOfSound(80.0f);
	//alSourcef(this->handle, AL_ROLLOFF_FACTOR, 100.0f);
	//alSourcei(this->handle, AL_REFERENCE_DISTANCE, 1.0f);
	//alSourcei(this->handle, AL_MAX_DISTANCE, 1000.0f);

	//MwVector3 p(0), v(0), o[2] = { MwVector3(0.0f, 0.0f, 1.0f), MwVector3(0.0f, 1.0f, 0.0f) } ;
	//alListenerfv(AL_POSITION, (float*)&v);
	//alListenerfv(AL_VELOCITY, (float*)&v);
	//alListenerfv(AL_ORIENTATION, (float*)&o); //d holds "at" vector3f and "up" vector3f
}


MwOpenALSoundEmitter::~MwOpenALSoundEmitter(void)
{
	this->Stop();
	
	this->context->RemoveStreamingSoundEmitter(this);

	alDeleteSources(1, &this->handle);
}

void MwOpenALSoundEmitter::Play()
{
	alSourcePlay(this->handle); 
}

void MwOpenALSoundEmitter::Stop()
{
	alSourceStop(this->handle); 
}

bool MwOpenALSoundEmitter::RefillStreamingBuffers()
{
	if (!this->soundBuffer->isStreaming)
		return false;

    ALint processedBuffersCount;
	alGetSourcei(this->handle, AL_BUFFERS_PROCESSED, &processedBuffersCount);

	if (processedBuffersCount == 0)
		return false;

    while (processedBuffersCount > 0)
    {
        ALuint alBufferID;

		alSourceUnqueueBuffers(this->handle, 1, &alBufferID);

		unsigned int readBytes;
		if (this->isLooping)
			readBytes = this->soundBuffer->mediaSource->ReadDataLooping(this->soundBuffer->mediaSource->dataSize);
		else
			readBytes = this->soundBuffer->mediaSource->ReadData(this->soundBuffer->mediaSource->dataSize);
		
		alBufferData(alBufferID, this->soundBuffer->alFormat, this->soundBuffer->mediaSource->data, readBytes, this->soundBuffer->mediaSource->pcmFormat.frequency);

        alSourceQueueBuffers(this->handle, 1, &alBufferID);

		processedBuffersCount--;
    }

	return true;
}

int MwOpenALSoundEmitter::GetParameterAddress(MwString parameterName)
{
	if (parameterName.Equals("sound"))
		return 1;
	else if (parameterName.Equals("worldMatrix"))
		return 2;
	else if (parameterName.Equals("velocity"))
		return 3;
	else if (parameterName.Equals("loop"))
		return 4;
	else if (parameterName.Equals("rate"))
		return 5;
	else if (parameterName.Equals("volume"))
		return 6;
	else if (parameterName.Equals("ambient"))
		return 7;
	else if (parameterName.Equals("play"))
		return 8;

	return -1;
}

void MwOpenALSoundEmitter::SetParameter(int address, int index, void *value)
{
	if (address == -1)
		return;

	switch (address)
	{
		// Sound
		case 1:
		{
			MwOpenALSound *buffer = value != 0 ? (MwOpenALSound*)value : 0;

			if (buffer == this->soundBuffer)
				break;

			if (this->soundBuffer != 0)
			{
				if (this->soundBuffer->isStreaming)
					this->context->RemoveStreamingSoundEmitter(this);

				alSourceStop(this->handle); 

				ALuint unqueuedBuffer;
				for (int i = 0; i < this->soundBuffer->buffersCount; i++)
					alSourceUnqueueBuffers(this->handle, 1, &unqueuedBuffer);
			}

			this->soundBuffer = buffer;

			alSourceQueueBuffers(this->handle, this->soundBuffer->buffersCount, this->soundBuffer->bufferIds);

			if (this->soundBuffer->isStreaming)
			{
				alSourcei(this->handle, AL_LOOPING, false);

				this->context->AddStreamingSoundEmitter(this);
			}
			else
			{
				alSourcei(this->handle, AL_LOOPING, this->isLooping);
			}

			if (this->isPlaying)
				alSourcePlay(this->handle); 

			break;
		}

		// World matrix
		case 2:
		{
			if (!this->isAmbient)
				if (value != 0)
				{
					alSourcefv(this->handle, AL_POSITION, (ALfloat*)&((MwMatrix*)value)->_41);
					alSourcefv(this->handle, AL_DIRECTION, (ALfloat*)&((MwMatrix*)value)->_31);
				}
			break;
		}

		// Velocity
		case 3:
		{
			alSourcefv(this->handle, AL_VELOCITY, (ALfloat*)(MwVector3*)value);
			break;
		}

		// Loop
		case 4:
		{
			bool looping = *(bool*)value;
			if (looping == this->isLooping)
				break;

			this->isLooping = looping;

			if (this->soundBuffer == 0)
				break;

			if (!this->soundBuffer->isStreaming)
				alSourcei(this->handle, AL_LOOPING, this->isLooping);

			break;
		}

		// Rate
		case 5:
		{
			alSourcef(this->handle, AL_PITCH, *(float*)value);
			break;
		}

		// Volume
		case 6:
		{
			alSourcef(this->handle, AL_GAIN, *(float*)value);
			break;
		}

		// Ambient
		case 7:
		{
			bool ambient = *(bool*)value;
			if (ambient == this->isAmbient)
				break;

			this->isAmbient = ambient;

			if (this->isAmbient)
			{
				alSourcei(this->handle, AL_SOURCE_RELATIVE, AL_TRUE);
				alSource3f(this->handle, AL_POSITION, 0.0f, 0.0f, 0.0f);
			}
			else
			{
				alSourcei(this->handle, AL_SOURCE_RELATIVE, AL_FALSE);
			}

			break;
		}
		
		// Play
		case 8:
		{
			bool play = *(bool*)value;
			if (play == this->isPlaying)
				break;

			this->isPlaying = play;

			if (this->isPlaying)
				alSourcePlay(this->handle); 
			else
				alSourceStop(this->handle); 

			break;
		}
	}
}
