#pragma once
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/Texture.hpp"

#include "Game/TileDefinitions.hpp"
#include "Game/GameCommon.hpp"
class Tiles
{
public:
	// VARIABLES
	float			m_length  = ENTITY_WIDTH;
	float			m_bredth  = ENTITY_HEIGHT;
	float			m_centreX = 0.f;
	float			m_centreY = 0.f;
	float			m_angle   = 0;
	bool			m_isSolid = false;
	AABB2			m_aabb2;

	IntVector2		m_position;
	TileType		m_tileType	 = TILE_TYPE_GRASS;

	// FUNCTIONS
	Tiles();
	Tiles(Vector2 positionVector);
	~Tiles();

	void			Render();
	void			SetPosition(Vector2 positionVector);
};
