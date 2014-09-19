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

#include "MwVector4.h"

#include "..\..\Tools\MwMath.h"

#include "MwMatrix.h"
#include "MwVector3.h"
#include "MwVector2.h"

MwVector4::MwVector4(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}
	
MwVector4::MwVector4(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

MwVector4::MwVector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

MwVector4::MwVector4(MwVector4 &source)
{
	this->x = source.x;
	this->y = source.y;
	this->z = source.z;
	this->w = source.w;
}

MwVector4::MwVector4(MwVector3 &source, float w)
{
	this->x = source.x;
	this->y = source.y;
	this->z = source.z;
	this->w = w;
}

MwVector4::MwVector4(MwVector2 &source, float z, float w)
{
	this->x = source.x;
	this->y = source.y;
	this->z = z;
	this->w = w;
}

MwVector4::~MwVector4(void)
{
}

float MwVector4::GetLength()
{
    return (float)(MwMath::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
}
	
void MwVector4::Set(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

void MwVector4::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}



// Stataic Methods

void MwVector4::Copy(MwVector4 &result, MwVector4 &source)
{
    result.x = source.x;
    result.y = source.y;
    result.z = source.z;
    result.w = source.w;
}

void MwVector4::SetLength(MwVector4 &result, MwVector4 &v, float length)
{
    float k = MwMath::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    if (k != 0.0f)
    {
        k = length / k;

        result.x = v.x * k;
        result.y = v.y * k;
        result.z = v.z * k;
        result.w = v.w * k;
    }
}

void MwVector4::Normalize(MwVector4 &result, MwVector4 &v)
{
	MwVector4::SetLength(result, v, 1.0f);
}
	
float MwVector4::Distance(MwVector4 &v1, MwVector4 &v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;
    float z = v1.z - v2.z;
    float w = v1.w - v2.w;

    return MwMath::Sqrt(x * x + y * y + z * z + w * w);
}
	
void MwVector4::Lerp(MwVector4 &result, MwVector4 &v1, MwVector4 &v2, float factor)
{
    result.x += (v2.x - v1.x) * factor;
    result.y += (v2.y - v1.y) * factor;
    result.z += (v2.z - v1.z) * factor;
    result.w += (v2.w - v1.w) * factor;
}

void MwVector4::Subtract(MwVector4 &result, MwVector4 &v1, MwVector4 &v2)
{
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    result.w = v1.w - v2.w;
}

void MwVector4::Add(MwVector4 &result, MwVector4 &v1, MwVector4 &v2)
{
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    result.w = v1.w + v2.w;
}

float MwVector4::Dot(MwVector4 &v1, MwVector4 &v2)
{
    return (v1.x * v2.x +
            v1.y * v2.y +
            v1.z * v2.z + 
            v1.w * v2.w);
}

void MwVector4::Cross(MwVector4 &result, MwVector4 &v1, MwVector4 &v2, MwVector4 &v3)
{
    // not implemented
}
    
void MwVector4::Scale(MwVector4 &result, MwVector4 &v1, MwVector4 &v2)
{
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    result.z = v1.z * v2.z;
    result.w = v1.w * v2.w;
}

void MwVector4::Scale(MwVector4 &result, MwVector4 &v1, float factor)
{
    result.x = v1.x * factor;
    result.y = v1.y * factor;
    result.z = v1.z * factor;
    result.w = v1.w * factor;
}
    
void MwVector4::Min(MwVector4 &result, MwVector4 &v1, MwVector4 &v2)
{
    result.x = v1.x < v2.x ? v1.x : v2.x;
    result.y = v1.y < v2.y ? v1.y : v2.y;
    result.z = v1.z < v2.z ? v1.z : v2.z;
    result.w = v1.w < v2.w ? v1.w : v2.w;
}

void MwVector4::Max(MwVector4 &result, MwVector4 &v1, MwVector4 &v2)
{
    result.x = v1.x > v2.x ? v1.x : v2.x;
    result.y = v1.y > v2.y ? v1.y : v2.y;
    result.z = v1.z > v2.z ? v1.z : v2.z;
    result.w = v1.w > v2.w ? v1.w : v2.w;
}
    
void MwVector4::Transform(MwVector4 &result, MwVector4 &v, MwMatrix &transformation)
{
    float x = 	v.x * transformation._11 +
    		    v.y * transformation._21 +
			    v.z * transformation._31 +
			    v.w * transformation._41;
    float y = 	v.x * transformation._12 +
        		v.y * transformation._22 +
        		v.z * transformation._32 +
        		v.w * transformation._42;
    float z = 	v.x * transformation._13 +
			    v.y * transformation._23 +
			    v.z * transformation._33 +
			    v.w + transformation._43;
    float w = 	v.x * transformation._14 +
			    v.y * transformation._24 +
			    v.z * transformation._34 +
			    v.w * transformation._44;
        
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
}

void MwVector4::Transform(MwVector4 &result, MwVector3 &v, MwMatrix &transformation)
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
    float w = 	v.x * transformation._14 +
			    v.y * transformation._24 +
			    v.z * transformation._34 +
			    transformation._44;
        
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
}