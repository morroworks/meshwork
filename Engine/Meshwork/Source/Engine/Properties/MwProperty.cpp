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

#include "MwProperty.h"

MwProperty::MwProperty(const MwString &name, int value)
	: MwParameter(value)
{
	this->name = name;
}

MwProperty::MwProperty(const MwString &name, float value)
	: MwParameter(value)
{
	this->name = name;
}

MwProperty::MwProperty(const MwString &name, bool value)
	: MwParameter(value)
{
	this->name = name;
}

MwProperty::MwProperty(const MwString &name, const MwVector4 &value)
	: MwParameter(value)
{
	this->name = name;
}

MwProperty::MwProperty(const MwString &name, MwParameterType type, void *value)
	: MwParameter(type, value)
{
	this->name = name;
}


MwProperty::~MwProperty(void)
{
}
