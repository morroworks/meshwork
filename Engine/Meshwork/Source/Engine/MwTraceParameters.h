#pragma once

#include "..\MwGlobals.h"

#include "Primitive\MwMatrix.h"

#include "Entities\Mesh\MwMesh.h"
#include "Entities\Camera\MwCamera.h"
#include "Entities\Transform\MwTransform.h"
#include "Entities\Material\MwMaterial.h"
#include "Entities\EntitySet\MwEntitySet.h"
#include "Entities\Mechanisms\MwBaseMechanism.h"
#include "Entities\Textures\MwTexture2D.h"
#include "Entities\Light\MwLight.h"
#include "Entities\SoundEmitter\MwSoundEmitter.h"
#include "Entities\SoundReceptor\MwSoundReceptor.h"

class MWDLLCLASS MwTraceParameters
{
public:
	    MwMesh *meshRef;
        MwEntitySet *meshBranch;
		int meshIndex;

		MwCamera *cameraRef;
        MwEntitySet *cameraBranch;
		int cameraIndex;
        
		MwMaterial *materialRef;
        MwEntitySet *materialBranch;
		int materialIndex;

		MwTransform *transformRef;
        MwEntitySet *transformBranch;
		int transformIndex;

		MwLight *lightRef;
        MwEntitySet *lightBranch;
		int lightIndex;

		MwSoundEmitter *soundEmitterRef;
        MwEntitySet *soundEmitterBranch;
		int soundEmitterIndex;

		MwSoundReceptor *soundReceptorRef;
        MwEntitySet *soundReceptorBranch;
		int soundReceptorIndex;

		MwBaseMechanism *mechanismRef;

		MwTexture2D *textureRef, *renderTargetRef;

        MwMatrix parentTransform;

        MwTraceParameters(void);
        MwTraceParameters(MwTraceParameters &parent);
		~MwTraceParameters(void);
};

