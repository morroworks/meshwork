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

#include "MwVector3.h"

#include "..\..\Tools\MwMath.h"

#include "MwMatrix.h"
#include "MwVector2.h"

MwVector3::MwVector3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

MwVector3::MwVector3(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

MwVector3::MwVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
	
	
MwVector3::MwVector3(MwVector3 &source)
{
	this->x = source.x;
	this->y = source.y;
	this->z = source.z;
}
	
MwVector3::MwVector3(MwVector2 &source, float z)
{
	this->x = source.x;
	this->y = source.y;
	this->z = z;
}

MwVector3::~MwVector3(void)
{
}

float MwVector3::GetLength()
{
    return MwMath::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void MwVector3::Set(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

void MwVector3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
	


// Static Methods

void MwVector3::Copy(MwVector3 &result, MwVector3 &source)
{
    result.x = source.x;
    result.y = source.y;
    result.z = source.z;
}

void MwVector3::SetLength(MwVector3 &result, MwVector3 &v, float length)
{
    float k = MwMath::Sqrt(v.x * v.x + v.y * v.y +	v.z * v.z);
    if (k != 0.0f)
    {
        k = length / k;

        result.x = v.x * k;
        result.y = v.y * k;
        result.z = v.z * k;
    }
}

void MwVector3::Normalize(MwVector3 &result, MwVector3 &v)
{
	MwVector3::SetLength(result, v, 1.0f);
}
	
float MwVector3::Distance(MwVector3 &v1, MwVector3 &v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;
    float z = v1.z - v2.z;

    return (float)(MwMath::Sqrt(x * x + y * y + z * z));
}
	
void MwVector3::Lerp(MwVector3 &result, MwVector3 &v1, MwVector3 &v2, float factor)
{
    result.x = v1.x + (v2.x - v1.x) * factor;
    result.y = v1.y + (v2.y - v1.y) * factor;
    result.z = v1.z + (v2.z - v1.z) * factor;
}

void MwVector3::Subtract(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
}

void MwVector3::Add(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
}

float MwVector3::Dot(MwVector3 &v1, MwVector3 &v2)
{
    return (v1.x * v2.x +
            v1.y * v2.y +
            v1.z * v2.z);
}

void MwVector3::Cross(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
}
    
void MwVector3::Scale(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    result.z = v1.z * v2.z;
}

void MwVector3::Scale(MwVector3 &result, MwVector3 &v1, float factor)
{
    result.x = v1.x * factor;
    result.y = v1.y * factor;
    result.z = v1.z * factor;
}
    
void MwVector3::Min(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.x < v2.x ? v1.x : v2.x;
    result.y = v1.y < v2.y ? v1.y : v2.y;
    result.z = v1.z < v2.z ? v1.z : v2.z;
}
    
void MwVector3::Max(MwVector3 &result, MwVector3 &v1, MwVector3 &v2)
{
    result.x = v1.x > v2.x ? v1.x : v2.x;
    result.y = v1.y < v2.y ? v1.y : v2.y;
    result.z = v1.z > v2.z ? v1.z : v2.z;
}
    
void MwVector3::Transform(MwVector3 &result, MwVector3 &v, MwMatrix &transformation)
{
    float x = 	v.x * transformation._11 +
    		    v.y * transformation._21 +
			    v.z * transformation._31 +
					   transformation._41;
    float y = 	v.x * transformation._12 +
        		v.y * transformation._22 +
        		v.z * transformation._32 +
        			   transformation._42;
    float z = 	v.x * transformation._13 +
			    v.y * transformation._23 +
			    v.z * transformation._33 +
					   transformation._43;
        
    result.x = x;
    result.y = y;
    result.z = z;
}

void MwVector3::TransformNormal(MwVector3 &result, MwVector3 &v, MwMatrix &transformation)
{
    float x =	v.x * transformation._11 +
			    v.y * transformation._21 +
			    v.z * transformation._31;
	float y =	v.x * transformation._12 +
			    v.y * transformation._22 +
			    v.z * transformation._32;
	float z = 	v.x * transformation._13 +
			    v.y * transformation._23 +
			    v.z * transformation._33;

	result.x = x;
    result.y = y;
    result.z = z;
}

// Converts the given Cartesian coordinates into Spherical coordinates
// result.x: azimuth, range 0 to 2Pi, initial direction is negative Z (east), increasing towards full revolution around positive Y
// result.y: elevation, range -Pi/2 to Pi/2, initial direction is negative Y (down), increasing towards positive Y (up)
// result.z: distance
void MwVector3::CartesianToSphere(MwVector3 &result, float x, float y, float z)
{
    result.z = MwMath::Sqrt(x * x + y * y + z * z);
    if (result.z == 0.0f)
        return;

    result.y = MwMath::ArcSin(y / result.z);

    if (x == 0)
        if (z > 0)
			result.x = MwMath::Pi / 2.0f;
        else
			result.x = -MwMath::Pi / 2.0f;
    else
        result.x = MwMath::ArcTan(z / x);

    if (x < 0)
		result.x += MwMath::Pi;

    if (result.x < 0)
		result.x += MwMath::Pi * 2;
}

void MwVector3::CartesianToSphere(MwVector3 &result, MwVector3 &cartesian)
{
    MwVector3::CartesianToSphere(result, cartesian.x, cartesian.y, cartesian.z);
}

void MwVector3::SphereToCartesian(MwVector3 &result, float azimuth, float elevation, float radius)
{
    float eCos = MwMath::Cos(elevation) * radius;
    result.x = MwMath::Cos(azimuth) * eCos;
    result.y = MwMath::Sin(elevation) * radius;
    result.z = MwMath::Sin(azimuth) * eCos;
}

void MwVector3::SphereToCartesian(MwVector3 &result, MwVector3 &spherical)
{
    MwVector3::SphereToCartesian(result, spherical.x, spherical.y, spherical.z);
}
    
void MwVector3::LerpSherical(MwVector3 &result, MwVector3 &v1, MwVector3 &v2, float factor)
{
    float delta = v2.x - v1.x;
	if (MwMath::Abs(delta) < MwMath::Pi)
        result.x = v1.x + delta * factor;
    else
    {
        if (delta > 0)
        {
            delta -= MwMath::Pi2;
            result.x = v1.x + delta * factor;
            if (result.x < 0)
                result.x += MwMath::Pi2;
        }
        else
        {
            delta += MwMath::Pi * 2;
            result.x = v1.x + delta * factor;
            if (result.x > MwMath::Pi2)
                result.x -= MwMath::Pi2;
        }
    }

    delta = v2.y - v1.y;
	if (MwMath::Abs(delta) < MwMath::Pi)
        result.y = v1.y + delta * factor;
    else
    {
        if (delta > 0)
        {
            delta -= MwMath::Pi2;
            result.y = v1.y + delta * factor;
            if (result.y < 0)
				result.y += MwMath::Pi2;
        }
        else
        {
			delta += MwMath::Pi2;
            result.y = v1.y + delta * factor;
            if (result.y > MwMath::Pi2)
                result.y -= MwMath::Pi2;
        }
    }

    result.z = v1.z + (v2.z - v1.z) * factor;
} 