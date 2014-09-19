#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwStrings.h"
#include "..\..\Tools\MwList.h"

#include "MwScriptToken.h"

class MWDLLCLASS MwScriptTokens :
	public MwList<MwScriptToken>
{
private:
	// Checks if a sign from the signSet is found at the given script position and returns its index. If not found, returns -1
	int FindSignIndex(int scriptPos);


public:
	MwString ignoreCharset;
	MwStrings signSet;

	MwString sourceCode;
	
	MwScriptTokens(void);
	~MwScriptTokens(void);

	// Adds a sign to be distinguished as a separate token in the script and returns its id.
	int AddSign(MwString sign);

	// Reads the tokens from the given script code and fills them in
	void Parse(MwString sourceCode);

	// Searches for the index of the bracket, closing the expression starting at startIndex.
	int FindClosingBracket(int closingBracketTokenId, int startIndex, int endIndex = -1);

	// Searches within startIndex and endIndex for the first token with the given code and returns its index. If not found returns -1
	int FindId(int startIndex, int endIndex, int tokenId);
};

