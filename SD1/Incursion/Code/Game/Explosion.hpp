#pragma once
#include "Game/Entity.hpp"


class Explosion : public Entity
{
public:
	Vector2			 m_position;
	float			 m_radius			  = ENTITY_WIDTH;
	float			 m_duration			  = EXPLOSION_TIME;
	SpriteAnimation *m_explosionAnimation = nullptr;

	// FUNCTIONS
	Explosion();
	Explosion(Vector2 position,float radius);
	Explosion(Vector2 position,float radius,float duration);

	void Update(float deltaSecond);
	void Render();
};