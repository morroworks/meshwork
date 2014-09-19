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

#include "MwFbxKeyframesTrack.h"


MwFbxKeyframesTrack::MwFbxKeyframesTrack(void)
{
	this->valid = true;
}


MwFbxKeyframesTrack::~MwFbxKeyframesTrack(void)
{
}

bool MwFbxKeyframesTrack::FindFrameKey(int &index, float time)
{
	index = 0;

	//int left = 0;
    //int right = this->keyframes.count - 1;

    //while (left <= right)
    //{
    //    index = left + (right - left) / 2;

    //    if (this->keyframes[index].time == time)
    //        return true;

    //    if (this->keyframes[index].time < time)
    //        left = index + 1;
    //    else
    //        right = index - 1;
    //}

    //return false;

	while (index < this->keyframes.count)
	{
		if (this->keyframes[index].time == time)
			return true;

		if (this->keyframes[index].time > time)
			return false;
		
		index++;
	}

	return false;
}


void MwFbxKeyframesTrack::ProcessFbxCurve(FbxAnimCurve* curve, MwFbxKeyFrameValueComponent valueComponent, float defaultValue)
{
	//if ((curve == 0) || (curve->KeyGetCount() == 0))
	//{
	//	this->keyframes.Clear();
	//	this->valid = true;
	//}

	//if (!this->valid)
	//	return;
	
	if (curve == 0)
		return;

	int numKeys = curve->KeyGetCount();
	for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
	{
		float keyTime = (float)curve->KeyGetTime(keyIndex).GetSecondDouble();
		//float keyTime = curve->KeyGetTime(keyIndex).GetFrameCount();
		//float keyValueComponent = curve->EvaluateIndex(keyIndex); 
		float keyValueComponent = curve->KeyGetValue(keyIndex);

		bool isConstant = (curve->KeyGetInterpolation(keyIndex) & FbxAnimCurveDef::eInterpolationConstant) != 0;
		bool isLinear = (curve->KeyGetInterpolation(keyIndex) & FbxAnimCurveDef::eInterpolationLinear) != 0;
		bool isCubic = (curve->KeyGetInterpolation(keyIndex) & FbxAnimCurveDef::eInterpolationCubic) != 0;
		
		int trackKey = 0;
		if (!this->FindFrameKey(trackKey, keyTime))
		{
			//if (trackKey != this->keyframes.count)
			//	return;

			MwFbxKeyframe newKeyframe;
			newKeyframe.time = keyTime;
			newKeyframe.value.Set(defaultValue);
			this->keyframes.Insert(trackKey, newKeyframe);
			trackKey = this->keyframes.count - 1;
		}

		switch (valueComponent)
		{
			case MwFbxKeyFrameValueComponentX:
				this->keyframes[trackKey].value.x = keyValueComponent;
				break;

			case MwFbxKeyFrameValueComponentY:
				this->keyframes[trackKey].value.y = keyValueComponent;
				break;

			case MwFbxKeyFrameValueComponentZ:
				this->keyframes[trackKey].value.z = keyValueComponent;
				break;
		}
	}
}