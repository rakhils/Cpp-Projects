#include "Game/EnemyTank.hpp"

#include "Engine/Math/MathUtil.hpp"

#include "Game/GameCommon.hpp"
#include "Game/Map.hpp"

EnemyTank::EnemyTank()
{
	m_centreX				 = 10;
	m_centreY				 = 10;
	m_angle					 = 180;
	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
	m_collisionDisk.radius   = m_length;
	m_speed					 = ENEMY_TANK_SPEED;
	m_targetPostion			 = Vector2(0,0);
}

EnemyTank::EnemyTank(Vector2 position,Map *map)
{
	m_centreX			= position.x;
	m_centreY			= position.y;
	m_speed				= ENEMY_TANK_SPEED;
	m_targetPostion		= Vector2(0,0);
	m_angularVelocity	= TANK_ANGULAR_VELOCITY;
	m_map = map;
}

EnemyTank::~EnemyTank()
{

}

void EnemyTank::Update(float deltaTime) 
{
	m_counter++;
	m_bulletCounterTime++;
	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;
	m_collisionDisk.radius   = ((m_length/2)*ENTITY_PHYSICS_RATIO);
	
	if(m_turnInProgress)
	{
		float turnAngle = TurnTowards(&m_startAngle,m_finalAngle,m_angularVelocity*deltaTime);
		if(m_turnDirection == -1)	
		{
			m_angle -= turnAngle*deltaTime*m_angularVelocity;
		}
		else
		{
			m_angle += turnAngle*deltaTime*m_angularVelocity;
		}
		if(IsAngleWithinRangeOf(m_startAngle,m_finalAngle,10,m_turnDirection))
		{
			m_turnInProgress = false;
		}
	}	
}

bool EnemyTank::IsPlayerTankInsideRange()
{
	if(m_playerTankPosition.GetLength() < m_range)
	{
		return true;
	}
	return false;
}

void EnemyTank::CheckAndSetBehaviourState()
{
	Vector2 playerPosition = m_map->m_entityByType[PLAYER_TANK].at(0)->GetCenter();
	Vector2 playerDistance = playerPosition - GetCenter();

	if (m_map->HasLineOfSight(GetCenter(), playerPosition) && playerDistance.GetLength() < PLAYER_RANGE)
	{
		m_lastActiveTime = static_cast<float>(GetCurrentTimeSeconds());
		if (DotProduct(GetForwardUnitVector().GetNormalized(), playerDistance.GetNormalized()) > CosDegrees(5))
		{
			m_state = ENEMY_SHOOT_ON_PLAYER;
			m_currentTargetPosition = playerPosition;
			return;
		}
		else
		{
			m_state = ENEMY_TURN_TO_PLAYER;
			m_currentTargetPosition = playerPosition;
			return;
		}
	}
	for (size_t enemyIndex = 0; enemyIndex < m_map->m_entityByType[ALLY_TANK].size(); enemyIndex++)
	{
		AllyTank *enemyTank = (AllyTank*)m_map->m_entityByType[ALLY_TANK].at(enemyIndex);
		if (enemyTank->m_markForDelete)
		{
			continue;
		}
		Vector2 enemyPosition = enemyTank->GetCenter();
		Vector2 enemyDistance = enemyPosition - GetCenter();
		if (m_map->HasLineOfSight(GetCenter(), enemyPosition) && enemyDistance.GetLength() < PLAYER_RANGE)
		{
			m_lastActiveTime = static_cast<float>(GetCurrentTimeSeconds());
			if (DotProduct(GetForwardUnitVector().GetNormalized(), enemyDistance.GetNormalized()) > CosDegrees(5))
			{
				m_state = ENEMY_SHOOT_ON_PLAYER;
				m_currentTargetPosition = enemyPosition;
				return;
			}
			else
			{
				m_state = ENEMY_TURN_TO_PLAYER;
				m_currentTargetPosition = enemyPosition;
				return;
			}
		}
	}
	m_state = ENEMY_WANDER;
}

void EnemyTank::ShootAtPlayer()
{
	if (m_lastBulletSpawnTime + PLAYER_BULLET_SHOOT_INTERVAL < m_bulletCounterTime && !m_markForDelete)
	{
		m_lastBulletSpawnTime = m_bulletCounterTime;
		Vector2 playerTurretDirecton = GetForwardUnitVector();
		Vector2 bulletSpawnPosition = GetCenter() + GetForwardUnitVector();
		Entity *entityBP = m_map->SpawnNewEntity(ENEMY_BULLET, bulletSpawnPosition, Vector2(0, -1));
		m_map->SpawnNewEntity(EXPLOSION_ENTITY, bulletSpawnPosition, Vector2(0, -1), 1.0f);
		entityBP->SetDirectionVector(GetForwardUnitVector());
	}
}

void EnemyTank::TurnTowardsPlayer()
{
	Vector2 distanceVector      = m_currentTargetPosition - GetCenter();
	distanceVector			    = distanceVector.GetNormalized();
	float randomAngle			= Atan2Degrees(distanceVector.y, distanceVector.x);
	float angularDisplacement   = GetModulus(GetAngularDisplacement(m_angle, randomAngle));
	m_turnDirection				= GetRotationDirectionBetween2Angles(m_angle, randomAngle);
	m_startAngle				= 0;
	m_finalAngle				= angularDisplacement;
	m_turnInProgress = true;
}

void EnemyTank::Wander(float deltaTime)
{
	if (!m_turnInProgress)
	{
		if (GetCurrentTimeSeconds() - m_lastActiveTime > 2)
		{
			m_lastActiveTime			= static_cast<float>(GetCurrentTimeSeconds());
			float randomAngle			= GetRandomFloatInRange(0, 360);
			float angularDisplacement	= GetModulus(GetAngularDisplacement(m_angle, randomAngle));
			m_turnDirection			    = GetRotationDirectionBetween2Angles(m_angle, randomAngle);
			m_startAngle				= 0;
			m_finalAngle			    = angularDisplacement;
			m_turnInProgress			= true;
		}
		else
		{
			MoveForward(0.50, deltaTime);
		}
	}
}


void EnemyTank::Render()
{	
	m_tankTexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\Etank.png");
	Vector2 texCoordsAtMins(0,0);
	Vector2 texCoordsAtMaxs(1,1);
	Rgba tint((unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)255);
	
	Vector2 centr = GetCenter();
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_angle);
	AABB2 aabb2(Vector2(0,0),m_length/2,m_bredth/2);
	g_theRenderer->DrawTexturedAABB(aabb2, m_tankTexture, texCoordsAtMins, texCoordsAtMaxs,tint);
	g_theRenderer->PopMatrix();

	if(m_playerInRange)
	{
		g_theRenderer->SetColor(1,0,0);
		g_theRenderer->DrawLine(GetCenter(),(PTank->GetCenter()));
		g_theRenderer->SetColor(1,1,1);
	}

	Entity::Render();
}


