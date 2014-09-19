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

#include "MwVector2.h"

#include "..\..\Tools\MwMath.h"

#include "MwMatrix.h"

MwVector2::MwVector2(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
}

MwVector2::MwVector2(float value)
{
	this->x = value;
	this->y = value;
}

MwVector2::MwVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
	
MwVector2::MwVector2(MwVector2 &source)
{
	this->x = source.x;
	this->y = source.y;
}
	
MwVector2::~MwVector2(void)
{
}

float MwVector2::GetLength()
{
    return MwMath::Sqrt(this->x * this->x + this->y * this->y);
}

void MwVector2::Set(float value)
{
	this->x = value;
	this->y = value;
}

void MwVector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}
	



// Static Methods

void MwVector2::Copy(MwVector2 &result, MwVector2 &source)
{
    result.x = source.x;
    result.y = source.y;
}

void MwVector2::SetLength(MwVector2 &result, MwVector2 &v, float length)
{
    float k = MwMath::Sqrt(v.x * v.x + v.y * v.y);

    if (k != 0.0f)
    {
        k = length / k;

        result.x = v.x * k;
        result.y = v.y * k;
    }
}

void MwVector2::Normalize(MwVector2 &result, MwVector2 &v)
{
	MwVector2::SetLength(result, v, 1.0f);
}

float MwVector2::Distance(MwVector2 &v1, MwVector2 &v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;

    return (float)(MwMath::Sqrt(x * x + y * y));
}
	
void MwVector2::Lerp(MwVector2 &result, MwVector2 &v1, MwVector2 &v2, float factor)
{
    result.x += (v2.x - v1.x) * factor;
    result.y += (v2.y - v1.y) * factor;
}

void MwVector2::Subtract(MwVector2 &result, MwVector2 &v1, MwVector2 &v2)
{
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
}

void MwVector2::Add(MwVector2 &result, MwVector2 &v1, MwVector2 &v2)
{
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
}

float MwVector2::Dot(MwVector2 &v1, MwVector2 &v2)
{
    return (v1.x * v2.x +
            v1.y * v2.y);
}

void MwVector2::Cross(MwVector2 &result, MwVector2 &v1)
{
    result.x = -v1.y;
    result.y = v1.x;
}
    
void MwVector2::Scale(MwVector2 &result, MwVector2 &v1, MwVector2 &v2)
{
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
}

void MwVector2::Scale(MwVector2 &result, MwVector2 &v1, float factor)
{
    result.x = v1.x * factor;
    result.y = v1.y * factor;
}
    
void MwVector2::Min(MwVector2 &result, MwVector2 &v1, MwVector2 &v2)
{
    result.x = v1.x < v2.x ? v1.x : v2.x;
    result.y = v1.y < v2.y ? v1.y : v2.y;
}
    
void MwVector2::Max(MwVector2 &result, MwVector2 &v1, MwVector2 &v2)
{
    result.x = v1.x > v2.x ? v1.x : v2.x;
    result.y = v1.y < v2.y ? v1.y : v2.y;
}
    
void MwVector2::Transform(MwVector2 &result, MwVector2 &v, MwMatrix &transformation)
{
    float x = 	v.x * transformation._11 +
    		    v.y * transformation._21 +
					   transformation._31 +
					   transformation._41;
    float y = 	v.x * transformation._12 +
        		v.y * transformation._22 +
        			   transformation._32 +
        			   transformation._42;
        
    result.x = x;
    result.y = y;
}

void MwVector2::TransformNormal(MwVector2 &result, MwVector2 &v, MwMatrix &transformation)
{
    float x =	v.x * transformation._11 +
			    v.y * transformation._21;
	float y =	v.x * transformation._12 +
			    v.y * transformation._22;

	result.x = x;
    result.y = y;
}