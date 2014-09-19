#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwList.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<int>;

struct MwSubMeshFace
{
	MwList<int> indices;
};