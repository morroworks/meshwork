#pragma once

#include "..\..\..\MeshworkEngine.h"

class MwILImage :
	public MwImage
{
private:
	class Initialization
	{
	public:
		Initialization(void);
	};

	static Initialization initialization;

	void *imageId_ILuint;

public:
	MwILImage(void);
	~MwILImage(void);

	bool Load(MwBaseStream &source);
	bool Save(MwBaseStream &destination, const char *format);
};

