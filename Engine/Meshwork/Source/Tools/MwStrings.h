#pragma once

#include "..\MwGlobals.h"

#include "MwString.h"
#include "MwList.h"

enum StringComparison
{
	StringComparison_CaseSensitive,
	StringComparison_CaseInsensitive
};

class MWDLLCLASS MwStrings
	: public MwList<MwString>
{
public:
	MwStrings(void);
	MwStrings(MwStrings *strings);
	~MwStrings(void);

	void SplitString(MwString &string, const MwString &splitter, bool ignoreEmpty = true);
	MwString ToString(const MwString &splitter = ",");

	int IndexOf(MwString &string, StringComparison comparisonMode = StringComparison_CaseSensitive);
};