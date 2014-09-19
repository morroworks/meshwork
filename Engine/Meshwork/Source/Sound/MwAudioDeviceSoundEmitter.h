#pragma once

#include "..\MwGlobals.h"

#include "..\Tools\MwString.h"

// Represents a physical emitter of a sound. Can be played and has certain adjustable parameters which define its physical properties, like position, velocity, volume and et cetera
// In order to be able to emit a sound, it needs to have a MwAudioDeviceSound set
class MWDLLCLASS MwAudioDeviceSoundEmitter
{
public:
	MwAudioDeviceSoundEmitter(void);
	virtual ~MwAudioDeviceSoundEmitter(void);

	// Starts playing the sound from its current position
	virtual void Play() = 0;
	// Stops playing the sound and sets its current position to 0
	virtual void Stop() = 0;

	// Refills buffers if needed in case of a streaming audio. It is typically called continuously by the implementation of the respective audio device, preferably in separate thread.
	// returns - true is any buffers were refilled, false otherwise.
	virtual bool RefillStreamingBuffers() = 0;

	// Returns an address for the parameter with the given name. The address can then be used to set the parameter's value
	// parameterName - name of the parameter, whose address is requested
	// returns - the address of the parameter, -1 if there is no such parameter.
	virtual int GetParameterAddress(MwString parameterName) = 0;
	// Sets a value to a parameter.
	// address - the address of the parameter to be set
	// index - index of the paramter to be set. In case of non-indexed parameter, it should be 0
	// value - pointer to the value which is to be set to the parameter
	virtual void SetParameter(int address, int index, void *value) = 0;
};
