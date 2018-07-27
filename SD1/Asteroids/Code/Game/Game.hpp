#pragma once
#include "Game/Ship.hpp"
#include "Game/Bullet.hpp"
#include "Game/Asteroid.hpp"

struct LevelDetails
{
	int numOfAsteroids;
};

class Game
{
public:
	// VARIABLES
	Ship*					m_playerShip					= nullptr;
	Ship*					m_enemyShip						= nullptr;
	std::vector<Bullet*>	m_bullets;
	std::vector<Bullet*>	m_enemyBullets;
	std::vector<Asteroid*>	m_asteroids;

	int						m_currentLevel					= 0;
	bool					m_debugMode						= false;
	LevelDetails			m_level[10];
	
	// FUNCTIONS
	Game::Game();
	
	void					Update(float deltaTime);
	void					Render();

	
	void					FireBullet();
	void					RemoveTail();
	void					AddTail();
	void					RespawnShip();

	void					CreateRandomAsteroids();
	void					CreateRandomAsteroids(float centreX,float centreY,float radius,Vector2 directionXY);
	void					DeleteRandomAsteroid();
	
	void					TurnOnDebugMode();
	void					TurnOffDebugMode();
	
	void					FireEnemyShipBullet();
	void					SpawnNextAsteroidsWave(int level);

	void					DoPlayerShipVsAsteroidCollision();
	void					DoAsteroidVsBulletCollision();
	void					DoPlayerShipVsEnemyBulletCollision();
	void					DoEnemyShipVsShipCollision();
	void					DoEnemyShipVsBulletCollision();

	void					UpdatePlayerShip(float deltaTime);
	void					UpdateEnemyShip(float deltaTime);
	void					UpdateAllAsteroids();
	void					UpdateAllBullets();
	void					UpdateAllEnemyBullets();
	void					UpdateEnemyShipAttack();
};