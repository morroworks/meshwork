#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\Primitive\MwBounds.h"
#include "..\..\Primitive\MwIntersectionInfo.h"

#include "..\..\..\Graphics\MwGraphicsDevice.h"

// TODO: Remove this. See the "bones" member variable. Maybe use a new "MwSkeleton" resource
#include "..\..\..\Tools\MwList.h"
#include "..\Transform\MwTransform.h"

class Meshwork;

class MWDLLCLASS MwMesh
	: public MwBaseResource
{
private:
	static const unsigned int SerializationId_Vertices	= 0x21111004;
	static const unsigned int SerializationId_Normals	= 0x21112004;
	static const unsigned int SerializationId_TexCoords	= 0x21113004;
	static const unsigned int SerializationId_Triangles	= 0x21114004;
	static const unsigned int SerializationId_Bones		= 0x21115004;

	void SerializeVector2(MwBaseStream &stream, MwVector2 &vector);
	MwVector2 DeserializeVector2(MwBaseStream &stream);

	void SerializeVector3(MwBaseStream &stream, MwVector3 &vector);
	MwVector3 DeserializeVector3(MwBaseStream &stream);

	void SerializeVector4(MwBaseStream &stream, MwVector4 &vector);
	MwVector4 DeserializeVector4(MwBaseStream &stream);

public:
	static const int classId = (MwResourceType_Mesh << 16) | 0;

	// TODO: Use false for screen quad and other special cases. Remove in future, replace by a 2D management system
	static const int propertyIndex_Cull = 0;

	MwDeviceMesh *deviceMesh;

	MwBounds bounds;

	bool active;

	MwMesh(Meshwork &context);
	~MwMesh(void);

    void ComputeNormals();
    void ComputeBounds();
    bool Intersection(MwVector3 &rayPoint, MwVector3 &rayDir, MwIntersectionInfo &intersectionInfo);

	void CopyFrom(MwMesh &source);

	virtual bool Deserialize(MwBaseStream &source);

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};
