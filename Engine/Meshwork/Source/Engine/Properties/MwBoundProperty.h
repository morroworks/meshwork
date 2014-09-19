#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwString.h"

#include "MwProperty.h"

class MWDLLCLASS MwBoundProperty
	: public MwProperty
{
public:
	MwString boundName;
    int boundIndex;

	MwBoundProperty(const MwString &shaderName, const MwString &name, int value);
	MwBoundProperty(const MwString &shaderName, const MwString &name, float value);
	MwBoundProperty(const MwString &shaderName, const MwString &name, bool value);
	MwBoundProperty(const MwString &shaderName, const MwString &name, const MwVector4 &value);
	MwBoundProperty(const MwString &shaderName, const MwString &name, MwParameterType type, void *value);
	virtual ~MwBoundProperty(void);
};

