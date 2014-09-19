#pragma once

#include "..\MwGlobals.h"

#include "Base\MwEntityDispatcher.h"
#include "Base\MwDispatcher.h"

#include "MwTraceEvents.h"
#include "MwTraceParameters.h"

#include "MwRenderEvents.h"
#include "MwScreenPickEvents.h"
#include "MwRayIntersectionEvents.h"

#include "Utilities\MwTimer.h"
#include "Utilities\MwLogging.h"

#include "Entities\Light\MwLight.h"
#include "Entities\Sound\MwSound.h"

#include "..\Media\Image\MwImage.h"
#include "..\Media\Sound\MwSoundMedia.h"

#include "..\FileSystem\MwFileSystem.h"

#include "..\Graphics\MwGraphicsDevice.h"
#include "..\Sound\MwAudioDevice.h"

#include "..\Script\Parsing\MwCodeBuilder.h"
#include "..\Script\Processing\MwCodeProcessor.h"

#include "MwSerializationParameters.h"

struct MwActiveLightInfo
{
	MwLight* lightRef;
	MwMatrix lightTransform;
	MwVector3 lightPos;
	float distance;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwBaseResource*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwEntityDispatcher*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwDispatcher*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<void*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwActiveLightInfo>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwActiveLightInfo*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwMatrix>;

class MWDLLCLASS Meshwork
{
private:
	static const unsigned int SerializationId_ResourceSerialization = 0x21100000;

	long long resourceID;

	MwList<void*> loadedModules;

	// Each of activeLights1 and activeLights2 are alternating each frame to be the list of the lights currently being collected and the list of all the lights, collected in the previous scene
	MwList<MwActiveLightInfo> activeLights1, activeLights2;


	void SwapLightsLists();
	void CreateDefaultTexture();

public:
	void *windowHandle;
	MwTraceEvents *traceEvents;
    MwRenderEvents *renderEvents;
    MwRayIntersectionEvents *rayIntersectionEvents;
    MwScreenPickEvents *screenPickEvents;

    int viewportWidth, viewportHeight;
	MwVector4 ambientLighting;
    double speed;

	MwTexture2D *currentRenderTarget;

	MwLogging logging;

	MwSerializationParameters serializationParameters;

    MwList<MwBaseResource*> resources;
    MwEntitySet *root;
	MwVector4 clearColor;
    MwTimer *timer;
    
	MwFileSystem *fileSystem;

	MwGraphicsDevice *graphicsDevice;

	MwAudioDevice *audioDevice;

	MwList<MwEntityDispatcher*> entityDispatchers;

	MwList<MwDispatcher*> imageMediaDispatchers, soundMediaDispatchers, sceneMediaDispatchers, graphicsDeviceDispatchers, audioDeviceDispatchers, fileSystemDispatchers;

	// activeLights should be used as the set of lights currently affecting the scene. It is the list of all active lights, collected while rendering the last frame. activeLightsCollecting should be used to collect active lights while rendering the current frame.
	MwList<MwActiveLightInfo> *activeLights, *activeLightsCollecting;
	// Filled by the CalculateNearestLights() method, holds pointers to a number of lights from the activeLights member variable, which are the nearest to a certain point in space, sorted ascending by distance to that point
	MwList<MwActiveLightInfo*> nearestActiveLights;

	MwList<MwMatrix> bones;

	MwTexture2D *defaultTexture;

	MwCodeBuilder scriptBuilder;
	MwCodeProcessor scriptProcessor;

	Meshwork(void *windowHandle);
	~Meshwork(void);
    
	void LoadModules(MwString modulesDir = "");
	void UnloadModules();

	void SetGraphicsDevice(MwGraphicsDevice *graphicsDevice);
	int SetGraphicsDevice(const MwString &graphicsDeviceName);

	void SetAudioDevice(MwAudioDevice *audioDevice);
	int SetAudioDevice(const MwString &audioDeviceName);
    
	void Reset();

	bool ImportScene(MwBaseStream &stream);
	bool ImportScene(MwString fileName);
	bool ExportScene(MwBaseStream &stream);
	bool ExportScene(MwString fileName);

	void SetViewport(int width, int height);

	void TraceBranch(int startIndex, MwEntitySet &branch, MwTraceParameters &parameters, bool singleItem);
	void TraceWorld(MwTraceEvents &traceEvents);

	void RenderWorld();
    
    bool GetRayIntersection(MwVector3 &rayPoint1, MwVector3 &rayPoint2, MwIntersectionInfo intersectionInfo, MwTraceParameters entityInfo);
    bool Pick(int x, int y, int screenWidth, int screenHeight, MwIntersectionInfo &intersectionInfo, MwTraceParameters &entityInfo);

	void CalculateNearestActiveLights(int maxCount, MwVector3 &position);

    MwBaseResource *AddResource(MwBaseResource &resource);
	void RemoveResource(MwBaseResource *resource);
	//void RemoveResource(long long id);
	// Recursively removes each encounter of a resource from the contents of a resource set
	void RemoveResourceFromSet(MwEntitySet *resourceSet, MwBaseResource *resource);
    int GetResourceIndex(MwBaseResource &resource);
    MwBaseResource *FindResourceX(const MwString &resourceName, MwResourceType resourceType);
    MwBaseResource *FindResourceX(long long id);
    MwString AcquireResourceName(MwString &resourceName, MwResourceType resourceType);
	MwBaseResource *FindEntity(MwResourceType resourceType, MwEntitySet *entitySet = 0);
	MwBaseResource *FindEntity(const MwString &entityName, MwResourceType resourceType, MwEntitySet *entitySet = 0);

	MwImage *CreateImage(MwBaseStream &stream);
	MwImage *CreateImage(MwString fileName);

	MwTexture2D *AcquireTexture(MwString fileName);

	MwSoundMedia *CreateSoundMedia(MwBaseStream &stream);
	MwSoundMedia *CreateSoundMedia(MwString fileName, MwBaseStream **sourceStream);

	MwSound *AcquireSound(MwString fileName);

	MwEntity *CreateEntity(int typeId);
	
	void SerializeResource(MwBaseStream *destination, MwBaseResource *resource);
	MwBaseResource *DeserializeResource(MwBaseStream *source);

	MwString GetFullFileName(MwString fileName);
};
