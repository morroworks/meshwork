#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwList.h"

#include "..\..\..\Graphics\MwGraphicsDevice.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\Primitive\MwRenderState.h"

#include "..\..\Properties\MwBoundProperty.h"

#include "MwMaterialShaderSlot.h"

struct MwMaterialShadingPropertyInfo
{
	int propertyIndex, shadingParameterIndex;
	MwString shadingParameterName;
};

class Meshwork;

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwMaterialShaderSlot>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwRenderState>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwMaterialShadingPropertyInfo>;

class MWDLLCLASS MwMaterial
	: public MwBaseResource
{
private:
	static const unsigned int SerializationId_ShaderSlots		= 0x21111003;
	static const unsigned int SerializationId_ShaderSlot		= 0x21111103;
	static const unsigned int SerializationId_ShaderOp			= 0x21111113;
	static const unsigned int SerializationId_ColorOp			= 0x21111123;
	static const unsigned int SerializationId_RenderStates		= 0x21112003;
	static const unsigned int SerializationId_RenderState		= 0x21112103;

public:
	static const int classId = (MwResourceType_Material << 16) | 0;

	static const int propertyIndex_OverrideMaterials = 0;

	Meshwork *context;

	MwDeviceShader *deviceShader;
    
	MwList<MwMaterialShadingPropertyInfo> shadingProperties;

	MwList<MwMaterialShaderSlot> shaderSlots;
    MwList<MwRenderState> renderStates;
    int lightSourcesCount;
	bool isAnimated;
	bool successfullyCompiled;
	MwString compilationMessage;

    bool updateState;

	int paramAddressWorldMatrix, paramAddressViewMatrix, paramAddressProjectionMatrix,
		paramAddressViewPosition,
		paramAddressLightsPos, paramAddressLightsColor, paramAddressLightsIntensity, paramAddressActiveLightsCount, paramAddressAmbientLight;

	MwMaterial(Meshwork &context);

	~MwMaterial(void);

    void CommitRenderStates();
    void InsertShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp, int index);
    int AddShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp);
    void RemoveShaderSlot(int index);
    void MoveShaderSlot(int originalIndex, int newIndex);
    void ClearShaderSlots();

	bool UpdateShader();

    // Applies to the device shader a parameter of the material
	void ApplyProperty(MwBoundProperty *materialProperty);
    // Applies to the device shader all parameters of the material
    void ApplyProperties();
    // Applies to the device shader lights from the context which are nearest to the given location and with respect to the number of light sources in the shader
	void ApplyLights(MwVector3 &location);
    // Applies to the device shader bones from the context and with respect to whether the shader has animation
	void ApplyBones();

	virtual bool Deserialize(MwBaseStream &source);

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

