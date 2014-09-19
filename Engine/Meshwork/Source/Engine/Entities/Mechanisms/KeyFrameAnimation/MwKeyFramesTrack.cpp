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

#include "MwKeyFramesTrack.h"


MwKeyFramesTrack::MwKeyFramesTrack(void)
	: MwList<MwKeyFrame*>()
{
}


MwKeyFramesTrack::~MwKeyFramesTrack(void)
{
	for (int i = 0; i < this->count; i++)
		delete this->Get(i);
}

void MwKeyFramesTrack::GetTransform(MwMatrix &result, float time)
{
	int count = this->count;
	
	// No keyframes
	if (count == 0)
	{
		MwMatrix::CreateIdentity(result);
		return;
	}

	// Only one keyframe
	else if (count == 1)
	{
		this->Get(0)->Process(result);
		return;
	}

	// Time outside of left boundary
	else if (time <= this->Get(0)->time)
	{
		this->Get(0)->Process(result);
		return;
	}

	// Time outside of right boundary
	else if (time >= this->Get(count - 1)->time)
	{
		this->Get(count - 1)->Process(result);
		return;
	}

	// Search - a minimum of 2 key frames are required
	else
	{
		int left = 0;
		int right = count - 2;

		int index;
		float startTime, endTime;

		while (left <= right)
		{
			index = left + (right - left) / 2;
			startTime = this->Get(index)->time;
			endTime = this->Get(index + 1)->time;

			if (time > endTime)
				left = index + 1;
			else if (time < startTime)
				right = index - 1;
			else
				break;
		}

		float blend = (time - startTime) / (float)(endTime - startTime);

		this->Get(index)->Process(result, this->Get(index + 1), blend);
	}
}
