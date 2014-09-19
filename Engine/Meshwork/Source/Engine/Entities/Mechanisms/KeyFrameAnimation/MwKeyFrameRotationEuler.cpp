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

#include "MwKeyFrameRotationEuler.h"


MwKeyFrameRotationEuler::MwKeyFrameRotationEuler(void)
	: MwKeyFrame()
{
	this->typeId = MwKeyFrameRotationEuler::classId;
}

MwKeyFrameRotationEuler::MwKeyFrameRotationEuler(float time, MwVector3 &eulerAngles)
	: MwKeyFrame(time)
{
	this->typeId = MwKeyFrameRotationEuler::classId;

	this->eulerAngles = eulerAngles;
}

MwKeyFrameRotationEuler::~MwKeyFrameRotationEuler(void)
{
}

void MwKeyFrameRotationEuler::Process(MwMatrix &result)
{
	MwMatrix m;
	MwMatrix::CreateRotationX(result, this->eulerAngles.x);
	MwMatrix::CreateRotationY(m, this->eulerAngles.y);
	MwMatrix::Multiply(result, result, m);
	MwMatrix::CreateRotationZ(m, this->eulerAngles.z);
	MwMatrix::Multiply(result, result, m);
}

void MwKeyFrameRotationEuler::Process(MwMatrix &result, MwKeyFrame *next, float blend)
{
	MwVector3 v;
	MwVector3::Lerp(v, this->eulerAngles, ((MwKeyFrameRotationEuler*)next)->eulerAngles, blend);

	MwMatrix m;
	MwMatrix::CreateRotationX(result, v.x);
	MwMatrix::CreateRotationY(m, v.y);
	MwMatrix::Multiply(result, result, m);
	MwMatrix::CreateRotationZ(m, v.z);
	MwMatrix::Multiply(result, result, m);
}

void MwKeyFrameRotationEuler::Serialize(MwBaseStream &destination)
{
	MwKeyFrame::Serialize(destination);

	destination.WriteFloat(this->eulerAngles.x);
	destination.WriteFloat(this->eulerAngles.y);
	destination.WriteFloat(this->eulerAngles.z);
}

bool MwKeyFrameRotationEuler::Deserialize(MwBaseStream &source)
{
	if (!MwKeyFrame::Deserialize(source))
		return false;

	this->eulerAngles.x = source.ReadFloat();
	this->eulerAngles.y = source.ReadFloat();
	this->eulerAngles.z = source.ReadFloat();

	return true;
}
