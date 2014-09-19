#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwFileSystem.h"

class MWDLLCLASS MwPhysicalFileSystem :
	public MwFileSystem
{
public:
	MwPhysicalFileSystem(void);
	~MwPhysicalFileSystem(void);

	MwBaseStream *OpenFile(MwString path);
	MwBaseStream *CreateNewFile(MwString path);

	virtual bool GetFileInfo(MwString path, MwFileInfo &result);
	virtual bool GetDirectoryContents(MwString path, MwList<MwFileInfo> &result);
};

