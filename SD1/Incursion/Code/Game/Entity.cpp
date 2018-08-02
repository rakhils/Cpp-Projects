#include "Entity.hpp"

Entity::Entity()
{
	m_radius		  = 1;
	m_speed			  = TANK_SPEED;
	m_angularVelocity = TANK_ANGULAR_VELOCITY;
}

Entity::Entity(Vector2 position)
{
	m_centreX		  = position.x;
	m_centreY		  = position.y;
	m_speed			  = TANK_SPEED;
	m_angularVelocity = TANK_ANGULAR_VELOCITY;
}

void Entity::Update(float deltaTime)
{
	UNUSED(deltaTime);
	m_collisionDisk.center = Vector2(m_centreX, m_centreY);
}

void Entity::Render()
{
	if(m_debugMode)
	{
		g_theRenderer->SetColor(255,0,255);
		g_theRenderer->DrawDottedCircle(m_centreX,m_centreY,m_radius);
		g_theRenderer->SetColor(0,255,255);
		g_theRenderer->DrawDottedCircle(m_centreX,m_centreY,m_radius*0.8f);
		g_theRenderer->SetColor(255,255,255);
		g_theRenderer->SetColor(255,255,0);
		g_theRenderer->SetColor(255, 255, 255);
		Vector2 directionVector = Vector2(CosDegrees(m_angle),SinDegrees(m_angle));
		directionVector			= directionVector*2;
		directionVector			+= GetCenter();
		g_theRenderer->SetColor(255, 255, 0);
		g_theRenderer->DrawLine(directionVector,(Vector2(m_centreX,m_centreY)));
		g_theRenderer->SetColor(255, 255, 255);
	}
}

void Entity::SetDirectionVector(Vector2 direction)
{
	direction		  = direction.GetNormalized();
	m_directionVector = direction;
	m_angle			  = direction.GetOrientationDegrees();
}

void Entity::TurnEntity(float incrementalAngle, float direction)
{
	if(direction > 0)
	{
		m_angle -= incrementalAngle;
	}
	else
	{
		m_angle += incrementalAngle;
	}
}

void Entity::MoveForward(float thrust,float deltaTime)
{
	Vector2 directionVector = GetForwardUnitVector();
	m_centreX += directionVector.x*thrust*deltaTime*m_speed;
	m_centreY += directionVector.y*thrust*deltaTime*m_speed;
}

Vector2 Entity::GetForwardUnitVector()
{
	Vector2 directionVector(CosDegrees(m_angle),SinDegrees(m_angle));
	return directionVector;
}

Disc2 Entity::GetDisc2D()
{
	return m_collisionDisk;
}

void Entity::TurnTowards2(float finalAngle)
{
	DoAngleCorrection(m_angle);
	float angularDisplacement = GetAngularDisplacement(m_angle,finalAngle);
	angularDisplacement       = GetModulus(angularDisplacement);
	float directionOfRotation = GetRotationDirectionBetween2Angles(m_angle,finalAngle);
	m_startAngle			  = 0;
	m_finalAngle			  = angularDisplacement;
	m_turnDirection			  = directionOfRotation;
	m_turnInProgress		  = true;
}

Vector2 Entity::GetPosition()
{
	return GetCenter();
}

Vector2 Entity::GetCenter()
{
	return Vector2(m_centreX,m_centreY);
}







