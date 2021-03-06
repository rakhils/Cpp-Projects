#include <math.h>
#include <string>

#include "Engine/Math/MathUtil.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector2.hpp"
//-----------------------------------------------------------------------------------------------
Vector2 Vector2::ZERO  = Vector2(+0, +0);
Vector2 Vector2::ONE   = Vector2(+1, +1);

Vector2 Vector2::EAST  = Vector2(+1, +0);
Vector2 Vector2::WEST  = Vector2(-1, +0);
Vector2 Vector2::NORTH = Vector2(+0, +1);
Vector2 Vector2::SOUTH = Vector2(+0, -1);

Vector2 Vector2::NORTHEAST = Vector2(+1, +1);
Vector2 Vector2::NORTHWEST = Vector2(-1, +1);
Vector2 Vector2::SOUTHEAST = Vector2(+1, -1);
Vector2 Vector2::SOUTHWEST = Vector2(-1, -1);

Vector2::Vector2( const Vector2& copy )
	: x( 99.f )
	, y( 99.f )
{
	x = copy.x;
	y = copy.y;
}

//-----------------------------------------------------------------------------------------------
Vector2::Vector2(float initialX, float initialY ): x( 99.f ), y( 99.f )
{
	x = initialX;
	y = initialY;
}

Vector2::Vector2(float angle)
{
	this->x = CosDegrees(angle);
	this->y = SinDegrees(angle);
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/01/31
*@purpose : Construct from IntVector
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
/*
Vector2::Vector2(IntVector2 intVector)
{
	this->x = static_cast<float>(intVector.x);
	this->y = static_cast<float>(intVector.y);
}*/

//-----------------------------------------------------------------------------------------------
const Vector2 Vector2::operator + ( const Vector2& vecToAdd ) const
{
	return Vector2(x+vecToAdd.x, y+vecToAdd.y ); // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
const Vector2 Vector2::operator-( const Vector2& vecToSubtract ) const
{
	return Vector2(x-vecToSubtract.x, y-vecToSubtract.y ); // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
const Vector2 Vector2::operator*( float uniformScale ) const
{
	return Vector2( x*uniformScale, y*uniformScale ); // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
const Vector2 Vector2::operator/( float inverseScale ) const
{
	return Vector2( x/inverseScale, y/inverseScale ); // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
void Vector2::operator+=( const Vector2& vecToAdd )
{
	x+=vecToAdd.x;
	y+=vecToAdd.y;
}

void Vector2::operator+=( float value )
{
	x+=value;
	y+=value;
}


//-----------------------------------------------------------------------------------------------
void Vector2::operator-=( const Vector2& vecToSubtract )
{
	x-=vecToSubtract.x;
	y-=vecToSubtract.y;
}


//-----------------------------------------------------------------------------------------------
void Vector2::operator*=( const float uniformScale )
{
	x*=uniformScale;
	y*=uniformScale;
}


//-----------------------------------------------------------------------------------------------
void Vector2::operator/=( const float uniformDivisor )
{
	x = x/uniformDivisor; // #MP1Fixme
	y = y/uniformDivisor; // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
void Vector2::operator=( const Vector2& copyFrom )
{
	x = copyFrom.x; // #MP1Fixme
	y = copyFrom.y; // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
const Vector2 operator*( float uniformScale, const Vector2& vecToScale )
{
	return Vector2( vecToScale.x*uniformScale, vecToScale.y*uniformScale ); // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
bool Vector2::operator==( const Vector2& compare ) const
{
	if(x == compare.x && y==compare.y)
	{
		return true;
	}
	return false; // #MP1Fixme
}


//-----------------------------------------------------------------------------------------------
bool Vector2::operator!=( const Vector2& compare ) const
{
	if(x!=compare.x || y!=compare.y)
	{
		return true;
	}
	return false; // #MP1Fixme
}

float Vector2::GetLength() const
{
	float val = sqrtf((float)((x*x)+(y*y)));
	return val;
}

float Vector2::GetLengthSquared() const
{
	float val = ((float)((x*x)+(y*y)));
	return val;
}

float Vector2::NormalizeAndGetLength()
{
	float val = sqrtf((float)((x*x)+(y*y)));
	this->x=this->x/val;
	this->y=this->y/val;
	return val;
}

Vector2 Vector2::GetNormalized() const
{
	float length = GetLength();
	if(length == 0)
	{
		return *this;
	}
	Vector2 normalizedVector(this->x/length,this->y/length);
	return normalizedVector;
}

float Vector2::GetOrientationDegrees() const
{
	float MATH_PIE = (float)3.1415926535897932384626433832795;
	float degrees = (atan2f(y,x)/(MATH_PIE/180.0f));
	return  degrees;
}

Vector2 Vector2::MakeDirectionAtDegrees( float degrees ) 
{
	float length = 1;
	float MATH_PIE = (float)3.1415926535897932384626433832795;
	float radiant = (MATH_PIE/180.0f)*degrees;
	Vector2 newVector(length*cosf(radiant),length*sinf(radiant));
	return newVector;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2017/12/18
*@purpose : static method to interpolate vector from start to end
*
*@param   : start vector,end vector and fraction already evolved
*
*@return  : Vector at current position
*/
//////////////////////////////////////////////////////////////

Vector2 Vector2::Interpolate(const Vector2& start, const Vector2& end, float fractionTowardEnd)
{
	float finalX = ::Interpolate(start.x,end.x,fractionTowardEnd);
	float finalY = ::Interpolate(start.y,end.y,fractionTowardEnd);
	return Vector2(finalX,finalY);
}

void Vector2::SetFromText(const char* text)
{
	std::string value;
	value.append(text);
	size_t index = value.find_first_of(',',0);
	std::string xValue = value.substr(0,index); 
	std::string yValue = value.substr(index+1,value.length());

	x = (float)stof(xValue);
	y = (float)stof(yValue);

}



