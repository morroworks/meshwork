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

#include "MwNativeScene.h"

#include "MwNativeFileReader.h"
#include "MwNativeFileWriter.h"

MwNativeScene::MwNativeScene(void)
{
}


MwNativeScene::~MwNativeScene(void)
{
}

bool MwNativeScene::Load(MwBaseStream &source)
{
	if (this->context == 0)
		return false;

	MwNativeFileReader reader(this->context);

	return reader.Read(source);
}

bool MwNativeScene::Save(MwBaseStream &destination, const char *format)
{
	if (this->context == 0)
		return false;

	if (format != 0)
	{
		MwString encodingCode = MwString(format).Trim('.');
		if ((encodingCode.length != 0) && (!encodingCode.Equals("mw")))
			return false;
	}


	MwNativeFileWriter writer(this->context);
	writer.Write(destination);

	return true;
}
