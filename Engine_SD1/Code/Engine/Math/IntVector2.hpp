#pragma once

#include <string>

#include "Engine/Math/Vector2.hpp"

class IntVector2
{
public:
	int x;
	int y;

	IntVector2();
	IntVector2(int x,int y);
	IntVector2(Vector2);

	void	   operator =  (Vector2 positionVector);
	bool	   operator == (const IntVector2& compare) const;
	bool	   operator == (const Vector2& compare)    const;
	IntVector2 operator -  (const IntVector2& compare);
	void IntVector2::SetFromText(const char* text);
	
	static IntVector2 ZERO;
	static IntVector2 ONE;
	static IntVector2 EAST;
	static IntVector2 WEST;
	static IntVector2 NORTH;
	static IntVector2 SOUTH;
		   
	static IntVector2 NORTHEAST;
	static IntVector2 NORTHWEST;
	static IntVector2 SOUTHEAST;
	static IntVector2 SOUTHWEST;
};