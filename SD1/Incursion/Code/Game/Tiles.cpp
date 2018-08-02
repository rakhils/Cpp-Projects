#include "Game/Tiles.hpp"

#include "Engine/Math/MathUtil.hpp"

#include "Game/Entity.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TileDefinitions.hpp"


Vector2 texCoordsAtMins(0,0);
Vector2 texCoordsAtMaxs(1,1);


Tiles::Tiles()
{
	m_aabb2.mins = Vector2(0,0);
	m_aabb2.maxs = Vector2(2,2);
}

Tiles::Tiles(Vector2 positionVector)
{
	m_centreX = positionVector.x + m_length/2;
	m_centreY = positionVector.y + m_bredth/2;
}

Tiles::~Tiles()
{

}

void Tiles::Render()
{
	Texture *m_texture = g_theRenderer->CreateOrGetTexture("Data\\Images\\terrain.png");	
	if(g_TerrainTile==nullptr)
	{
		g_TerrainTile = new SpriteSheet(*m_texture,8,8);
	}
	
	Vector2 minPosition  = TileDefinitions::GetMinPos(m_tileType);
	Vector2 maxPosition  = TileDefinitions::GetMaxPos(m_tileType);
	
	g_theRenderer->DrawTexturedAABB(m_aabb2, m_texture, minPosition , maxPosition,Rgba::WHITE);
}

void Tiles::SetPosition(Vector2 positionVector)
{
	positionVector += (m_length/2); 
	m_position		= positionVector;
	m_centreX		= positionVector.x;
	m_centreY		= positionVector.y;
	AABB2 tempaabb2(positionVector,m_length/2,m_bredth/2);
	m_aabb2			= tempaabb2;
}
