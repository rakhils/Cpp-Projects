
#include "Engine/Math/MathUtil.hpp"
#include "Engine/Math/Vector2.hpp"
#include "GameCommon.hpp"

#include "Bullet.hpp"


Bullet::Bullet()
{

}

Bullet::Bullet(float centreX, float centreY, float angle, float nvelocity, int timeToLive)
{
	m_disc2.center = Vector2(centreX, centreY);
	m_disc2.radius = 0.1f;
	this->m_angle = angle;
	m_length = 20;
	m_innlength = m_length*0.8f;
	timeToLive = 1000;
	nvelocity = 10;

}

void Bullet::Render()
{
	if (!m_isAlive)
	{
		return;
	}
	float endX = m_disc2.center.x + (m_length)*CosDegrees(m_angle);
	float endY = m_disc2.center.y + (m_length)*SinDegrees(m_angle);
	g_theRenderer->DrawCircle(m_disc2.center.x,m_disc2.center.y, 1, 3);

	if (m_debugMode)
	{
		g_theRenderer->SetColor(255, 0, 255);
		g_theRenderer->DrawCircle(m_disc2.center.x, m_disc2.center.y, m_length);
		g_theRenderer->SetColor(0, 255, 255);
		g_theRenderer->DrawCircle(m_disc2.center.x,m_disc2.center.y, m_innlength);
		g_theRenderer->SetColor(255, 255, 0);
		Vector2 unitVector = Vector2(endX - m_disc2.center.x, endY - m_disc2.center.y).GetNormalized();
		g_theRenderer->DrawLine(m_disc2.center.x,m_disc2.center.y, m_disc2.center.x + (m_velocity*unitVector.x*60), m_disc2.center.y + (m_velocity*unitVector.y*60));
		////glVertex2f(centreX,centreY);
		//	glVertex2f(centreX+(velocity*unitVector->x*60.0f),centreY+(velocity*unitVector->y*60.0f));
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
	if (m_timeFromstart > (4200))
	{
		this->m_isAlive = false;
		return;
	}
	float endRadiant = GetRadiantFromDegree(((float)m_angle));
	float endX = m_disc2.center.x + (m_length)*CosDegrees(m_angle);
	float endY = m_disc2.center.y + (m_length)*SinDegrees(m_angle);
	Vector2 unitVector = Vector2(endX - m_disc2.center.x, endY - m_disc2.center.y).GetNormalized();
	m_disc2.center += deltaTime * (unitVector)*m_velocity;
}

void Bullet::CheckIfBoundsOutsideWorld()
{
	if (m_disc2.center.x - m_length > 1000)
	{
		m_disc2.center.x = 0 - m_length;
	}

	if (m_disc2.center.x + m_length < 0)
	{
		m_disc2.center.x = 1000 + m_length;
	}

	if (m_disc2.center.y - m_length > 1000)
	{
		m_disc2.center.y = 0 - m_length;
	}

	if (m_disc2.center.y + m_length < 0)
	{
		m_disc2.center.y = 1000 + m_length;
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