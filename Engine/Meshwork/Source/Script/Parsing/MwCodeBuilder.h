#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwStack.h"

#include "..\..\Tools\Streams\MwBaseStream.h"
#include "..\..\Tools\Streams\MwMemoryStream.h"

#include "MwScriptTokens.h"
#include "MwScriptDataTypes.h"
#include "MwScriptIdentifiers.h"

#include "..\Processing\MwCodeProcessor.h"

class MwScriptExpression;

struct MwScriptTokenToOperationMapping
{
	int tokenId, iOperationId, fOperationId;
	bool isAssignmentOperation, singleArgument;

	MwScriptTokenToOperationMapping(int tokenId, int iOperationId, int fOperationId, bool isAssignmentOperation, bool singleArgument);
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwScriptTokenToOperationMapping*>;

class MWDLLCLASS MwCodeBuilder
{
public:
	int tokenId_LeftBracket,
		tokenId_RightBracket,
		tokenId_Comma,
		tokenId_Point,
		tokenId_SemiColon,
		tokenId_Question,
		tokenId_Set,
		tokenId_Add,
		tokenId_Sub,
		tokenId_Mul,
		tokenId_Div,
		tokenId_Mod,
		tokenId_SubSub,
		tokenId_AddAdd,
		tokenId_Shl,
		tokenId_Shr,
		tokenId_AddEquals,
		tokenId_SubEquals,
		tokenId_Equal,
		tokenId_NotEqual,
		tokenId_GreaterEqual,
		tokenId_LesserEqual,
		tokenId_Greater,
		tokenId_Lesser,
		tokenId_LogicalNot,
		tokenId_LogicalAnd,
		tokenId_LogicalOr,
		tokenId_BinNot,
		tokenId_BinAnd,
		tokenId_BinOr,
		tokenId_BinXor,
		tokenId_MulEquals,
		tokenId_DivEquals,
		tokenId_XorEquals,
		tokenId_OrEquals,
		tokenId_AndEquals,
		tokenId_LeftBracket_Big,
		tokenId_RightBracket_Big,
		tokenId_Colon,
		tokenId_ModEquals,
		tokenId_LeftIndexBracket,
		tokenId_RightIndexBracket;

	MwScriptDataType
		*dataType, // the current data type for operations
		*dataType_int,
		*dataType_float;

	MwScriptTokens tokens;
	int tokenIndex;
	MwScriptToken *invalidToken;
	MwList<MwScriptTokenToOperationMapping*> tokenToOperationMapping;

	MwStack<int> tokenRanges;

	MwScriptDataTypes dataTypes;
	MwScriptIdentifiers identifiers;
	MwMemoryStream *code;
	
	MwCodeProcessor *processor;

	MwCodeBuilder(void);
	~MwCodeBuilder(void);

	// Locks a range of tokens that can be processed starting with the first and ending with the given index
	void LockTokenRange(int lastTokenIndex);
	// Unlocks a previously locked token range. After calling this method, the current range will be the one before calling LockTokenRange
	void UnlockTokenRange();
	// Returns the token at the current tokenIndex. If tokenIndex is invalid, returns a pointer to invalidToken
	MwScriptToken *GetToken(int peekOffset = 0);
	
	// Searches tokens from startToken to endToken for a token of an evaluation operaion with the least priority. Used for evaluating expressions with operations of different proirity. Returns -1 if fails to find any such token
	int FindTokenEvaluationOperationByPriority(int startToken, int endToken, int &operationId);
	// Returns the assignment operationId matching the given tokenId. If none is found, return -1
	int GetTokenAssignmentOperation();
	
	// Sets a code processor. The processor is needed int order to map its operaionIds with the tokenIds. No processing of alteration of the processor is done.
	void SetProcessor(MwCodeProcessor *processor);

	// Builds the give sourceCode into executable script code in output. Returns true if succeeds or false otherwuse.
	bool Build(MwBaseStream *output, MwString sourceCode);
};

