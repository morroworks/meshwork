#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\Streams\MwBaseStream.h"
#include "..\..\..\..\Tools\MwList.h"
#include "..\..\..\..\Tools\MwStrings.h"
#include "..\..\..\..\Tools\MwDictionary.h"

#include "MwFileObjMesh.h"
#include "MwFileObjMaterial.h"


struct MwFileObjArgument
{
	int start, end;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjArgument>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjMesh*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjMaterial*>;

class MWDLLCLASS MwFileObj
{
private:
	// To avoid slow string processing, read all the file contents into one data buffer and process each separate file token directly from this buffer
	char* data;
	int dataSize, dataPos;
	MwList<MwFileObjArgument> arguments;
	int argumentsCount;

	bool ParseLine();

	bool ArgEquals(int argIndex, const char *str);
	bool ArgEquals(int arg1Index, MwFileObjArgument *arg2);
	bool DataEquals(int start, int end, const char *str);
	bool DataToInt(int pos, int &value);
	bool DataToFloat(int pos, float &value);
	int DataCharIndex(int start, int end, const char character);
	MwString DataCreateString(int startArgIndex, int endArgIndex);

	bool ReadTextureMap(MwFileObjTextureMap * texture);

public:
	MwList<MwFileObjMesh*> meshes;
	MwList<MwFileObjMaterial*> materials;
	MwStrings materialFiles;

	MwFileObj(void);
	~MwFileObj(void);

	bool Read(MwBaseStream *dataStream);
};
