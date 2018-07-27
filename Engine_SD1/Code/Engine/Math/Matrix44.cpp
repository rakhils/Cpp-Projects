#include "Engine/Math/Matrix44.hpp"

Matrix44::Matrix44()
{
	Ix = 1;
	Iy = 0;
	Iz = 0;
	Iw = 0;
	Jx = 0;
	Jy = 1;
	Jz = 0;
	Jw = 0;
	Kx = 0;
	Ky = 0;
	Kz = 1;
	Kw = 0;
	Tx = 0;
	Ty = 0;
	Tz = 0;
	Tw = 1; 
}

Matrix44::Matrix44(const float* sixteenValuesBasisMajor)
{
	Ix = sixteenValuesBasisMajor[0];
	Iy = sixteenValuesBasisMajor[1];
	Iz = sixteenValuesBasisMajor[2];
	Iw = sixteenValuesBasisMajor[3];
	Jx = sixteenValuesBasisMajor[4];
	Jy = sixteenValuesBasisMajor[5];
	Jz = sixteenValuesBasisMajor[6];
	Jw = sixteenValuesBasisMajor[7];
	Kx = sixteenValuesBasisMajor[8];
	Ky = sixteenValuesBasisMajor[9];
	Kz = sixteenValuesBasisMajor[10];
	Kw = sixteenValuesBasisMajor[11];
	Tx = sixteenValuesBasisMajor[12];
	Ty = sixteenValuesBasisMajor[13];
	Tz = sixteenValuesBasisMajor[14];
	Tw = sixteenValuesBasisMajor[15]; 
}

Matrix44::Matrix44(const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation/*=Vector2(0.f,0.f) */)
{
	Ix = iBasis.x;
	Iy = iBasis.y;
	Iz = 0;
	Iw = 0;
	Jx = jBasis.x;
	Jy = jBasis.y;
	Jz = 0;
	Jw = 0;
	Kx = 0;
	Ky = 0;
	Kz = 1;
	Kw = 0;
	Tx = translation.x;
	Ty = translation.y;
	Tz = 0;
	Tw = 1;
}

Vector2 Matrix44::TransformPosition2D(const Vector2& position2D)
{

	Vector4 IVector(Ix,Jx,Kx,Tx);
	Vector4 JVector(Iy,Jy,Ky,Ty);
	Vector4 KVector(Iz,Jz,Kz,Tz);
	Vector4 TVector(Iw,Jw,Kw,Tw);

	Vector4 Position(position2D.x,position2D.y,0,1);
	float IDotPosition = DotProduct(IVector,Position);
	float JDotPosition = DotProduct(JVector,Position);
	return Vector2(IDotPosition,JDotPosition);
}

Vector2 Matrix44::TransformDisplacement2D(const Vector2& displacement2D)
{
	Vector4 IVector(Ix,Jx,Kx,Tx);
	Vector4 JVector(Iy,Jy,Ky,Ty);
	Vector4 KVector(Iz,Jz,Kz,Tz);
	Vector4 TVector(Iw,Jw,Kw,Tw);

	Vector4 Position(displacement2D.x,displacement2D.y,0,0);
	float IDotPosition = DotProduct(IVector,Position);
	float JDotPosition = DotProduct(JVector,Position);
	return Vector2(IDotPosition,JDotPosition);
}

void Matrix44::SetIdentity()
{
	Ix = 1;
	Iy = 0;
	Iz = 0;
	Iw = 0;
	Jx = 0;
	Jy = 1;
	Jz = 0;
	Jw = 0;
	Kx = 0;
	Ky = 0;
	Kz = 1;
	Kw = 0;
	Tx = 0;
	Ty = 0;
	Tz = 0;
	Tw = 1; 
}

void Matrix44::SetValues(const float* sixteenValuesBasisMajor)
{
	Ix = sixteenValuesBasisMajor[0];
	Iy = sixteenValuesBasisMajor[1];
	Iz = sixteenValuesBasisMajor[2];
	Iw = sixteenValuesBasisMajor[3];
	Jx = sixteenValuesBasisMajor[4];
	Jy = sixteenValuesBasisMajor[5];
	Jz = sixteenValuesBasisMajor[6];
	Jw = sixteenValuesBasisMajor[7];
	Kx = sixteenValuesBasisMajor[8];
	Ky = sixteenValuesBasisMajor[9];
	Kz = sixteenValuesBasisMajor[10];
	Kw = sixteenValuesBasisMajor[11];
	Tx = sixteenValuesBasisMajor[12];
	Ty = sixteenValuesBasisMajor[13];
	Tz = sixteenValuesBasisMajor[14];
	Tw = sixteenValuesBasisMajor[15]; 
}

void Matrix44::Append(const Matrix44& matrixToAppend)
{
	MultiplyAndSet(matrixToAppend);
}

void Matrix44::RotateDegrees2D(float rotationDegreesAboutZ)
{
	Vector4 IVector(CosDegrees(rotationDegreesAboutZ),-1*SinDegrees(rotationDegreesAboutZ),0,0);
	Vector4 JVector(SinDegrees(rotationDegreesAboutZ),CosDegrees(rotationDegreesAboutZ),0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);
	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};
	Matrix44 rotationMatrix(points); 

	MultiplyAndSet(rotationMatrix); 

}

void Matrix44::Translate2D(const Vector2& translation)
{
	Vector4 IVector(1,0,0,translation.x);
	Vector4 JVector(0,1,0,translation.y);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);
	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};
	Matrix44 rotationMatrix(points); 

	MultiplyAndSet(rotationMatrix); 
}

void Matrix44::ScaleUniform2D(float scaleXY)
{
	Vector4 IVector(scaleXY,0,0,0);
	Vector4 JVector(0,scaleXY,0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);
	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w };
	Matrix44 rotationMatrix(points); 

	MultiplyAndSet(rotationMatrix); 
}

void Matrix44::Scale2D(float scaleX, float scaleY)
{
	Vector4 IVector(scaleX,0,0,0);
	Vector4 JVector(0,scaleY,0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);
	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};
	Matrix44 rotationMatrix(points); 

	MultiplyAndSet(rotationMatrix); 
}

Matrix44 Matrix44::MakeRotationDegrees2D(float rotationDegreesAboutZ)
{
	Vector4 IVector(CosDegrees(rotationDegreesAboutZ),-1*SinDegrees(rotationDegreesAboutZ),0,0);
	Vector4 JVector(SinDegrees(rotationDegreesAboutZ),CosDegrees(rotationDegreesAboutZ),0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);
	
	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};

	return Matrix44(points);

}

Matrix44 Matrix44::MakeTranslation2D(const Vector2& translation)
{
	Vector4 IVector(1,0,0,translation.x);
	Vector4 JVector(0,1,0,translation.y);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);

	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};

	return Matrix44(points);
}

Matrix44 Matrix44::MakeScaleUniform2D(float scaleXY)
{
	Vector4 IVector(scaleXY,0,0,0);
	Vector4 JVector(0,scaleXY,0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);

	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};

	return Matrix44(points);
}

Matrix44 Matrix44::MakeScale2D(float scaleX, float scaleY)
{
	Vector4 IVector(scaleX,0,0,0);
	Vector4 JVector(0,scaleY,0,0);
	Vector4 KVector(0,0,1,0);
	Vector4 TVector(0,0,0,1);

	float points[16] = {IVector.x,JVector.x,KVector.x,TVector.x,
						IVector.y,JVector.y,KVector.y,TVector.y,
						IVector.z,JVector.z,KVector.z,TVector.z,
						IVector.w,JVector.w,KVector.w,TVector.w};

	return Matrix44(points);
}

Matrix44 Matrix44::MakeOrtho2D(const Vector2& bottomLeft, const Vector2& topRight)
{
	float far = 0.0f;
	float near = -1.0f;
	Vector2 centre = (bottomLeft + topRight)/2.0f;
	Matrix44 translateMatrix44 = MakeTranslation2D(-1.0f*centre);
	Matrix44 scaleMatrix44 = MakeScale2D(2.0f/(topRight.x-bottomLeft.x),2.0f/(topRight.y-bottomLeft.y));
	Matrix44 orthoMatrix;
	orthoMatrix.SetIdentity();
	
	orthoMatrix.MultiplyAndSet(scaleMatrix44);
	orthoMatrix.MultiplyAndSet(translateMatrix44);
	orthoMatrix.Kz = -2.0f/(far - near);
	orthoMatrix.Tz = near;
	
	return orthoMatrix;
}

void Matrix44::MultiplyAndSet(Matrix44 valueMatrix)
{
	Vector4 IVector(Ix,Jx,Kx,Tx);
	Vector4 JVector(Iy,Jy,Ky,Ty);
	Vector4 KVector(Iz,Jz,Kz,Tz);
	Vector4 TVector(Iw,Jw,Kw,Tw);

	Vector4 XValueMatrix(valueMatrix.Ix,valueMatrix.Iy,valueMatrix.Iz,valueMatrix.Iw);
	Vector4 YValueMatrix(valueMatrix.Jx,valueMatrix.Jy,valueMatrix.Jz,valueMatrix.Jw);
	Vector4 ZValueMatrix(valueMatrix.Kx,valueMatrix.Ky,valueMatrix.Kz,valueMatrix.Kw);
	Vector4 TValueMatrix(valueMatrix.Tx,valueMatrix.Ty,valueMatrix.Tz,valueMatrix.Tw);

	Ix = DotProduct(IVector,XValueMatrix);
	Jx = DotProduct(IVector,YValueMatrix);
	Kx = DotProduct(IVector,ZValueMatrix);
	Tx = DotProduct(IVector,TValueMatrix);

	Iy = DotProduct(JVector,XValueMatrix);
	Jy = DotProduct(JVector,YValueMatrix);
	Ky = DotProduct(JVector,ZValueMatrix);
	Ty = DotProduct(JVector,TValueMatrix);

	Iz = DotProduct(KVector,XValueMatrix);
	Jz = DotProduct(KVector,YValueMatrix);
	Kz = DotProduct(KVector,ZValueMatrix);
	Tz = DotProduct(KVector,TValueMatrix);

	Iw = DotProduct(TVector,XValueMatrix);
	Jw = DotProduct(TVector,YValueMatrix);
	Kw = DotProduct(TVector,ZValueMatrix);
	Tw = DotProduct(TVector,TValueMatrix);
}
