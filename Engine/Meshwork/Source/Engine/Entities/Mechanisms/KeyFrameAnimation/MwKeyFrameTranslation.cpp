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

#include "MwKeyFrameTranslation.h"


MwKeyFrameTranslation::MwKeyFrameTranslation(void)
	: MwKeyFrame()
{
	this->typeId = MwKeyFrameTranslation::classId;
}

MwKeyFrameTranslation::MwKeyFrameTranslation(float time, MwVector3 &position)
	: MwKeyFrame(time)
{
	this->typeId = MwKeyFrameTranslation::classId;

	this->position = position;
}

MwKeyFrameTranslation::~MwKeyFrameTranslation(void)
{
}

void MwKeyFrameTranslation::Process(MwMatrix &result)
{
	MwMatrix::CreateTranslation(result, this->position);
}

void MwKeyFrameTranslation::Process(MwMatrix &result, MwKeyFrame *next, float blend)
{
	MwVector3 v;
	MwVector3::Lerp(v, this->position, ((MwKeyFrameTranslation*)next)->position, blend);
	MwMatrix::CreateTranslation(result, v);
}

void MwKeyFrameTranslation::Serialize(MwBaseStream &destination)
{
	MwKeyFrame::Serialize(destination);

	destination.WriteFloat(this->position.x);
	destination.WriteFloat(this->position.y);
	destination.WriteFloat(this->position.z);
}

bool MwKeyFrameTranslation::Deserialize(MwBaseStream &source)
{
	if (!MwKeyFrame::Deserialize(source))
		return false;

	this->position.x = source.ReadFloat();
	this->position.y = source.ReadFloat();
	this->position.z = source.ReadFloat();

	return true;
}
