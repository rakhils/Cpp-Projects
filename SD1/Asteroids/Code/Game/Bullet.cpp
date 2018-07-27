
#include "Engine/Math/MathUtil.hpp"
#include "Engine/Math/Vector2.hpp"
#include "GameCommon.hpp"

#include "Bullet.hpp"


Bullet::Bullet()
{

}

Bullet::Bullet(float centreX, float centreY, float angle, float nvelocity, float timeToLive)
{
	m_disc2.center  = Vector2(centreX, centreY);
	m_disc2.radius  = BULLET_RADIUS;
	m_angle			= angle;
	m_velocity      = nvelocity;
	m_timeToLive    = timeToLive;
}

void Bullet::Render()
{
	if (!m_isAlive)
	{
		return;
	}
	float endX = m_disc2.center.x + (m_disc2.radius)*CosDegrees(m_angle);
	float endY = m_disc2.center.y + (m_disc2.radius)*SinDegrees(m_angle);
	g_theRenderer->DrawCircle(m_disc2.center.x,m_disc2.center.y, BULLET_RADIUS, 5);

	if (m_debugMode)
	{
		g_theRenderer->SetColor(255, 0, 255);
		g_theRenderer->DrawCircle(m_disc2.center.x, m_disc2.center.y, m_disc2.radius);
		g_theRenderer->SetColor(0, 255, 255);
		g_theRenderer->DrawCircle(m_disc2.center.x,m_disc2.center.y, m_disc2.radius*0.8f);
		g_theRenderer->SetColor(255, 255, 0);
		Vector2 unitVector = Vector2(endX - m_disc2.center.x, endY - m_disc2.center.y).GetNormalized();
		g_theRenderer->DrawLine(m_disc2.center.x,m_disc2.center.y, m_disc2.center.x + (m_velocity*unitVector.x*60), m_disc2.center.y + (m_velocity*unitVector.y*60));
		
		g_theRenderer->SetColor(255, 255, 255);
	}
	CheckIfBoundsOutsideWorld();
}

void Bullet::Update(float deltaTime)
{
	if (!m_isAlive)
	{
		return;
	}
	m_timeFromstart += 1;
	if (m_timeFromstart > (m_timeToLive))
	{
		this->m_isAlive = false;
		return;
	}
	float endX			= m_disc2.center.x + (m_disc2.radius)*CosDegrees(m_angle);
	float endY			= m_disc2.center.y + (m_disc2.radius)*SinDegrees(m_angle);
	Vector2 unitVector  = Vector2(endX - m_disc2.center.x, endY - m_disc2.center.y).GetNormalized();
	m_disc2.center		+= deltaTime * (unitVector)*m_velocity;
}

void Bullet::CheckIfBoundsOutsideWorld()
{
	if (m_disc2.center.x - m_disc2.radius > SCREEN_WIDTH)
	{
		m_disc2.center.x = 0 - m_disc2.radius;
	}

	if (m_disc2.center.x + m_disc2.radius < 0)
	{
		m_disc2.center.x = SCREEN_WIDTH + m_disc2.radius;
	}

	if (m_disc2.center.y - m_disc2.radius > SCREEN_WIDTH)
	{
		m_disc2.center.y = 0 - m_disc2.radius;
	}

	if (m_disc2.center.y + m_disc2.radius < 0)
	{
		m_disc2.center.y = SCREEN_WIDTH + m_disc2.radius;
	}
}

bool Bullet::HasCollisionOccured(Disc2 disc2)
{
	bool collision = DoDiscsOverlap(m_disc2,disc2);

	if (collision)
	{
		return true;
	}
	return false;
}