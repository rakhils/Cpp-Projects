#include "Vector4.hpp"

Vector4::Vector4(float xval, float yval, float zval, float wval)
{
	x = xval;
	y = yval;
	z = zval;
	w = wval;
}

const Vector4 Vector4::operator-( const Vector4& vecToSubtract ) const
{
	return Vector4(x-vecToSubtract.x, y-vecToSubtract.y,z-vecToSubtract.z,w-vecToSubtract.w); // #MP1Fixme
}

void Vector4::operator*=( const float uniformScale )
{
	x*=uniformScale;
	y*=uniformScale;
	z*=uniformScale;
	w*=uniformScale;
}
