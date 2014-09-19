#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwString.h"

// TODO: Consider removing FormatExtension and the info tag parameter and passing the extensions as one string, extensions divided by '/'
class MWDLLCLASS MwDispatcher
{
public:
	// Request of the typeId of the dispatched object
	static const unsigned int infoId_TypeId									= 0x00000000;
	// Request of a user friendly name of the dispatched object
	static const unsigned int infoId_Name									= 0x10000000;
	// Request of a user friendly description of the dispatched object
	static const unsigned int infoId_Description							= 0x20000000;
	// Media serialization and deserialization. As the dispatched object might support number of formats for serialization and different number for deserialization, info on each can be accessed by providing an index to the infoTag parameter in the MwMediaDispatcher::GetInfoType method. The method returning false means the index and all consequent indices are invalid
	// Request the format extension of a type supported for serialization by the dispatched object. This is effectively a file type extension. Index of type is fed to the infoTag parameter of the MwMediaDispatcher::GetInfoType method
	static const unsigned int infoId_MediaSerializationFormatExtension		= 0x30000000;
	// Request the format description of a type supported for serialization by the dispatched object. Index of type is fed to the infoTag parameter of the MwMediaDispatcher::GetInfoType method
	static const unsigned int infoId_MediaSerializationFormatDescription	= 0x40000000;
	// Request the format extension of a type supported for deserialization by the dispatched object. This is effectively a file type extension. Index of type is fed to the infoTag parameter of the MwMediaDispatcher::GetInfoType method
	static const unsigned int infoId_MediaDeserializationFormatExtension	= 0x50000000;
	// Request the format description of a type supported for deserialization by the dispatched object. Index of type is fed to the infoTag parameter of the MwMediaDispatcher::GetInfoType method
	static const unsigned int infoId_MediaDeserializationFormatDescription	= 0x60000000;

	static const unsigned int typeId_Image			= 0;
	static const unsigned int typeId_Sound			= 1;
	static const unsigned int typeId_Scene			= 2;
	static const unsigned int typeId_GraphicsDevice	= 3;
	static const unsigned int typeId_AudioDevice	= 4;
	static const unsigned int typeId_FileSystem		= 5;

	MwDispatcher(void);
	virtual ~MwDispatcher(void);

	// Requests information about the dispatched object. The requested is specified by the infoId parameter, and depending on it, the infoTag parameter may have to be used. If the requested information is availabe, it is filled in the info parameter and the method returns true, otherwise returns false.
	// infoId - Specifies what information is requested
	// infoTag - An additional parameter, used for some infoIds. Depending on which infoId is used, the infoTag may or may not have a specific meaning.
	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info) = 0;
	// Creates an instance of the dispatched object.
	virtual void *CreateObject() = 0;
};

