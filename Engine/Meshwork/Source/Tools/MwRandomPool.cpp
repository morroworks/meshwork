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

#include "MwRandomPool.h"

#include "MwMath.h"

MwRandomPool::MwRandomPool(void)
{
}


MwRandomPool::MwRandomPool(int count)
{
	this->Generate(count);
}

MwRandomPool::~MwRandomPool(void)
{
}


void MwRandomPool::Generate(int count)
{
	this->pool.Clear();
	this->pool.EnsureCapacity(count);

	for (int i = 0; i < count; i++)
		this->pool.Add(i);
}

void MwRandomPool::Put(int value)
{
	this->pool.Add(value);
}

int MwRandomPool::Pull()
{
	if (this->pool.count == 0)
		return 0;

	int index = MwMath::Random(this->pool.count);
	this->pool.count--;
	int result = this->pool.values[index];
	this->pool.values[index] = this->pool.values[this->pool.count];
	
	return result;
}

bool MwRandomPool::Contains(int value)
{
	return this->pool.IndexOf(value) != -1;
}

bool MwRandomPool::Remove(int value)
{
	int index = this->pool.IndexOf(value);
	if (index == -1)
		return false;

	this->pool.count--;
	int result = this->pool.values[index];
	this->pool.values[index] = this->pool.values[this->pool.count];

	return true;
}
