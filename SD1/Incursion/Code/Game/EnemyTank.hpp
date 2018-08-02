#pragma once
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Time.hpp"

#include "Game/Entity.hpp"
#include "Game/Tank.hpp"

class Map;
enum EnemyStates
{
	ENEMY_WANDER,
	ENEMY_TURN_TO_PLAYER,
	ENEMY_SHOOT_ON_PLAYER
};
class EnemyTank: public Entity
{
public:

	float					m_length					= ENTITY_WIDTH;
	float					m_bredth					= ENTITY_HEIGHT;
	float					m_range						= VIEW_RANGE;
	bool					m_playerInRange				= false;
	float					m_lastRotatedTime			= static_cast<float>(GetCurrentTimeSeconds());
	int						m_counter					= 0;
	float					m_lastBulletSpawnTime		= 0;
	float					m_bulletCounterTime			= 0;
	Vector2					m_targetPostion;

	Vector2					m_playerTankPosition;
	Vector2					m_playerTankLastSeenPosition;
	Texture *				m_tankTexture				= nullptr;
	unsigned int			m_textureNum				= 0;
	EnemyStates				m_state;
	Map	*					m_map						= nullptr;
	float					m_lastActiveTime			= 0.f;
	Vector2					m_currentTargetPosition;

	// FUNCTIONS
	EnemyTank();
	EnemyTank(Vector2 position,Map *map);
	~EnemyTank();

	void Update(float deltaTime);
	void Render();

	bool IsPlayerTankInsideRange();

	void CheckAndSetBehaviourState();
	void ShootAtPlayer();
	void TurnTowardsPlayer();
	void Wander(float deltaTime);
};