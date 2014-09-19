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

#include "MwStandardEntityDispatcher.h"

#include "Entities\Camera\MwCamera.h"
#include "Entities\Material\MwMaterial.h"
#include "Entities\Mechanisms\MwFloatMechanism.h"
#include "Entities\Mechanisms\MwNegateFloatMechanism.h"
#include "Entities\Mechanisms\MwLinearMechanism.h"
#include "Entities\Mechanisms\MwLinearInterpolationMechanism.h"
#include "Entities\Mechanisms\MwSineMechanism.h"
#include "Entities\Mechanisms\MwDirectionMechanism.h"
#include "Entities\Mechanisms\MwDirectionLagMechanism.h"
#include "Entities\Mechanisms\MwKeyframeAnimationMechanism.h"
#include "Entities\Mechanisms\MwPivotalMechanism.h"
#include "Entities\Mechanisms\MwTimeRateMechanism.h"
#include "Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameRotationAxis.h"
#include "Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameRotationEuler.h"
#include "Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameScaling.h"
#include "Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameTranslation.h"
#include "Entities\Mesh\MwMesh.h"
#include "Entities\EntitySet\MwEntitySet.h"
#include "Entities\Textures\MwTexture2D.h"
#include "Entities\Transform\MwTransform.h"
#include "Entities\Light\MwLight.h"
#include "Entities\Sound\MwSound.h"
#include "Entities\SoundEmitter\MwSoundEmitter.h"
#include "Entities\SoundReceptor\MwSoundReceptor.h"
#include "Entities\Script\MwScript.h"

MwStandardEntityDispatcher::MwStandardEntityDispatcher(void)
{
}


MwStandardEntityDispatcher::~MwStandardEntityDispatcher(void)
{
}

MwEntity *MwStandardEntityDispatcher::CreateEntity(Meshwork *context, int typeId)
{
	switch (typeId)
	{
		case MwMesh::classId:
		{
			return new MwMesh(*context);
		}

		case MwTransform::classId:
		{
			return new MwTransform();
		}

		case MwCamera::classId:
		{
			return new MwCamera(context);
		}

		case MwMaterial::classId:
		{
			return new MwMaterial(*context);
		}

		case MwEntitySet::classId:
		{
			return new MwEntitySet();
		}

		case MwTexture2D::classId:
		{
			return new MwTexture2D(*context);
		}

		case MwFloatMechanism::classId:
		{
			return new MwFloatMechanism(0);
		}

		case (MwResourceType_Mechanism << 16) | 2:
		{
			return new MwNegateFloatMechanism(0);
		}

		case (MwResourceType_Mechanism << 16) | 3:
		{
			return new MwLinearMechanism(0, 10, 1, false);
		}

		case (MwResourceType_Mechanism << 16) | 4:
		{
			return new MwSineMechanism(0, 10, 1, false);
		}

		case (MwResourceType_Mechanism << 16) | 5:
		{
			return new MwDirectionMechanism();
		}

		case (MwResourceType_Mechanism << 16) | 6:
		{
			return new MwDirectionLagMechanism();
		}

		case (MwResourceType_Mechanism << 16) | 7:
		{
			return new MwKeyframeAnimationMechanism(context);
		}

		case (MwResourceType_Mechanism << 16) | 8:
		{
			return new MwPivotalMechanism();
		}

		case (MwResourceType_Mechanism << 16) | 9:
		{
			return new MwLinearInterpolationMechanism(0, 1, 0);
		}

		case (MwResourceType_Mechanism << 16) | 10:
		{
			return new MwTimeRateMechanism(context);
		}

		case MwLight::classId:
		{
			return new MwLight();
		}

		case MwSound::classId:
		{
			return new MwSound(context);
		}

		case MwSoundEmitter::classId:
		{
			return new MwSoundEmitter(context);
		}

		case MwSoundReceptor::classId:
		{
			return new MwSoundReceptor(context);
		}

		case MwKeyFrameTranslation::classId:
		{
			return new MwKeyFrameTranslation();
		}

		case MwScript::classId:
		{
			return new MwScript(context);
		}


		case MwKeyFrameRotationAxis::classId:
		{
			return new MwKeyFrameRotationAxis();
		}

		case MwKeyFrameRotationEuler::classId:
		{
			return new MwKeyFrameRotationEuler();
		}

		case MwKeyFrameScaling::classId:
		{
			return new MwKeyFrameScaling();
		}

	}

	return 0;
}