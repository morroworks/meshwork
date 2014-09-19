#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Media\Image\MwImage.h"

#include "MwPlaneGeometry.h"

class MWDLLCLASS MwHeightMapGeometry
{
public:
	MwHeightMapGeometry(MwDeviceMesh &result, MwImage &map, float scale);
	~MwHeightMapGeometry(void);
};

