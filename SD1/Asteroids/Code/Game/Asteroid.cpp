#include <math.h>

#include "Engine/Math/MathUtil.hpp"	

#include "Game/Asteroid.hpp"
#include "Game/GameCommon.hpp"

Asteroid::Asteroid(float centreX,float centreY,int numOfSides,float radius,float startAngle,float directionX,float directionY,float changeInAngle)
{
	m_disc2.center  = Vector2(centreX, centreY);
	m_disc2.radius  = radius;
	m_numOfSides    = numOfSides;
	m_startAngle    = startAngle;
	m_innRadius     = radius*ENITY_VS_PHYSICS_FACTOR;
	m_direction     = Vector2(directionX, directionY);
	m_changeInAngle = changeInAngle;
}		  

Asteroid::Asteroid()
{

}

Asteroid::~Asteroid()
{
	//delete 
}

void Asteroid::Render()
{
	if(this->m_isAlive == false)
	{
		return;
	}
	Vector2 positionVector = m_disc2.center;

	g_theRenderer->PushMatrix();	
	g_theRenderer->Translate(positionVector);
	g_theRenderer->Rotate(m_startAngle);
	g_theRenderer->ScaleUniform(1);
	g_theRenderer->DrawLines(m_points,Rgba::WHITE,false);
	g_theRenderer->PopMatrix();
	if(m_debugMode)
	{
		g_theRenderer->SetColor(255,255,0);
		g_theRenderer->DrawLine(positionVector.x,positionVector.y,(positionVector.x + m_direction.x*60.f),(positionVector.y + m_direction.y*60.0f));
		g_theRenderer->SetColor(255,0,255);
		g_theRenderer->DrawDottedCircle(positionVector.x,positionVector.y,m_disc2.radius);
		g_theRenderer->SetColor(0,255,255);
		g_theRenderer->DrawDottedCircle(positionVector.x,positionVector.y,m_innRadius);
	}
}

void Asteroid::InitAsteroidPositions()
{
	float angle  = 360.0f/(float)m_numOfSides;
	float radius = m_disc2.radius;
	Vector2 prevPoint;
	for(int pointIndex = 0; pointIndex <= m_numOfSides; pointIndex++)
	{
		float maxEndX =  (radius)*CosDegrees(pointIndex*angle);
		float maxEndy =  (radius)*SinDegrees(pointIndex*angle);

		float minEndX =  (m_innRadius)*CosDegrees(pointIndex*angle);
		float minEndY =  (m_innRadius)*SinDegrees(pointIndex*angle);

		float pointx  =  GetRandomFloatInRange(minEndX, maxEndX);
		float pointY  =  GetRandomFloatInRange(minEndY, maxEndy);

		if (pointIndex > 1)
		{
			m_points.push_back(prevPoint);
		}
		m_points.push_back(Vector2(pointx,pointY));
		prevPoint = Vector2(pointx, pointY);
	}
}


void Asteroid::Update(float deltaTime)
{
	m_prevPosition =   m_disc2.center;
	m_disc2		   +=  m_direction * deltaTime;
	m_startAngle   +=  m_changeInAngle*deltaTime;
	CheckIfPositionOutsideWorld();
}

void Asteroid::CheckIfPositionOutsideWorld()
{
	if(m_disc2.center.x - m_disc2.radius > WINDOWS_WIDTH)
	{
		m_disc2.center.x = 0 - m_disc2.radius;
	}
	else if(m_disc2.center.x + m_disc2.radius < 0)
	{
		m_disc2.center.x = WINDOWS_WIDTH + m_disc2.radius;
	}
	else if(m_disc2.center.y - m_disc2.radius > WINDOWS_WIDTH)
	{
		m_disc2.center.y = 0 - m_disc2.radius;
	}
	else if(m_disc2.center.y + m_disc2.radius < 0)
	{
		m_disc2.center.y = WINDOWS_WIDTH + m_disc2.radius;
	}
}

bool Asteroid::HasCollisionOccured(Disc2 entityDisk2)
{
	bool collision = DoDiscsOverlap(m_disc2,entityDisk2);
	
	if(collision)
	{
		return true;
	}
	return false;
}

