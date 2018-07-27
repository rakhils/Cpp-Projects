#pragma once
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(float xval,float yval,float zval);
	Vector3 operator-( const Vector3& vecToSubtract );				// vec2 -= vec2
	void operator*=( const float uniformScale );

};