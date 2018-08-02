#include "Game/TileDefinitions.hpp"
#include "Game/GameCommon.hpp"
TileDefinitionData_t		TileDefinitions::s_tileDefinitions[NUM_TOTAL];

void TileDefinitions::InitTileDefinitions()
{
	Texture *m_texture  = g_theRenderer->CreateOrGetTexture("Data\\Images\\terrain.png");
	g_TerrainTile		= new SpriteSheet(*m_texture, 8,8);
	for (int tileNum = 0 ;tileNum < NUM_TILE_TYPE;tileNum++)
	{
		switch(tileNum)
		{
			case TILE_TYPE_STONE:
				s_tileDefinitions[tileNum].m_isSolid = true;
				break;
			case TILE_TYPE_GRASS:
				s_tileDefinitions[tileNum].m_isSolid = false;
				break;
			case TILE_TYPE_SAND:
				s_tileDefinitions[tileNum].m_isSolid = false;
				break;
		}
	}
}


void TileDefinitions::SetTileCoord(TileType type,const IntVector2 position)
{
	AABB2 aabb2							  = g_TerrainTile->GetTexCoordsForSpriteCoords(position);
	s_tileDefinitions[type].m_minPosition = Vector2(aabb2.mins.x, aabb2.maxs.y);
	s_tileDefinitions[type].m_maxPosition = Vector2(aabb2.maxs.x, aabb2.mins.y);
}

Vector2 TileDefinitions::GetMinPos(TileType type)
{
	return s_tileDefinitions[type].m_minPosition;
}

Vector2 TileDefinitions::GetMaxPos(TileType type)
{
	return s_tileDefinitions[type].m_maxPosition;
}

