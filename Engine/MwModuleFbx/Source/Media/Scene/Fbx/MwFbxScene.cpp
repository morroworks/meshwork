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

#include "MwFbxScene.h"

#include "MwFbxKeyframesTrack.h"

MwFbxScene::MwFbxScene(void)
{
}


MwFbxScene::~MwFbxScene(void)
{
}

MwVector2 MwFbxScene::FbxToMwVector2(FbxDouble2 fbxVector)
{
	return MwVector2((float)fbxVector[0], (float)fbxVector[1]);
}

MwVector3 MwFbxScene::FbxToMwVector3(FbxDouble3 fbxVector)
{
	return MwVector3((float)fbxVector[0], (float)fbxVector[1], (float)fbxVector[2]);
}

MwVector3 MwFbxScene::FbxToMwVector3(FbxDouble4 fbxVector)
{
	return MwVector3((float)fbxVector[0], (float)fbxVector[1], (float)fbxVector[2]);
}

void MwFbxScene::FbxToMwMatrix(MwMatrix &result, FbxAMatrix *fbxMatrix)
{
	result._11 = (float)fbxMatrix->Get(0, 0);
	result._12 = (float)fbxMatrix->Get(0, 1);
	result._13 = (float)fbxMatrix->Get(0, 2);
	result._14 = (float)fbxMatrix->Get(0, 3);
	result._21 = (float)fbxMatrix->Get(1, 0);
	result._22 = (float)fbxMatrix->Get(1, 1);
	result._23 = (float)fbxMatrix->Get(1, 2);
	result._24 = (float)fbxMatrix->Get(1, 3);
	result._31 = (float)fbxMatrix->Get(2, 0);
	result._32 = (float)fbxMatrix->Get(2, 1);
	result._33 = (float)fbxMatrix->Get(2, 2);
	result._34 = (float)fbxMatrix->Get(2, 3);
	result._41 = (float)fbxMatrix->Get(3, 0);
	result._42 = (float)fbxMatrix->Get(3, 1);
	result._43 = (float)fbxMatrix->Get(3, 2);
	result._44 = (float)fbxMatrix->Get(3, 3);
}

void MwFbxScene::FbxCreateRotationMatrix(MwMatrix &result, MwVector3 eulerAngles, EFbxRotationOrder rotationOrder)
{
	MwVector3 rotation;
	MwVector3::Scale(rotation, eulerAngles, MwMath::Pi / 180.0f);

	MwMatrix m;

	switch (rotationOrder)
	{
		case eEulerXYZ:
		{
			MwMatrix::CreateRotationX(result, rotation.x);
			MwMatrix::CreateRotationY(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationZ(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}
		
		case eEulerXZY:
		{
			MwMatrix::CreateRotationX(result, rotation.x);
			MwMatrix::CreateRotationZ(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationY(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}

		case eEulerYZX:
		{
			MwMatrix::CreateRotationY(result, rotation.x);
			MwMatrix::CreateRotationZ(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationX(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}

		case eEulerYXZ:
		{
			MwMatrix::CreateRotationY(result, rotation.x);
			MwMatrix::CreateRotationX(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationZ(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}

		case eEulerZXY:
		{
			MwMatrix::CreateRotationZ(result, rotation.x);
			MwMatrix::CreateRotationX(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationY(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}

		case eEulerZYX:
		{
			MwMatrix::CreateRotationZ(result, rotation.x);
			MwMatrix::CreateRotationY(m, rotation.y);
			MwMatrix::Multiply(result, result, m);
			MwMatrix::CreateRotationX(m, rotation.z);
			MwMatrix::Multiply(result, result, m);

			break;
		}

		case eSphericXYZ:
		{
			MwMatrix::CreateRotationX(result, rotation.x);
			MwMatrix::CreateRotationY(m, rotation.y);
			MwMatrix::Multiply(result, m, result);
			MwMatrix::CreateRotationZ(m, rotation.z);
			MwMatrix::Multiply(result, m, result);

			break;
		}

		default:
		{
			MwMatrix::CreateIdentity(result);
		}
	}
}

// Geometric transformation for the fbx node. This transformation should not be inherited to children. It is to be applied directly to the position of the node's attributes in object space
void MwFbxScene::GetNodeGeometryTransform(MwMatrix &transform, FbxNode *fbxNode)
{
	MwMatrix m;
	MwMatrix::CreateTranslation(transform, this->FbxToMwVector3(fbxNode->GetGeometricTranslation(FbxNode::eSourcePivot)));
	this->FbxCreateRotationMatrix(m, this->FbxToMwVector3(fbxNode->GetGeometricRotation(FbxNode::eSourcePivot)), fbxNode->RotationOrder);
	MwMatrix::Multiply(transform, m, transform);
	MwMatrix::CreateScale(m, this->FbxToMwVector3(fbxNode->GetGeometricScaling(FbxNode::eSourcePivot)));
	MwMatrix::Multiply(transform, m, transform);
}

void MwFbxScene::LoadNodeDefaultTransform(MwTransform *transform, FbxNode *fbxNode)
{
	MwMatrix m;

	MwVector3 translation = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
	MwMatrix::CreateTranslation(transform->manual, translation);


		MwVector3 total;
		MwVector3 rotationOffset = this->FbxToMwVector3(fbxNode->RotationOffset.Get());
		MwVector3 rotationPivot = this->FbxToMwVector3(fbxNode->RotationPivot.Get());
		MwVector3 preRotation = this->FbxToMwVector3(fbxNode->PreRotation.Get());
		//MwVector3::Add(total, rotationOffset, rotationPivot);
		//MwVector3::Add(total, total, preRotation);
		//MwMatrix::CreateTranslation(m, total);
		//MwMatrix::Multiply(transform->manual, m, transform->manual);


	MwVector3 rotation = this->FbxToMwVector3(fbxNode->LclRotation.Get());
	this->FbxCreateRotationMatrix(m, rotation, fbxNode->RotationOrder);
	MwMatrix::Multiply(transform->manual, m, transform->manual);


		MwVector3 postRotation = this->FbxToMwVector3(fbxNode->PostRotation.Get());
		MwVector3 rotationPivotInverse;
		MwVector3::Scale(rotationPivotInverse, rotationPivot, -1.0f);
		MwVector3 scalingOffset = this->FbxToMwVector3(fbxNode->ScalingOffset.Get());
		MwVector3 scalingPivot = this->FbxToMwVector3(fbxNode->ScalingPivot.Get());
		//MwVector3::Add(total, postRotation, rotationPivotInverse);
		//MwVector3::Add(total, total, scalingOffset);
		//MwVector3::Add(total, total, scalingPivot);
		//MwMatrix::CreateTranslation(m, total);
		//MwMatrix::Multiply(transform->manual, m, transform->manual);


	MwVector3 scaling = this->FbxToMwVector3(fbxNode->LclScaling.Get());
	MwMatrix::CreateScale(m, scaling);
	MwMatrix::Multiply(transform->manual, m, transform->manual);


		MwVector3 scalingPivotInverse;
		MwVector3::Scale(scalingPivotInverse, scalingPivot, -1.0f);
		//MwMatrix::CreateTranslation(m, scalingPivotInverse);
		//MwMatrix::Multiply(transform->manual, m, transform->manual);
}

//bool MwFbxScene::LoadNodeKeyframeAnimation(MwEntitySet *entitySet, FbxNode* fbxNode, MwTransform *transformToAnimate)
//{
//	MwString name = fbxNode->GetName();
//	
//	float frameRate = FbxTime::GetFrameRate(this->fbxScene->GetGlobalSettings().GetTimeMode());
//	MwVector3 v1 = this->FbxToMwVector3(fbxNode->RotationOffset.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//	MwVector3 v2 = this->FbxToMwVector3(fbxNode->RotationPivot.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//	MwVector3 v3 = this->FbxToMwVector3(fbxNode->PreRotation.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//	MwVector3 v4 = this->FbxToMwVector3(fbxNode->PostRotation.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//	MwVector3 v5 = this->FbxToMwVector3(fbxNode->ScalingOffset.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//	MwVector3 v6 = this->FbxToMwVector3(fbxNode->ScalingPivot.Get());
//	//if ((v.x != 0.0f) || (v.y != 0.0f) || (v.z != 0.0f))
//	//	return false;
//
//	MwVector3 ro = this->FbxToMwVector3(fbxNode->RotationOffset.Get());
//	MwVector3 rp = this->FbxToMwVector3(fbxNode->RotationPivot.Get());
//	MwVector3 pr = this->FbxToMwVector3(fbxNode->PreRotation.Get());
//	MwVector3 sr = this->FbxToMwVector3(fbxNode->PostRotation.Get());
//	MwVector3 so = this->FbxToMwVector3(fbxNode->ScalingOffset.Get());
//	MwVector3 sp = this->FbxToMwVector3(fbxNode->ScalingPivot.Get());
//
//	MwMatrix geometryTransform;
//	this->GetNodeGeometryTransform(geometryTransform, fbxNode);
//	transformToAnimate->pivot = geometryTransform;
//
//	bool isAnimated = false;
//
//	int numAnimations = this->fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
//	for (int animationIndex = 0; animationIndex < numAnimations; animationIndex++)
//	{
//		FbxAnimStack *animStack = (FbxAnimStack*)this->fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
//		MwString animationName = animStack->GetName();
//
//		//FbxAnimEvaluator *animEvaluator = this->fbxScene->GetEvaluator();
//		//animEvaluator->SetContext(animStack);
//
//
//		int numLayers = animStack->GetMemberCount();
//		for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
//		{
//			FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
//			MwString layerName = animLayer->GetName();
//
//			MwFbxKeyframesTrack translationTrack;
//			translationTrack.ProcessFbxCurve(fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X), MwFbxKeyFrameValueComponentX);
//			translationTrack.ProcessFbxCurve(fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y), MwFbxKeyFrameValueComponentY);
//			translationTrack.ProcessFbxCurve(fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z), MwFbxKeyFrameValueComponentZ);
//
//			MwFbxKeyframesTrack rotationTrack;
//			rotationTrack.ProcessFbxCurve(fbxNode->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X), MwFbxKeyFrameValueComponentX);
//			rotationTrack.ProcessFbxCurve(fbxNode->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y), MwFbxKeyFrameValueComponentY);
//			rotationTrack.ProcessFbxCurve(fbxNode->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z), MwFbxKeyFrameValueComponentZ);
//
//			MwFbxKeyframesTrack scalingTrack;
//			scalingTrack.ProcessFbxCurve(fbxNode->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X), MwFbxKeyFrameValueComponentX, 1.0f);
//			scalingTrack.ProcessFbxCurve(fbxNode->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y), MwFbxKeyFrameValueComponentY, 1.0f);
//			scalingTrack.ProcessFbxCurve(fbxNode->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z), MwFbxKeyFrameValueComponentZ, 1.0f);
//
//			if ((translationTrack.keyframes.count != 0) || (rotationTrack.keyframes.count != 0) || (scalingTrack.keyframes.count != 0))
//			{
//				MwKeyframeAnimationMechanism *keyFrames = (MwKeyframeAnimationMechanism*)this->context->AddResource(*new MwKeyframeAnimationMechanism());
//				keyFrames->name = this->context->AcquireResourceName(animationName, MwResourceType_Mechanism);
//				entitySet->references.Add(keyFrames);
//				
//				keyFrames->properties[MwKeyframeAnimationMechanism::propertyIndex_Frame]->SetReference(MwParameterType_ReferenceMechanism, this->animationFrame);
//				keyFrames->properties[MwKeyframeAnimationMechanism::propertyIndex_Transform]->SetReference(MwParameterType_ReferenceTransform, transformToAnimate);
//
//
//				// Translation
//				if (translationTrack.keyframes.count > 0)
//				{
//					// TEST METHOD 1
//					//MwVector3 t1 = translationTrack.keyframes[0].value;
//					MwVector3 t1(0);
//					MwVector3 t1t;
//					FbxAnimCurve *c = fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X);
//					if (c != 0)
//					{
//						if (c->KeyGetCount() > 0)
//						{
//							t1.x = c->KeyGetValue(0);
//							t1t.x = c->KeyGetTime(0).GetSecondDouble();
//						}
//					}
//					c = fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y);
//					if (c != 0)
//					{
//						if (c->KeyGetCount() > 0)
//						{
//							t1.y = c->KeyGetValue(0);
//							t1t.y = c->KeyGetTime(0).GetSecondDouble();
//						}
//					}
//					c = fbxNode->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z);
//					if (c != 0)
//					{
//						if (c->KeyGetCount() > 0)
//						{
//							t1.z = c->KeyGetValue(0);
//							t1t.z = c->KeyGetTime(0).GetSecondDouble();
//						}
//					}
//
//					// TEST METHOD 2
//					MwVector3 t2(0);
//					FbxAnimCurve *translationCurve = fbxNode->LclTranslation.GetCurve(animLayer);
//					if (translationCurve != 0)
//					{
//						if (translationCurve->KeyGetCount() > 0)
//						{
//							FbxAnimEvaluator *animEvaluator = this->fbxScene->GetAnimationEvaluator();
//							FbxTime frameTime = translationCurve->KeyGetTime(0);
//							t2 = this->FbxToMwVector3(animEvaluator->GetNodeLocalTranslation(fbxNode, frameTime));
//						}
//					}
//
//					// TEST METHOD 3
//					MwVector3 t3 = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
//
//					// TEST METHOD 4
//					MwVector3 t4(0);
//					if (translationCurve != 0)
//					{
//						if (translationCurve->KeyGetCount() > 0)
//						{
//							FbxTime frameTime = translationCurve->KeyGetTime(0);
//							t4 = this->FbxToMwVector3(fbxNode->EvaluateLocalTranslation(frameTime));
//						}
//					}
//
//
//
//					for (int keyIndex = 0; keyIndex < translationTrack.keyframes.count; keyIndex++)
//					{
//						keyFrames->translation.Add(new MwKeyframeAnimationMechanism::TranslationFrame(translationTrack.keyframes[keyIndex].time, translationTrack.keyframes[keyIndex].value));
//						//keyFrames->translation.Add(new MwKeyframeAnimationMechanism::TranslationFrame(translationTrack.keyframes[keyIndex].time, translationTrack.keyframes[0].value));
//					}
//				}
//				else
//				{
//					MwVector3 translation = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
//
//					//MwVector3 pivot = this->FbxToMwVector3(fbxNode->RotationPivot);
//					//MwVector3::Add(translation, translation, pivot);
//					//MwMatrix::CreateTranslation(transformToAnimate->pivot, pivot);
//						
//					keyFrames->translation.Add(new MwKeyframeAnimationMechanism::TranslationFrame(0.0f, translation));
//				}
//				
//				
//				// Rotation
//				if (rotationTrack.keyframes.count > 0)
//				{
//					for (int keyIndex = 0; keyIndex < rotationTrack.keyframes.count; keyIndex++)
//					{
//						MwVector3::Scale(rotationTrack.keyframes[keyIndex].value, rotationTrack.keyframes[keyIndex].value, MwMath::Pi / 180.0f);
//						keyFrames->rotationEuler.Add(new MwKeyframeAnimationMechanism::RotationEulerFrame(rotationTrack.keyframes[keyIndex].time, rotationTrack.keyframes[keyIndex].value));
//					}
//				}
//				else
//				{
//					MwVector3 rotation = this->FbxToMwVector3(fbxNode->LclRotation.Get());
//					MwVector3::Scale(rotation, rotation, MwMath::Pi / 180.0f);
//
//					keyFrames->rotationEuler.Add(new MwKeyframeAnimationMechanism::RotationEulerFrame(0.0f, rotation));
//				}
//				
//
//				// Scaling
//				if (scalingTrack.keyframes.count > 0)
//				{
//					for (int keyIndex = 0; keyIndex < scalingTrack.keyframes.count; keyIndex++)
//					{
//						keyFrames->scaling.Add(new MwKeyframeAnimationMechanism::ScalingFrame(scalingTrack.keyframes[keyIndex].time, scalingTrack.keyframes[keyIndex].value));
//					}
//				}
//				else
//				{
//					MwVector3 scaling = this->FbxToMwVector3(fbxNode->LclScaling.Get());
//					keyFrames->scaling.Add(new MwKeyframeAnimationMechanism::ScalingFrame(0.0f, scaling));
//				}
//
//				// Set the frame mechanism to the biggest number of frames
//				float animationTime = MwMath::Max(MwMath::Max(keyFrames->translation[keyFrames->translation.count - 1]->frame, keyFrames->rotationEuler[keyFrames->rotationEuler.count - 1]->frame), keyFrames->scaling[keyFrames->scaling.count - 1]->frame);
//				this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->SetFloat(MwMath::Max(this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->GetFloat(), animationTime));
//			
//				keyFrames->BuildKeyframeTransformations();
//
//				return true;
//			}
//		}
//	}
//
//	return isAnimated;
//}

bool MwFbxScene::LoadNodeKeyframeAnimation(MwEntitySet *entitySet, FbxNode* fbxNode, MwTransform *transformToAnimate)
{
	MwString name = fbxNode->GetName();
	FbxEuler::EOrder rotationOrder = fbxNode->RotationOrder;

	MwMatrix geometryTransform;
	this->GetNodeGeometryTransform(geometryTransform, fbxNode);
	transformToAnimate->pivot = geometryTransform;

	MwVector3 ro = this->FbxToMwVector3(fbxNode->RotationOffset.Get());
	MwVector3 rp = this->FbxToMwVector3(fbxNode->RotationPivot.Get());
	MwVector3 pr = this->FbxToMwVector3(fbxNode->PreRotation.Get());
	MwVector3 sr = this->FbxToMwVector3(fbxNode->PostRotation.Get());
	MwVector3 so = this->FbxToMwVector3(fbxNode->ScalingOffset.Get());
	MwVector3 sp = this->FbxToMwVector3(fbxNode->ScalingPivot.Get());
	MwMatrix preRotation;
	this->FbxCreateRotationMatrix(preRotation, pr, rotationOrder);

	bool isAnimated = false;

	int numAnimations = this->fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
	for (int animationIndex = 0; animationIndex < numAnimations; animationIndex++)
	{
		FbxAnimStack *animStack = (FbxAnimStack*)this->fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
		MwString animationName = animStack->GetName();

		FbxAnimEvaluator *animEvaluator = this->fbxScene->GetAnimationEvaluator();
		//animEvaluator->SetContext(animStack);

		int numLayers = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
		{
			FbxAnimLayer *animLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);
			MwString layerName = animLayer->GetName();

			FbxAnimCurve *translationCurve = fbxNode->LclTranslation.GetCurve(animLayer);
			FbxAnimCurve *rotationCurve = fbxNode->LclRotation.GetCurve(animLayer);
			FbxAnimCurve *scalingCurve = fbxNode->LclScaling.GetCurve(animLayer);

			bool hasAnimation = (translationCurve != 0) || (rotationCurve != 0) || (scalingCurve != 0);

			if (hasAnimation)
			{
				MwKeyframeAnimationMechanism *keyFrames = (MwKeyframeAnimationMechanism*)this->context->AddResource(*new MwKeyframeAnimationMechanism(this->context));
				keyFrames->name = this->context->AcquireResourceName(animationName, MwResourceType_Mechanism);
				entitySet->references.Add(keyFrames);
				
				keyFrames->properties[MwKeyframeAnimationMechanism::propertyIndex_Frame]->SetReference(MwParameterType_ReferenceMechanism, this->animationFrame);
				keyFrames->properties[MwKeyframeAnimationMechanism::propertyIndex_Transform]->SetReference(MwParameterType_ReferenceTransform, transformToAnimate);

				if (scalingCurve != 0)
				{
					MwKeyFramesTrack *scalingTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

					int numKeys = scalingCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
					{
						FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
						//MwVector3 scaling = this->FbxToMwVector3(animEvaluator->GetNodeLocalScaling(fbxNode, frameTime));
						MwVector3 scaling = this->FbxToMwVector3(fbxNode->EvaluateLocalScaling(frameTime));
						//MwVector3 scaling(1.0f);

						float frameSeconds = (float)frameTime.GetSecondDouble();
						scalingTrack->Add(new MwKeyFrameScaling(frameSeconds, scaling));

						this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->SetFloat(MwMath::Max(this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->GetFloat(), frameSeconds));
					}
				}
				else
				{
					MwKeyFramesTrack *scalingTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());
					MwVector3 scaling = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
					scalingTrack->Add(new MwKeyFrameScaling(0.0f, scaling));
				}

				if (rotationCurve != 0)
				{
					MwKeyFramesTrack *rotationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

					int numKeys = rotationCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
					{
						FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
						//MwVector3 rotation = this->FbxToMwVector3(animEvaluator->GetNodeLocalRotation(fbxNode, frameTime));
						MwVector3 rotation = this->FbxToMwVector3(fbxNode->EvaluateLocalRotation(frameTime));
						//MwVector3 rotation(0.0f);
						MwVector3::Scale(rotation, rotation, MwMath::Pi / 180.0f);
						//MwMatrix m;
						//this->FbxCreateRotationMatrix(m, rotation, rotationOrder);
						//MwMatrix::Multiply(m, preRotation, m);
						//MwMatrix::ExtractEulerRotation(rotation, m);
						//if (rotation.x < 0)
						//	rotation.x += MwMath::Pi2;
						//if (rotation.y < 0)
						//	rotation.y += MwMath::Pi2;
						//if (rotation.z < 0)
						//	rotation.z += MwMath::Pi2;

						float frameSeconds = (float)frameTime.GetSecondDouble();
						rotationTrack->Add(new MwKeyFrameRotationEuler(frameSeconds, rotation));

						this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->SetFloat(MwMath::Max(this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->GetFloat(), frameSeconds));
					}
				}
				else
				{
					MwKeyFramesTrack *rotationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());
					MwVector3 rotation = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
					MwVector3::Scale(rotation, rotation, MwMath::Pi / 180.0f);
					rotationTrack->Add(new MwKeyFrameRotationEuler(0.0f, rotation));
				}

				if (translationCurve != 0)
				{
					MwKeyFramesTrack *translationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

					int directIndex = -1;
					int numKeys = translationCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
					{
						FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
						//MwVector3 translation = this->FbxToMwVector3(animEvaluator->GetNodeLocalTranslation(fbxNode, frameTime));
						MwVector3 translation = this->FbxToMwVector3(fbxNode->EvaluateLocalTranslation(frameTime));
						//MwVector3 translation(0.0f);

						float frameSeconds = (float)frameTime.GetSecondDouble();
						translationTrack->Add(new MwKeyFrameTranslation(frameSeconds, translation));

						this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->SetFloat(MwMath::Max(this->animationFrame->properties[MwLinearMechanism::propertyIndex_Max]->GetFloat(), frameSeconds));
					}
				}
				else
				{
					MwKeyFramesTrack *translationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());
					MwVector3 translation = this->FbxToMwVector3(fbxNode->LclTranslation.Get());
					translationTrack->Add(new MwKeyFrameTranslation(0.0f, translation));
				}

				return true;
			}
		}
	}

	return false;
}

bool MwFbxScene::GetMaterialPropertyTextureName(const FbxProperty &fbxProperty, MwString &fileName)
{
	if (!fbxProperty.IsValid())
		return false;

	// Check for layered textues. A layered texture contains number of standard textures
	int numLayeredTextures = fbxProperty.GetSrcObjectCount<FbxLayeredTexture>();
	if (numLayeredTextures > 0)
	{
		// Get only the first layered texture with index 0
		FbxLayeredTexture *layeredTexture = fbxProperty.GetSrcObject<FbxLayeredTexture>(0);
		int numTextures = layeredTexture->GetSrcObjectCount<FbxTexture>();
		if (numTextures > 0)
		{
			// Get only the first texture with index 0
			const FbxFileTexture* texture = layeredTexture->GetSrcObject<FbxFileTexture>(0);
			if (texture != 0)
			{
				//char *textureName = (char*)texture->GetUserDataPtr();
				fileName = texture->GetFileName();
				return true;
			}
		}
	}

	// Check for standard textures
	else 
	{
		const int numTextures = fbxProperty.GetSrcObjectCount<FbxFileTexture>();
		if (numTextures > 0)
		{
			// Get only the first texture with index 0
			const FbxFileTexture* texture = fbxProperty.GetSrcObject<FbxFileTexture>(0);
			if (texture != 0)
			{
				//char *textureName = (char*)texture->GetUserDataPtr();
				fileName = texture->GetFileName();
				return true;
			}
		}
	}

	return false;
}

MwVector4 MwFbxScene::GetMaterialPropertyColor(const FbxProperty &fbxProperty)
{
	if (!fbxProperty.IsValid())
		return MwVector4(0.0f, 0.0f, 0.0f, 1.0f);

	FbxDouble3 colorValue = fbxProperty.Get<FbxDouble3>();
	return MwVector4((float)colorValue[0], (float)colorValue[1], (float)colorValue[2], 1.0f);
}

float MwFbxScene::GetMaterialPropertyColorFactor(const FbxProperty &fbxProperty)
{
	if (!fbxProperty.IsValid())
		return 1.0f;

	return (float)fbxProperty.Get<FbxDouble>();
}

MwMaterial *MwFbxScene::AcquireNodeMaterial(FbxSurfaceMaterial *fbxMaterial)
{
	MwBaseResource *existingMaterial;
	if (this->resourceMap.GetValue(fbxMaterial, existingMaterial))
	{
		return (MwMaterial*)existingMaterial;
	}
					
	MwMaterial *material = (MwMaterial*)this->context->AddResource(*new MwMaterial(*this->context));
	material->name = this->context->AcquireResourceName(MwString(fbxMaterial->GetName()), material->resourceType);

	this->resourceMap.Add(fbxMaterial, material);

	material->AddShaderSlot(MwShaderOperation_Material, MwColorOperation_None);

	MwString textureName;
	MwVector4 colorValue;
	FbxProperty color;
			
	material->AddShaderSlot(MwShaderOperation_LightSource, MwColorOperation_None);
	material->AddShaderSlot(MwShaderOperation_LightSource, MwColorOperation_None);

	bool usePixelLighting = false;
	color = fbxMaterial->FindProperty(FbxSurfaceMaterial::sNormalMap);
	if (this->GetMaterialPropertyTextureName(color, textureName))
	{
		MwTexture2D *texture = this->context->AcquireTexture(textureName);
		if (texture != 0)
		{
			material->AddShaderSlot(MwShaderOperation_NormalMap, MwColorOperation_Set);
			material->GetProperty("Normal Map")->SetReference(MwParameterType_ReferenceTexture, texture);

			usePixelLighting = true;
		}
	}

	if (usePixelLighting)
		material->AddShaderSlot(MwShaderOperation_PixelLighting, MwColorOperation_Set);
	else
		material->AddShaderSlot(MwShaderOperation_VertexLighting, MwColorOperation_Set);


	color = fbxMaterial->FindProperty(FbxSurfaceMaterial::sAmbient);
	if (this->GetMaterialPropertyTextureName(color, textureName))
	{
	}
	else
	{
		FbxProperty colorFactor = fbxMaterial->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
		MwVector4::Scale(colorValue, this->GetMaterialPropertyColor(color), this->GetMaterialPropertyColorFactor(colorFactor));
		material->GetProperty("Ambient")->SetColor(colorValue);
	}
			
	color = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	if (this->GetMaterialPropertyTextureName(color, textureName))
	{
		MwTexture2D *texture = this->context->AcquireTexture(textureName);
		if (texture != 0)
		{
			material->AddShaderSlot(MwShaderOperation_ColorMap, MwColorOperation_Modulate);
			material->GetProperty("Color Map")->SetReference(MwParameterType_ReferenceTexture, texture);
		}
	}
	else
	{
		FbxProperty colorFactor = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
		MwVector4::Scale(colorValue, this->GetMaterialPropertyColor(color), this->GetMaterialPropertyColorFactor(colorFactor));
		material->GetProperty("Diffuse")->SetColor(colorValue);
	}
			
	color = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
	if (this->GetMaterialPropertyTextureName(color, textureName))
	{
	}
	else
	{
		FbxProperty colorFactor = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
		MwVector4::Scale(colorValue, this->GetMaterialPropertyColor(color), this->GetMaterialPropertyColorFactor(colorFactor));
		material->GetProperty("Specular")->SetColor(colorValue);
	}
			
	color = fbxMaterial->FindProperty(FbxSurfaceMaterial::sReflection);
	if (this->GetMaterialPropertyTextureName(color, textureName))
	{
		MwTexture2D *texture = this->context->AcquireTexture(textureName);
		if (texture != 0)
		{
			material->AddShaderSlot(MwShaderOperation_EnvMap, MwColorOperation_Add);
			material->GetProperty("Reflection Map")->SetReference(MwParameterType_ReferenceTexture, texture);
		}
	}

	FbxProperty shininess = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
	material->GetProperty("Gloss")->SetFloat(this->GetMaterialPropertyColorFactor(shininess));
	
	material->UpdateShader();

	return material;
}

void MwFbxScene::LoadMesh_Vertices(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh, MwMatrix &geometryTransform)
{
	// Load Vertices
	int numVertices = fbxMesh->GetControlPointsCount();
	FbxVector4 *verticesFbx = fbxMesh->GetControlPoints(); 
	deviceMesh->CreateVertexBuffer(numVertices);
	MwVector4 nullBone(0.0f);
	for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
	{
		MwVector3 position(this->FbxToMwVector3(verticesFbx[vertexIndex]));
		//MwVector3::Transform(position, position, geometryTransform);
		deviceMesh->SetVertexPosition(vertexIndex, position);

		deviceMesh->SetVertexBones(vertexIndex, nullBone, nullBone);
	}
}

void MwFbxScene::LoadMesh_TextureCoords(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh)
{
	int numLayers = fbxMesh->GetLayerCount();
	for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
	{
		FbxLayer *layer = fbxMesh->GetLayer(layerIndex);
		
		FbxLayerElementUV *layerUV = layer->GetUVs();
        if (layerUV != 0)
		{
			FbxLayerElement::EMappingMode mappingMode = layerUV->GetMappingMode();
			FbxLayerElement::EReferenceMode referenceMode = layerUV->GetReferenceMode();

			const bool useIndex = referenceMode != FbxGeometryElement::eDirect;
			const int numPolygons = fbxMesh->GetPolygonCount();

			if (mappingMode == FbxGeometryElement::eByControlPoint )
			{
				int numVertices = fbxMesh->GetControlPointsCount();
				for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
				{
					int texCoordsIndex = useIndex ? layerUV->GetIndexArray().GetAt(vertexIndex) : vertexIndex;
					MwVector2 texCoords = this->FbxToMwVector2(layerUV->GetDirectArray().GetAt(texCoordsIndex));
					
					deviceMesh->SetVertexTexCoords(vertexIndex, texCoords);
				}
			}

			// If uv is per polygon means each polygon has own uv mapping. Normally, this means polygons that share the same vertex position may have different uv, which requires to create a new vertex, but instead we'll only write to the existing vertices
			else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
			{
				const int numIndices = (useIndex) ? layerUV->GetIndexArray().GetCount() : 0;
				
				int index = 0;
				for (int polyIndex = 0; polyIndex < numPolygons; polyIndex++)
				{
					const int numPolyVertices = fbxMesh->GetPolygonSize(polyIndex);
					for (int polyVertexIndex = 0; polyVertexIndex < numPolyVertices; polyVertexIndex++)
					{
						if (index < numIndices)
						{
							int texCoordsIndex = useIndex ? layerUV->GetIndexArray().GetAt(index) : index;
							MwVector2 texCoords = this->FbxToMwVector2(layerUV->GetDirectArray().GetAt(texCoordsIndex));

							deviceMesh->SetVertexTexCoords(fbxMesh->GetPolygonVertex(polyIndex, polyVertexIndex), texCoords);

							index++;
						}
					}
				}
			}
		}
	}
}

bool MwFbxScene::LoadMesh_Animation(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh)
{
	bool result = false;
	int numDeformers = fbxMesh->GetDeformerCount();
	FbxSkin* skin = (FbxSkin*)fbxMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (skin != 0)
	{
		// Max 64 bones. Parameterize this, or make renderer bone limit to be read
		int boneCount = MwMath::Min(skin->GetClusterCount(), 64);
		int validBoneIndex = 0;
		for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		{
			FbxCluster* cluster = skin->GetCluster(boneIndex);
			FbxNode* bone = cluster->GetLink();

			MwBaseResource *mwBone;
			if (this->resourceMap.GetValue(bone, mwBone))
			{
				result = true;
				MwTransform *boneTransform = (MwTransform*)mwBone;
				boneTransform->Process();
				boneTransform->properties[MwTransform::propertyIndex_BoneIndex]->SetInt(boneIndex);
				boneTransform->properties[MwTransform::propertyIndex_Bone]->SetBool(true);

				FbxAMatrix bindPoseMatrix;
				cluster->GetTransformLinkMatrix(bindPoseMatrix);
				this->FbxToMwMatrix(boneTransform->boneBindPoseInverse, &bindPoseMatrix);
				MwMatrix::Invert(boneTransform->boneBindPoseInverse, boneTransform->boneBindPoseInverse);

				int *boneVertexIndices = cluster->GetControlPointIndices();
				double *boneVertexWeights = cluster->GetControlPointWeights();

				int numBoneVertexIndices = cluster->GetControlPointIndicesCount();
				for (int boneVertexIndex = 0; boneVertexIndex < numBoneVertexIndices; boneVertexIndex++) 
				{
					MwVector4 boneIndices, boneWeights;
					deviceMesh->GetVertexBones(boneVertexIndices[boneVertexIndex], boneIndices, boneWeights);
					if (boneWeights.x == 0.0f)
					{
						boneIndices.x = (float)validBoneIndex;
						boneWeights.x = (float)boneVertexWeights[boneVertexIndex];
						deviceMesh->SetVertexBones(boneVertexIndices[boneVertexIndex], boneIndices, boneWeights);
					}
					else if (boneWeights.y == 0.0f)
					{
						boneIndices.y = (float)validBoneIndex;
						boneWeights.y = (float)boneVertexWeights[boneVertexIndex];
						deviceMesh->SetVertexBones(boneVertexIndices[boneVertexIndex], boneIndices, boneWeights);
					}
					else if (boneWeights.z == 0.0f)
					{
						boneIndices.z = (float)validBoneIndex;
						boneWeights.z = (float)boneVertexWeights[boneVertexIndex];
						deviceMesh->SetVertexBones(boneVertexIndices[boneVertexIndex], boneIndices, boneWeights);
					}
					else if (boneWeights.w == 0.0f)
					{
						boneIndices.w = (float)validBoneIndex;
						boneWeights.w = (float)boneVertexWeights[boneVertexIndex];
						deviceMesh->SetVertexBones(boneVertexIndices[boneVertexIndex], boneIndices, boneWeights);
					}
				}

				validBoneIndex++;
			}
			else
			{
				// Debug tests
				MwString boneName = bone->GetName();

				// Get default attribute
				FbxNodeAttribute *nodeAttributeFbx = bone->GetNodeAttribute();
				if (nodeAttributeFbx != 0)
					FbxNodeAttribute::EType attributeType = nodeAttributeFbx->GetAttributeType();

				// Get all attributes
				int numAttributes = bone->GetNodeAttributeCount();
				for (int i = 0; i < numAttributes; i++)
				{
					FbxNodeAttribute *nodeAttributeFbx = bone->GetNodeAttributeByIndex(i);

					MwString name = MwString(bone->GetName());

					FbxNodeAttribute::EType attributeType = nodeAttributeFbx->GetAttributeType();
				}

			}
		}
	}

	return result;
}

MwSmoothGrouping* MwFbxScene::LoadMesh_CreateSmoothGrouping(FbxMesh *fbxMesh)
{
	// If no smoothing information is present, use fbx to generate it - first, compute soft/hard edge info from mesh normals, then convert the soft/hard edge info to smoothing group info
	FbxGeometryElementSmoothing *smoothing = fbxMesh->GetElementSmoothing();
	if (smoothing == 0)
	{
		FbxGeometryConverter geometryConverter(this->fbxManager);
		geometryConverter.ComputeEdgeSmoothingFromNormals(fbxMesh);
	    geometryConverter.ComputePolygonSmoothingFromEdgeSmoothing(fbxMesh);
		
		smoothing = fbxMesh->GetElementSmoothing();
	}
	// If smoothing information is present, but mapping is by edge, convert the soft/hard edge info to smoothing group info.
	else
	{
		if (smoothing->GetMappingMode() == FbxGeometryElement::eByEdge)
		{
			FbxGeometryConverter geometryConverter(this->fbxManager);
			geometryConverter.ComputePolygonSmoothingFromEdgeSmoothing(fbxMesh);
		}
	}

	int numPolygons = fbxMesh->GetPolygonCount();
	int numVertices = fbxMesh->GetControlPointsCount();
	
	if (smoothing != 0)
	{
		FbxLayerElement::EMappingMode mappingMode = smoothing->GetMappingMode();
		FbxLayerElement::EReferenceMode referenceMode = smoothing->GetReferenceMode();

		bool useIndexing = referenceMode != FbxGeometryElement::eDirect;

		if (mappingMode == FbxGeometryElement::eByPolygon)
		{
			MwSmoothGrouping *smoothGrouping = new MwSmoothGrouping(numPolygons, numVertices);

			for (int polyIndex = 0; polyIndex < numPolygons; polyIndex++)
			{
				int smoothingIndex = useIndexing ? smoothing->GetIndexArray().GetAt(polyIndex) : polyIndex;
				int smoothingGroupFlags = smoothing->GetDirectArray().GetAt(smoothingIndex);

				smoothGrouping->SetFaceSmoothingGroups(polyIndex, smoothingGroupFlags);

				int numPolygonVertices = fbxMesh->GetPolygonSize(polyIndex);
				for (int polyVertexIndex = 0; polyVertexIndex < numPolygonVertices; polyVertexIndex++)
				{
					smoothGrouping->AddFaceVertex(polyIndex, fbxMesh->GetPolygonVertex(polyIndex, polyVertexIndex));
				}
			}

			return smoothGrouping;
		}
	}

	
	// Backup case - if smooth grouping could not be created because of some reason, create a default one with all faces of the same smoothing group
	MwSmoothGrouping *smoothGrouping = new MwSmoothGrouping(numPolygons, numVertices);
	for (int polyIndex = 0; polyIndex < numPolygons; polyIndex++)
	{
		smoothGrouping->SetFaceSmoothingGroups(polyIndex, 1);

		int numPolygonVertices = fbxMesh->GetPolygonSize(polyIndex);
		for (int polyVertexIndex = 0; polyVertexIndex < numPolygonVertices; polyVertexIndex++)
		{
			smoothGrouping->AddFaceVertex(polyIndex, fbxMesh->GetPolygonVertex(polyIndex, polyVertexIndex));
		}
	}

	return smoothGrouping;
}

void MwFbxScene::LoadMesh(MwEntitySet *entitySet, FbxMesh *fbxMesh, MwMatrix &geometryTransform)
{
	MwDeviceIndependentMesh *vertexDataMesh= new MwDeviceIndependentMesh();

	// Load vertices' position. Faces will be load at the end, as they might have more than 3 vertices
	this->LoadMesh_Vertices(vertexDataMesh, fbxMesh, geometryTransform);
	
	// Load vertices' texture coordinates
	this->LoadMesh_TextureCoords(vertexDataMesh, fbxMesh);

	// Load vertices bone indices and weights, if any, and setup the transforms of the skeleton. The transforms of the skeleton must be already loaded
	bool isAnimated = this->LoadMesh_Animation(vertexDataMesh, fbxMesh);

	// Load the smoothing groups data
	MwSmoothGrouping *smoothGrouping = this->LoadMesh_CreateSmoothGrouping(fbxMesh);

	// Create a temporary mesh, whith geometry affected by the smoothing groups and calculate its normals.
	// This mesh will later be used to get vertex information for the final meshes, which will additionally be affected by sub materials
	MwDeviceIndependentMesh smoothGroupedMesh;
	// Fill vertices
	MwVector2 v2;
	MwVector3 v3;
	MwVector4 v41, v42;
	smoothGroupedMesh.CreateVertexBuffer(smoothGrouping->vertexIndices.count);
	for (int vertexIndex = 0; vertexIndex < smoothGrouping->vertexIndices.count; vertexIndex++)
	{
		int originalVertexIndex = smoothGrouping->vertexIndices[vertexIndex].index;
						
		vertexDataMesh->GetVertexPosition(originalVertexIndex, v3);
		smoothGroupedMesh.SetVertexPosition(vertexIndex, v3);

		vertexDataMesh->GetVertexNormal(originalVertexIndex, v3);
		smoothGroupedMesh.SetVertexNormal(vertexIndex, v3);

		vertexDataMesh->GetVertexTexCoords(originalVertexIndex, v2);
		smoothGroupedMesh.SetVertexTexCoords(vertexIndex, v2);

		vertexDataMesh->GetVertexBones(originalVertexIndex, v41, v42);
		smoothGroupedMesh.SetVertexBones(vertexIndex, v41, v42);
	}
	int numTriangles = 0;
	for (int faceIndex = 0; faceIndex < smoothGrouping->faces.count; faceIndex++)
		numTriangles += smoothGrouping->faces[faceIndex].indices.count - 2;
	// Now fill the triangles
	smoothGroupedMesh.CreateIndexBuffer(numTriangles * 3);
	int index = 0;
	for (int faceIndex = 0; faceIndex < smoothGrouping->faces.count; faceIndex++)
	{
		int numFaceVertices = smoothGrouping->faces[faceIndex].indices.count;

		// As in the native obj scene
		// In case of polygons with any number of sides, use the first vertex to form a triangle fan with the rest vertices
		int zeroVertexIndex = smoothGrouping->faces[faceIndex].indices[0];
		for (int polyVertexIndex = 2; polyVertexIndex < numFaceVertices; polyVertexIndex++)
		{
			smoothGroupedMesh.SetIndex(index++, zeroVertexIndex);
			smoothGroupedMesh.SetIndex(index++, smoothGrouping->faces[faceIndex].indices[polyVertexIndex]);
			smoothGroupedMesh.SetIndex(index++, smoothGrouping->faces[faceIndex].indices[polyVertexIndex - 1]);
		}
	}
	MwGenerateNormals(*(MwDeviceMesh*)(&smoothGroupedMesh));
	delete vertexDataMesh;


	// Materials and submaterials. Divide the mesh into sub meshes for the sub materials
	// Materials for a mesh may be mapped onto the whole mesh (FbxLayerElement::EMappingMode::eAllSame) or a number of materials may be mapped to each polygon (FbxLayerElement::EMappingMode::eByPolygon)
	// If it's a whole mesh material, we simply put the material into meshwork, followed by the mesh
	// If however, there are multiple materials mapped to different polygons of the mesh, we split the mesh into submeshes, each of the submeshes with its respective material
	int numLayers = fbxMesh->GetLayerCount();
	for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
	{
		FbxLayer *layer = fbxMesh->GetLayer(layerIndex);

		FbxLayerElementMaterial *layerMaterial = layer->GetMaterials();
		if (layerMaterial != 0)
		{
			FbxLayerElement::EMappingMode mappingMode = layerMaterial->GetMappingMode();
			FbxLayerElement::EReferenceMode referenceMode = layerMaterial->GetReferenceMode();
			
			switch (mappingMode)
			{
				// One material to the whole mesh
				case FbxLayerElement::EMappingMode::eAllSame:
				{
					FbxLayerElementArrayTemplate<int> &polygonMaterialIndices = layerMaterial->GetIndexArray();
					FbxSurfaceMaterial *meshMaterial = fbxMesh->GetNode()->GetMaterial(polygonMaterialIndices.GetAt(0));
					
					// Add the material
					MwMaterial *material = this->AcquireNodeMaterial(meshMaterial);
					entitySet->references.Add(material);

					// Add skinning operation to material, if the mesh is animated
					if (isAnimated)
					{
						material->InsertShaderSlot(MwShaderOperation_Skinning, MwColorOperation_None, 0);
						material->UpdateShader();
					}
					
					// Add the mesh
					MwMesh *mesh = (MwMesh*)entitySet->references.Add(this->context->AddResource(*new MwMesh(*this->context)));
					mesh->name = this->context->AcquireResourceName(MwString(fbxMesh->GetNode()->GetName()), mesh->resourceType);

					// Copy smoothgrouped mesh
					int numVertices = smoothGroupedMesh.GetVertexCount();
					mesh->deviceMesh->CreateVertexBuffer(numVertices);
					for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
					{
						smoothGroupedMesh.GetVertexPosition(vertexIndex, v3);
						mesh->deviceMesh->SetVertexPosition(vertexIndex, v3);

						smoothGroupedMesh.GetVertexNormal(vertexIndex, v3);
						mesh->deviceMesh->SetVertexNormal(vertexIndex, v3);

						smoothGroupedMesh.GetVertexTexCoords(vertexIndex, v2);
						mesh->deviceMesh->SetVertexTexCoords(vertexIndex, v2);

						smoothGroupedMesh.GetVertexBones(vertexIndex, v41, v42);
						mesh->deviceMesh->SetVertexBones(vertexIndex, v41, v42);
					}


					// Now fill the triangles
					mesh->deviceMesh->CreateIndexBuffer(smoothGroupedMesh.GetIndexCount());
					int numIndices = smoothGroupedMesh.GetIndexCount();
					for (int index = 0; index < numIndices; index++)
					{
						mesh->deviceMesh->SetIndex(index, smoothGroupedMesh.GetIndex(index));
					}

					// ComputeNormals should not be called, since the normals are computed with smoothGroupedMesh and copied
					mesh->ComputeBounds();

					mesh->deviceMesh->UpdateVertices(0, mesh->deviceMesh->GetVertexCount());
					mesh->deviceMesh->UpdateIndices(0, mesh->deviceMesh->GetIndexCount());

					break;
				}
				
				// Each polygon has some material
				case FbxLayerElement::EMappingMode::eByPolygon:
				{
					// Will hold the mapping of each sub material with its respective polygon indices
					MwDictionary<FbxSurfaceMaterial*, MwList<int>*> subMaterialsPolygonsMapping;

					if ((referenceMode == FbxLayerElementMaterial::eIndex) || (referenceMode == FbxLayerElementMaterial::eIndexToDirect))
					{
						FbxLayerElementArrayTemplate<int> &polygonMaterialIndices = layerMaterial->GetIndexArray();
						int numPolygons = polygonMaterialIndices.GetCount();
						for (int polygonIndex = 0; polygonIndex < numPolygons; polygonIndex++)
						{
							FbxSurfaceMaterial *polygonMaterial = fbxMesh->GetNode()->GetMaterial(polygonMaterialIndices.GetAt(polygonIndex));

							MwList<int> *subMaterialPolygons;
							if (subMaterialsPolygonsMapping.GetValue(polygonMaterial, subMaterialPolygons))
							{
								subMaterialPolygons->Add(polygonIndex);
							}
							else
							{
								subMaterialPolygons = new MwList<int>();
								subMaterialPolygons->Add(polygonIndex);
								subMaterialsPolygonsMapping.Add(polygonMaterial, subMaterialPolygons);
							}
						}
					}



					// Create the submeshes and free the materialPolygons dictionary
					MwSubMesh subMesh(smoothGrouping->vertexIndices.count);
					void* node = subMaterialsPolygonsMapping.GetNodeNext(0);
					while (node != 0)
					{
						FbxSurfaceMaterial *subMaterial = subMaterialsPolygonsMapping.GetNodeValue(node).key;
						MwList<int> *subMaterialPolygons = subMaterialsPolygonsMapping.GetNodeValue(node).value;
					
						// Add the material
						MwMaterial *material = this->AcquireNodeMaterial(subMaterial);
						entitySet->references.Add(material);

						// Add skinning operation to material, if the mesh is animated
						if (isAnimated)
						{
							material->InsertShaderSlot(MwShaderOperation_Skinning, MwColorOperation_None, 0);
							material->UpdateShader();
						}

						// Add the mesh which will hold the polygons of the material
						MwMesh *mesh = (MwMesh*)entitySet->references.Add(this->context->AddResource(*new MwMesh(*this->context)));
						mesh->name = this->context->AcquireResourceName(MwString(fbxMesh->GetNode()->GetName()) + " " + material->name, mesh->resourceType);

						// Generate the polygons and vertices as a submesh of the whole geometry
						// subMesh, as well as the original fbx mesh may have polygons with more then 3 vertices, so we'll count the number of triangles the submesh will have
						int numSubMaterialTriangles = 0;
						for (int subMaterialPolygonIndex = 0; subMaterialPolygonIndex < subMaterialPolygons->count; subMaterialPolygonIndex++)
						{
							// Get the submaterial's polygon index in the original fbx mesh. This index also matches the index of the polygon in the smooth grouping
							int polygonIndex = subMaterialPolygons->Get(subMaterialPolygonIndex);

							subMesh.AddFace();
							const int numPolygonVertices = smoothGrouping->faces[polygonIndex].indices.count;
							for (int polyVertexIndex = 0; polyVertexIndex < numPolygonVertices; polyVertexIndex++)
							{
								// As a vace vertex index of the sub mesh, add in index to a vertex of the smooth grouping
								int vertexIndex = smoothGrouping->faces[polygonIndex].indices[polyVertexIndex];
								subMesh.AddFaceVertex(subMaterialPolygonIndex, vertexIndex);
							}
							numSubMaterialTriangles += numPolygonVertices - 2;
						}


						// Fill vertices
						mesh->deviceMesh->CreateVertexBuffer(subMesh.vertexIndices.count);
						for (int vertexIndex = 0; vertexIndex < subMesh.vertexIndices.count; vertexIndex++)
						{
							int originalVertexIndex = subMesh.vertexIndices[vertexIndex];
						
							smoothGroupedMesh.GetVertexPosition(originalVertexIndex, v3);
							mesh->deviceMesh->SetVertexPosition(vertexIndex, v3);

							smoothGroupedMesh.GetVertexNormal(originalVertexIndex, v3);
							mesh->deviceMesh->SetVertexNormal(vertexIndex, v3);

							smoothGroupedMesh.GetVertexTexCoords(originalVertexIndex, v2);
							mesh->deviceMesh->SetVertexTexCoords(vertexIndex, v2);

							smoothGroupedMesh.GetVertexBones(originalVertexIndex, v41, v42);
							mesh->deviceMesh->SetVertexBones(vertexIndex, v41, v42);
						}


						// Now fill the triangles
						mesh->deviceMesh->CreateIndexBuffer(numSubMaterialTriangles * 3);
						int index = 0;
						for (int faceIndex = 0; faceIndex < subMesh.faces.count; faceIndex++)
						{
							int numFaceVertices = subMesh.faces[faceIndex]->indices.count;

							// As in the native obj scene
							// In case of polygons with any number of sides, use the first vertex to form a triangle fan with the rest vertices
							int zeroVertexIndex = subMesh.faces[faceIndex]->indices[0];
							for (int polyVertexIndex = 2; polyVertexIndex < numFaceVertices; polyVertexIndex++)
							{
								mesh->deviceMesh->SetIndex(index++, zeroVertexIndex);
								mesh->deviceMesh->SetIndex(index++, subMesh.faces[faceIndex]->indices[polyVertexIndex]);
								mesh->deviceMesh->SetIndex(index++, subMesh.faces[faceIndex]->indices[polyVertexIndex - 1]);
							}

						}

						// ComputeNormals should not be called, since the normals are computed with smoothGroupedMesh and copied
						mesh->ComputeBounds();

						mesh->deviceMesh->UpdateVertices(0, mesh->deviceMesh->GetVertexCount());
						mesh->deviceMesh->UpdateIndices(0, mesh->deviceMesh->GetIndexCount());

						// Reset the submesh to make it ready for another go
						subMesh.Reset();
					
						delete subMaterialPolygons;
						node = subMaterialsPolygonsMapping.GetNodeNext(node);
					}

					break;
				}
			}
		}
	}

	if (smoothGrouping != 0)
		delete smoothGrouping;
}



void MwFbxScene::LoadNode(MwEntitySet *entitySet, FbxNode* fbxNode, FbxNodeAttribute::EType loadType)
{
	if (loadType == FbxNodeAttribute::eSkeleton)
	{
	entitySet = (MwEntitySet*)entitySet->references.Add(this->context->AddResource(*new MwEntitySet()));
	entitySet->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), entitySet->resourceType);

	// Transform
	MwTransform *transform = (MwTransform*)entitySet->references.Add(this->context->AddResource(*new MwTransform()));
	transform->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), transform->resourceType);
	if (!this->LoadNodeKeyframeAnimation(entitySet, fbxNode, transform))
		this->LoadNodeDefaultTransform(transform, fbxNode);

	this->resourceMap.Add(fbxNode, transform);
	}

	MwString name = MwString(fbxNode->GetName());

	int numAttributes = fbxNode->GetNodeAttributeCount();
	for (int i = 0; i < numAttributes; i++)
	{
		FbxNodeAttribute *nodeAttributeFbx = fbxNode->GetNodeAttributeByIndex(i);

		MwString attributeName = MwString(nodeAttributeFbx->GetName());

		FbxNodeAttribute::EType attributeType = nodeAttributeFbx->GetAttributeType();

		if (attributeType == loadType)
		{
			switch (attributeType)
			{
				case FbxNodeAttribute::eCamera:
				{
					FbxCamera *fbxCamera = (FbxCamera*)nodeAttributeFbx;

					// Transform
					MwTransform *transform = (MwTransform*)entitySet->references.Add(this->context->AddResource(*new MwTransform()));
					transform->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), transform->resourceType);
					MwMatrix::CreateOrientedPosition(transform->manual, this->FbxToMwVector3(fbxCamera->Position.Get()), this->FbxToMwVector3(fbxCamera->InterestPosition.Get()), MwVector3(0.0f, 0.0f, 1.0f)); // Get both position and orientation

					MwCamera *camera = (MwCamera*)entitySet->references.Add(this->context->AddResource(*new MwCamera(this->context)));
					camera->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), MwResourceType_Camera);

					camera->properties[MwCamera::propertyIndex_FOV]->SetFloat((float)fbxCamera->FieldOfView * MwMath::Pi / 180.0f);
					
					break;
				}

				case FbxNodeAttribute::eLight:
				{
					FbxLight *fbxLight = (FbxLight*)nodeAttributeFbx;

					// Transform
					MwTransform *transform = (MwTransform*)entitySet->references.Add(this->context->AddResource(*new MwTransform()));
					transform->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), transform->resourceType);
					if (!this->LoadNodeKeyframeAnimation(entitySet, fbxNode, transform))
						this->LoadNodeDefaultTransform(transform, fbxNode);

					MwLight *light = (MwLight*)entitySet->references.Add(this->context->AddResource(*new MwLight()));
					light->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), MwResourceType_Light);

					light->properties[MwLight::propertyIndex_Color]->SetColor(MwVector4(this->FbxToMwVector3(fbxLight->Color.Get()), 1.0f));
					light->properties[MwLight::propertyIndex_Intensity]->SetFloat((float)fbxLight->FarAttenuationEnd.Get());
					
					break;
				}

				case FbxNodeAttribute::eMesh:
				{
					entitySet = (MwEntitySet*)entitySet->references.Add(this->context->AddResource(*new MwEntitySet()));
					entitySet->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), entitySet->resourceType);

					// Transform
					MwTransform *transform = (MwTransform*)entitySet->references.Add(this->context->AddResource(*new MwTransform()));
					transform->name = this->context->AcquireResourceName(MwString(fbxNode->GetName()), MwResourceType_Transform);
					if (!this->LoadNodeKeyframeAnimation(entitySet, fbxNode, transform))
						this->LoadNodeDefaultTransform(transform, fbxNode);

					// Geometric transform required to be applied on vertex positions
					MwMatrix geometryTransform;
					this->GetNodeGeometryTransform(geometryTransform, fbxNode);

					// Load mesh data
					this->LoadMesh(entitySet, (FbxMesh*)nodeAttributeFbx, geometryTransform);

					break;
				}

				case FbxNodeAttribute::eSkeleton:
				{
					//FbxSkeleton *fbxSkeleton = (FbxSkeleton*)nodeAttributeFbx;

					//FbxSkeleton::EType skeletonType = fbxSkeleton->GetSkeletonType();


					break;
				}
			}
		}
	}

	int numChildren = fbxNode->GetChildCount();
	for(int i = 0; i < numChildren; i++)
	{
		this->LoadNode(entitySet, fbxNode->GetChild(i), loadType);
	}
}

bool MwFbxScene::Load(MwBaseStream &source)
{
	MwString fileName = this->context->serializationParameters.fullSourceName;
	
    // Initialize the SDK manager. This object handles all our memory management.
    this->fbxManager = FbxManager::Create();
    
    // Create the IO settings object.
    FbxIOSettings *ioSettings = FbxIOSettings::Create(this->fbxManager, IOSROOT);
    this->fbxManager->SetIOSettings(ioSettings);

    // Create an importer using the SDK manager.
    FbxImporter* importer = FbxImporter::Create(this->fbxManager, "MwFbxManager");
    
    // Use the first argument as the filename for the importer.
	if (!importer->Initialize(fileName.GetCharContents(), -1, this->fbxManager->GetIOSettings()))
	{
		this->fbxManager->Destroy();
		return false;
	}

    // Create a new scene so that it can be populated by the imported file.
    this->fbxScene = FbxScene::Create(this->fbxManager, "MwFbxScene");

    // Import the contents of the file into the scene.
	if (!importer->Import(this->fbxScene))
	{
	    this->fbxManager->Destroy();
		return false;
	}

	// The file is imported; so get rid of the importer.
    importer->Destroy();


	MwEntitySet *parent = (MwEntitySet*)this->context->root;
	
	MwEntitySet *importSet = (MwEntitySet*)parent->references.Add(this->context->AddResource(*new MwEntitySet()));
	importSet->name = this->context->AcquireResourceName(this->context->serializationParameters.friendlyName, importSet->resourceType);

	FbxNode* fbxRootNode = this->fbxScene->GetRootNode();
    if (fbxRootNode != 0)
	{
		// Add an animation frame mechanism
		this->animationFrame = (MwLinearMechanism*)this->context->AddResource(*new MwLinearMechanism(0.0f, 0.0f, 1.0f, false));
		this->animationFrame->name = this->context->AcquireResourceName(importSet->name + " frame", MwResourceType_Mechanism);
		importSet->references.Add(this->animationFrame);

		// Cameras first
		this->LoadNode(importSet, fbxRootNode, FbxNodeAttribute::eCamera);

		// Lights
		this->LoadNode(importSet, fbxRootNode, FbxNodeAttribute::eLight);

		// Add a transform to act as a conversion between fbx and mw coord systems, as well as a glabal transform for the whole fbx content
		MwTransform *transform = (MwTransform*)importSet->references.Add(this->context->AddResource(*new MwTransform()));
		transform->name = this->context->AcquireResourceName(importSet->name, transform->resourceType);
		MwMatrix::CreateRotationX(transform->manual, -MwMath::PiHalf);

		this->LoadNode(importSet, fbxRootNode, FbxNodeAttribute::eSkeleton);
		this->LoadNode(importSet, fbxRootNode, FbxNodeAttribute::eMesh);
    }


    // Destroy the SDK manager and all the other objects it was handling.
	this->fbxManager->Destroy();

	return true;
}

bool MwFbxScene::Save(MwBaseStream &destination, const char *format)
{
	return false;
}
