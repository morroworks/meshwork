#pragma once

#include "Engine\Meshwork.h"
#include "Engine\MwRayIntersectionEvents.h"
#include "Engine\MwRenderEvents.h"
#include "Engine\MwScreenPickEvents.h"
#include "Engine\MwTraceEvents.h"
#include "Engine\MwTraceParameters.h"
#include "Engine\MwStandardEntityDispatcher.h"

#include "Engine\Base\MwBaseResource.h"
#include "Engine\Base\MwResourceType.h"
#include "Engine\Base\MwEntity.h"
#include "Engine\Base\MwEntityDispatcher.h"
#include "Engine\Base\MwDispatcher.h"

#include "Engine\Entities\Camera\MwCamera.h"

#include "Engine\Entities\Material\MwMaterial.h"
#include "Engine\Entities\Material\MwMaterialShaderSlot.h"

#include "Engine\Entities\Mechanisms\MwBaseMechanism.h"
#include "Engine\Entities\Mechanisms\MwDirectionLagMechanism.h"
#include "Engine\Entities\Mechanisms\MwDirectionMechanism.h"
#include "Engine\Entities\Mechanisms\MwFloatMechanism.h"
#include "Engine\Entities\Mechanisms\MwKeyframeAnimationMechanism.h"
#include "Engine\Entities\Mechanisms\MwLinearMechanism.h"
#include "Engine\Entities\Mechanisms\MwLinearInterpolationMechanism.h"
#include "Engine\Entities\Mechanisms\MwNegateFloatMechanism.h"
#include "Engine\Entities\Mechanisms\MwPivotalMechanism.h"
#include "Engine\Entities\Mechanisms\MwSineMechanism.h"
#include "Engine\Entities\Mechanisms\MwTimeRateMechanism.h"

#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrame.h"
#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameRotationAxis.h"
#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameRotationEuler.h"
#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameScaling.h"
#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFramesTrack.h"
#include "Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameTranslation.h"

#include "Engine\Entities\Mesh\MwMesh.h"

#include "Engine\Entities\EntitySet\MwEntitySet.h"

#include "Engine\Entities\Sound\MwSound.h"

#include "Engine\Entities\SoundEmitter\MwSoundEmitter.h"

#include "Engine\Entities\SoundReceptor\MwSoundReceptor.h"

#include "Engine\Entities\Textures\MwTexture2D.h"

#include "Engine\Entities\Script\MwScript.h"

#include "Engine\Entities\Transform\MwTransform.h"
#include "Engine\Entities\Transform\MwTransformOperation.h"
#include "Engine\Entities\Transform\MwTransformSlot.h"

#include "Engine\Entities\Light\MwLight.h"

#include "Engine\Primitive\MwBounds.h"
#include "Engine\Primitive\MwColorOperation.h"
#include "Engine\Primitive\MwIntersectionInfo.h"
#include "Engine\Primitive\MwMatrix.h"
#include "Engine\Primitive\MwPixelFormat.h"
#include "Engine\Primitive\MwRenderState.h"
#include "Engine\Primitive\MwVector2.h"
#include "Engine\Primitive\MwVector3.h"
#include "Engine\Primitive\MwVector4.h"
#include "Engine\Primitive\MwVertex.h"

#include "Engine\Properties\MwParameter.h"
#include "Engine\Properties\MwParameterType.h"
#include "Engine\Properties\MwProperty.h"
#include "Engine\Properties\MwBoundProperty.h"

#include "Engine\Utilities\MwMaths.h"
#include "Engine\Utilities\MwTimer.h"
#include "Engine\Utilities\MwLogging.h"

#include "Engine\Utilities\Serialization\MwHierarchyStreamReader.h"
#include "Engine\Utilities\Serialization\MwHierarchyStreamWriter.h"

#include "Engine\Utilities\Geometry\MwBoxGeometry.h"
#include "Engine\Utilities\Geometry\MwConvexHullGeometry.h"
#include "Engine\Utilities\Geometry\MwCopyGeometry.h"
#include "Engine\Utilities\Geometry\MwHeightMapGeometry.h"
#include "Engine\Utilities\Geometry\MwIcosahedronGeometry.h"
#include "Engine\Utilities\Geometry\MwMergeGeometry.h"
#include "Engine\Utilities\Geometry\MwPlaneGeometry.h"
#include "Engine\Utilities\Geometry\MwSphereGeometry.h"

#include "Engine\Utilities\Normals\MwGenerateNormals.h"

#include "Engine\Utilities\TexCoords\MwPlanarTexCoords.h"
#include "Engine\Utilities\TexCoords\MwSphericalTexCoords.h"

#include "Engine\Utilities\SmoothGrouping\MwSmoothGrouping.h"
#include "Engine\Utilities\SmoothGrouping\MwSmoothGroupingPrimitiveTypes.h"

#include "Engine\Utilities\SubMesh\MwSubMesh.h"
#include "Engine\Utilities\SubMesh\MwSubMeshPrimitiveTypes.h"


#include "FileSystem\MwFileInfo.h"
#include "FileSystem\MwFileSystem.h"

#include "FileSystem\PhysicalFileSystem\MwPhysicalFileSystem.h"

#include "Graphics\MwDeviceMesh.h"
#include "Graphics\MwDeviceTexture2D.h"
#include "Graphics\MwDeviceShader.h"
#include "Graphics\MwGraphicsDevice.h"

#include "Graphics\DeviceIndependent\MwDeviceIndependentMesh.h"
#include "Graphics\DeviceIndependent\MwDeviceIndependentShader.h"

#include "Graphics\Soras\MwSorasGraphicsDeviceDispatcher.h"
#include "Graphics\Soras\MwSorasGraphicsDevice.h"
#include "Graphics\Soras\MwSorasMesh.h"
#include "Graphics\Soras\MwSorasShader.h"
#include "Graphics\Soras\MwSorasTexture2D.h"

#include "Graphics\Soras\Engine\Soras.h"
#include "Graphics\Soras\Engine\SrMesh.h"
#include "Graphics\Soras\Engine\SrRenderThread.h"
#include "Graphics\Soras\Engine\SrTexture.h"

#include "Graphics\Soras\Engine\Primitive\SrARGB.h"
#include "Graphics\Soras\Engine\Primitive\SrARGBInt.h"
#include "Graphics\Soras\Engine\Primitive\SrCullModes.h"
#include "Graphics\Soras\Engine\Primitive\SrLight.h"
#include "Graphics\Soras\Engine\Primitive\SrMaterial.h"
#include "Graphics\Soras\Engine\Primitive\SrMatrix.h"
#include "Graphics\Soras\Engine\Primitive\SrShaderOperations.h"
#include "Graphics\Soras\Engine\Primitive\SrShadingParameters.h"
#include "Graphics\Soras\Engine\Primitive\SrTextureSamplers.h"
#include "Graphics\Soras\Engine\Primitive\SrUnit.h"
#include "Graphics\Soras\Engine\Primitive\SrVector2Int.h"
#include "Graphics\Soras\Engine\Primitive\SrVector3.h"
#include "Graphics\Soras\Engine\Primitive\SrVector3Int.h"
#include "Graphics\Soras\Engine\Primitive\SrVector4.h"
#include "Graphics\Soras\Engine\Primitive\SrVector4Int.h"
#include "Graphics\Soras\Engine\Primitive\SrVertex.h"

#include "Media\MwMedia.h"

#include "Media\Image\MwImage.h"

#include "Media\Scene\MwScene.h"

#include "Media\Sound\MwSoundMedia.h"

#include "Media\Scene\Native\MwNativeFileId.h"
#include "Media\Scene\Native\MwNativeFileReader.h"
#include "Media\Scene\Native\MwNativeFileWriter.h"
#include "Media\Scene\Native\MwNativeScene.h"
#include "Media\Scene\Native\MwNativeSceneDispatcher.h"

#include "Media\Scene\3ds\Mw3dsScene.h"
#include "Media\Scene\3ds\Mw3dsSceneDispatcher.h"

#include "Media\Scene\3ds\File3ds\MwFile3ds.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsBaseObject.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsCamera.h"
#include "Media\Scene\3ds\File3ds\MwFile3ds.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsHierarchy.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsKeyFrames.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsLight.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsMaterial.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsMesh.h"
#include "Media\Scene\3ds\File3ds\MwFile3dsPrimitiveTypes.h"

#include "Media\Scene\Obj\MwObjScene.h"
#include "Media\Scene\Obj\MwObjSceneDispatcher.h"

#include "Media\Scene\Obj\FileObj\MwFileObj.h"
#include "Media\Scene\Obj\FileObj\MwFileObjMaterial.h"
#include "Media\Scene\Obj\FileObj\MwFileObjMesh.h"
#include "Media\Scene\Obj\FileObj\MwFileObjPrimitiveTypes.h"

#include "Media\Sound\Wav\MwWavSoundMedia.h"
#include "Media\Sound\Wav\MwWavSoundMediaDispatcher.h"

#include "Media\Sound\Wav\WavFile\MwWavFile.h"

#include "Script\Parsing\MwCodeBuilder.h"
#include "Script\Parsing\MwScriptToken.h"
#include "Script\Parsing\MwScriptTokens.h"

#include "Script\Processing\MwCodeProcessor.h"

#include "Sound\MwAudioDevice.h"
#include "Sound\MwAudioDeviceSound.h"
#include "Sound\MwAudioDeviceSoundEmitter.h"
#include "Sound\MwAudioDeviceSoundReceptor.h"

#include "Tools\MwDictionary.h"
#include "Tools\MwIntegralQuotientDistribution.h"
#include "Tools\MwLinkedList.h"
#include "Tools\MwSortedLinkedList.h"	
#include "Tools\MwList.h"
#include "Tools\MwMath.h"
#include "Tools\MwMem.h"
#include "Tools\MwRandomPool.h"
#include "Tools\MwStack.h"
#include "Tools\MwString.h"
#include "Tools\MwStrings.h"

#include "Tools\Networking\TCPIP\MwTcpIpConnection.h"
#include "Tools\Networking\TCPIP\MwTcpIpListener.h"
#include "Tools\Networking\TCPIP\MwTcpIpClient.h"
#include "Tools\Networking\TCPIP\MwTcpIpServer.h"

#include "Tools\Networking\WebServer\MwWebRequest.h"
#include "Tools\Networking\WebServer\MwWebResponse.h"
#include "Tools\Networking\WebServer\MwWebServer.h"

#include "Tools\Networking\WebServer\WebPageComponents\MwWebPageComponent.h"
#include "Tools\Networking\WebServer\WebPageComponents\MwWebPageFileListing.h"
#include "Tools\Networking\WebServer\WebPageComponents\MwWebPageHostName.h"

#include "Tools\OS\MwDrawSurface.h"
#include "Tools\OS\MwOSUtils.h"
#include "Tools\OS\MwWindowsForm.h"

#include "Tools\Streams\MwBaseStream.h"
#include "Tools\Streams\MwFileStream.h"
#include "Tools\Streams\MwMemoryStream.h"
#include "Tools\Streams\MwSubStream.h"

#include "Tools\Threading\MwMutex.h"
#include "Tools\Threading\MwThread.h"
#include "Tools\Threading\MwThreadsPool.h"
#include "Tools\Threading\MwThreadsPoolThread.h"