#pragma once
#include "Engine/Math/MathUtil.hpp"
#include "GameCommon.hpp"
enum EntityType
{
	PLAYER_TANK,
	ENEMY_TANK,
	ENEMY_TURRET,
	ENEMY_BULLET,
	PLAYER_BULLET,
	ALLY_TANK,
	EXPLOSION_ENTITY
};

enum EntityByShape
{
	Disk_Type,
	AABB2_Type
};

enum EntityBySide
{
	ENTITY_ENEMY,
	ENTITY_ALLY
};

class Entity
{


public:
	// VARIABLES
	float			m_centreX				= 0;
	float			m_centreY				= 0;
	float			m_prev_centreX			= 0;
	float			m_prev_centreY			= 0;
	float			m_radius				= ENTITY_WIDTH;
	float			m_innerRadius			= m_radius*ENTITY_PHYSICS_RATIO;
	float			m_angle					= 0;
	float			m_startAngle			= 0;
	float			m_finalAngle			= 0;
	float			m_turnDirection			= 1;
	float			m_health				= 0;
	bool			m_turnInProgress		= false;
	bool			m_debugMode				= false;
	bool			m_isGamePaused			= false;
	float			m_angularVelocity		= 0.f;
	float			m_speed				    = 0.f;
	bool			m_markForDelete			= false;
	Vector2			m_directionVector;

	EntityType		m_type;
	Disc2			m_collisionDisk;
	Entity *		PTank;
	
	Vector2			m_forwardVector;

	// FUNCTIONS
	Entity();
	Entity(Vector2 position);
	
	void			Update(float deltaTime);
	void			Render();

	void			SetDirectionVector(Vector2 direction);

	void			TurnEntity(float incrementalAngle, float direction);
	void			TurnTowards2(float finalAngle);
	Vector2			GetPosition();
	Vector2			GetCenter();
	void			MoveForward(float thrust, float deltaTime);
	Vector2			GetForwardUnitVector();
	Disc2			GetDisc2D();
};