#pragma once
#include "Game/GameCommon.hpp"

#include "Engine/Core/Time.hpp"

#include "Game/Entity.hpp"

class Map;
enum AllyStates
{
	ALLY_TURN_TO_ENEMY,
	ALLY_SHOOT_ON_ENEMY,
	ALLY_TURN_TO_PLAYER,
	ALLY_MOVE_TO_PLAYER,
	ALLY_WANDER
};
class AllyTank : public Entity
{
public:
	// VARIABLES
	float							m_length					= ENTITY_WIDTH;
	float							m_bredth					= ENTITY_HEIGHT;
	float							m_lastBulletSpawnTime		= 0;
	float							m_bulletCounter				= 0;
	float							m_lastActiveTime			= 0;
	float							m_actuallyTurned			= 0;
	Vector2							m_enemyPosition;
	Texture *						m_texture					= nullptr;
	std::string						m_name;
	int								m_number;
	std::string						m_message;
	AllyStates						m_state;
	Vector2							m_currentTargetPosition;

	Map *							m_map						= nullptr;

	// FUNCTIONS

	AllyTank(Vector2 positionVector,Map *map);
	void Update(float deltaTime);
	void Render();
	bool DoUpdateAllyState(AllyStates state);

	// BEHAVIOURS
	void CheckAndSetBehaviourState();
	void ShootAtEnemy();
	void TurnTowardsEnemy();
	void MoveTowardsPlayer(float deltaTime);
	void TurnTowardsPlayer(float deltaTime);
	void Wander(float deltaTime);

	void InitiateTurnTowards();
};