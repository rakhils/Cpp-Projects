#pragma once
#include "Game/Entity.hpp"
#include "Game/GameCommon.hpp"

enum ExtraBonusPickUps
{
	EXTRA_HEALTH,
	EXTRA_MISSILE
};

class Extras : public Entity
{
public:

	float m_length = ENTITY_WIDTH;
	float m_bredth = ENTITY_HEIGHT;

	float m_scalingUpperLimit = 1.5;
	float m_scalingLowerLimit = 0.5;
	float m_scalingDirection  = 1;
	float m_scaleFactor		  = 1;

	Texture *			m_texture = nullptr;
	ExtraBonusPickUps	m_type;
	AABB2				m_textureCord;

	// FUNCTIONS
	Extras();
	Extras(Vector2 position,ExtraBonusPickUps type);
	void Update(float deltaTime);
	void Render();

};