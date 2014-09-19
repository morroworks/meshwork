#pragma once

#include "..\..\MwGlobals.h"

class MwVector2;
class MwVector3;
class MwVector4;
class MwMatrix;
class MwBounds;

class MWDLLCLASS MwMaths
{
public:
	MwMaths(void);
	~MwMaths(void);

	static bool RayTriangleIntersection(MwVector3 &rayPoint, MwVector3 &rayVector,
												MwVector3 &v0, MwVector3 &v1, MwVector3 &v2,
												float &d, float &u, float &v);
	static float RayToPerpendicularPlaneDistance(MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint);
	static float RayToPerpendicularPlaneIntersection(MwVector3 &intersection, MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint);
	static float PointToPlaneDistance(MwVector3 &point, MwVector3 &planePoint, MwVector3 &planeNormal);
	static float PointToPlaneDistance(MwVector3 &point, MwVector4 &plane);
	static float PointToPlaneProjection(MwVector3 &projection, MwVector3 &point, MwVector3 &planePoint, MwVector3 &planeNormal);
	static float RayToRayDistance(MwVector3 &ray1Point, MwVector3 &ray1Direction, MwVector3 &ray2Point, MwVector3 &ray2Direction);
	static void PerpendicularPlaneIntersection(MwVector3 &result, MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint);
	static bool SphereIntersection(MwVector3 &rayPoint, MwVector3 &rayVector,
								   MwVector3 &sphereCenter, float sphereRadius);
	static bool SphereConeIntersection(MwVector3 &conePoint, MwVector3 &coneVector, float coneAngle, MwVector3 &sphereCenter, float sphereRadius);
	static void GetBarycentricCoordinates(MwVector2 &result, MwVector3 &cartesianCoords, MwVector3 &uAxis, MwVector3 &vAxis);
	static float VectorAngle(MwVector3 &v1, MwVector3 &v2);
	static int GetPowerOf2Boundary(int value);
	static int GetBoundary(int value, int boundarySize);
	static float DegreeToRad(float degree);
	static float RadToDegree(float rad);
	static float LensToFOV(float lens, float filmSize = 36);
	static float FOVToLens(float fov, float filmSize = 36);
};

