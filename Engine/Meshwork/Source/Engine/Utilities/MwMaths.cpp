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

#include "MwMaths.h"

#include "..\..\Tools\MwMath.h"

#include "..\Primitive\MwVector2.h"
#include "..\Primitive\MwVector3.h"
#include "..\Primitive\MwVector4.h"
#include "..\Primitive\MwMatrix.h"
#include "..\Primitive\MwBounds.h"

MwMaths::MwMaths(void)
{
}


MwMaths::~MwMaths(void)
{
}

// rayVector must be normalized
bool MwMaths::RayTriangleIntersection(MwVector3 &rayPoint, MwVector3 &rayVector,
									 MwVector3 &v0, MwVector3 &v1, MwVector3 &v2,
									 float &d, float &u, float &v)
{
	MwVector3 edge1, edge2,
			perp, tvec, qvec;

	MwVector3::Subtract(edge1, v1, v0);
    MwVector3::Subtract(edge2, v2, v0);

    MwVector3::Cross(perp, rayVector, edge2);
        
    float det = MwVector3::Dot(edge1, perp);
    if (det <= 0.0f)
        return false;

    MwVector3::Subtract(tvec, rayPoint, v0);
    u = MwVector3::Dot(tvec, perp);
    if ((u < 0.0f) || (u > det))
        return false;

    MwVector3::Cross(qvec, tvec, edge1);
    v = MwVector3::Dot(rayVector, qvec);
    if ((v < 0.0f) || (u + v > det))
        return false;

    d = MwVector3::Dot(edge2, qvec);
    float fInvDet = 1.0f / det;
    d *= fInvDet;
    u *= fInvDet;
    v *= fInvDet;

    return true;
}

//planeNormal must be normalized
float MwMaths::RayToPerpendicularPlaneDistance(MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint)
{
    MwVector3 rayDir;
	MwVector3::Subtract(rayDir, planePoint, rayPoint);
    return MwVector3::Dot(rayVector, rayDir);
}
    
//planeNormal must be normalized
float MwMaths::RayToPerpendicularPlaneIntersection(MwVector3 &intersection, MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint)
{
	float distance = RayToPerpendicularPlaneDistance(rayPoint, rayVector, planePoint);
	MwVector3::Scale(intersection, rayVector, distance);
	MwVector3::Add(intersection, rayPoint, intersection);
    return distance;
}
    
//planeNormal must be normalized
float MwMaths::PointToPlaneDistance(MwVector3 &point, MwVector3 &planePoint, MwVector3 &planeNormal)
{
    return -RayToPerpendicularPlaneDistance(point, planeNormal, planePoint);
}

//planeNormal must be normalized
float MwMaths::PointToPlaneProjection(MwVector3 &projection, MwVector3 &point, MwVector3 &planePoint, MwVector3 &planeNormal)
{
    float distance = PointToPlaneDistance(point, planePoint, planeNormal);
	MwVector3::Scale(projection, planeNormal, -distance);
	MwVector3::Add(projection, point, projection);
	return distance;
}

float RayToRayDistance(MwVector3 &ray1Point, MwVector3 &ray1Direction, MwVector3 &ray2Point, MwVector3 &ray2Direction)
{
 //   MwVector3 a, b, c;
	//MwVector3::Subtract(a, camera1Vector, ref camera1Point);
 //   MwVector3::Subtract(b, camera2Vector, ref camera2Point);
 //   MwVector3::Subtract(c, camera2Point, ref camera1Point);

 //   float p = Vector.DotProduct(ref a, ref b);
 //   float q = Vector.DotProduct(ref a, ref c);
 //   float r = Vector.DotProduct(ref b, ref c);
 //   float s = Vector.DotProduct(ref a, ref a);
 //   float t = Vector.DotProduct(ref b, ref b);

 //   //float p2 = p * p;
 //   //float ptsp2 = p / (t * s - p2);
 //   //float vd = r * ptsp2 + q / (s - p2 / t);
 //   //float ve = q * ptsp2 + r / (t - p2 / s);
 //   float vd = r * p / (t * s - p * p) + q / (s - p * p / t);
 //   float ve = q * p / (t * s - p * p) + r / (t - p * p / s);

 //   a.Scale(vd);
 //   b.Scale(ve);

 //   Vector ray1Point = Vector.Add(ref camera1Point, ref a);
 //   Vector ray2Point = Vector.Add(ref camera2Point, ref b);

 //   Vector point = Vector.Lerp(ref ray1Point, ref ray2Point, 0.5f);
	return 0;
}

// TODO: Make a method set for planes in MwVector4, concenring conversion from Vvector4 plane to MwVector3 planePoint and Vector2 planeNormal
//static public float Plane4ToPlane3(MwVector3 &planePoint, MwVector3 &planeNormal, MwVector4 &plane)
//{
//	planePoint.Set(0.0f, 0.0f, -plane.w / plane.z);
//	planeNormal.Set(plane.x, plane.y, plane.z);
//}

float MwMaths::PointToPlaneDistance(MwVector3 &point, MwVector4 &plane)
{
	// TODO: sophisticate the straightforward division by plane.z, make conversion functions for plane of Vector3s and of Vector4
	MwVector3 planePoint(0.0f, 0.0f, -plane.w / plane.z);
    MwVector3 planeNormal(plane.x, plane.y, plane.z);

	MwVector3::Normalize(planeNormal, planeNormal);

    return -RayToPerpendicularPlaneDistance(point, planeNormal, planePoint);
}

//rayVector must be normalized
void MwMaths::PerpendicularPlaneIntersection(MwVector3 &result, MwVector3 &rayPoint, MwVector3 &rayVector, MwVector3 &planePoint)
{
    MwVector3 ray;
	MwVector3::Scale(ray, rayVector, RayToPerpendicularPlaneDistance(rayPoint, rayVector, planePoint));
    MwVector3::Add(result, rayPoint, ray);
}

//rayVector must be normalized
bool MwMaths::SphereIntersection(MwVector3 &rayPoint, MwVector3 &rayVector,
                                MwVector3 &sphereCenter, float sphereRadius)
{
    MwVector3 intersectionPoint;
	PerpendicularPlaneIntersection(intersectionPoint, rayPoint, rayVector, sphereCenter);
    return MwVector3::Distance(sphereCenter, intersectionPoint) <= sphereRadius;
}

//coneVector must be normalized
bool MwMaths::SphereConeIntersection(MwVector3 &conePoint, MwVector3 &coneVector, float coneAngle, MwVector3 &sphereCenter, float sphereRadius)
{
	coneAngle /= 2.0f;
    float d = RayToPerpendicularPlaneDistance(conePoint, coneVector, sphereCenter);
    float maxSphereToAxisDistance = (sphereRadius + d * MwMath::Sin(coneAngle)) / MwMath::ArcCos(coneAngle);
        
    MwVector3 intersectionVector, intersectionPoint;
    MwVector3::Scale(intersectionVector, coneVector, d);
    MwVector3::Add(intersectionPoint, conePoint, intersectionVector);
        
    float sphereToAxisDistance = MwVector3::Distance(sphereCenter, intersectionPoint);
    return sphereToAxisDistance <= maxSphereToAxisDistance;
}

void MwMaths::GetBarycentricCoordinates(MwVector2 &result, MwVector3 &cartesianCoords, MwVector3 &uAxis, MwVector3 &vAxis)
{
    float p = MwVector3::Dot(uAxis, vAxis);
    float q = MwVector3::Dot(uAxis, cartesianCoords);
    float r = MwVector3::Dot(vAxis, cartesianCoords);
    float s = MwVector3::Dot(uAxis, uAxis);
    float t = MwVector3::Dot(vAxis, vAxis);

	float invD = 1.0f / (s * t - p * p);

	result.x = (q * t - p * r) * invD;
	result.y = (r * s - p * q) * invD;
}

float MwMaths::VectorAngle(MwVector3 &v1, MwVector3 &v2)
{
	return MwMath::ArcCos(MwVector3::Dot(v1, v2) / (v1.GetLength() * v2.GetLength()));
}

int MwMaths::GetPowerOf2Boundary(int value)
{
    int result = 1;
    while (result < value)
        result = result << 1;
    return result;
}

int MwMaths::GetBoundary(int value, int boundarySize)
{
	int mod = value % boundarySize;
	if (mod == 0)
		return value;
	else
		return value + boundarySize - mod;
}

float MwMaths::DegreeToRad(float degree)
{
    return MwMath::Pi * degree / 180.0f;
}

float MwMaths::RadToDegree(float rad)
{
    return 180.0f * rad / MwMath::Pi;
}


float MwMaths::LensToFOV(float lens, float filmSize)
{
    return 2.0f * MwMath::ArcTan(filmSize / (2.0f * lens));
}

float MwMaths::FOVToLens(float fov, float filmSize)
{
	return filmSize / (2.0f * MwMath::Tan(fov / 2.0f));
}
