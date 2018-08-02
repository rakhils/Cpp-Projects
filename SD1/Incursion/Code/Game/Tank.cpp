#include "Game/Tank.hpp"

#include "Engine/Math/MathUtil.hpp"

#include "Game/GameCommon.hpp"

Tank::Tank()
{
	m_centreX					= 3;
	m_centreY					= 3;
	m_angle						= 180;
	m_angularVelocity			= TANK_ANGULAR_VELOCITY;
	m_collisionDisk.center.x	= m_centreX;
	m_collisionDisk.center.y	= m_centreY;
	m_collisionDisk.radius		= m_length/2 * ENTITY_PHYSICS_RATIO;

}

Tank::Tank(Vector2 position)
{
	m_centreX					= position.x;
	m_centreY					= position.y;
	m_angularVelocity			= TANK_ANGULAR_VELOCITY;
	m_collisionDisk.center.x	= m_centreX;
	m_collisionDisk.center.y	= m_centreY;
	m_collisionDisk.radius		= m_length / 2 * ENTITY_PHYSICS_RATIO;
}

Tank::~Tank()
{

}


void Tank::Update(float deltaTime) 
{
	if(m_markForDelete)
	{
		m_deathCounter++;
		return;
	}
	m_deathCounter = 0;
	m_prev_centreX = m_centreX;
	m_prev_centreY = m_centreY;
	m_bulletCounter++;
	if(m_turnInProgress)
	{
		DoAngleCorrection(m_finalAngle);
		float turnAngle = TurnTowards(&m_startAngle,m_finalAngle,deltaTime*m_angularVelocity);
		DoAngleCorrection(m_angle);
		if(m_turnDirection == -1)
		{
			m_angle -= turnAngle;
		}
		else
		{
			m_angle += turnAngle;
		}
		DoAngleCorrection(m_angle);
		MoveForward(1.0f,deltaTime);
		if(m_startAngle >= m_finalAngle)
		{
			m_turnInProgress = false;
		}
	}

	if(m_turret_turnInProgress)
	{
		float turnAngle = TurnTowards(&m_turret_startAngle,m_turret_finalAngle,deltaTime*m_angularVelocity);
		if (m_turret_turnDirection == -1)
		{
			m_turret_angle -= turnAngle;//*deltaTime*m_angularVelocity;
		}
		else
		{
			m_turret_angle += turnAngle;//*deltaTime*m_angularVelocity;
		}
		DoAngleCorrection(m_turret_angle);
		
		if(m_turret_startAngle >= m_turret_finalAngle)
		{
			m_turret_turnInProgress = false;
		}
	}

	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
}

void Tank::Render()
{		
	m_tankTexture		= g_theRenderer->CreateOrGetTexture("Data\\Images\\1.png");
	m_tankTopTexture	= g_theRenderer->CreateOrGetTexture("Data\\Images\\PlayerTankTop.png");
	
	Vector2 texCoordsAtMins(0,0);
	Vector2 texCoordsAtMaxs(1,1);
	Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255));
	
	// TANK
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_angle);
	AABB2 aabb2t(Vector2(0,0),m_length/2,m_bredth/2);
	g_theRenderer->DrawTexturedAABB(aabb2t, m_tankTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();

	// TURRET
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_turret_angle);
	g_theRenderer->DrawTexturedAABB(aabb2t, m_tankTopTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();
	Entity::Render();
}

void Tank::TurretTurnTowards(float angle)
{
	DoAngleCorrection(m_turret_angle);
	m_turret_finalAngle			= angle;
	float angularDisplacement	= GetAngularDisplacement(m_turret_angle,angle);
	angularDisplacement			= GetModulus(angularDisplacement);
	float directionOfRotation	= GetRotationDirectionBetween2Angles(m_turret_angle,m_turret_finalAngle);
	m_turret_startAngle			= 0;
	m_turret_finalAngle			= angularDisplacement;
	m_turret_turnDirection		= directionOfRotation;
	m_turret_turnInProgress		= true;
}

Vector2 Tank::GetTurretDirectionVector()
{
	Vector2 turretDirection(CosDegrees(m_turret_angle),SinDegrees(m_turret_angle));
	return turretDirection.GetNormalized();
}

void Tank::TurnTurret(float direction)
{
	m_turret_angle += direction;
}

