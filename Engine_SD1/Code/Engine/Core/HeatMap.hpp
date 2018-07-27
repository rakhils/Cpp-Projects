#pragma once
#include <vector>

#include "Engine/Math/IntVector2.hpp"

class HeatMap
{
public:
	std::vector<float> m_heatPerGridCell;
	IntVector2 m_dimensions;

	HeatMap();

	void setHeat(int cellCoords,float heatValue);
	void addHeat(int cellCoords,float heatValue);
	float getHeat(int cellCoords);
	void populateWithMaxValue();
};