#pragma once
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/MathUtil.hpp"

class Matrix44
{
public:
	float Ix;
	float Iy;
	float Iz;
	float Iw;
	float Jx;
	float Jy;
	float Jz;
	float Jw;
	float Kx;
	float Ky;
	float Kz;
	float Kw;
	float Tx;
	float Ty;
	float Tz;
	float Tw; 

	Matrix44(); // default-construct to Identity matrix (via variable initialization)
	explicit Matrix44( const float* sixteenValuesBasisMajor ); // float[16] array in order Ix, Iy...
	explicit Matrix44( const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation=Vector2(0.f,0.f) );

	// Accessors
	Vector2 TransformPosition2D( const Vector2& position2D ); // Written assuming z=0, w=1
	Vector2 TransformDisplacement2D( const Vector2& displacement2D ); // Written assuming z=0, w=0

																	  // Mutators
	void SetIdentity();
	void SetValues( const float* sixteenValuesBasisMajor ); // float[16] array in order Ix, Iy...
	void Append( const Matrix44& matrixToAppend ); // a.k.a. Concatenate (right-multiply)
	void RotateDegrees2D( float rotationDegreesAboutZ ); // 
	void Translate2D( const Vector2& translation );
	void ScaleUniform2D( float scaleXY );
	void Scale2D( float scaleX, float scaleY );

	// Producers
	static Matrix44 MakeRotationDegrees2D( float rotationDegreesAboutZ );
	static Matrix44 MakeTranslation2D( const Vector2& translation );
	static Matrix44 MakeScaleUniform2D( float scaleXY );
	static Matrix44 MakeScale2D( float scaleX, float scaleY );
	static Matrix44 MakeOrtho2D( const Vector2& bottomLeft, const Vector2& topRight );

	void MultiplyAndSet(Matrix44 valueMatrix);
};