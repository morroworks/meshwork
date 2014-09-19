#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwList.h"
#include "..\..\Tools\Streams\MwBaseStream.h"

class MwCodeProcessor;

typedef void (*MwCodeProcessorOperation) (MwCodeProcessor *context);

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwCodeProcessorOperation>;


class MWDLLCLASS MwCodeProcessor
{
private:
	static void Operation_JMP						(MwCodeProcessor *context);
	static void Operation_JZ						(MwCodeProcessor *context);
	static void Operation_JNZ						(MwCodeProcessor *context);
	static void Operation_Call						(MwCodeProcessor *context);
	static void Operation_RET						(MwCodeProcessor *context);
	static void Operation_CallOut					(MwCodeProcessor *context);
	
	// Integer
	static void Operation_IToF						(MwCodeProcessor *context);
	static void Operation_IPushAddress				(MwCodeProcessor *context);
	static void Operation_IPushIndexedAddress		(MwCodeProcessor *context);
	static void Operation_IPushAddressValue			(MwCodeProcessor *context);
	static void Operation_IPushIndexedAddressValue	(MwCodeProcessor *context);
	// Evaluation
	static void Operation_INot						(MwCodeProcessor *context);
	static void Operation_IAnd						(MwCodeProcessor *context);
	static void Operation_IOr						(MwCodeProcessor *context);
	static void Operation_IXor						(MwCodeProcessor *context);
	static void Operation_IShl						(MwCodeProcessor *context);
	static void Operation_IShr						(MwCodeProcessor *context);
	static void Operation_IDiv						(MwCodeProcessor *context);
	static void Operation_IMod						(MwCodeProcessor *context);
	static void Operation_IMul						(MwCodeProcessor *context);
	static void Operation_ISub						(MwCodeProcessor *context);
	static void Operation_IAdd						(MwCodeProcessor *context);
	static void Operation_ILogicalNot				(MwCodeProcessor *context);
	static void Operation_ILogicalAnd				(MwCodeProcessor *context);
	static void Operation_ILogicalOr				(MwCodeProcessor *context);
	static void Operation_IGreater					(MwCodeProcessor *context);
	static void Operation_ILesser					(MwCodeProcessor *context);
	static void Operation_IEqual					(MwCodeProcessor *context);
	static void Operation_INotEqual					(MwCodeProcessor *context);
	static void Operation_IGreaterEqual				(MwCodeProcessor *context);
	static void Operation_ILesserEqual				(MwCodeProcessor *context);
	// Assignment
	static void Operation_ISet						(MwCodeProcessor *context);
	static void Operation_IAddAdd					(MwCodeProcessor *context);
	static void Operation_ISubSub					(MwCodeProcessor *context);
	static void Operation_IAddEquals				(MwCodeProcessor *context);
	static void Operation_ISubEquals				(MwCodeProcessor *context);
	static void Operation_IMulEquals				(MwCodeProcessor *context);
	static void Operation_IModEquals				(MwCodeProcessor *context);
	static void Operation_IDivEquals				(MwCodeProcessor *context);
	static void Operation_IXorEquals				(MwCodeProcessor *context);
	static void Operation_IOrEquals					(MwCodeProcessor *context);
	static void Operation_IAndEquals				(MwCodeProcessor *context);
	
	// Floating point
	static void Operation_FToI						(MwCodeProcessor *context);
	static void Operation_FPushAddress				(MwCodeProcessor *context);
	static void Operation_FPushIndexedAddress		(MwCodeProcessor *context);
	static void Operation_FPushAddressValue			(MwCodeProcessor *context);
	static void Operation_FPushIndexedAddressValue	(MwCodeProcessor *context);
	// Evaluations
	static void Operation_FGreater					(MwCodeProcessor *context);
	static void Operation_FLesser					(MwCodeProcessor *context);
	static void Operation_FEqual					(MwCodeProcessor *context);
	static void Operation_FNotEqual					(MwCodeProcessor *context);
	static void Operation_FGreaterEqual				(MwCodeProcessor *context);
	static void Operation_FLesserEqual				(MwCodeProcessor *context);
	static void Operation_FDiv						(MwCodeProcessor *context);
	static void Operation_FMul						(MwCodeProcessor *context);
	static void Operation_FSub						(MwCodeProcessor *context);
	static void Operation_FAdd						(MwCodeProcessor *context);
	// Assignment
	static void Operation_FSet						(MwCodeProcessor *context);
	static void Operation_FAddEquals				(MwCodeProcessor *context);
	static void Operation_FSubEquals				(MwCodeProcessor *context);
	static void Operation_FMulEquals				(MwCodeProcessor *context);
	static void Operation_FDivEquals				(MwCodeProcessor *context);


public: // public only for debugging. make private
	void *stack;
	int stackCapacity, stackPos;

	void EnsureStackCapacity(int capacity);
	
	void PushInt(int value);
	int PopInt();

	void PushFloat(float value);
	float PopFloat();

	int ReadAddressIntValue(int address);
	void WriteAddressIntValue(int address, int value);

	float ReadAddressFloatValue(int address);
	void WriteAddressFloatValue(int address, float value);

public:
	int 
		operationId_JMP,
		operationId_JZ,
		operationId_JNZ,
		operationId_Call,
		operationId_RET,
		operationId_CallOut,

		operationId_IToF,
		operationId_IPushAddress,
		operationId_IPushIndexedAddress,
		operationId_IPushAddressValue,
		operationId_IPushIndexedAddressValue,

		operationId_INot,		
		operationId_IAnd,		
		operationId_IOr,			
		operationId_IXor,		
		operationId_IShl,			
		operationId_IShr,			
		operationId_IDiv,			
		operationId_IMul,			
		operationId_IMod,			
		operationId_ISub,			
		operationId_IAdd,			
		operationId_ILogicalNot,		
		operationId_ILogicalAnd,		
		operationId_ILogicalOr,		
		operationId_IGreater,		
		operationId_ILesser,		
		operationId_IEqual,			
		operationId_INotEqual,		
		operationId_IGreaterEqual,	
		operationId_ILesserEqual,	
	
		operationId_ISet,			
		operationId_IAddAdd,		
		operationId_ISubSub,		
		operationId_IAddEquals,		
		operationId_ISubEquals,		
		operationId_IModEquals,
		operationId_IMulEquals,		
		operationId_IDivEquals,		
		operationId_IXorEquals,		
		operationId_IOrEquals,		
		operationId_IAndEquals,

		operationId_FToI,
		operationId_FPushAddress,
		operationId_FPushIndexedAddress,
		operationId_FPushAddressValue,
		operationId_FPushIndexedAddressValue,

		operationId_FDiv,			
		operationId_FMul,			
		operationId_FSub,			
		operationId_FAdd,			
		operationId_FGreater,		
		operationId_FLesser,		
		operationId_FEqual,			
		operationId_FNotEqual,		
		operationId_FGreaterEqual,	
		operationId_FLesserEqual,	
	
		operationId_FSet,			
		operationId_FAddEquals,		
		operationId_FSubEquals,		
		operationId_FMulEquals,		
		operationId_FDivEquals;

	MwList<MwCodeProcessorOperation> operations;

	MwBaseStream *memory;


	MwCodeProcessor(void);
	~MwCodeProcessor(void);

	// Adds an operation to the processor the returns the id given to that operation
	int AddOperation(MwCodeProcessorOperation operation);

	// Sets the memory which holds the code to be processed
	void SetMemory(MwBaseStream *memory);
	// Runs the code from memory
	void Process();

	// Called in a Callout operation, used for communication between script and native code
	virtual void OnCallout(int calloutId);
};

