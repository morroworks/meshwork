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

#include "MwKeyFrameScaling.h"


MwKeyFrameScaling::MwKeyFrameScaling(void)
	: MwKeyFrame()
{
	this->typeId = MwKeyFrameScaling::classId;
}

MwKeyFrameScaling::MwKeyFrameScaling(float time, MwVector3 &scaling)
	: MwKeyFrame(time)
{
	this->typeId = MwKeyFrameScaling::classId;

	this->scaling = scaling;
}

MwKeyFrameScaling::~MwKeyFrameScaling(void)
{
}

void MwKeyFrameScaling::Process(MwMatrix &result)
{
	MwMatrix::CreateScale(result, this->scaling);
}

void MwKeyFrameScaling::Process(MwMatrix &result, MwKeyFrame *next, float blend)
{
	MwVector3 v;
	MwVector3::Lerp(v, this->scaling, ((MwKeyFrameScaling*)next)->scaling, blend);
	MwMatrix::CreateScale(result, v);
}

void MwKeyFrameScaling::Serialize(MwBaseStream &destination)
{
	MwKeyFrame::Serialize(destination);

	destination.WriteFloat(this->scaling.x);
	destination.WriteFloat(this->scaling.y);
	destination.WriteFloat(this->scaling.z);
}

bool MwKeyFrameScaling::Deserialize(MwBaseStream &source)
{
	if (!MwKeyFrame::Deserialize(source))
		return false;

	this->scaling.x = source.ReadFloat();
	this->scaling.y = source.ReadFloat();
	this->scaling.z = source.ReadFloat();

	return true;
}
