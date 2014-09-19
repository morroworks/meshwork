#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\MwScene.h"

class MWDLLCLASS MwNativeScene :
	public MwScene
{
public:
	MwNativeScene(void);
	~MwNativeScene(void);

	bool Load(MwBaseStream &source);
	bool Save(MwBaseStream &destination, const char *format);
};

