#pragma once

#include "..\..\MwGlobals.h"

#include "MwParameter.h"
#include "..\..\Tools\MwString.h"

class MWDLLCLASS MwProperty
	: public MwParameter
{
public:
	MwString name;

	MwProperty(const MwString &name, int value);
	MwProperty(const MwString &name, float value);
	MwProperty(const MwString &name, bool value);
	MwProperty(const MwString &name, const MwVector4 &value);
	MwProperty(const MwString &name, MwParameterType type, void *value);
	virtual ~MwProperty(void);
};

