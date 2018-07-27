#include "Engine/Core/HeatMap.hpp"

HeatMap::HeatMap()
{

}

void HeatMap::setHeat(int cellCoords,float value)
{
	m_heatPerGridCell.at(cellCoords) = value;
}

void HeatMap::addHeat(int cellCoords,float value)
{
	float heatValue = getHeat(cellCoords);
	setHeat(cellCoords,heatValue + value);
}

float HeatMap::getHeat(int cellCoords)
{
	if(cellCoords < 0 && cellCoords > m_dimensions.x*m_dimensions.y)
	{
		return 99999;
	}
	return m_heatPerGridCell.at(cellCoords);
}

//////////////////////////////////////////////////////////////////////////
//@purpose : Populating all elements in matrix with max value = 9999(infinity)
void HeatMap::populateWithMaxValue()
{
	for(int index = 0;index < m_dimensions.x*m_dimensions.y;index++)
	{
		m_heatPerGridCell.push_back(9999.0f);// MAX VALUE
	}
}

