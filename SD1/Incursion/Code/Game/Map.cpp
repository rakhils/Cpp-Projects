#include "Game/Map.hpp"

#include "Engine/Core/Time.hpp"

#include "Game/Camera.hpp"
#include "Game/EnemyTank.hpp"
#include "Game/EnemyTurret.hpp"
#include "Game/TileDefinitions.hpp"

Map::Map()
{
}

Map::Map(int row,int column)
{
	m_NUM_OF_COLUMNS = column;
	m_NUM_OF_ROWS	 = row;
}

void Map::Init()
{
	InitEntities();
	InitTiles();
	InitVariables();
}

Map::~Map()
{
	
}

void Map::InitilizeMap()
{
	for (int i = 0; i < m_NUM_OF_COLUMNS * m_NUM_OF_ROWS; i++)
	{	
		Tiles newTile;
		newTile.SetPosition(GetPositionVectorFromMap(i,m_NUM_OF_COLUMNS));
		m_tiles->push_back(newTile);
		int Y = i / m_NUM_OF_COLUMNS;
		int X = i % m_NUM_OF_COLUMNS;

		// INIT WITH STONE
		if(X == 0 || Y == 0 || X == m_NUM_OF_COLUMNS - 1 || Y == m_NUM_OF_ROWS - 1)
		{
			m_tiles->at(i).m_tileType = TILE_TYPE_STONE;
			m_tiles->at(i).m_isSolid  = true;
			continue;
		}
		int maxTileTypeForThisLevel	  = NUM_TILE_TYPE - (MAX_LEVELS - m_level);
		int randVal					  = GetRandomIntInRange(0,maxTileTypeForThisLevel-1);
		
		TileType type = (TileType)randVal;
		if(type == TILE_TYPE_STONE)
		{
			if((X < NUM_TILE_TYPE && Y < NUM_TILE_TYPE) || (X > m_NUM_OF_COLUMNS - NUM_TILE_TYPE && Y > m_NUM_OF_ROWS - NUM_TILE_TYPE))
			{
				type = TILE_TYPE_GRASS; // PUTTIN GRASS IN THE PLAYER SPAWN POSITIONS AND ON FINAL POSITIONS
			}
		}
		if(type == TILE_TYPE_STONE)
		{
			m_tiles->at(i).m_isSolid = true;
		}
		//m_tiles->at(i).m_tileDef = TileDefinitions::GetTileDefenition(type);
		m_tiles->at(i).m_tileType = type;
	}
	//SpawnNewEntity(PlayerTank,Vector2(5,5),Vector2(0,-1));
}

// SETTING VARIABLES IN MAP INIT
void Map::InitVariables()
{
	m_gameOver				= false;
	m_gamePaused			= false;
	m_debugMode				= false;
	m_isZoomedIn			= true;
	switchLevelDown			= false;
	switchLevelUp			= false;
	isQuitTriggered			= false;
	m_mapAlpha				= 0;
	m_blackQuadEnable		= false;
	m_missionAccomplished	= false;
	m_time					= 100;

	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];
	PTank->m_health = static_cast<float>(m_playerHealth);
}

// DIFFERENT TILES FOR VICTORY AND STONES IN EACH LEVEL
void Map::InitTiles()  
{
	TileDefinitions::InitTileDefinitions();
	TileDefinitions::SetTileCoord(TILE_TYPE_GRASS, IntVector2(0, 0));// 
	TileDefinitions::SetTileCoord(TILE_TYPE_STONE, IntVector2(2, 4));//  
	TileDefinitions::SetTileCoord(TILE_TYPE_SAND, IntVector2(7, 1));//	 
	TileDefinitions::SetTileCoord(TILE_TYPE_MUD, IntVector2(5, 2));
	TileDefinitions::SetTileCoord(TILE_TYPE_BUSH, IntVector2(7, 0));
	TileDefinitions::SetTileCoord(TILE_TYPE_GRANITE, IntVector2(2, 3));
	if(m_level == 0)
	{
		TileDefinitions::SetTileCoord(TILE_TYPE_STONE,	IntVector2(2,4));
		TileDefinitions::SetTileCoord(TILE_TYPE_LEVELPROGRESS,	IntVector2(0,7));
	}
	if(m_level == 1)
	{
		TileDefinitions::SetTileCoord(TILE_TYPE_STONE,	IntVector2(0,5));
		TileDefinitions::SetTileCoord(TILE_TYPE_LEVELPROGRESS,	IntVector2(1,7));
	}
	if(m_level == 2)
	{
		TileDefinitions::SetTileCoord(TILE_TYPE_STONE,	IntVector2(5,6));
		TileDefinitions::SetTileCoord(TILE_TYPE_LEVELPROGRESS,	IntVector2(0,7));
	}
	//SETTING UP LEVEL PROGRESSTION TILE TO THE MAX - 1 POSITIONS
	int levelProgressionTileValue = (m_NUM_OF_COLUMNS)*(m_NUM_OF_ROWS -1 ) - 2; // TOP RIGHT CORNER
	m_levelProgressionTilePosition = Vector2(static_cast<float>(m_NUM_OF_COLUMNS-2.0f),static_cast<float>(m_NUM_OF_ROWS-2.0f));
	//m_tiles->at(levelProgressionTileValue).m_tileDef = TileDefinitions::GetTileDefenition(TILE_TYPE_LEVELPROGRESS);
	m_tiles->at(levelProgressionTileValue).m_tileType = TILE_TYPE_LEVELPROGRESS;

}

// SPAWNINGIN ENTITIES
void Map::InitEntities()
{
	m_entityByType[ENEMY_TANK].clear();
	m_entityByType[ENEMY_TURRET].clear();
	m_entityByType[ALLY_TANK].clear();
	m_entityByType[PLAYER_TANK].clear();
	m_entityByType[EXTRA_HEALTH].clear();
	m_entityByType[ENEMY_BULLET].clear();
	m_entityByType[PLAYER_BULLET].clear();
	// CLEARING OUT ENTITIES TO ON MAP REINIT

	//SPAWNINGIN PLAYER TANK
	for(int i = 0; i < 1; i++)
	{
		Vector2 randomFreePositionVector = GetRandomFreePosition();
		SpawnNewEntity(PLAYER_TANK,Vector2(5,5),Vector2(0,-1));
	}

	// SPAWNINGIN ENEMY TURRET
	for(int i = 0;i < m_numOfEnemyTurrets; i++)
	{
		Vector2 randomFreePositionVector = GetRandomFreePosition();
		float orientationX = GetRandomFloatInRange(-1, 1);
		float orientationY = GetRandomFloatInRange(-1, 1);
		SpawnNewEntity(ENEMY_TURRET,randomFreePositionVector,Vector2(orientationX,orientationY));
	}

	// SPAWNING ENEMY TANKS
	for(int i = 0;i<m_numOfEnemyTanks;i++)
	{
		Vector2 randomFreePositionVector = GetRandomFreePosition();
		float orientationX = GetRandomFloatInRange(-1,1);
		float orientationY = GetRandomFloatInRange(-1,1);

		SpawnNewEntity(ENEMY_TANK,randomFreePositionVector,Vector2(orientationX,orientationY));
	}
	// SPAWNING HEALTH PICKUPS
	for(int i = 0;i<(m_level+1);i++)
	{
		Vector2 randomFreePositionVector = GetRandomFreePosition();
		Extras *extra = new Extras(randomFreePositionVector,EXTRA_HEALTH);
		m_extrasList->push_back(extra);
	}

	//SPAWNING DUMMY ENEMY
	SpawnNewEntity(ENEMY_TANK,Vector2(3,3),Vector2(0,-1));

	AllyTank *allyTank1 = (AllyTank*)SpawnNewEntity(ALLY_TANK,Vector2(5,3),Vector2(0,0));
	allyTank1->m_number = 1;
	
	AllyTank *allyTank2 = (AllyTank*)SpawnNewEntity(ALLY_TANK,Vector2(3,5),Vector2(0,0));
	allyTank2->m_number = 2;
	//////////////////////

}

// LEVEL INCREMENT CONTROLLER
void Map::IncrementLevel()
{
	if (m_level == 2)
	{
		SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY + SOUND_VICTORY);
		g_audio->PlaySound(testSound);
		m_missionAccomplished = true;
		return;
	}
	switchLevelUp = true;
	m_camera.SetOrtographicPosition(Vector2(0,0),Vector2(1000,1000));
}

// GETTING RANDOM FREE POSITION (FREE FROM STONES AND ENTITITES)
Vector2 Map::GetRandomFreePosition()
{
	float cx = 0;
	float cy = 0;
	for(int i=0; i<1; i++)
	{
		int randx = GetRandomIntInRange(0,m_NUM_OF_COLUMNS-1);
		int randy = GetRandomIntInRange(0,m_NUM_OF_ROWS-1);
		int value = randy*m_NUM_OF_COLUMNS+randx;

		if((m_tiles->at(value).m_isSolid) || (randx<5 || randy<5))
		{
			i--;
			continue;
		}
		m_tiles->at(value).m_isSolid = true;
		cx = static_cast<float>(m_tiles->at(value).m_position.x);
		cy = static_cast<float>(m_tiles->at(value).m_position.y);
	}
	return Vector2(cx,cy);
}

void Map::Update(float deltaTime)
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank				  = (Tank*)playerTankList[0];
	m_playerHealth			  = PTank->m_health;
	if (m_gamePaused)
	{
		deltaTime = 0;
	}
	// GETTING BLACK QUAD FOR GAME OVER
	if(GetCurrentTimeSeconds() - m_lastTimeChanged > 1 && !m_gameOver && !m_gamePaused)
	{
		m_lastTimeChanged = static_cast<float>(GetCurrentTimeSeconds());
		m_time--;
		if(m_time <= 0)
		{
			m_blackQuadEnable		= true;
			m_gameOver				= true;
			PTank->m_markForDelete  = true;
		}
	}

	
	// CHANGING ALPHA IF QUAD IS ENABLED
	if(m_blackQuadEnable)
	{
		m_mapAlpha+=2;
		if(m_mapAlpha > GAME_PAUSE_QUAD_MAX_ALPHA)
		{
			m_mapAlpha = static_cast<float>(GAME_PAUSE_QUAD_MAX_ALPHA);
			deltaTime = 0;
		}
	}

	// CAMERA ZOOM OUT ON DEATH
	if(PTank->m_markForDelete && m_mapAlpha < GAME_PAUSE_QUAD_MAX_ALPHA)
	{
		m_camera.m_numTilesInViewHorizontally += 0.1f;
		m_camera.m_numTilesInViewVertically   += 0.1f;
	}

	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_LEFT_ARROW))
	{
		PTank->TurnEntity(10.0f,1);
	}
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_RIGHT_ARROW))
	{
		PTank->TurnEntity(10.0f,-1);
	}
	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_A))
	{
		PTank->TurnTurret(1);
	}
	if (g_theInput->isKeyPressed(InputSystem::KEYBOARD_D))
	{
		PTank->TurnTurret(-1);
	}
	
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_UP_ARROW))
	{
		PTank->MoveForward(1.0f,deltaTime);
	}
	if (g_theInput->wasKeyJustPressed((InputSystem::KEYBOARD_G)))
	{
		m_godMode = true;
	}

	// ESCAPE KEY PRESSED
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ESCAPE))
	{
		if(m_missionAccomplished && m_mapAlpha >= GAME_PAUSE_QUAD_MAX_ALPHA)
		{
			switchLevelUp = true;
			m_camera.SetOrtographicPosition(Vector2(0,0),Vector2(1000,1000));
			return;
		}
		if(m_gamePaused)
		{
			SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_QUIT_GAME);
			g_audio->PlaySound( testSound );
			isQuitTriggered = true;
			m_camera.SetOrtographicPosition(Vector2(0,0),Vector2(1000,1000));
			return;
		}
	}
	// ESCAPE KEY PRESSED
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_P) || g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ESCAPE))
	{	
		SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_PAUSE);
		g_audio->PlaySound( testSound );
		
		if(m_gameOver)
		{
			// IF GAME OVER AND QUAD ALPHA REACHES MAXIMUM REENAMBLING ALL VARIABLES
			if(m_mapAlpha >= GAME_PAUSE_QUAD_MAX_ALPHA)
			{
				m_gameOver = false;
				PTank->m_markForDelete = false;
				m_camera.ResetCamera();
				PTank->m_deathCounter = 0;
				PTank->m_health = 10;
				deltaTime = MAX_DELTA;
				m_blackQuadEnable = false;
				m_mapAlpha = 0;
				m_time = 100;
			}
		}
		else
		{
			if(!PTank->m_markForDelete)
			{
				if(m_gamePaused)
				{
					m_gamePaused = false;
					deltaTime = MAX_DELTA;
					m_mapAlpha = 0;
					m_blackQuadEnable = false;
				}
				else
				{
					m_gamePaused = true;
					deltaTime = 0;
				
				}
			}
		}
	}
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_T))
	{
		deltaTime = deltaTime / 10;
	}
	if(g_theInput->wasKeyJustReleased(InputSystem::KEYBOARD_N))
	{
		IncrementLevel();
	}
	// DEBUG MODE ON F1
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_F1))
	{
		m_debugMode = m_debugMode ? false : true;
	}
	// RESPAWN ON PRESS OF 'N'
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_N))
	{
		PTank->m_health			= 10;
		PTank->m_markForDelete  = false;
		m_mapAlpha				= 0;
		m_blackQuadEnable		= false;
	}
	// WHOLE MAP VIEW ON Q
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_M))
	{
		if(m_isZoomedIn)
		{
			m_isZoomedIn	= false;
			float largest	= static_cast<float>(m_NUM_OF_COLUMNS);
			if(m_NUM_OF_ROWS > m_NUM_OF_COLUMNS)
			{
				largest  = static_cast<float>( m_NUM_OF_ROWS);
			}
			m_camera.SetOrtographicPosition(Vector2(0,0),Vector2(largest*m_TILE_WIDTH,largest*m_TILE_WIDTH));
		}
		else
		{
			m_isZoomedIn = true;
		}
	}
	if (m_isZoomedIn)
	{
		Vector2 maxCamPosition = Vector2(m_NUM_OF_COLUMNS * m_TILE_WIDTH, m_NUM_OF_ROWS * m_TILE_WIDTH);
		m_camera.SetOrtographicPosition(PTank->GetPosition() + m_screenshakeRandomDeltaPosition, Vector2::ZERO, maxCamPosition);
	}
	if(g_theInput->GetController(0).isConnected())
	{
		Vector2 leftStickDirection = g_theInput->GetController(0).getLeftStickVector();
		if(leftStickDirection.x !=0 && leftStickDirection.y !=0)
		{
			PTank->TurnTowards2(leftStickDirection.GetOrientationDegrees());
		}
	}

	if(g_theInput->GetController(0).isConnected())
	{
		Vector2 rightStickDirection = g_theInput->GetController(0).getRigthStickVector();
		if(rightStickDirection.x !=0 && rightStickDirection.y !=0)
		{
			PTank->TurretTurnTowards(rightStickDirection.GetOrientationDegrees());
		}
	}
	
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_W) || (g_theInput->GetController(0).isConnected() && g_theInput->GetController(0).rightTrigger))
	{
		
		if(PTank->m_lastBulletSpawnTime + PLAYER_BULLET_SHOOT_INTERVAL < PTank->m_bulletCounter && !PTank->m_markForDelete)
		{
			SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_PTANK_FIRE);
			g_audio->PlaySound( testSound );
			PTank->m_lastBulletSpawnTime = PTank->m_bulletCounter;
			Vector2 playerTurretDirecton = PTank->GetTurretDirectionVector();
			Vector2 bulletSpawnPosition = PTank->GetCenter() + playerTurretDirecton.GetNormalized();
			Entity *entity = SpawnNewEntity(PLAYER_BULLET,bulletSpawnPosition,Vector2(0,-1));
			CreateExplosion(entity->GetPosition(),1.0f,1.0f);
			entity->SetDirectionVector(PTank->GetTurretDirectionVector());
		}
	}

	PTank->Update(deltaTime);
	if(m_gamePaused)
	{
		PTank->m_isGamePaused = true;
	}
	
	// CHECK IF PTANK IS ON LEVEL FINISH TILE
	if(CheckIFEntityInsideTile(PTank,m_levelProgressionTilePosition))
	{
		IncrementLevel();
		return;
	}
	MakeHealthbarShine();
	SetScreenShakeAmount(deltaTime);
	UpdateEnemyTurret(deltaTime);
	UpdateEnemyTank(deltaTime);
	UpdateAllyTanks(deltaTime);
	
	CheckAndReflectPlayerBullet(deltaTime);
	CheckAndReflectEnemyBullets(deltaTime);
	UpdateExtraList(deltaTime); // UPDATING EXTRA PICK UPS
	UpdateExplosionList(deltaTime);
	UpdateAllyMessage();	// UPDATING ALLY MESSAGES SHOW IN STATUS BAR

	CheckForEntityEntityCollision();
	CheckAndPushPlayerOutOfWall();
	CheckAndPushEnemyOutOfWall();	
	CheckAndPushAllyOutOfWall();
	CheckPBulletEnemyCollision(); // PLAYER BULLET VS ENEMY COLLSION
	CheckEBulletCollisionWithAllies();// EBULLET WITH ALLIES COLLSION 
	CheckPlayerCollisionWithEBullets();
	CheckPlayerCollsionWithExtras(); // PLAYER COLLSION WITH PICKUPS
	
}

void Map::UpdateEnemyTurret(float deltaTime)
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];
	EntityList EnemyTurretList = m_entityByType[ENEMY_TURRET];
	for (size_t i = 0; i < EnemyTurretList.size(); i++)
	{
		EnemyTurret *ETurret = (EnemyTurret*)EnemyTurretList[i];
		if(ETurret->m_markForDelete == true)
		{
			continue;
		}
		ETurret->m_debugMode = m_debugMode;
		Vector2 distanceVector = PTank->GetCenter() - ETurret->GetCenter();
		bool isPlayerOnSight = false;
		if(distanceVector.GetLength() < ETurret->m_range && !PTank->m_markForDelete && HasLineOfSight(ETurret->GetCenter(),(PTank->GetCenter())))
		{	
				
			if(DotProduct(ETurret->GetForwardUnitVector().GetNormalized(),distanceVector.GetNormalized()) > CosDegrees(5))
			{
				isPlayerOnSight = true;
				if(ETurret->m_lastBulletSpawnTime + 10 < ETurret->m_bulletCounterTime)
				{

					SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_FIRE);
					g_audio->PlaySound( testSound );
					ETurret->m_lastBulletSpawnTime = ETurret->m_bulletCounterTime;
					Vector2 playerTurretDirecton = ETurret->GetForwardUnitVector();
					Vector2 bulletSpawnPosition = ETurret->GetCenter() + ETurret->GetForwardUnitVector();
					Entity *bullet = SpawnNewEntity(ENEMY_BULLET,bulletSpawnPosition,ETurret->GetForwardUnitVector());
					bullet->SetDirectionVector(playerTurretDirecton);
				}
			}
			if(isPlayerOnSight) // IF PLAYER ON SIGHT JUST KEEPS DOING THE SAME DONT CHECK OTHER CONDITIONS
			{
				ETurret->Update(deltaTime);
				continue;
			}
			// TURNING TOWARDS THE INTEDED ANGLE
			float finalAngle = Atan2Degrees(distanceVector.y,distanceVector.x);
			DoAngleCorrection(ETurret->m_angle);
			float angularDisplacement = GetModulus(GetAngularDisplacement(ETurret->m_angle,finalAngle));
			ETurret->m_turnDirection = GetRotationDirectionBetween2Angles(ETurret->m_angle,finalAngle);
			ETurret->m_startAngle = 0;	ETurret->m_finalAngle = angularDisplacement;
			ETurret->m_turnInProgress = true;
			ETurret->m_playerInRange = true;
			ETurret->Update(deltaTime);
			continue;
		}
		else
		{
			EntityListBySide allyList = m_entityBySide[ENTITY_ALLY];
			bool isAllyTankFound = false;
			// CHECKING ALLIES ARE ON RANGE
			for(size_t allyListIndex=0;allyListIndex<allyList.size();allyListIndex++)
			{
				Entity *entity = allyList[allyListIndex];
				if(entity->m_type == PLAYER_TANK || entity->m_markForDelete)
					continue;

				Vector2 allyDistanceVector = entity->GetCenter() - ETurret->GetCenter();
				if(allyDistanceVector.GetLength() < ETurret->m_range && !PTank->m_markForDelete)
				{	
					if(HasLineOfSight(ETurret->GetCenter(),(entity->GetCenter())))
					{
						isAllyTankFound = true;
						if(DotProduct(ETurret->GetForwardUnitVector().GetNormalized(),allyDistanceVector.GetNormalized()) > CosDegrees(5))
						{
							if(ETurret->m_lastBulletSpawnTime + 10 < ETurret->m_bulletCounterTime)
							{
								SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_FIRE);
								g_audio->PlaySound( testSound );
								ETurret->m_lastBulletSpawnTime = ETurret->m_bulletCounterTime;
								Vector2 playerTurretDirecton = ETurret->GetForwardUnitVector();
								Vector2 bulletSpawnPosition = ETurret->GetCenter() + ETurret->GetForwardUnitVector();
								Entity *bullet = SpawnNewEntity(ENEMY_BULLET,bulletSpawnPosition,ETurret->GetForwardUnitVector());
								bullet->SetDirectionVector(playerTurretDirecton);
							}
						}
						else
						{
							// TURNING TOWARDS THE INTEDED ANGLE
							float finalAngle = Atan2Degrees(allyDistanceVector.y,allyDistanceVector.x);
							DoAngleCorrection(ETurret->m_angle);
							float angularDisplacement = GetModulus(GetAngularDisplacement(ETurret->m_angle,finalAngle));
							ETurret->m_turnDirection = GetRotationDirectionBetween2Angles(ETurret->m_angle,finalAngle);
							ETurret->m_startAngle = 0;	ETurret->m_finalAngle = angularDisplacement;
							ETurret->m_turnInProgress = true;
							ETurret->m_playerInRange = true;
						}
					}
				}
				if(isAllyTankFound)
				{
					ETurret->Update(deltaTime);
					break;
				}
			}
			if(isAllyTankFound)
			{
				continue;
			}
			//ETurret->m_turnInProgress = false;
			ETurret->m_playerInRange = false;
			// TURNING TOWARDS THE 2 DEGREES ANTI CLOCKWISE
			DoAngleCorrection(ETurret->m_angle);
			float finalAngle = ETurret->m_angle + 2;
			float angularDisplacement = GetModulus(GetAngularDisplacement(ETurret->m_angle,finalAngle));
			ETurret->m_turnDirection = GetRotationDirectionBetween2Angles(ETurret->m_angle,finalAngle);
			ETurret->m_startAngle = 0;	ETurret->m_finalAngle = angularDisplacement;
			ETurret->m_turnInProgress = true;
		
		}
		ETurret->Update(deltaTime);
		if(m_gamePaused)
		{
			ETurret->m_isGamePaused = true;
		}
	}
}

void Map::UpdateEnemyTank(float deltaTime)
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	EntityList enemyTankList = m_entityByType[ENEMY_TANK];

	for (size_t enemyTankIndex = 0; enemyTankIndex < enemyTankList.size(); enemyTankIndex++)
	{
		EnemyTank *eTank = ((EnemyTank*)enemyTankList.at(enemyTankIndex));
		eTank->CheckAndSetBehaviourState();
		switch (eTank->m_state)
		{
		case ENEMY_SHOOT_ON_PLAYER:
			eTank->ShootAtPlayer();
			break;
		case ENEMY_TURN_TO_PLAYER:
			eTank->TurnTowardsPlayer();
			break;
		case ENEMY_WANDER:
			eTank->Wander(deltaTime);
			break;
		default:
			break;
		}
		eTank->Update(deltaTime);
	}
}

void Map::UpdateAllyTanks(float deltaTime)
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	EntityList allyTankList   = m_entityByType[ALLY_TANK];

	for (size_t allyTankIndex = 0; allyTankIndex < allyTankList.size(); allyTankIndex++)
	{
		AllyTank *aTank = ((AllyTank*)allyTankList.at(allyTankIndex));
		aTank->CheckAndSetBehaviourState();
		switch (aTank->m_state)
		{
		case ALLY_SHOOT_ON_ENEMY:
			aTank->ShootAtEnemy();
			break;
		case ALLY_TURN_TO_ENEMY:
			aTank->TurnTowardsEnemy();
			break;
		case ALLY_MOVE_TO_PLAYER:
			aTank->MoveTowardsPlayer(deltaTime);
			break;
		case ALLY_TURN_TO_PLAYER:
			aTank->TurnTowardsPlayer(deltaTime);
			break;
		case ALLY_WANDER:
			aTank->Wander(deltaTime);
			break;
		default:
			break;
		}
		aTank->Update(deltaTime);
	}
}

void Map::CheckAndReflectPlayerBullet(float deltaTime)
{
	EntityList PBulletList = m_entityByType[PLAYER_BULLET];
	for (size_t PBulletCount = 0; PBulletCount < PBulletList.size(); PBulletCount++)
	{
		Bullet *PBulletPtr = (Bullet*)PBulletList[PBulletCount];
		if(PBulletPtr->m_markForDelete == true)
		{
			/*delete PBulletPtr;
			PBulletList.erase(PBulletList.begin() + PBulletCount, PBulletList.begin() + PBulletCount + 1);
			PBulletCount--;*/
			continue;
		}
		if(m_gamePaused)
		{
			PBulletPtr->m_isGamePaused = true;
			continue;
		}
		PBulletPtr->m_debugMode = m_debugMode;
		Vector2 nextPosition = PBulletPtr->GetNextPosition();
		Vector2 eBullVelocityVector = PBulletPtr->m_directionVector*PBulletPtr->m_speed;
		Vector2 prevTilePos = GetTileCoordFromPosition(PBulletPtr->GetCenter());
		Vector2 nextTilePos = GetTileCoordFromPosition(nextPosition);
		int tileValue = GetTileValueFromPosition(nextPosition);

		if(tileValue < m_NUM_OF_COLUMNS*m_NUM_OF_ROWS && tileValue >= 0)
			if(m_tiles->at(tileValue).m_tileType == TILE_TYPE_STONE)
			{
				PBulletPtr->m_health--;
				if(PBulletPtr->m_health <= 0)
				{
					PBulletPtr->m_markForDelete = true;
					CreateExplosion(PBulletPtr->GetPosition(),1,1.0f);
					continue;
				}
				nextTilePos = GetPositionVectorFromMap(tileValue,m_NUM_OF_COLUMNS);
				Vector2 normalUnitVector = prevTilePos - nextTilePos;
				normalUnitVector = normalUnitVector.GetNormalized();
				Vector2 Vn = normalUnitVector*DotProduct(eBullVelocityVector,normalUnitVector);
				Vector2 Vt = eBullVelocityVector - Vn;
				Vector2 newVeolcity = eBullVelocityVector - 2*Vn; // BULLET REBOUNCE
				PBulletPtr->SetDirection(newVeolcity.GetNormalized());
			}
		PBulletPtr->Update(deltaTime);
	}
}

void Map::CheckAndReflectEnemyBullets(float deltaTime)
{
	EntityList EBulletList = m_entityByType[ENEMY_BULLET];
	for (size_t EBulletCount = 0; EBulletCount < EBulletList.size(); EBulletCount++)
	{
		Bullet *EBulletPtr = (Bullet*)EBulletList[EBulletCount];
		if(EBulletPtr->m_markForDelete == true)
		{
			/*delete EBulletPtr;
			EBulletList.erase(EBulletList.begin() + EBulletCount, EBulletList.begin() + EBulletCount + 1);
			EBulletCount--;*/
			continue;
		}
		if(m_gamePaused)
		{
			EBulletPtr->m_isGamePaused = true;
			continue;
		}
		EBulletPtr->m_debugMode = m_debugMode;
		Vector2 nextPosition = EBulletPtr->GetNextPosition();
		Vector2 eBullVelocityVector = EBulletPtr->m_directionVector*EBulletPtr->m_speed;
		Vector2 prevTilePos = GetTileCoordFromPosition(EBulletPtr->GetCenter());
		Vector2 nextTilePos = GetTileCoordFromPosition(nextPosition);
		int tileValue = GetTileValueFromPosition(nextPosition);

		if(tileValue < m_NUM_OF_COLUMNS*m_NUM_OF_ROWS && tileValue >= 0)
			if(m_tiles->at(tileValue).m_tileType == TILE_TYPE_STONE)
			{
				EBulletPtr->m_health--;
				if(EBulletPtr->m_health <= 0)
				{
					EBulletPtr->m_markForDelete = true;
					CreateExplosion(EBulletPtr->GetPosition(),1,1.0f);
					continue;
				}
				nextTilePos = GetPositionVectorFromMap(tileValue,m_NUM_OF_COLUMNS);
				Vector2 normalUnitVector = prevTilePos - nextTilePos;
				normalUnitVector = normalUnitVector.GetNormalized();
				Vector2 Vn = normalUnitVector*DotProduct(eBullVelocityVector,normalUnitVector);
				Vector2 Vt = eBullVelocityVector - Vn;
				Vector2 newVeolcity = eBullVelocityVector - 2*Vn;
				EBulletPtr->SetDirection(newVeolcity.GetNormalized());
			}
		EBulletPtr->Update(deltaTime);
	}
}

void Map::UpdateExtraList(float deltaTime)
{
	for(size_t i =0;i<m_extrasList->size();i++)
	{
		m_extrasList->at(i)->Update(deltaTime);
	}
}

void Map::UpdateExplosionList(float deltaTime)
{
	for(size_t explosionIndex = 0;explosionIndex < m_explosionList.size();explosionIndex++)
	{
		Explosion* explosion = m_explosionList.at(explosionIndex);
		if(explosion != nullptr && explosion->m_markForDelete)
		{
			/*delete explosion;
			explosion = nullptr;
			m_explosionList.erase(m_explosionList.begin() + explosionIndex, m_explosionList.begin() + explosionIndex + 1);
			explosionIndex--;
			continue;*/
		}
		if(!explosion->m_markForDelete)
		{
			explosion->Update(deltaTime);
		}
	}
}

void Map::CheckAndPushPlayerOutOfWall()
{
	EntityList playerTankList	 = m_entityByType[PLAYER_TANK];
	Tank *PTank					 = (Tank*)playerTankList[0];
	PTank->m_debugMode			 = m_debugMode;
	Vector2 tankPositionVector   = PTank->GetCenter();
	int tileValue				 = GetTileValueFromPosition(tankPositionVector);
	if(tileValue >= 0 && tileValue < m_NUM_OF_COLUMNS*m_NUM_OF_ROWS)
	{
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(+0,-1));
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(+1,+0));
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(+0,+1));
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(-1,+0));


		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(-1,-1));
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(+1,+1));									 
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(-1,+1));
		CheckAndPushEntityOutOfCollision(PTank,tileValue,Vector2(+1,-1));
	}
}

void Map::CheckAndPushEnemyOutOfWall()
{
	EntityList ETankList = m_entityByType[ENEMY_TANK];
	for (size_t EtankCout = 0; EtankCout < ETankList.size(); EtankCout++)
	{
		Entity *entity = ETankList[EtankCout];
		Vector2 tankPositionVector = entity->GetCenter();
		int tileValue = GetTileValueFromPosition(tankPositionVector);
		if(tileValue >= 0 && tileValue < m_NUM_OF_COLUMNS*m_NUM_OF_ROWS)
		{
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+0,-1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,+0));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+0,+1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,+0));


			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,-1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,+1));									 
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,+1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,-1));
		}
	}
}

void Map::CheckAndPushAllyOutOfWall()
{
	EntityList ETankList = m_entityByType[ALLY_TANK];
	for (size_t EtankCout = 0; EtankCout < ETankList.size(); EtankCout++)
	{
		Entity *entity = ETankList[EtankCout];
		Vector2 tankPositionVector = entity->GetCenter();
		int tileValue = GetTileValueFromPosition(tankPositionVector);
		if(tileValue >= 0 && tileValue < m_NUM_OF_COLUMNS*m_NUM_OF_ROWS)
		{
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+0,-1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,+0));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+0,+1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,+0));


			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,-1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,+1));									 
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(-1,+1));
			CheckAndPushEntityOutOfCollision(entity,tileValue,Vector2(+1,-1));
		}
	}
}

void Map::CheckForEntityEntityCollision()
{
	EntityListByShape EnitityListByShape = m_entityByShape[Disk_Type];
	for(size_t EntityListCount = 0;EntityListCount<m_entityByShape[Disk_Type].size();EntityListCount++)
	{
		Entity *entity = EnitityListByShape[EntityListCount];
		if(entity->m_markForDelete == true)
		{
			continue;
		}
		for(size_t EntityListCount1 = 0;EntityListCount1<m_entityByShape[Disk_Type].size();EntityListCount1++)
		{
			Entity *entity1 = EnitityListByShape[EntityListCount1];
			if(entity1->m_markForDelete == true)
			{
				continue;
			}
			if(entity == entity1)
			{
				continue;
			}
			if(DoDiscsOverlap(entity1->m_collisionDisk,entity->m_collisionDisk))
			{
				
				Vector2 entityDistVector = Vector2(entity1->GetCenter() - entity->GetCenter());
				float overLapDistance = (entity->m_innerRadius/2.0f+entity1->m_innerRadius/2.0f) - entityDistVector.GetLength();
				Vector2 entityDistUnitVector = entityDistVector.GetNormalized();
				Vector2 entity1Reduction = entityDistUnitVector*overLapDistance/2.0f;
				Vector2 entity2Reduction = (-1*entityDistUnitVector)*overLapDistance/2.0f;
				if(entity->m_type != ENEMY_TURRET) // TURRETS DONT MOVE
				{
					entity->m_centreX += entity2Reduction.x;
					entity->m_centreY += entity2Reduction.y;
				}

				if(entity1->m_type != ENEMY_TURRET)
				{
					entity1->m_centreX += entity1Reduction.x;
					entity1->m_centreY += entity1Reduction.y;
				}
			}
		}
	}
}

void Map::CheckPBulletEnemyCollision()
{
	EntityList PBulletList = m_entityByType[PLAYER_BULLET];
	for(size_t PBulletCount = 0;PBulletCount<m_entityByType[PLAYER_BULLET].size();PBulletCount++)
	{
		Entity *PBullet = PBulletList[PBulletCount];
		if(PBullet->m_markForDelete == true)
		{
			continue;
		}
		EntityList ETankList = m_entityByType[ENEMY_TANK];
		for(size_t ETankCount = 0;ETankCount<ETankList.size();ETankCount++)
		{
			Entity *Etank =  ETankList[ETankCount];
			if(Etank->m_markForDelete == true)
			{
				continue;
			}
			bool isHit = IsPointInsideDisc2(PBullet->GetCenter(),Etank->m_collisionDisk); // CHECK FOR COLLISION
			if(isHit)
			{
				SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_HIT);
				g_audio->PlaySound( testSound );
				PBullet->m_markForDelete = true;
				Etank->m_health--;
				if(Etank->m_health <= 0)
				{
					testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_DESTROY);
					g_audio->PlaySound( testSound );
					CreateExplosion(Etank->GetPosition(),Etank->m_radius*2,1.0f);
					Etank->m_markForDelete = true;
				}
			}
		}

		EntityList ETurretList = m_entityByType[ENEMY_TURRET];
		for(size_t ETurretCount = 0;ETurretCount<ETurretList.size();ETurretCount++)
		{
			Entity *Eturret = ETurretList[ETurretCount];
			if(Eturret->m_markForDelete == true)
			{
				continue;
			}
			bool isHit = IsPointInsideDisc2(PBullet->GetCenter(),Eturret->m_collisionDisk);
			if(isHit)
			{
				SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_HIT);
				g_audio->PlaySound( testSound );
				PBullet->m_markForDelete = true;
				Eturret->m_health--;
				if(Eturret->m_health <= 0)
				{
					CreateExplosion(Eturret->GetPosition(),Eturret->m_radius*2,1.0f);
					 testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_DESTROY);
					g_audio->PlaySound( testSound );
					Eturret->m_markForDelete = true;
				}
			}
		}
		
	}
}

void Map::CheckPlayerCollisionWithEBullets()
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];
	if(PTank->m_markForDelete)
	{
		return;
	}
	EntityList EbulletList = m_entityByType[ENEMY_BULLET];
	for(size_t EbulletCount = 0;EbulletCount<EbulletList.size();EbulletCount++)
	{
		Entity *EBullet = EbulletList[EbulletCount];
		if(EBullet->m_markForDelete == true)
		{
			continue;
		}
		if(IsPointInsideDisc2(EBullet->GetCenter(),PTank->m_collisionDisk))
		{
			CreateScreenshake(0.50f);
			SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_PTANK_HIT);
			g_audio->PlaySound( testSound );
			SpawnNewEntity(EXPLOSION_ENTITY,Vector2(PTank->m_centreX,PTank->m_centreY),Vector2(0,-1),1.0f);
			EBullet->m_markForDelete = true;
			if(!m_godMode)
			PTank->m_health--;
			CreateExplosion(PTank->GetPosition(),PTank->m_radius*1,1.0f);
			if(PTank->m_health <=0)
			{
				CreateExplosion(PTank->GetPosition(),PTank->m_radius*3,1.5f);
				 testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_PTANK_DESTROY);
				g_audio->PlaySound( testSound );
				PTank->m_markForDelete = true;
				m_gameOver = true;
				m_mapAlpha = 0;
				m_blackQuadEnable = true;
			}
		}
	}

}

void Map::CheckEBulletCollisionWithAllies()
{
	EntityList EBulletList = m_entityByType[ENEMY_BULLET];
	for(size_t EBulletCount = 0;EBulletCount<m_entityByType[ENEMY_BULLET].size();EBulletCount++)
	{
		Entity *EBullet = EBulletList[EBulletCount];
		if(EBullet->m_markForDelete == true)
		{
			continue;
		}
		EntityList AllyList = m_entityBySide[ENTITY_ALLY];
		for(size_t AllyCount = 0;AllyCount<AllyList.size();AllyCount++)
		{
			Entity *entityAlly =  AllyList[AllyCount];
			if(entityAlly->m_markForDelete == true || entityAlly->m_type == PLAYER_TANK)
			{
				continue;
			}
			
			bool isHit = IsPointInsideDisc2(EBullet->GetCenter(),entityAlly->m_collisionDisk);
			if(isHit)
			{
				//SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_HIT);
				//g_audio->PlaySound1( testSound );
				EBullet->m_markForDelete = true;
				entityAlly->m_health--;
				if(entityAlly->m_health == 0)
				{
					CreateExplosion(entityAlly->GetPosition(),2.0f,1.0f);
					entityAlly->m_markForDelete = true;
				}
			}
		}
	}
}

void Map::CheckPlayerCollsionWithExtras()
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];
	for(size_t i =0;i<m_extrasList->size();i++)
	{
		Extras *extra = m_extrasList->at(i);
		if(extra->m_markForDelete)
		{
			continue;
		}
		if(DoDiscsOverlap(PTank->GetDisc2D(),extra->GetDisc2D()))
		{
			switch (extra->m_type)
			{
			case EXTRA_HEALTH:
			{
				SoundID testSound = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_PICKUP_HEALTH);
				g_audio->PlaySound( testSound );
				extra->m_markForDelete = true;
				PTank->m_health = 10;
			}
			break;
			default:
				break;
			}
			
		}
	}
}

void Map::UpdateAllyMessage()
{
	float currentTime = static_cast<float>(GetCurrentTimeSeconds());
	if(currentTime - m_AllyMessageLastDeleteTime > 5)
	{
		m_AllySingleMessageAlly1.erase(0,m_AllySingleMessageAlly1.length());
		m_AllySingleMessageAlly2.erase(0,m_AllySingleMessageAlly2.length());
		m_AllyMessageLastDeleteTime = currentTime;
	}
}

void Map::UpdateAllyMessageString(int number, std::string str)
{
	m_AllySingleMessageAlly1 = ALLY_TANK_MESSAGE + ToString(number) +" "+str;
}

bool Map::CheckIFEntityInsideTile(Entity *entity,Vector2 tileValue)
{
	AABB2 aabb2 = GetTileCoord(tileValue);
	if(IsPointInsideAABB2(aabb2,entity->GetCenter()))
	{
		return true;
	}
	return false;
}

void Map::Render()
{
	RenderTiles();
	RenderPTanks();
	RenderETanks();
	RenderETurrets();
	RenderAllyTanks();
	RenderPBullets();
	RenderEBullets();
	RenderExtras();
	RenderExplosions();
	
	if(m_gameOver)
	{
		RenderBlackQuad();
		if(m_mapAlpha >= GAME_PAUSE_QUAD_MAX_ALPHA)
		{
			Texture *gameOvertexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\gameover.png");
			Vector2 texCoordsAtMins(0,1);
			Vector2 texCoordsAtMaxs(1,0);
			Rgba tint((unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)255);

			g_theRenderer->PushMatrix();
			g_theRenderer->Translate(m_camera.m_positionVector);
			g_theRenderer->Rotate(0);
			AABB2 aabb2t2(Vector2(0,0),m_camera.m_numTilesInViewHorizontally/2,m_camera.m_numTilesInViewVertically/2);
			g_theRenderer->DrawTexturedAABB(aabb2t2, gameOvertexture, texCoordsAtMins, texCoordsAtMaxs,tint);
			g_theRenderer->PopMatrix();
		}
	}

	if(m_gamePaused)
	{
		m_blackQuadEnable = true;
		m_mapAlpha = static_cast<float>(GAME_PAUSE_QUAD_MAX_ALPHA);
		RenderBlackQuad();

		Texture *pausetexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\PauseMenu.png");
		Vector2 texCoordsAtMins(0,1);
		Vector2 texCoordsAtMaxs(1,0);
		Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255));
		
		g_theRenderer->PushMatrix();
		g_theRenderer->Translate(m_camera.m_positionVector);
		g_theRenderer->Rotate(0);
		//AABB2 aabb2t2(Vector2(0,0),camera.m_maxPosition.x/2,camera.m_maxPosition.y/2);
		AABB2 aabb2t2(Vector2(0,0),m_camera.m_numTilesInViewHorizontally,m_camera.m_numTilesInViewVertically);
		g_theRenderer->DrawTexturedAABB(aabb2t2, pausetexture, texCoordsAtMins, texCoordsAtMaxs,tint);
		g_theRenderer->PopMatrix();
	}
	
	if(m_missionAccomplished)
	{
		m_blackQuadEnable = true;
		RenderBlackQuad();
		if(m_mapAlpha >= 100)
		{
			Texture *pausetexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\victory.png");
			Vector2 texCoordsAtMins(0,1);
			Vector2 texCoordsAtMaxs(1,0);
			Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255));

			g_theRenderer->PushMatrix();
			g_theRenderer->Translate(m_camera.m_positionVector);
			g_theRenderer->Rotate(0);
			AABB2 aabb2t2(Vector2(0,0),5,5);
			g_theRenderer->DrawTexturedAABB(aabb2t2, pausetexture, texCoordsAtMins, texCoordsAtMaxs,tint);
			g_theRenderer->PopMatrix();
		}

	}
	//exp->render();
	
	if(m_isZoomedIn)
	{
		RenderStatusBar();
		RenderHealthBar();
		RenderAllyMessage();
		RenderTime();
	}
	//DeleteAll
}
	
void Map::RenderTiles()
{
	for (int i = 0; i < m_NUM_OF_ROWS*m_NUM_OF_COLUMNS; i++)
	{
		m_tiles->at(i).Render();
	}
}

void Map::RenderPTanks()
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];

	if(!PTank->m_markForDelete)
		PTank->Render();
}

void Map::RenderETanks()
{
	EntityList ETankList = m_entityByType[ENEMY_TANK];
	for (size_t i = 0; i < ETankList.size(); i++)
	{
		EnemyTank *ETank = (EnemyTank*)ETankList[i];
		if(ETank->m_markForDelete == true)
		{
			continue;
		}

		ETank->Render();
		g_theRenderer->SetColor(COLOR_RED);
		g_theRenderer->DrawCircle(ETank->m_targetPostion,1);
		g_theRenderer->SetColor(COLOR_WHITE);

	}
}

void Map::RenderETurrets()
{
	EntityList EnemyTurretList = m_entityByType[ENEMY_TURRET];
	for (size_t i = 0; i < EnemyTurretList.size(); i++)
	{
		EnemyTurret *ETurret = (EnemyTurret*)EnemyTurretList[i];
		if(ETurret->m_markForDelete == true)
		{
			continue;
		}
		ETurret->Render();

		RaycastResult2D rayCastResult = Raycast(ETurret->GetCenter(),(ETurret->GetForwardUnitVector()),10);
		g_theRenderer->SetColor(0,1,0);
		g_theRenderer->DrawLine((ETurret->GetCenter()),(rayCastResult.m_impcatPos));

	}
}

void Map::RenderAllyTanks()
{
	EntityList AllyTankList = m_entityByType[ALLY_TANK];
	for (size_t i = 0; i < AllyTankList.size(); i++)
	{
		AllyTank *ATank = (AllyTank*)AllyTankList[i];
		if(ATank->m_markForDelete)
		{
			continue;
		}
		ATank->m_debugMode = m_debugMode;
		ATank->Render();
		g_theRenderer->SetColor(COLOR_BLUE);
		g_theRenderer->DrawCircle(ATank->m_enemyPosition,1);
		g_theRenderer->SetColor(COLOR_WHITE);
	}
}

void Map::RenderPBullets()
{
	EntityList PBulletList = m_entityByType[PLAYER_BULLET];
	for (size_t i = 0; i < PBulletList.size(); i++)
	{
		Bullet *bulletPtr = (Bullet*)PBulletList[i];
		if(bulletPtr->m_markForDelete  == false)
		{
			bulletPtr->Render();
		}
	}
}

void Map::RenderEBullets()
{
	EntityList EBulletList = m_entityByType[ENEMY_BULLET];
	for (size_t i = 0; i < EBulletList.size(); i++)
	{
		Bullet *bulletPtr = (Bullet*)EBulletList[i];
		if(bulletPtr->m_markForDelete == false)
		{
			bulletPtr->Render();
		}
	}
}

void Map::RenderExtras()
{
	for(size_t i =0;i<m_extrasList->size();i++)
	{
		m_extrasList->at(i)->Render();
		m_extrasList->at(i)->m_debugMode = m_debugMode;
	}
}

void Map::RenderExplosions()
{
	for(size_t i = 0;i<m_explosionList.size();i++)
	{
		m_explosionList.at(i)->Render();
	}
}

void Map::RenderBlackQuad()
{
	if(m_blackQuadEnable)
	{
		Rgba alphaTint;
		alphaTint.SetAsBytes((char)0,(char)0,(char)0,(char)m_mapAlpha);
		AABB2 aabb2t(Vector2(0,0),m_NUM_OF_COLUMNS*m_TILE_WIDTH,m_NUM_OF_ROWS*m_TILE_WIDTH);
		g_theRenderer->DrawAABB(aabb2t,alphaTint);
	}
}

void Map::RenderStatusBar()
{
	Rgba alphaTint;
	alphaTint.SetAsBytes((unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)150);

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(m_camera.m_positionVector);
	g_theRenderer->Rotate(0);

	AABB2 aabb2t(-13,-5,13,-7);
	g_theRenderer->DrawAABB(aabb2t,alphaTint);

	g_theRenderer->PopMatrix();
}

void Map::RenderHealthBar()
{
	EntityList playerTankList = m_entityByType[PLAYER_TANK];
	Tank *PTank = (Tank*)playerTankList[0];
	Rgba tint1;

	
	tint1.SetAsBytes((unsigned char)255,(unsigned char)0,(unsigned char)0,(unsigned char)m_healthBarAlphaValue);
	Rgba tint2;
	tint2.SetAsBytes((unsigned char)0,(unsigned char)255,(unsigned char)0,(unsigned char)m_healthBarAlphaValue);

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(m_camera.m_positionVector);
	g_theRenderer->Rotate(0);
	g_theRenderer->ScaleUniform(0.25f);
	
	g_theRenderer->DrawTextOnPoint("HEALTH",0,6,Vector2(10.0f,-25.0f),1,COLOR_WHITE);
	AABB2 aabb2(25.0f,-24.0f,25+PTank->m_health*2,-26.0f);
	g_theRenderer->DrawRectangle(25,-24,45,-26);
	AABB2 bl(25.0f,-24.0f,45.0f,-26.0f);
	g_theRenderer->DrawAABB(bl,COLOR_BLACK);
	g_theRenderer->DrawAABB(aabb2,tint1,tint2);
	g_theRenderer->PopMatrix();
}

void Map::RenderAllyMessage()
{
	int allyTankCount = 0;
	EntityList AllyTankList = m_entityByType[ALLY_TANK];
	for (size_t index = 0; index < AllyTankList.size(); index++)
	{
		if(!AllyTankList.at(index)->m_markForDelete)
		{
			allyTankCount++;
		}
	}
	if(allyTankCount == 0)
	{
		return;
	}

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(m_camera.m_positionVector);
	g_theRenderer->ScaleUniform(0.2f);
	g_theRenderer->DrawTextOnPoint(m_AllySingleMessageAlly1, 0, static_cast<int>(m_AllySingleMessageAlly1.length()), Vector2(-60, -28), 1, COLOR_WHITE);
	g_theRenderer->DrawTextOnPoint(m_AllySingleMessageAlly2, 0, static_cast<int>(m_AllySingleMessageAlly2.length()), Vector2(-60, -33), 1, COLOR_WHITE);
	g_theRenderer->PopMatrix();
}

void Map::RenderTime()
{
	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(m_camera.m_positionVector);
	g_theRenderer->ScaleUniform(0.2f);
	g_theRenderer->DrawTextOnPoint("TIME -",0,6,Vector2(25,-28),1,COLOR_WHITE);
	g_theRenderer->DrawInt(m_time,Vector2(+40,-28),1);//,COLOR_WHITE);
	g_theRenderer->PopMatrix();
}

// RETURNS THE INDEX OF TILE OF POSTION PARAM
int Map::GetTileValueFromPosition(Vector2 positionVector)
{
	int columnValueX = static_cast<int>(positionVector.x/(m_TILE_WIDTH));
	int columnValueY = static_cast<int>(positionVector.y/(m_TILE_WIDTH));

	return columnValueY*m_NUM_OF_COLUMNS + columnValueX;
}

// RETURNS THE TILE VECTOR VALUE FROM INDEX COUNT
Vector2 Map::GetPositionVectorFromMap(int count,int width)
{
	float Y = static_cast<float>(count/width) *(m_TILE_WIDTH);
	float X = static_cast<float>(count%width) *(m_TILE_WIDTH);
	return Vector2(X,Y);
}

int Map::GetArrayIndexFromVector(Vector2 position)
{
	return static_cast<int>((position.y*static_cast<float>(m_NUM_OF_COLUMNS))+position.x);
}

// RETURN TILE CORDINATES FROM POSTIONS
Vector2 Map::GetTileCoordFromPosition(Vector2 positionVector)
{
	int tileValue = GetTileValueFromPosition(positionVector);
	return GetPositionVectorFromMap(tileValue,m_NUM_OF_COLUMNS);
}

AABB2 Map::GetTileCoord(Vector2 positionVector)
{
	Vector2 centrePositionOfTile ;
	centrePositionOfTile.x = positionVector.x*m_TILE_WIDTH + m_TILE_WIDTH/2;
	centrePositionOfTile.y = positionVector.y*m_TILE_WIDTH + m_TILE_WIDTH/2;
	AABB2 aabb2(centrePositionOfTile,m_TILE_WIDTH/2,m_TILE_WIDTH/2);
	return aabb2;
}

void Map::CheckAndPushEntityOutOfCollision(Entity *tank, int tileValue, Vector2 posistionVector)
{
	int originalTileValue = tileValue;
	if(posistionVector.y != 0)
	{
		tileValue = tileValue+(m_NUM_OF_COLUMNS*static_cast<int>(posistionVector.y));
	}
	tileValue+=static_cast<int>(posistionVector.x);
	if(m_tiles->at(tileValue).m_tileType == TILE_TYPE_STONE)
	{
		Directions direction;
		if(DoDiscAndAABBOverlap(direction,m_tiles->at(tileValue).m_aabb2 , tank->m_collisionDisk, posistionVector))
		{
			Vector2 overlapDistance = GetAABBDiscOverlapDistance(m_tiles->at(tileValue).m_aabb2 , tank->m_collisionDisk, m_tiles->at(originalTileValue).m_aabb2.GetCenter(), posistionVector);
			
			tank->m_centreX += overlapDistance.x;
			tank->m_centreY += overlapDistance.y;
		}
	}	
}

Entity * Map::SpawnNewEntity(EntityType type, Vector2 pos, Vector2 orientation)
{
	return SpawnNewEntity(type,pos,orientation,m_TILE_WIDTH);
}

Entity * Map::SpawnNewEntity(EntityType type, Vector2 pos, Vector2 orientation,float radius)
{
	Entity *newEntity = nullptr;
	float angle = Atan2Degrees(orientation.y,orientation.x);
	switch (type)
	{
		case PLAYER_TANK : newEntity = new Tank(pos); newEntity->m_health = 10; break;
		case ENEMY_TURRET:
		{
			EntityList playerTankList12 = m_entityByType[PLAYER_TANK];
			Tank *PTank12				= (Tank*)playerTankList12[0];
			newEntity					= new EnemyTurret(pos);
			newEntity->PTank			= PTank12;
			newEntity->m_health			= ENEMY_TURRET_HEALTH;
		}
		break;
		case ENEMY_TANK:
		{
			EntityList playerTankList12 = m_entityByType[PLAYER_TANK];
			Tank *PTank12				= (Tank*)playerTankList12[0];
			newEntity					= new EnemyTank(pos,this);
			newEntity->PTank			= PTank12;
			newEntity->m_health			= ENEMY_TANK_HEALTH;
		}
		break;
		case ENEMY_BULLET:
		{	
			newEntity					= new Bullet(pos);
			newEntity->m_health			= ENEMY_TURRET_HEALTH;
			newEntity->m_angle			= orientation.GetOrientationDegrees();
			SoundID testSound			= g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_FIRE);
			g_audio->PlaySound( testSound );
		}
		break;
		case PLAYER_BULLET:
		{	
			newEntity					= new Bullet(pos);
			newEntity->m_health			= PLAYER_BULLET_HEALTH;
			newEntity->m_angle			= orientation.GetOrientationDegrees();
		}
		break;
		case ALLY_TANK:
		{	
			newEntity					= new AllyTank(pos,this);
			newEntity->m_health			= PLAYER_TANK_HEALTH;
			//newEntity->m_angle = orientation.GetOrientationDegrees();
		}
		break;
		case EXPLOSION_ENTITY:
		{
			Explosion *exp = new Explosion(pos,radius);
			m_explosionList.push_back(exp);
			return newEntity;
		}
		break;
	}
	newEntity->m_angle = angle;
	newEntity->m_type = type;
	AddToList(newEntity,type); 
	AddToTypeByShapeList(newEntity,type);
	AddToTypeByFactionList(newEntity,type);
	return newEntity;
}

// GENERAL LIST
void Map::AddToList(Entity *entity, EntityType type)
{
	m_entityByType[type].push_back(entity);
}

// ENTITY TYPE BY SHAPE
void Map::AddToTypeByShapeList(Entity *entity, EntityType type)
{
	if(type == PLAYER_TANK || type == ENEMY_TANK || type == ENEMY_TURRET || type == ALLY_TANK)
	{
		m_entityByShape[Disk_Type].push_back(entity);
	}
}

// SIDE LIST TO KNOW ENTITIES ARE ENEMIES OR ALLIES
void Map::AddToTypeByFactionList(Entity *entity, EntityType type)
{
	if(type == PLAYER_TANK || type == ALLY_TANK)
	{
		m_entityBySide[ENTITY_ALLY].push_back(entity);
	}
	if(type == ENEMY_TANK || type == ENEMY_TURRET)
	{
		m_entityBySide[ENTITY_ENEMY].push_back(entity);
	}
}

void Map::SetDebugMode()
{
	EntityList entityList = m_entityByType[PLAYER_TANK];
	if(entityList.size() == 0)
	{
		return;
	}
	for (size_t i = 0; i<entityList.size(); i++)
	{
		if(entityList.at(i) != nullptr)
		{
			if(entityList.at(i)->m_debugMode == true)
			{
				entityList.at(i)->m_debugMode = false;
			}
			else
			{
				entityList.at(i)->m_debugMode = true;
			}
		}
	}
}

bool Map::HasLineOfSight(Vector2 startPos, Vector2 endPos)
{
	Vector2 directionVector       = endPos - startPos;
	float dirLength				  = directionVector.GetLength();
	RaycastResult2D Raycastresult = Raycast(startPos,directionVector.GetNormalized(),dirLength);
	if(Raycastresult.m_diditImpact)
	{
		return  true;
	}
	return false;
}

RaycastResult2D Map::Raycast(Vector2 startPos,Vector2 direction,float maxDistance)
{
	float numOfSteps           = maxDistance * RAYCAST_STEPS_PER_TILE;
	float singleStep           = 1.0f / RAYCAST_STEPS_PER_TILE;
	Vector2 previousTileCoords = GetTileCoordFromPosition(startPos);
	Vector2 currentPosition(0,0);
	Vector2 currentTileCoord(0,0);
	for (int stepNum = 0; stepNum <= numOfSteps; stepNum++)
	{
		currentPosition.x = (startPos.x + direction.x * (float)stepNum * (float)singleStep);
		currentPosition.y = (startPos.y + direction.y * (float)stepNum * (float)singleStep);
		
		currentTileCoord = GetTileCoordFromPosition(currentPosition);
		if(currentTileCoord == previousTileCoords)
		{
			continue;
		}
		
		int tileValue = GetTileValueFromPosition(currentPosition);
		if(tileValue >= 0 && tileValue < m_NUM_OF_COLUMNS * m_NUM_OF_ROWS)
		if(m_tiles->at(tileValue).m_tileType == TILE_TYPE_STONE)
		{
			RaycastResult2D retValue;
			retValue.m_diditImpact		= false;
			retValue.m_impactdistance	= (currentPosition - startPos).GetLength();
			retValue.m_impcatPos		= currentPosition;
			retValue.m_impcatTileCord	= currentTileCoord;
			return retValue;
		}
	}

	RaycastResult2D retValue;
	retValue.m_diditImpact		= true;
	retValue.m_impactdistance	= (currentPosition - startPos).GetLength();
	retValue.m_impcatPos		= currentPosition;
	retValue.m_impcatTileCord	= currentTileCoord;
	return retValue;
}

void Map::CreateExplosion(Vector2 position, float radius, float duration)
{
	Explosion *exp = new Explosion(position,radius,duration);
	m_explosionList.push_back(exp);
}

void Map::SetScreenShakeAmount(float deltaTime)
{
	if(m_screenShakeEndTime > GetCurrentTimeSeconds())
	{
		m_screenshakeRandomDeltaPosition.x = GetRandomFloatZeroToOne() * SCREENSHAKE_CAMERA_DELTA_X * deltaTime;
		m_screenshakeRandomDeltaPosition.y = GetRandomFloatZeroToOne() * SCREENSHAKE_CAMERA_DELTA_Y * deltaTime;
	}		
}

void Map::MakeHealthbarShine()
{
	// === CHANGES FOR HEALTH BAR SHINING
	m_healthBarAlphaValue += m_healthBarAlphaVDirection;
	if (m_healthBarAlphaValue > m_healthBarAlphaMax)
	{
		m_healthBarAlphaValue = m_healthBarAlphaMax;
		m_healthBarAlphaVDirection = -6;
	}
	if (m_healthBarAlphaValue < m_healthBarAlphaMin)
	{
		m_healthBarAlphaValue = m_healthBarAlphaMin;
		m_healthBarAlphaVDirection = 6;
	}
	//=====================================
}

void Map::CreateScreenshake(float time)
{
	m_screenShakeEnabled   = true;
	m_screenShakeStartTime = static_cast<float>(GetCurrentTimeSeconds());
	m_screenShakeEndTime   = time + m_screenShakeStartTime;
}
