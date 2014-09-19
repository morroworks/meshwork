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

#include "MwKeyFrameRotationAxis.h"


MwKeyFrameRotationAxis::MwKeyFrameRotationAxis(void)
	: MwKeyFrame()
{
	this->typeId = MwKeyFrameRotationAxis::classId;
}

MwKeyFrameRotationAxis::MwKeyFrameRotationAxis(float time, float angle, MwVector3 &axis)
	: MwKeyFrame(time)
{
	this->typeId = MwKeyFrameRotationAxis::classId;
	
	this->axis = axis;
	this->angle = angle;
}


MwKeyFrameRotationAxis::~MwKeyFrameRotationAxis(void)
{
}

void MwKeyFrameRotationAxis::Process(MwMatrix &result)
{
	MwMatrix::Copy(result, this->previousTransform);
}

void MwKeyFrameRotationAxis::Process(MwMatrix &result, MwKeyFrame *next, float blend)
{
	MwMatrix rotationMatrix;
	MwMatrix::CreateRotationAxis(rotationMatrix, ((MwKeyFrameRotationAxis*)next)->axis, ((MwKeyFrameRotationAxis*)next)->angle * blend);
	MwMatrix::Multiply(result, this->previousTransform, rotationMatrix);
}

void MwKeyFrameRotationAxis::Serialize(MwBaseStream &destination)
{
	MwKeyFrame::Serialize(destination);

	destination.WriteFloat(this->axis.x);
	destination.WriteFloat(this->axis.y);
	destination.WriteFloat(this->axis.z);

	destination.WriteFloat(this->angle);
}

bool MwKeyFrameRotationAxis::Deserialize(MwBaseStream &source)
{
	if (!MwKeyFrame::Deserialize(source))
		return false;

	this->axis.x = source.ReadFloat();
	this->axis.y = source.ReadFloat();
	this->axis.z = source.ReadFloat();

	this->angle = source.ReadFloat();
	
	return true;
}
