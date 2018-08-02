#pragma once
#include <vector>

#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Time.hpp"

#include "Game/Tiles.hpp"
#include "Game/Tank.hpp"
#include "Game/EnemyTank.hpp"
#include "Game/Camera.hpp"
#include "Game/Entity.hpp"
#include "Game/Bullet.hpp"
#include "Game/EnemyTurret.hpp"
#include "Game/Explosion.hpp"
#include "Game/Extras.hpp"
#include "Game/AllyTank.hpp"

struct RaycastResult2D
{
	bool						 m_diditImpact;
	Vector2						 m_impcatPos;
	IntVector2					 m_impcatTileCord;
	float						 m_impactdistance;
	float						 m_impactFraction;
	Vector2						 m_impactSurfaceNormal;
};								 
								 
class Map						 
{								 
public:							 
								 
	Camera						 m_camera;
	int							 m_NUM_OF_ROWS					= static_cast<int>(LEVEL1_DIMENSIONS.x);
	int							 m_NUM_OF_COLUMNS				= static_cast<int>(LEVEL1_DIMENSIONS.y);
	float						 m_TILE_WIDTH					= ENTITY_WIDTH;
	static const int			 MAX_NUM_TILES					= 1000;
	static const int			 m_MAX_NUM_OF_ENTITY_TYPE		= 20;
	const float					 RAYCAST_STEPS_PER_TILE			= 100.0f;
	int							 m_numOfEnemyTanks				= 2;
	int							 m_numOfEnemyTurrets			= 10;
								 
	bool						 m_gameOver						= false;
	bool						 m_gamePaused					= false;
	bool						 m_debugMode					= false;
	bool						 m_isZoomedIn					= true;
	int							 m_level						= 1;
	bool						 switchLevelDown				= false;
	bool						 switchLevelUp					= false;
	bool						 isQuitTriggered				= false;
	float						 m_mapAlpha						= 0;
	bool						 m_blackQuadEnable				= false;
	bool						 m_missionAccomplished			= false;
	bool						 m_godMode						= false;
								 
	int							 m_time							= 100;
	float						 m_lastTimeChanged				= 0;
	float						 m_playerHealth					= 10;
								 
	Vector2						 m_levelProgressionTilePosition;
	Texture *					 m_terrainTexture				= nullptr;
								 
	float						 m_screenShakeStartTime			= 0.f;
	float						 m_screenShakeEndTime			= 0.f;
	Vector2						 m_screenshakeRandomDeltaPosition;
	bool						 m_screenShakeEnabled			= true;
								 
	// ALLY RELATED VARIABLES	 
	std::string					 m_AllyMessage;
	std::string					 m_AllySingleMessageAlly1;
	std::string					 m_AllySingleMessageAlly2;
	float						 m_AllyMessageLastDeleteTime	= 0;

	// HEALTH BAR VAIABLES
	float						 m_healthBarAlphaMin			= 150;
	float						 m_healthBarAlphaMax			= 255;
	float						 m_healthBarAlphaValue			= 150;
	float						 m_healthBarAlphaVDirection		= 6;

	std::vector<Tiles>			 m_tiles[MAX_NUM_TILES];
	std::vector<Explosion*>		 m_explosionList;
	std::vector<Extras*>		 m_extrasList[20];

	std::vector<Entity*>		 m_allEntities;
	typedef std::vector<Entity*> EntityList;
	EntityList					 m_entityByType[m_MAX_NUM_OF_ENTITY_TYPE];

	typedef std::vector<Entity*> EntityListByShape;
	EntityListByShape			 m_entityByShape[m_MAX_NUM_OF_ENTITY_TYPE];

	typedef std::vector<Entity*> EntityListBySide;			// ENEMY OR ALLY
	EntityListBySide			 m_entityBySide[m_MAX_NUM_OF_ENTITY_TYPE];


	Map();
	Map(int row, int column);
	~Map();

	void						 Update(float deltaTime);
	void						 Render();

	void						 Init();
	void						 InitilizeMap();
	void						 InitVariables();
	void						 InitTiles();
	void						 InitEntities();
	Entity *					 SpawnNewEntity(EntityType type, Vector2 pos, Vector2 orientation);
	Entity *					 SpawnNewEntity(EntityType type, Vector2 pos, Vector2 orientation, float radius);
	void						 AddToList(Entity *entity,EntityType type);
	void						 AddToTypeByShapeList(Entity *entity, EntityType type);
	void						 AddToTypeByFactionList(Entity *entity, EntityType type);
	Vector2						 GetPositionVectorFromMap(int count,int width);
	void						 CheckAndPushEntityOutOfCollision(Entity *tank,int tileValue, Vector2 posistionVector);
	int							 GetTileValueFromPosition(Vector2 positionVector);
	void						 SetDebugMode();
	bool						 HasLineOfSight(Vector2 startPos, Vector2 endPos);


	bool						 CheckIFEntityInsideTile(Entity *entity,Vector2 tileValue);
	int							 GetArrayIndexFromVector(Vector2 position);
	AABB2						 GetTileCoord(Vector2 posistionVector);
	RaycastResult2D				 Raycast(Vector2 startPos,Vector2 direction,float maxDistance);
	Vector2						 GetTileCoordFromPosition(Vector2 positionVector);
	void						 CreateExplosion(Vector2 position,float radius,float duration);
	void						 CreateScreenshake(float time);
	void						 SetScreenShakeAmount(float deltaTime);
	void						 MakeHealthbarShine();
	void						 IncrementLevel();

	Vector2						 GetRandomFreePosition();
	void						 UpdateEnemyTurret(float deltaTime);
	void						 UpdateEnemyTank(float deltaTime);
	void						 UpdateAllyTanks(float deltaTime);
	void						 CheckAndReflectPlayerBullet(float deltaTime);
	void						 CheckAndReflectEnemyBullets(float deltaTime);
	void						 UpdateExtraList(float deltaTime);
	void						 UpdateExplosionList(float deltaTime);
	void						 CheckAndPushPlayerOutOfWall();
	void						 CheckAndPushEnemyOutOfWall();
	void						 CheckAndPushAllyOutOfWall();
	void						 CheckForEntityEntityCollision();
	void						 CheckPBulletEnemyCollision();
	void						 CheckPlayerCollisionWithEBullets();
	void						 CheckEBulletCollisionWithAllies();
	void						 CheckPlayerCollsionWithExtras();
	void						 UpdateAllyMessage();
	void						 UpdateAllyMessageString(int number, std::string str);

	void						 RenderTiles();
	void						 RenderPTanks();
	void						 RenderETanks();
	void						 RenderETurrets();
	void						 RenderAllyTanks();
	void						 RenderPBullets();
	void						 RenderEBullets();
	void						 RenderExtras();
	void						 RenderExplosions();
	void						 RenderBlackQuad();
	void						 RenderStatusBar();
	void						 RenderHealthBar();
	void						 RenderAllyMessage();
	void						 RenderTime();
};