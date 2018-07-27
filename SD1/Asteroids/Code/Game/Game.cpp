#include "Game/Game.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Math/MathUtil.hpp"
#include "Engine/Core/Rgba.hpp"

Game::Game()
{
	m_playerShip					= new Ship();
	m_playerShip->m_health			= PLAYER_MAX_HEALTH;
	m_enemyShip						= new Ship();
	m_enemyShip->m_health			= ENEMY_MAX_HEALTH;						
	m_playerShip->m_isPlayerShip    = true;
	m_enemyShip->m_angle			= ENEMY_INIT_ANGLE;
	m_enemyShip->m_disc2.center		= ENEMY_INIT_POSITION;
	
	for(int levelIndex = 0; levelIndex < 10; levelIndex++)
	{
		m_level[levelIndex].numOfAsteroids = (levelIndex+1)*4; // SAMPLE . CAN BE RETRIEVED FROM XML
	}
	SpawnNextAsteroidsWave(m_currentLevel);
	m_currentLevel++;
}

void Game::Render()
{
	m_playerShip->Render();
	m_enemyShip->Render();

	for(int bulletIndex = 0; bulletIndex < m_bullets.size();bulletIndex++)
	{
		Bullet *bullet = m_bullets.at(bulletIndex);
		if(bullet!=nullptr)
		{
			bullet->Render();
		}
	}
	for(int enemyBulletIndex = 0; enemyBulletIndex < m_enemyBullets.size(); enemyBulletIndex++)
	{
		Bullet *enemyBullet = m_enemyBullets.at(enemyBulletIndex);
		if(enemyBullet!=nullptr)
		{
			enemyBullet->Render();
		}
	}
	for(int asteroidIndex = 0; asteroidIndex < m_asteroids.size(); asteroidIndex++)
	{
		Asteroid *asteroid = m_asteroids.at(asteroidIndex);
		if(asteroid!= nullptr)
		{
			asteroid->Render();
		}
	}
}


void Game::Update(float deltaTime)
{		
	if (g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ESCAPE))
	{
		g_isQuitTriggered = true;
	}

	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_RIGHT_ARROW) || g_theInput->isKeyPressed(InputSystem::KEYBOARD_D))
	{
		m_playerShip->ApplyAngularAcceleration(-1);
	}

	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_LEFT_ARROW) || g_theInput->isKeyPressed(InputSystem::KEYBOARD_A))
	{
		m_playerShip->ApplyAngularAcceleration(1);
	}

	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_UP_ARROW) || g_theInput->isKeyPressed(InputSystem::KEYBOARD_W))
	{
		m_playerShip->ApplyLinearAcceleration(PLAYER_MAX_SPEED,deltaTime);
	}

	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_UP_ARROW) || g_theInput->isKeyPressed(InputSystem::KEYBOARD_W))
	{
		m_playerShip->ApplyLinearAcceleration(PLAYER_MAX_SPEED,deltaTime);
	}

	

	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_R))
	{
		RespawnShip();
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_SPACE))
	{ 
		FireBullet();
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_Z))
	{
		DeleteRandomAsteroid();		
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_X))
	{
		CreateRandomAsteroids();
	}
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_F2))
	{
		deltaTime = (MAX_DELTA_VALUE/250);
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_F1))
	{
		if(!m_debugMode)
		{
			TurnOnDebugMode();
			m_debugMode = true;
		}
		else
		{
			TurnOffDebugMode();
			m_debugMode = false;
		}
	}

	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_P))
	{
		if(deltaTime == MAX_DELTA_VALUE)
		{
			deltaTime = 0;
		}
		else
		{
			deltaTime = MAX_DELTA_VALUE;
		}
	}
	if(g_theInput->GetController(0).WasKeyJustPressed(INP_Menu))
	{
		RespawnShip();
	}

	if(g_theInput->GetController(0).WasKeyJustPressed(INP_A))
	{
		FireBullet();
	}
	
	if(g_theInput->GetController(0).isConnected())
	{
		Vector2 direction = g_theInput->GetController(0).getLeftStickVector();
		//float magnitude   = direction.GetLength();
		if(direction.x != 0 && direction.y != 0)
		{
			m_playerShip->ApplyAngularAcceleration(static_cast<int>(Atan2Degrees(direction.y,direction.x)));
			AddTail();
		}
		if(direction.x ==0 && direction.y==0)
		{
			RemoveTail();
		}
	}
	
	
	DoPlayerShipVsAsteroidCollision();
	DoPlayerShipVsEnemyBulletCollision();
	DoAsteroidVsBulletCollision();
	DoEnemyShipVsShipCollision();
	DoEnemyShipVsBulletCollision();
	
	UpdatePlayerShip(deltaTime);
	UpdateEnemyShip(deltaTime);
	
	UpdateAllAsteroids();
	UpdateAllBullets();
	UpdateAllEnemyBullets();
}

void Game::DoAsteroidVsBulletCollision()
{
	for(int bulletIndex = 0; bulletIndex < m_bullets.size(); bulletIndex++)
	{
		Bullet *bull = m_bullets.at(bulletIndex);
		if(bull == nullptr || !bull->m_isAlive)
		{
			continue;
		}
		for(int asteroidIndex = 0;asteroidIndex < m_asteroids.size(); asteroidIndex++)
		{
			Asteroid *asteroid = m_asteroids.at(asteroidIndex);
			if(asteroid == nullptr || !asteroid->m_isAlive)
			{
				continue;
			}
			if(asteroid->HasCollisionOccured(bull->m_disc2))
			{
				float screenWidth   = SCREEN_WIDTH;
				bull->m_isAlive     = false;
				asteroid->m_isAlive = false;
 				if(asteroid->m_disc2.radius == screenWidth/10.0f || asteroid->m_disc2.radius == screenWidth/20.0f)
				{ 
					Vector2 originalVelocity			= asteroid->m_direction;
					Vector2 newDirection (originalVelocity.x + asteroid->m_direction.x, originalVelocity.y - asteroid->m_direction.x);
					Vector2 newDirection1(originalVelocity.x + asteroid->m_direction.y, originalVelocity.y + asteroid->m_direction.y);
					newDirection						= (newDirection.GetNormalized());
					newDirection1						= (newDirection1.GetNormalized());
					
					CreateRandomAsteroids(asteroid->m_disc2.center.x,asteroid->m_disc2.center.y,asteroid->m_disc2.radius/2,newDirection);
					CreateRandomAsteroids(asteroid->m_disc2.center.x,asteroid->m_disc2.center.y,asteroid->m_disc2.radius/2,newDirection1);
				}
			}
		}
	}
}

void Game::DoPlayerShipVsAsteroidCollision()
{
	if(m_playerShip->m_isAlive == true)
	{
		for(int asteroidIndex=0; asteroidIndex<m_asteroids.size(); asteroidIndex++)	
		{
			Asteroid *asteroid = m_asteroids.at(asteroidIndex);
			if(asteroid==nullptr || asteroid->m_isAlive == false)
			{
				continue;
			}

			if(asteroid->HasCollisionOccured(m_playerShip->m_disc2))
			{
				asteroid->m_isAlive = false;
				m_playerShip->ReduceHealth();
				delete asteroid;
				m_asteroids.erase(m_asteroids.begin() + asteroidIndex, m_asteroids.begin() + asteroidIndex + 1);
				asteroidIndex--;
			}
		}
	}
}

void Game::DoPlayerShipVsEnemyBulletCollision()
{
	if(m_playerShip->m_isAlive == true)
	{
		for(int bulletIndex=0;bulletIndex<m_enemyBullets.size();bulletIndex++)
		{
			Bullet *bullet = m_enemyBullets.at(bulletIndex);
			if(bullet==nullptr || bullet->m_isAlive == false)
			{
				continue;
			}
			if(m_playerShip->HasCollisionOccured(bullet->m_disc2))
			{
				bullet->m_isAlive = false;
				m_playerShip->ReduceHealth();
				delete bullet;
				m_enemyBullets.erase(m_enemyBullets.begin() + bulletIndex, m_enemyBullets.begin() + bulletIndex + 1);
				bulletIndex--;
			}
		}
	}
}

void Game::DoEnemyShipVsShipCollision()
{
	if(m_playerShip->m_isAlive == true && m_enemyShip->m_isAlive == true)
	{
		if(m_playerShip->HasCollisionOccured(m_enemyShip->m_disc2))
		{
			m_enemyShip->ReduceHealth();
			m_playerShip->ReduceHealth();
		}
	}
}

void Game::DoEnemyShipVsBulletCollision()
{
	if(m_enemyShip->m_isAlive)
	{
		for(int bulletIndex=0;bulletIndex<m_bullets.size();bulletIndex++)
		{
			Bullet *bullet = m_bullets.at(bulletIndex);
			if(bullet==nullptr || bullet->m_isAlive == false)
			{
				continue;
			}
			if(m_enemyShip->HasCollisionOccured(bullet->m_disc2))
			{
				bullet->m_isAlive = false;
				m_enemyShip->ReduceHealth();
				delete bullet;
				m_bullets.erase(m_bullets.begin() + bulletIndex, m_bullets.begin() + bulletIndex + 1);
				bulletIndex--;
			}
		}
	}
}

void Game::UpdatePlayerShip(float deltaTime)
{
	m_playerShip->Update(deltaTime);
}

void Game::UpdateEnemyShip(float deltaTime)
{
	if (!m_enemyShip->m_isAlive)
	{
		return;
	}
	Vector2 distanceVector(m_playerShip->m_disc2.center.x - m_enemyShip->m_disc2.center.x, m_playerShip->m_disc2.center.y - m_enemyShip->m_disc2.center.y);
	Vector2 noseVector = m_enemyShip->GetNosePosition();

	distanceVector = distanceVector.GetNormalized();
	noseVector     = (noseVector.GetNormalized());
	//float angle    = Atan2Degrees(distanceVector.y, distanceVector.x);
	//float angle1   = Atan2Degrees(noseVector.y, noseVector.x);
	
	
	Vector2 distance     = m_playerShip->m_disc2.center - m_enemyShip->m_disc2.center;
	distance			 = distance.GetNormalized();
	m_enemyShip->m_angle = ConvertCartesianToPolar(distance.x, distance.y).y;
	

	if (distanceVector.GetLength() < ENEMY_MIN_DISTANCE_TO_SHOOT)
	{
		if (m_enemyShip->m_lastBulletFiredTime > ENEMY_RELOAD_TIME)
		{
			FireEnemyShipBullet();
			m_enemyShip->m_lastBulletFiredTime = 0;
			m_enemyShip->Update(deltaTime);
			return;
		}
	}
	m_enemyShip->ApplyLinearAcceleration(ENEMY_MAX_SPEED,deltaTime);
	m_enemyShip->Update(deltaTime);
}

void Game::UpdateAllAsteroids()
{
	for(int asteroidIndex=0;asteroidIndex<m_asteroids.size();asteroidIndex++)
	{
		Asteroid *asteroid = m_asteroids.at(asteroidIndex);
		if(asteroid!=nullptr && asteroid->m_isAlive == true)
		{
			asteroid->Update(MAX_DELTA_VALUE);
		}
	}
	if(m_asteroids.size() == 0)
	{
		SpawnNextAsteroidsWave(m_currentLevel);
	}
}

void Game::UpdateAllBullets()
{
	for(int bulletIndex=0;bulletIndex<m_bullets.size();bulletIndex++)
	{
		Bullet *bullet = m_bullets.at(bulletIndex);
		if(bullet==nullptr || bullet->m_isAlive == false)
		{
			continue;
		}
		bullet->Update(MAX_DELTA_VALUE);
	}
}

void Game::UpdateAllEnemyBullets()
{
	for(int enemyBullletIndex=0;enemyBullletIndex<m_enemyBullets.size();enemyBullletIndex++)
	{
		Bullet *bullet = m_enemyBullets.at(enemyBullletIndex);
		if(bullet==nullptr || bullet->m_isAlive == false)
		{
			continue;
		}
		bullet->Update(MAX_DELTA_VALUE);
	}
}

void Game::RemoveTail()
{
	m_playerShip->m_hasTail = false;
}

void Game::AddTail()
{
	m_playerShip->m_hasTail = true;
}

void Game::FireBullet()
{
	if(m_playerShip->m_isAlive == false)
	{
		return;
	}
	Vector2 shipNose = m_playerShip->GetNosePosition();
	Bullet *bullet   = new Bullet(shipNose.x,shipNose.y,m_playerShip->m_angle,PLAYER_BULLET_SPEED,BULLET_TIME_TO_LIVE);
	m_bullets.push_back(bullet);
}

void Game::FireEnemyShipBullet()
{
	Vector2 shipNose = m_enemyShip->GetNosePosition();
	Bullet *bullet = new Bullet(shipNose.x,shipNose.y,m_enemyShip->m_angle,ENEMY_BULLET_SPEED,BULLET_TIME_TO_LIVE);
	m_enemyBullets.push_back(bullet);
}

void Game::CreateRandomAsteroids()
{
	CreateRandomAsteroids(0.f,0.f,25.f,Vector2(0.f,0.f));
}

void Game::CreateRandomAsteroids(float centreX,float centreY,float radius,Vector2 directionXY)
{
	float screenWidth = 1000;

	int asteroidPosition = GetRandomIntInRange(0,4);
	if(centreX == 0 && centreY==0)
	{
		centreX = GetRandomFloatInRange(100.0f,1000.0f);
		centreY = GetRandomFloatInRange(100.0f,1000.0f);
	}

	int randumRadiusSelectionNum = GetRandomIntInRange(0,3);


	if(radius == 0)
	{
		if(randumRadiusSelectionNum == 0)
		{
			radius = (float)screenWidth/40.0f;
		}
		else if(randumRadiusSelectionNum == 1)
		{
			radius = (float)screenWidth/20.0f;
		}
		else
		{
			radius = (float)screenWidth/10.0f;
		}
		radius = (float)screenWidth/10.0f;
	}

	if((directionXY.x == 0 && directionXY.y==0))
	{
		if(asteroidPosition == 0)
		{
			centreX = 0 - radius;
		}
		else if(asteroidPosition == 1)
		{
			centreX = screenWidth + radius;
		}
		else if(asteroidPosition == 2)
		{
			centreY = 0 - radius;
		}
		else
		{
			centreY = screenWidth +radius;
		}
	}

	int numOfSides = GetRandomIntInRange(8,20);

	float startAngle = (float)GetRandomIntInRange(0,360);
	float directionX = 0;
	float directionY = 0;

	if(directionXY.x == 0 && directionXY.y==0)
	{
		directionX = (float)(GetRandomFloatInRange(0.1f,1.0f));
		directionY = (float)(GetRandomFloatInRange(0.1f,1.0f));
	}
	else
	{
		directionX = directionXY.x;
		directionY = directionXY.y;
	}
		
	int direction = 1;
	direction = GetRandomIntInRange(0,2);
	if(direction == 0)
	{
		direction = -1;
	}
	if(directionXY.x == 0 && directionXY.y==0)
	{
		direction = 1;
	}
	directionX = directionX*direction;
	directionY = directionY*direction;

	float changeInAngle = GetRandomFloatInRange(1,5);
	int angularVelocityDirection = GetRandomIntInRange(0,2);
	if(angularVelocityDirection == 0)
	{
		changeInAngle = changeInAngle*-1;
	}

	Asteroid *asteroid = new Asteroid(centreX,centreY,numOfSides,radius,startAngle,directionX,directionY,changeInAngle);
	asteroid->InitAsteroidPositions();
	m_asteroids.push_back(asteroid);

}

void Game::DeleteRandomAsteroid()
{
	if(m_asteroids.size() <= 0)
	{
		return;
	}
	int randomVal = GetRandomIntInRange(0,static_cast<int>(m_asteroids.size()));
	Asteroid *asteroid = m_asteroids.at(randomVal);
	asteroid->m_isAlive = false;
}

void Game::RespawnShip()
{
	if(m_playerShip->m_isAlive == false)
	{
		m_playerShip->m_disc2.center.x = 500;
		m_playerShip->m_disc2.center.y = 500;
		m_playerShip->m_angle = 90;
		m_playerShip->m_speed = 0.f;
		m_playerShip->m_isAlive = true;
	}
}

void Game::TurnOnDebugMode()
{
	m_playerShip->m_debugMode = true;
	m_enemyShip->m_debugMode = true;
	for(int i = 0;i<m_asteroids.size();i++)
	{
		Asteroid *asteroid = m_asteroids.at(i);
		asteroid->m_debugMode = true;
	}
	for(int i =0;i<m_bullets.size();i++)
	{
		Bullet *bull = m_bullets.at(i);
		if(bull == nullptr || bull->m_isAlive == false)
		{
			continue;
		}
		bull->m_debugMode = true;
	}
}

void Game::TurnOffDebugMode()
{
	m_playerShip->m_debugMode = false;
	m_enemyShip->m_debugMode = false;
	for(int i = 0;i<m_asteroids.size();i++)
	{
		Asteroid *asteroid = m_asteroids.at(i);
		asteroid->m_debugMode = false;
	}
	for(int i =0;i<m_bullets.size();i++)
	{
		Bullet *bull = m_bullets.at(i);
		if(bull == nullptr || bull->m_isAlive == false)
		{
			continue;
		}
		bull->m_debugMode = false;;
	}
}

void Game::SpawnNextAsteroidsWave(int levelnum)
{
	for(int levelIndex = 0;levelIndex < m_level[levelnum].numOfAsteroids;levelIndex++)
	{
		CreateRandomAsteroids();
		//numOfAsteroids++;
		//topAsteroidNum++;
	}
}