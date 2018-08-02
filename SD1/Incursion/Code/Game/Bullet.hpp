#pragma once
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Math/Vector2.hpp"

#include "Game/Entity.hpp"
#include "Game/Tank.hpp"


class Bullet: public Entity
{
public:

	Bullet();
	Bullet(Vector2 position);
	~Bullet();

	float m_length = 2;
	float m_bredth = 2;
	

	void Update(float deltaTime);
	void Render();

	Texture * BulletTexture;
	unsigned int m_textureNum = 0;
	void SetDirection(Vector2 direction);
	Vector2 GetNextPosition();
};