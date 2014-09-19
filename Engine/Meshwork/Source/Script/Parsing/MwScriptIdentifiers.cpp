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

#include "MwScriptIdentifiers.h"


MwScriptIdentifiers::MwScriptIdentifiers(void)
{
	this->size = 0;
}


MwScriptIdentifiers::~MwScriptIdentifiers(void)
{
	this->Clear();
}

MwScriptIdentifier *MwScriptIdentifiers::Find(MwString name)
{
	for (int i = 0; i < this->list.count; i++)
		if (this->list[i]->name.Equals(name))
			return this->list[i];

	return 0;
}

MwScriptIdentifier *MwScriptIdentifiers::Add(MwString name, MwScriptDataType *dataType, int numElements)
{
	MwScriptIdentifier *identifier = new MwScriptIdentifier(name, dataType, this->size);
	this->size += dataType->size * numElements;
	return this->list.Add(identifier);
}

void MwScriptIdentifiers::Clear()
{
	for (int i = 0; i < this->list.count; i++)
		delete this->list[i];
	this->list.Clear();
}
