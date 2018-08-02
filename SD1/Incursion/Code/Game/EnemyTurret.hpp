#pragma once
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Math/Vector2.hpp"

#include "Game/Entity.hpp"

enum STATE
{
	WANDER,
	PURSUE
};

class EnemyTurret: public Entity
{
public:

	EnemyTurret();
	EnemyTurret(Vector2 position);
	~EnemyTurret();

	float			m_length					= ENTITY_WIDTH;
	float			m_bredth					= ENTITY_HEIGHT;
	float			m_range						= ENEMY_TURRET_RANGE;
	bool			m_playerInRange				= false;

	Vector2			m_playerTankVector;
	float			m_lastBulletSpawnTime		= 0;
	float			m_bulletCounterTime			= 0;
	unsigned int    m_textureNum				= 0;
	Texture *		m_turretBaseTexture			= nullptr;
	Texture *		m_turretTopTexture			= nullptr;

	void Update(float deltaTime);
	void Render();
	bool IsPlayerTankInsideRange();
};