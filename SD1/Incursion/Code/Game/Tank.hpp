#pragma once
#include "Entity.hpp"
#include "Engine/Renderer/Texture.hpp"


class Tank: public Entity
{
public:

	Tank();
	Tank(Vector2 position);
	~Tank();

	float			m_length						= ENTITY_WIDTH;
	float			m_bredth						= ENTITY_HEIGHT;
	float			m_turret_angle					= 0;
	float			m_turret_startAngle				= 0;
	float			m_turret_finalAngle				= 0;
	float			m_turret_turnDirection			= 0;
	bool			m_turret_turnInProgress			= false;
	float			m_lastBulletSpawnTime			= 0;
	float			m_bulletCounter					= 0;
	float			m_deathCounter					= 0;

	Texture *		m_tankTexture					= nullptr;
	Texture *		m_tankTopTexture				= nullptr;
	unsigned int	m_textureNum					= 0;

	void			Update(float deltaTime);
	void			Render();

	void			TurretTurnTowards(float direction);
	Vector2			GetTurretDirectionVector();
	void			TurnTurret(float direction);
};