#include "Game/Bullet.hpp"

#include "Engine/Math/MathUtil.hpp"

#include "Game/GameCommon.hpp"

Bullet::Bullet()
{
	m_speed  = BULLET_SPEED;
	m_radius = BULLET_RADIUS;
}

Bullet::Bullet(Vector2 position)
{
	m_centreX = position.x;
	m_centreY = position.y;
	m_speed   = BULLET_SPEED;
	m_radius  = BULLET_RADIUS;
}

Bullet::~Bullet()
{

}

void Bullet::Update(float deltaTime) 
{
	m_centreX += m_directionVector.x*m_speed*deltaTime;
	m_centreY += m_directionVector.y*m_speed*deltaTime;

	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
	m_collisionDisk.radius = ((m_length/2)*ENTITY_PHYSICS_RATIO);
}

void Bullet::SetDirection(Vector2 direction)
{
	m_directionVector = direction;
}


Vector2 Bullet::GetNextPosition()
{
	Vector2 nextPosition(m_centreX + m_directionVector.x*m_speed*MAX_DELTA, m_centreY + m_directionVector.y*m_speed*MAX_DELTA);
	return nextPosition;
}

void Bullet::Render()
{

	BulletTexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\Bullet.png");
	
	Vector2 texCoordsAtMins(0,0);
	Vector2 texCoordsAtMaxs(1,1);
	Rgba tint;
	if(m_type == ENEMY_BULLET)
	{
		tint.SetAsBytes(static_cast<unsigned char>(255),static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(255));

	}
	if(m_type == PLAYER_BULLET)
	{
		tint.SetAsBytes(static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(255),static_cast<unsigned char>(255));
	}
	Vector2 centr = GetCenter();
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(Atan2Degrees(m_directionVector.y,m_directionVector.x));
	g_theRenderer->ScaleUniform(m_radius);
	AABB2 aabb2(Vector2(0,0),m_length/2,m_bredth/2);
	g_theRenderer->DrawTexturedAABB(aabb2, BulletTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();

	Entity::Render();
}


