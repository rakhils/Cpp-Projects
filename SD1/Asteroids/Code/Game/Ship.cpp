#include "Game/Ship.hpp"
#include "Game/GameCommon.hpp"

#include "Engine/Math/MathUtil.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Rgba.hpp"

Ship::Ship()
{
	m_disc2.Translate(Vector2(500, 500));
	m_disc2.radius			= 25;
	m_innRadius				= (float)(this->m_disc2.radius*ENITY_VS_PHYSICS_FACTOR);
	m_angle					= 90;
	m_speed					= 0.f;
	m_lastBulletFiredTime	= 0;
	for(int posIndex = 0; posIndex < 11; posIndex++)
	{
		m_posPositions.push_back(Vector2(0,0));
	}
}

void Ship::Render()
{
	if(m_isAlive == false)
	{
		return;
	}
	Rgba rgba;
	if(m_isPlayerShip)
	{
		rgba.SetAsFloats(RangeMapFloat(static_cast<float>(m_health), 0, static_cast<float>(PLAYER_MAX_HEALTH), 0, 1.f), 1.0f, 0.0f, 1.0f);
	}
	if(!m_isPlayerShip)
	{
		rgba.SetAsFloats(RangeMapFloat(static_cast<float>(m_health), 0, static_cast<float>(ENEMY_MAX_HEALTH), 0, 1.f), 0.0f, 1.0f, 1.0f);
	}
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(m_disc2.center);
	g_theRenderer->DrawLines(m_posPositions,rgba,false); // Drawing ship with pointArray
	g_theRenderer->PopMatrix();

	if(m_hasTail)
	{
		m_flickeringValue++;
		if(m_flickeringValue%2 == 0)
		{
			g_theRenderer->SetColor(255,0,0);
			g_theRenderer->PushMatrix();
			g_theRenderer->Translate(m_disc2.center);
			g_theRenderer->DrawLine(m_posPositions.at(3),m_posPositions.at(10),Rgba(255,0,0));
			g_theRenderer->DrawLine(m_posPositions.at(5),m_posPositions.at(10),Rgba(255,0,0));
			g_theRenderer->SetColor(255,255,255);
			g_theRenderer->PopMatrix();
		}
	}
	if(m_debugMode)
	{
		g_theRenderer->PushMatrix();
		g_theRenderer->Translate(m_disc2.center);
		g_theRenderer->SetColor(255,0,255);
		g_theRenderer->DrawDottedCircle(m_disc2.center.x,m_disc2.center.y,m_disc2.radius);
		g_theRenderer->SetColor(0,255,255);
		g_theRenderer->DrawDottedCircle(m_disc2.center.x,m_disc2.center.y,m_innRadius);
		g_theRenderer->SetColor(255,255,255);
		g_theRenderer->PopMatrix();

	}
}

void Ship::ReduceHealth()
{
	m_health -= 1;
	if(m_health <= 0)
	{
		m_destroyStarted = true;
		m_destroyEnded   = false;
	}
}

void Ship::Update(float deltaTime)
{
	if (m_destroyStarted && !m_destroyEnded)
	{
		m_hasTail = false;
		UpdateDestructionPoints(deltaTime);
		return;
	}
	m_lastBulletFiredTime++;
	Vector2 displacement = (m_forward*m_speed*deltaTime);
	m_disc2.Translate(displacement);
	if (m_isPlayerShip)
	{
		m_angle += m_angularVelocity * m_rotationDirection;
		m_angularVelocity -= deltaTime;
		m_angularVelocity = ClampFloat(m_angularVelocity, 0, PLAYER_MAX_ANGULAR_SPEED);
	}
	m_forward		     =  ConvertPolarToCartesian(1,m_angle);
	
	CheckAndSetPositionInsideBounds();
	
	m_posPositions.clear();
	float radius   = m_disc2.radius;
	Vector2 point1 = ConvertPolarToCartesian(radius,0		+ m_angle);

	Vector2 point2 = ConvertPolarToCartesian(radius,120		+ m_angle);

	Vector2 point3 = ConvertPolarToCartesian(radius/2.f,120 + m_angle);
	Vector2 point4 = ConvertPolarToCartesian(radius/2.f,240 + m_angle);
	Vector2 point5 = ConvertPolarToCartesian(radius,240     + m_angle);

	Vector2 point6 = ConvertPolarToCartesian(radius,180     + m_angle);
	
	m_posPositions.push_back(point1);
	m_posPositions.push_back(point2);
	m_posPositions.push_back(point2);
	m_posPositions.push_back(point3);
	m_posPositions.push_back(point3);
	m_posPositions.push_back(point4);
	m_posPositions.push_back(point4);
	m_posPositions.push_back(point5);
	m_posPositions.push_back(point5);
	m_posPositions.push_back(point1);
	m_posPositions.push_back(point6);
}

void Ship::ApplyAngularAcceleration(int direction)
{
	if (m_destroyStarted)
	{
		return;
	}
	m_angularVelocity   = PLAYER_MAX_ANGULAR_SPEED;
	m_rotationDirection = direction;
}

void Ship::ApplyLinearAcceleration(float MAX_SPEED,float deltaTime)
{
	if(m_destroyStarted)
	{
		return;
	}
	m_speed             += deltaTime;
	m_speed			    =  ClampFloat(m_speed,0,MAX_SPEED);
	m_hasTail		    =  true;
}

void Ship::UpdateDestructionPoints(float deltaTime)
{
	std::vector<Vector2> midPoints;
	for(int midpointIndex = 0,j=0; midpointIndex < 5; midpointIndex++,j+=2)
	{
		Vector2 midPoint;
		midPoint.x		=  (m_posPositions.at(j).x + m_posPositions.at(j+1).x)/2;
		midPoint.y		=  (m_posPositions.at(j).y + m_posPositions.at(j+1).y)/2;
		midPoints.push_back(midPoint.GetNormalized());
	}
	for(int midpointIndex = 0,j=0; midpointIndex < 5; midpointIndex++,j+=2)
	{
		m_posPositions.at(j).x   += (midPoints.at(midpointIndex).x*deltaTime);
		m_posPositions.at(j).y   += (midPoints.at(midpointIndex).y*deltaTime);						
		m_posPositions.at(j+1).x += (midPoints.at(midpointIndex).x*deltaTime);							
		m_posPositions.at(j+1).y += (midPoints.at(midpointIndex).y*deltaTime);
	}
	m_destroyCount++;
	m_speed -= deltaTime;
	m_speed = ClampFloat(m_speed, 0, PLAYER_MAX_SPEED);
	if(m_destroyCount >= 1500)
	{
		m_destroyEnded = true;
		m_isAlive      = false;
	}
}

void Ship::CheckAndSetPositionInsideBounds()
{
	if (m_disc2.center.x - m_disc2.radius > SCREEN_WIDTH)
	{
		m_disc2.center.x = 0 - m_disc2.radius;
	}

	if (m_disc2.center.x + m_disc2.radius < 0)
	{
		m_disc2.center.x = SCREEN_WIDTH + m_disc2.radius;
	}

	if(m_disc2.center.y - m_disc2.radius > SCREEN_WIDTH)
	{
		m_disc2.center.y = 0 - m_disc2.radius;
	}

	if(m_disc2.center.y + m_disc2.radius < 0)
	{
		m_disc2.center.y = SCREEN_WIDTH + m_disc2.radius;
	}
}

Vector2 Ship::GetNosePosition()
{
	float radius = m_disc2.radius;

	float noseX = m_disc2.center.x + (radius)*CosDegrees((m_angle));
	float noseY = m_disc2.center.y + (radius)*SinDegrees((m_angle));
	return Vector2(noseX,noseY);
}

bool Ship::HasCollisionOccured(Disc2 entityDisc)
{
	bool collision = DoDiscsOverlap(m_disc2,entityDisc);

	if(collision)
	{
		return true;
	}
	return false;
}
