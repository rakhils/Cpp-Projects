#include "AllyTank.hpp"
#include "Game/Map.hpp"
AllyTank::AllyTank(Vector2 positionVector,Map *map)
{
	m_centreX					= positionVector.x;
	m_centreY					= positionVector.y;
	m_angle						= 0;
	m_angularVelocity			= TANK_ANGULAR_VELOCITY;
	m_collisionDisk.center.x	= m_centreX;
	m_collisionDisk.center.y	= m_centreY;
	m_collisionDisk.radius		= m_length / 2.0f * ENTITY_PHYSICS_RATIO;
	m_map						= map;
}

void AllyTank::Update(float deltaTime)
{
	m_bulletCounter++;
	m_collisionDisk.center.x = m_centreX;
	m_collisionDisk.center.y = m_centreY;

	if(m_turnInProgress)
	{
		float turnDeltaAngle   = TurnTowards(&m_startAngle,m_finalAngle,m_angularVelocity*deltaTime);
		m_angle				  += turnDeltaAngle * m_turnDirection;
		m_actuallyTurned	  += turnDeltaAngle * m_turnDirection;
	
		if(IsAngleWithinRangeOf(m_startAngle,m_finalAngle,5,m_turnDirection) || IsAngleWithinRangeOf(m_actuallyTurned,m_finalAngle,5,m_turnDirection))
		{
			m_turnInProgress = false;
			m_lastActiveTime = static_cast<float>(GetCurrentTimeSeconds());
		}
	}	
} 

void AllyTank::Render()
{
	if(m_markForDelete)
	{
		return;
	}
	m_texture = g_theRenderer->CreateOrGetTexture(IMAGE_DIRECTORY+IMAGE_ALLY_TANK);

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_angle);
	g_theRenderer->ScaleUniform(1);
	AABB2 aabb2(Vector2(0,0),m_length/2,m_bredth/2);
	Vector2 texCoordsAtMins(0,0);
	Vector2 texCoordsAtMaxs(1,1);
	g_theRenderer->DrawTexturedAABB(aabb2, m_texture, texCoordsAtMins, texCoordsAtMaxs,COLOR_WHITE);
	g_theRenderer->PopMatrix();

	Entity::Render();
}

bool AllyTank::DoUpdateAllyState(AllyStates state)
{
	if(m_state == state)
	{
		//return false;
	}
	m_state = state;
	return true;
}

void AllyTank::CheckAndSetBehaviourState()
{
	Vector2 playerPosition	= m_map->m_entityByType[PLAYER_TANK].at(0)->GetCenter();
	for (size_t enemyIndex = 0; enemyIndex < m_map->m_entityByType[ENEMY_TANK].size(); enemyIndex++)
	{
		EnemyTank *enemyTank  = (EnemyTank*)m_map->m_entityByType[ENEMY_TANK].at(enemyIndex);
		if(enemyTank->m_markForDelete)
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
				m_state					= ALLY_SHOOT_ON_ENEMY;
				m_currentTargetPosition = enemyPosition;
				return;
			}
			else
			{
				m_state				    = ALLY_TURN_TO_ENEMY;
				m_currentTargetPosition = enemyPosition;
				return;
			}
		}
	}
	Vector2 playerDistance = playerPosition - GetCenter();
	if (m_map->HasLineOfSight(GetCenter(), playerPosition) && playerDistance.GetLength() < PLAYER_RANGE)
	{
		if (DotProduct(GetForwardUnitVector().GetNormalized(), playerDistance.GetNormalized()) > CosDegrees(5))
		{
			m_state					= ALLY_MOVE_TO_PLAYER;
			m_currentTargetPosition = playerPosition;
			return;
		}
		else
		{
			m_state					= ALLY_TURN_TO_PLAYER;
			m_currentTargetPosition = playerPosition;
			return;
		}
	}
	m_state = ALLY_WANDER;
}

void AllyTank::ShootAtEnemy()
{
	m_enemyPosition = m_currentTargetPosition;
	if (m_lastBulletSpawnTime + PLAYER_BULLET_SHOOT_INTERVAL < m_bulletCounter && !m_markForDelete)
	{
		m_lastBulletSpawnTime		 = m_bulletCounter;
		Vector2 playerTurretDirecton = GetForwardUnitVector();
		Vector2 bulletSpawnPosition  = GetCenter() + GetForwardUnitVector();
		Entity *entityBP			 = m_map->SpawnNewEntity(PLAYER_BULLET, bulletSpawnPosition, Vector2(0, -1));
		m_map->SpawnNewEntity(EXPLOSION_ENTITY, bulletSpawnPosition, Vector2(0, -1), 1.0f);
		entityBP->SetDirectionVector(GetForwardUnitVector());
		bool doUpdate				 = DoUpdateAllyState(ALLY_SHOOT_ON_ENEMY);
		if (doUpdate) // UPDATING ALLY MESSAGES
		{
			m_map->UpdateAllyMessageString(m_number, "ATTACKING ENEMY ");
		}
	}
}

void AllyTank::TurnTowardsEnemy()
{
	InitiateTurnTowards();
	m_enemyPosition					= m_currentTargetPosition;
	bool isUpdate					= DoUpdateAllyState(ALLY_TURN_TO_ENEMY);
	if (isUpdate)
	{
		m_map->UpdateAllyMessageString(m_number, "TURNING TO ENEMY ");
	}
}

void AllyTank::MoveTowardsPlayer(float deltaTime)
{
	UNUSED(deltaTime);
	Vector2 distanceVector = m_currentTargetPosition - GetCenter();
	if (distanceVector.GetLength() > 2)
	{
		MoveForward(0.75f, deltaTime);
	}
	bool isUpdate = DoUpdateAllyState(ALLY_MOVE_TO_PLAYER);
	if (isUpdate)
	{
		m_map->UpdateAllyMessageString(m_number, "MOVING TO PLAYER ");
	}
}

void AllyTank::TurnTowardsPlayer(float deltaTime)
{
	UNUSED(deltaTime);
	InitiateTurnTowards();
	bool isUpdate				= DoUpdateAllyState(ALLY_TURN_TO_PLAYER);
	if (isUpdate)
	{
		m_map->UpdateAllyMessageString(m_number, "TURNING TO PLAYER");
	}
}

void AllyTank::Wander(float deltaTime)
{
	if (!m_turnInProgress)
	{
		if (GetCurrentTimeSeconds() - m_lastActiveTime > 2)
		{
			m_lastActiveTime		  = static_cast<float>(GetCurrentTimeSeconds());
			float randomAngle		  = GetRandomFloatInRange(0, 360);
			m_currentTargetPosition	  = Vector2(randomAngle) + GetCenter();
			InitiateTurnTowards();
			bool isUpdate			  = DoUpdateAllyState(ALLY_TURN_TO_PLAYER);
			if (isUpdate)
			{
				m_map->UpdateAllyMessageString(m_number, "TURNING TO NOPOSITION");
			}
		}
		else
		{
			MoveForward(0.50, deltaTime);
		}
	}
}

void AllyTank::InitiateTurnTowards()
{
	Vector2 distanceVector		= m_currentTargetPosition - GetCenter();
	distanceVector				= distanceVector.GetNormalized();
	float turnAngle				= Atan2Degrees(distanceVector.y, distanceVector.x);
	float angularDisplacement   = GetModulus(GetAngularDisplacement(m_angle, turnAngle));
	m_turnDirection				= GetRotationDirectionBetween2Angles(m_angle, turnAngle);
	m_startAngle				= 0;
	m_finalAngle				= angularDisplacement;
	m_turnInProgress			= true;
}

