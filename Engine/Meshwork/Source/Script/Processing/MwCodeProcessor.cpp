//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwCodeProcessor.h"

#include "..\..\Tools\MwMem.h"

void MwCodeProcessor::Operation_JMP(MwCodeProcessor *context)
{
    int jumpOffset = context->memory->ReadInt32();
	context->memory->Seek(jumpOffset, StreamSeekMode_Relative);
}

void MwCodeProcessor::Operation_JZ(MwCodeProcessor *context)
{
    int condition = context->PopInt();
    int jumpOffset = context->memory->ReadInt32();
    if (condition == 0)
        context->memory->Seek(jumpOffset, StreamSeekMode_Relative);
}

void MwCodeProcessor::Operation_JNZ(MwCodeProcessor *context)
{
    int condition = context->PopInt();
    int jumpOffset = context->memory->ReadInt32();
    if (condition != 0)
        context->memory->Seek(jumpOffset, StreamSeekMode_Relative);
}

void MwCodeProcessor::Operation_Call(MwCodeProcessor *context)
{
	int currentAddress = (int)context->memory->position;
    int jumpOffset = context->memory->ReadInt32();
    context->PushInt(currentAddress);
    context->memory->Seek(jumpOffset, StreamSeekMode_Relative);
}

void MwCodeProcessor::Operation_CallOut(MwCodeProcessor *context)
{
    int calloutId = context->memory->ReadInt32();
    context->OnCallout(calloutId);
}

void MwCodeProcessor::Operation_RET(MwCodeProcessor *context)
{
    int returnOffset = context->PopInt();
    context->memory->Seek(returnOffset, StreamSeekMode_Relative);
}

// Integer operations

void MwCodeProcessor::Operation_IToF(MwCodeProcessor *context)
{
	context->PushFloat((float)context->PopInt());
}

void MwCodeProcessor::Operation_IPushAddress(MwCodeProcessor *context)
{
    context->PushInt(context->memory->ReadInt32());
}

void MwCodeProcessor::Operation_IPushIndexedAddress(MwCodeProcessor *context)
{
    int offset = context->PopInt();
    context->PushInt(context->memory->ReadInt32() + offset * 4);
}

void MwCodeProcessor::Operation_IPushAddressValue(MwCodeProcessor *context)
{
    context->PushInt(context->ReadAddressIntValue(context->memory->ReadInt32()));
}

void MwCodeProcessor::Operation_IPushIndexedAddressValue(MwCodeProcessor *context)
{
    int offset = context->PopInt();
    context->PushInt(context->ReadAddressIntValue(context->memory->ReadInt32() + offset * 4));
}


// Evaluation operations

void MwCodeProcessor::Operation_INot(MwCodeProcessor *context)
{
    int a = context->PopInt();
    context->PushInt(~a);
}

void MwCodeProcessor::Operation_IAnd(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a & b);
}

void MwCodeProcessor::Operation_IOr(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a | b);
}

void MwCodeProcessor::Operation_IXor(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a ^ b);
}

void MwCodeProcessor::Operation_IShl(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a << b);
}

void MwCodeProcessor::Operation_IShr(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a >> b);
}

void MwCodeProcessor::Operation_IDiv(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a / b);
}

void MwCodeProcessor::Operation_IMod(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a % b);
}

void MwCodeProcessor::Operation_IMul(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a * b);
}

void MwCodeProcessor::Operation_ISub(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a - b);
}

void MwCodeProcessor::Operation_IAdd(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(a + b);
}

void MwCodeProcessor::Operation_ILogicalNot(MwCodeProcessor *context)
{
    int a = context->PopInt();
    context->PushInt(a == 0 ? 1 : 0);
}

void MwCodeProcessor::Operation_ILogicalAnd(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt(((a != 0) && (b != 0)) ? 1 : 0);
}

void MwCodeProcessor::Operation_ILogicalOr(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a | b) != 0 ? 1 : 0);
}

void MwCodeProcessor::Operation_IGreater(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a > b) ? 1 : 0);
}

void MwCodeProcessor::Operation_ILesser(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a < b) ? 1 : 0);
}

void MwCodeProcessor::Operation_IEqual(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a == b) ? 1 : 0);
}

void MwCodeProcessor::Operation_INotEqual(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a != b) ? 1 : 0);
}

void MwCodeProcessor::Operation_IGreaterEqual(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a >= b) ? 1 : 0);
}

void MwCodeProcessor::Operation_ILesserEqual(MwCodeProcessor *context)
{
    int a = context->PopInt();
    int b = context->PopInt();
    context->PushInt((a <= b) ? 1 : 0);
}

// Assignment operations

void MwCodeProcessor::Operation_ISet(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, value);
}

void MwCodeProcessor::Operation_IAddAdd(MwCodeProcessor *context)
{
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) + 1);
}

void MwCodeProcessor::Operation_ISubSub(MwCodeProcessor *context)
{
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) - 1);
}

void MwCodeProcessor::Operation_IAddEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) + value);
}

void MwCodeProcessor::Operation_ISubEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) - value);
}

void MwCodeProcessor::Operation_IMulEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) * value);
}

void MwCodeProcessor::Operation_IModEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) % value);
}

void MwCodeProcessor::Operation_IDivEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) / value);
}

void MwCodeProcessor::Operation_IXorEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) ^ value);
}

void MwCodeProcessor::Operation_IOrEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) | value);
}

void MwCodeProcessor::Operation_IAndEquals(MwCodeProcessor *context)
{
    int value = context->PopInt();
    int address = context->PopInt();
    context->WriteAddressIntValue(address, context->ReadAddressIntValue(address) & value);
}

// Floating point operaions

void MwCodeProcessor::Operation_FToI(MwCodeProcessor *context)
{
	context->PushInt((int)context->PopFloat());
}

void MwCodeProcessor::Operation_FPushAddress(MwCodeProcessor *context)
{
    context->PushInt(context->memory->ReadInt32());
}

void MwCodeProcessor::Operation_FPushIndexedAddress(MwCodeProcessor *context)
{
    int offset = context->PopInt();
    context->PushInt(context->memory->ReadInt32() + offset * 4);
}

void MwCodeProcessor::Operation_FPushAddressValue(MwCodeProcessor *context)
{
    context->PushFloat(context->ReadAddressFloatValue(context->memory->ReadInt32()));
}

void MwCodeProcessor::Operation_FPushIndexedAddressValue(MwCodeProcessor *context)
{
    int offset = (int)context->PopInt();
    context->PushFloat(context->ReadAddressFloatValue(context->memory->ReadInt32() + offset * 4));
}

// Evaluation operations

void MwCodeProcessor::Operation_FDiv(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushFloat(a / b);
}

void MwCodeProcessor::Operation_FMul(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushFloat(a * b);
}

void MwCodeProcessor::Operation_FSub(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushFloat(a - b);
}

void MwCodeProcessor::Operation_FAdd(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushFloat(a + b);
}

void MwCodeProcessor::Operation_FGreater(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a > b) ? 1 : 0);
}

void MwCodeProcessor::Operation_FLesser(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a < b) ? 1 : 0);
}

void MwCodeProcessor::Operation_FEqual(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a == b) ? 1 : 0);
}

void MwCodeProcessor::Operation_FNotEqual(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a != b) ? 1 : 0);
}

void MwCodeProcessor::Operation_FGreaterEqual(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a >= b) ? 1 : 0);
}

void MwCodeProcessor::Operation_FLesserEqual(MwCodeProcessor *context)
{
	float a = context->PopFloat();
    float b = context->PopFloat();
    context->PushInt((a <= b) ? 1 : 0);
}

// Assignment operations

void MwCodeProcessor::Operation_FSet(MwCodeProcessor *context)
{
    float value = context->PopFloat();
    int address = context->PopInt();
    context->WriteAddressFloatValue(address, value);
}

void MwCodeProcessor::Operation_FAddEquals(MwCodeProcessor *context)
{
    float value = context->PopFloat();
    int address = context->PopInt();
    context->WriteAddressFloatValue(address, context->ReadAddressFloatValue(address) + value);
}

void MwCodeProcessor::Operation_FSubEquals(MwCodeProcessor *context)
{
    float value = context->PopFloat();
    int address = context->PopInt();
    context->WriteAddressFloatValue(address, context->ReadAddressFloatValue(address) - value);
}

void MwCodeProcessor::Operation_FMulEquals(MwCodeProcessor *context)
{
    float value = context->PopFloat();
    int address = context->PopInt();
    context->WriteAddressFloatValue(address, context->ReadAddressFloatValue(address) * value);
}

void MwCodeProcessor::Operation_FDivEquals(MwCodeProcessor *context)
{
    float value = context->PopFloat();
    int address = context->PopInt();
    context->WriteAddressFloatValue(address, context->ReadAddressFloatValue(address) / value);
}

MwCodeProcessor::MwCodeProcessor(void)
{
	this->operationId_JMP						= this->AddOperation(MwCodeProcessor::Operation_JMP							);
	this->operationId_JZ						= this->AddOperation(MwCodeProcessor::Operation_JZ							);
	this->operationId_JNZ						= this->AddOperation(MwCodeProcessor::Operation_JNZ							);
	this->operationId_Call						= this->AddOperation(MwCodeProcessor::Operation_Call						);
	this->operationId_RET						= this->AddOperation(MwCodeProcessor::Operation_RET							);
	this->operationId_CallOut					= this->AddOperation(MwCodeProcessor::Operation_CallOut						);
	
	// Integer
	this->operationId_IToF						= this->AddOperation(MwCodeProcessor::Operation_IToF						);
	this->operationId_IPushAddress				= this->AddOperation(MwCodeProcessor::Operation_IPushAddress				);
	this->operationId_IPushIndexedAddress		= this->AddOperation(MwCodeProcessor::Operation_IPushIndexedAddress			);
	this->operationId_IPushAddressValue			= this->AddOperation(MwCodeProcessor::Operation_IPushAddressValue			);
	this->operationId_IPushIndexedAddressValue	= this->AddOperation(MwCodeProcessor::Operation_IPushIndexedAddressValue	);
	// Evaluation
	this->operationId_INot						= this->AddOperation(MwCodeProcessor::Operation_INot						);
	this->operationId_IAnd						= this->AddOperation(MwCodeProcessor::Operation_IAnd						);
	this->operationId_IOr						= this->AddOperation(MwCodeProcessor::Operation_IOr							);
	this->operationId_IXor						= this->AddOperation(MwCodeProcessor::Operation_IXor						);
	this->operationId_IShl						= this->AddOperation(MwCodeProcessor::Operation_IShl						);
	this->operationId_IShr						= this->AddOperation(MwCodeProcessor::Operation_IShr						);
	this->operationId_IDiv						= this->AddOperation(MwCodeProcessor::Operation_IDiv						);
	this->operationId_IMod						= this->AddOperation(MwCodeProcessor::Operation_IMod						);
	this->operationId_IMul						= this->AddOperation(MwCodeProcessor::Operation_IMul						);
	this->operationId_ISub						= this->AddOperation(MwCodeProcessor::Operation_ISub						);
	this->operationId_IAdd						= this->AddOperation(MwCodeProcessor::Operation_IAdd						);
	this->operationId_ILogicalNot				= this->AddOperation(MwCodeProcessor::Operation_ILogicalNot					);
	this->operationId_ILogicalAnd				= this->AddOperation(MwCodeProcessor::Operation_ILogicalAnd					);
	this->operationId_ILogicalOr				= this->AddOperation(MwCodeProcessor::Operation_ILogicalOr					);
	this->operationId_IGreater					= this->AddOperation(MwCodeProcessor::Operation_IGreater					);
	this->operationId_ILesser					= this->AddOperation(MwCodeProcessor::Operation_ILesser						);
	this->operationId_IEqual					= this->AddOperation(MwCodeProcessor::Operation_IEqual						);
	this->operationId_INotEqual					= this->AddOperation(MwCodeProcessor::Operation_INotEqual					);
	this->operationId_IGreaterEqual				= this->AddOperation(MwCodeProcessor::Operation_IGreaterEqual				);
	this->operationId_ILesserEqual				= this->AddOperation(MwCodeProcessor::Operation_ILesserEqual				);
	// Assignment	
	this->operationId_ISet						= this->AddOperation(MwCodeProcessor::Operation_ISet						);
	this->operationId_IAddAdd					= this->AddOperation(MwCodeProcessor::Operation_IAddAdd						);
	this->operationId_ISubSub					= this->AddOperation(MwCodeProcessor::Operation_ISubSub						);
	this->operationId_IAddEquals				= this->AddOperation(MwCodeProcessor::Operation_IAddEquals					);
	this->operationId_ISubEquals				= this->AddOperation(MwCodeProcessor::Operation_ISubEquals					);
	this->operationId_IMulEquals				= this->AddOperation(MwCodeProcessor::Operation_IMulEquals					);
	this->operationId_IModEquals				= this->AddOperation(MwCodeProcessor::Operation_IModEquals					);
	this->operationId_IDivEquals				= this->AddOperation(MwCodeProcessor::Operation_IDivEquals					);
	this->operationId_IXorEquals				= this->AddOperation(MwCodeProcessor::Operation_IXorEquals					);
	this->operationId_IOrEquals					= this->AddOperation(MwCodeProcessor::Operation_IOrEquals					);
	this->operationId_IAndEquals				= this->AddOperation(MwCodeProcessor::Operation_IAndEquals					);
	
	// Floating point
	this->operationId_FToI						= this->AddOperation(MwCodeProcessor::Operation_FToI						);
	this->operationId_FPushAddress				= this->AddOperation(MwCodeProcessor::Operation_FPushAddress				);
	this->operationId_FPushIndexedAddress		= this->AddOperation(MwCodeProcessor::Operation_FPushIndexedAddress			);
	this->operationId_FPushAddressValue			= this->AddOperation(MwCodeProcessor::Operation_FPushAddressValue			);
	this->operationId_FPushIndexedAddressValue	= this->AddOperation(MwCodeProcessor::Operation_FPushIndexedAddressValue	);
	// Evaluation
	this->operationId_FDiv						= this->AddOperation(MwCodeProcessor::Operation_FDiv						);
	this->operationId_FMul						= this->AddOperation(MwCodeProcessor::Operation_FMul						);
	this->operationId_FSub						= this->AddOperation(MwCodeProcessor::Operation_FSub						);
	this->operationId_FAdd						= this->AddOperation(MwCodeProcessor::Operation_FAdd						);
	this->operationId_FGreater					= this->AddOperation(MwCodeProcessor::Operation_FGreater					);
	this->operationId_FLesser					= this->AddOperation(MwCodeProcessor::Operation_FLesser						);
	this->operationId_FEqual					= this->AddOperation(MwCodeProcessor::Operation_FEqual						);
	this->operationId_FNotEqual					= this->AddOperation(MwCodeProcessor::Operation_FNotEqual					);
	this->operationId_FGreaterEqual				= this->AddOperation(MwCodeProcessor::Operation_FGreaterEqual				);
	this->operationId_FLesserEqual				= this->AddOperation(MwCodeProcessor::Operation_FLesserEqual				);
	// Assignment	
	this->operationId_FSet						= this->AddOperation(MwCodeProcessor::Operation_FSet						);
	this->operationId_FAddEquals				= this->AddOperation(MwCodeProcessor::Operation_FAddEquals					);
	this->operationId_FSubEquals				= this->AddOperation(MwCodeProcessor::Operation_FSubEquals					);
	this->operationId_FMulEquals				= this->AddOperation(MwCodeProcessor::Operation_FMulEquals					);
	this->operationId_FDivEquals				= this->AddOperation(MwCodeProcessor::Operation_FDivEquals					);

	this->stackCapacity = 0;
	this->stackPos = 0;
	this->stack = 0;
	this->EnsureStackCapacity(256);
}


MwCodeProcessor::~MwCodeProcessor(void)
{
	MwMem::FreeAndNull(&this->stack);
}

void MwCodeProcessor::EnsureStackCapacity(int capacity)
{
	if (this->stackCapacity >= capacity)
		return;

	if (this->stackCapacity <= 0)
		this->stackCapacity = 1;
		
	while (this->stackCapacity < capacity)
		this->stackCapacity *= 2;

	void *newStack = MwMem::Get(capacity);
	MwMem::Copy(newStack, this->stack, this->stackPos);
	MwMem::FreeAndNull(&this->stack);
	this->stack = newStack;
	this->stackCapacity = capacity;
}

void MwCodeProcessor::PushInt(int value)
{
	this->EnsureStackCapacity(this->stackPos + 4);

	*(int*)((int)this->stack + this->stackPos) = value;
	this->stackPos += 4;
}

int MwCodeProcessor::PopInt()
{
	this->stackPos -= 4;
	int result = *(int*)((int)this->stack + this->stackPos);
	return result;
}

void MwCodeProcessor::PushFloat(float value)
{
	this->EnsureStackCapacity(this->stackPos + 4);

	*(float*)((int)this->stack + this->stackPos) = value;
	this->stackPos += 4;
}

float MwCodeProcessor::PopFloat()
{
	this->stackPos -= 4;
	float result = *(float*)((int)this->stack + this->stackPos);
	return result;
}

int MwCodeProcessor::ReadAddressIntValue(int address)
{
	long long oldPosition = this->memory->position;

	this->memory->Seek(address);
	int result = this->memory->ReadInt32();

	this->memory->Seek(oldPosition);

	return result;
}

void MwCodeProcessor::WriteAddressIntValue(int address, int value)
{
	long long oldPosition = this->memory->position;

	this->memory->Seek(address);
	this->memory->WriteInt32(value);

	this->memory->Seek(oldPosition);
}

float MwCodeProcessor::ReadAddressFloatValue(int address)
{
	long long oldPosition = this->memory->position;

	this->memory->Seek(address);
	float result = this->memory->ReadFloat();

	this->memory->Seek(oldPosition);

	return result;
}

void MwCodeProcessor::WriteAddressFloatValue(int address, float value)
{
	long long oldPosition = this->memory->position;

	this->memory->Seek(address);
	this->memory->WriteFloat(value);

	this->memory->Seek(oldPosition);
}

int MwCodeProcessor::AddOperation(MwCodeProcessorOperation operation)
{
	this->operations.Add(operation);
	return this->operations.count - 1;
}

void MwCodeProcessor::SetMemory(MwBaseStream *memory)
{
	this->memory = memory;
}

void MwCodeProcessor::Process()
{
	while (this->memory->position < this->memory->length)
	{
		unsigned char operationId = this->memory->ReadUInt8();

		this->operations[operationId](this);
	}
}

void MwCodeProcessor::OnCallout(int calloutId)
{
}