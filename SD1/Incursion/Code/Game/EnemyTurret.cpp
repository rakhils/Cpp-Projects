#include "Game/EnemyTurret.hpp"

#include "Engine/Math/MathUtil.hpp"

#include "Game/GameCommon.hpp"

EnemyTurret::EnemyTurret()
{
	m_centreX				 = 10;
	m_centreY				 = 10;
	m_angle					 = 180;
	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
	m_collisionDisk.radius   = m_length;
	m_angularVelocity		 = TANK_ANGULAR_VELOCITY;
}

EnemyTurret::EnemyTurret(Vector2 position)
{
	m_centreX			= position.x;
	m_centreY			= position.y;
	m_angularVelocity   = TANK_ANGULAR_VELOCITY;
}

EnemyTurret::~EnemyTurret()
{

}


void EnemyTurret::Update(float deltaTime) 
{
	m_bulletCounterTime++;
	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
	m_collisionDisk.radius = ((m_length/2)*ENTITY_PHYSICS_RATIO);
	
	if(m_turnInProgress)
	{
		float turnAngle = TurnTowards(&m_startAngle,m_finalAngle,m_angularVelocity*deltaTime);
		m_angle			+= m_turnDirection*turnAngle;
		if(IsAngleWithinRangeOf(m_angle,m_finalAngle,2,m_turnDirection))
		{
			m_turnInProgress = false;	
		}
	}
}

bool EnemyTurret::IsPlayerTankInsideRange()
{
	if(m_playerTankVector.GetLength() < m_range)
	{
		return true;
	}
	return false;
}

void EnemyTurret::Render()
{	
	m_turretBaseTexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\EnemyTurretBase.png");
	m_turretTopTexture  = g_theRenderer->CreateOrGetTexture("Data\\Images\\EnemyTurretTop.png");

	Vector2 texCoordsAtMins(0,0);
	Vector2 texCoordsAtMaxs(1,1);
	Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255));
	
	Vector2 centr = GetCenter();

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(0);
	AABB2 aabb2t(Vector2(0,0),m_length/2,m_bredth/2);
	g_theRenderer->DrawTexturedAABB(aabb2t, m_turretBaseTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_angle);
	g_theRenderer->DrawTexturedAABB(aabb2t, m_turretTopTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();

	if(m_playerInRange)
	{
		g_theRenderer->SetColor(1,0,0);
		Rgba startColor(static_cast<unsigned char>(255),static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(255));
		Rgba finalColor(static_cast<unsigned char>(255),static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(0));
		g_theRenderer->DrawFeatheredLine(GetCenter(),(PTank->GetCenter()),startColor,finalColor);
		g_theRenderer->SetColor(1,1,1);
	}

	Entity::Render();
}


