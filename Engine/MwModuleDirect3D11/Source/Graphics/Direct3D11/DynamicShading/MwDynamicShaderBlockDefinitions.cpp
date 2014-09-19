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

#include "MwDynamicShaderBlockDefinitions.h"


MwDynamicShaderBlockDefinitions::MwDynamicShaderBlockDefinitions(void)
{
}


MwDynamicShaderBlockDefinitions::~MwDynamicShaderBlockDefinitions(void)
{
	for (int i = 0; i < this->definitions.count; i++)
		delete this->definitions[i];
}

bool MwDynamicShaderBlockDefinitions::ProvideDefinition(MwString name, MwString code)
{
	if (name.length != 0)
		for (int i = 0; i < this->definitions.count; i++)
			if (this->definitions[i]->name.Equals(name))
				return false;

	MwDynamicShaderDefinition *definition = new MwDynamicShaderDefinition();
	definition->name = name;
	definition->code = code;
	this->definitions.Add(definition);

	return true;
}

MwString MwDynamicShaderBlockDefinitions::GetCode()
{
	MwString result;
	
	for (int i = 0; i < this->definitions.count; i++)
		result += this->definitions[i]->code + "\r\n";

	return MwString(result);
}
