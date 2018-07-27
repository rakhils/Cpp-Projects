#include "Vector3.hpp"

Vector3::Vector3(float xval, float yval, float zval)
{
	x = xval;
	y = yval;
	z = zval;
}

Vector3 Vector3::operator - ( const Vector3& vecToSub )
{
	return Vector3(x-vecToSub.x, y-vecToSub.y,z-vecToSub.z ); // #MP1Fixme
}

void Vector3::operator *=( float val) 
{
	x*=val; y*=val ; z*=val;
}
