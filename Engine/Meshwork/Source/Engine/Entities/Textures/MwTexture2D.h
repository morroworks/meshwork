#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\..\Graphics\MwDeviceTexture2D.h"

#include "..\..\..\Media\Image\MwImage.h"
#include "..\..\..\Tools\Streams\MwBaseStream.h"
#include "..\..\..\Tools\MwString.h"

class Meshwork;

class MWDLLCLASS MwTexture2D :
	public MwBaseResource
{
private:
	static const unsigned int SerializationId_FileName	= 0x21111006;

	// held only for checking if the respective properties have changed value, in which case texture should be resized
	int width, height;

public:
	static const int classId = (MwResourceType_Texture << 16) | 0;

	static const int propertyIndex_Width = 0;
	static const int propertyIndex_Height = 1;

	Meshwork *context;
	MwDeviceTexture2D *deviceTexture;
	MwString fileName;

	MwTexture2D(Meshwork &context);
	~MwTexture2D(void);

	void Load(void *data, int width, int height);
	void Load(MwImage &sourceImage);
	bool Load(MwBaseStream &source);
	bool Load(MwString &fileName);

	MwImage *Read();

	void UpdateToProperties();

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

