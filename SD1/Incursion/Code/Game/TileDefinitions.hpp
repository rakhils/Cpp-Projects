#pragma once
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/Vector2.hpp"


enum TileType
{
	TILE_TYPE_GRASS,
	TILE_TYPE_STONE,
	TILE_TYPE_SAND,
	TILE_TYPE_MUD,
	TILE_TYPE_BUSH,
	TILE_TYPE_GRANITE,
	NUM_TILE_TYPE,
	TILE_TYPE_LEVELPROGRESS,
	NUM_TOTAL
};
struct TileDefinitionData_t
{
	bool						m_isSolid = false;
	Vector2						m_minPosition;
	Vector2						m_maxPosition;
	TileType					m_type;
};
class TileDefinitions
{
public:
	// VARIABLES
	static TileDefinitionData_t		s_tileDefinitions[NUM_TOTAL];

	// FUNCTIONS
	static void						InitTileDefinitions();
	static void						SetTileCoord(TileType type,const IntVector2 position);
	static Vector2					GetMinPos(TileType type);
	static Vector2					GetMaxPos(TileType type);
	
};


