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

#include "MwParameter.h"

#include "MwParameterType.h"

#include "..\Entities\Mechanisms\MwBaseMechanism.h"

#include "..\Primitive\MwVector3.h"
#include "..\Primitive\MwVector4.h"

MwParameter *MwParameter::GetEffectiveParameter(MwParameter *parameter)
{
    if (parameter->type == MwParameterType_ReferenceMechanism)
    {
        return MwParameter::GetEffectiveParameter(&((MwBaseMechanism*)parameter->value)->parameter);
    }
    else
        return parameter;
}

MwParameter::MwParameter(void)
{
	this->type = MwParameterType_None;
	this->value = 0;
}

MwParameter::MwParameter(int value)
{
	this->type = MwParameterType_None;
	this->value = 0;

	this->SetInt(value);
}

MwParameter::MwParameter(float value)
{
	this->type = MwParameterType_None;
	this->value = 0;

	this->SetFloat(value);
}

MwParameter::MwParameter(bool value)
{
	this->type = MwParameterType_None;
	this->value = 0;

	this->SetBool(value);
}

MwParameter::MwParameter(const MwVector4 &value)
{
	this->type = MwParameterType_None;
	this->value = 0;

	this->SetColor(value);
}

MwParameter::MwParameter(MwParameterType type, void *value)
{
	this->type = MwParameterType_None;
	this->value = 0;

	this->SetReference(type, value);
}
    
MwParameter::~MwParameter(void)
{
	this->DisposeValue();
}

void MwParameter::DisposeValue()
{
	if (this->value == 0)
		return;

	switch (this->type)
	{
		case MwParameterType_Int:
		case MwParameterType_Float:
		case MwParameterType_Bool:
		case MwParameterType_Color:
		{
			// Only non-reference types have allocated memory and are to be deleted
			delete this->value;
			break;
		}
	}

	this->value = 0;
}

MwParameter *MwParameter::GetEffectiveParameter()
{
    return MwParameter::GetEffectiveParameter(this);
}

void MwParameter::RecallEffectiveParameter()
{
	MwParameter *parameter = this->GetEffectiveParameter();

	if (parameter != this)
		this->SetValue(parameter->type, parameter->value);
}

void MwParameter::SetType(MwParameterType type)
{
	if (this->type == type)
		return;

	this->DisposeValue();

	switch (type)
	{
		case MwParameterType_Int:
		{
			this->value = new int();
			break;
		}

		case MwParameterType_Float:
		{
			this->value = new float();
			break;
		}

		case MwParameterType_Bool:
		{
			this->value = new bool();
			break;
		}

		case MwParameterType_Color:
		{
			this->value = new MwVector4();
			break;
		}
	}

	this->type = type;
}

void MwParameter::SetReference(MwParameterType type, void *value)
{
	this->SetType(type);
	this->value = value;
}

void MwParameter::SetValue(MwParameterType type, void *value)
{
	this->SetType(type);
	
	switch (type)
	{
		case MwParameterType_Int:
		{
			this->SetInt(*(int*)value);
			break;
		}

		case MwParameterType_Float:
		{
			this->SetFloat(*(float*)value);
			break;
		}

		case MwParameterType_Bool:
		{
			this->SetBool(*(bool*)value);
			break;
		}

		case MwParameterType_Color:
		{
			this->SetColor(*(MwVector4*)value);
			break;
		}

		default:
		{
			this->SetReference(type, value);
		}
	}
}

void *MwParameter::GetEffectiveValue()
{
	return this->GetEffectiveParameter()->value;
}

void MwParameter::SetInt(int value)
{
	this->SetType(MwParameterType_Int);
	*(int*)this->value = value;
}

int MwParameter::GetInt()
{
	return *(int*)this->GetEffectiveParameter()->value;
}

void MwParameter::SetFloat(float value)
{
	this->SetType(MwParameterType_Float);
	*(float*)this->value = value;
}

float MwParameter::GetFloat()
{
	return *(float*)this->GetEffectiveParameter()->value;
}

void MwParameter::SetBool(bool value)
{
	this->SetType(MwParameterType_Bool);
	*(bool*)this->value = value;
}

bool MwParameter::GetBool()
{
	return *(bool*)this->GetEffectiveParameter()->value;
}

void MwParameter::SetColor(const MwVector4 &value)
{
	this->SetType(MwParameterType_Color);
	*(MwVector4*)this->value = value;
}

MwVector4 MwParameter::GetColor()
{
	return *(MwVector4*)this->GetEffectiveParameter()->value;
}