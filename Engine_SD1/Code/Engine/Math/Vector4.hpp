#pragma once
class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
	Vector4(float xval,float yval,float zval,float wval);
	const Vector4 operator-( const Vector4& vecToSubtract ) const;	// vec2 - vec2
	void operator*=( const float uniformScale );
};