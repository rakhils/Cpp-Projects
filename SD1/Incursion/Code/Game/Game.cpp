#include "Engine/Math/MathUtil.hpp"
#include "Engine/Core/Rgba.hpp"
#include "Engine/Renderer/SpriteSheet.hpp"

#include "Game/Game.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Tiles.hpp"
#include "Game/TileDefinitions.hpp"
#include "Game/TileDefinitions.hpp"


Game::Game()
{
	InitLevels();
	m_currentCanvas = new Canvas();
	EnterIntoAttractMode(Attract);
}

Game::~Game()
{
	delete m_currentCanvas;
	m_currentCanvas = nullptr;
}

void Game::Update(float deltaTime)
{	
	
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_Z))
	{
		m_currentMap = m_mapList.at(1);
	}
	if(g_theInput->isKeyPressed(InputSystem::KEYBOARD_X))
	{
		m_currentMap = m_mapList.at(2);
	}

	switch(m_currentScene)
	{
		case Attract:
		{
			m_currentCanvas->Update(deltaTime);
			if(m_currentCanvas->m_switchLevelUp)
			{
				m_currentCanvas->m_switchLevelUp = false;
				m_currentMap					 = m_mapList.at(m_currentCanvas->m_selectedLevel);
				m_currentMap->Init();
				m_currentScene					 = GamePlay;
				g_audio->StopSound(m_attractMusicSoundID);
				m_gamePlaySoundID				 = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_GAME_PLAY);
				m_gamePlaySoundID				 = g_audio->PlaySound( m_gamePlaySoundID );
			}
			m_isQuitTriggered = m_currentCanvas->isQuitTriggered;
		}
		break;
		case GamePlay:
		{
			m_currentMap->Update(deltaTime);
			if(m_currentMap->isQuitTriggered)
			{
				g_audio->StopSound(m_gamePlaySoundID);
				EnterIntoAttractMode(Attract);
				m_currentMap->isQuitTriggered = false;
			}
		}
		break;
		case Victory:
		{
			m_currentCanvas->Update(deltaTime);
		}
		break;
	}

	if(m_currentMap!= nullptr && m_currentMap->switchLevelUp)
	{
		m_currentMap->switchLevelUp = false;
		float health = m_currentMap->m_playerHealth;
		int currentLevel = m_currentMap->m_level;
		if(currentLevel == 2)
		{
			EnterIntoAttractMode(Attract);
			return;
		}
		if(currentLevel < (MAX_LEVELS - 1))
		{
			m_currentMap = m_mapList.at(++currentLevel);
			m_currentMap->m_playerHealth = health;
			m_currentMap->InitTiles();
			m_currentMap->InitEntities();
			m_currentMap->InitVariables();
		}
		
	}
}

void Game::InitLevels()
{
	std::vector<Vector2> mapDimensions;
	mapDimensions.push_back(LEVEL1_DIMENSIONS);
	mapDimensions.push_back(LEVEL2_DIMENSIONS);
	mapDimensions.push_back(LEVEL3_DIMENSIONS);
	for (int i = 0; i < MAX_LEVELS; i++)
	{
		Map *map = new Map(static_cast<int>(mapDimensions.at(i).x), static_cast<int>(mapDimensions.at(i).y));
		map->m_level = i;
		map->m_numOfEnemyTanks = 10 + i * 3;
		map->m_numOfEnemyTurrets = 10 + i * 3;
		map->InitilizeMap();
		m_mapList.push_back(map);
	}
}

void Game::Render()
{
	switch(m_currentScene)
	{
		case Attract:
		{
			m_currentCanvas->Render();
		}
		break;
		case GamePlay:
		{
			m_currentMap->Render();
		}
		break;
		case Victory:
		{
			m_currentCanvas->Render();
		}
		break;
	}
}

void Game::EnterIntoAttractMode(SceneType type)
{
	m_attractMusicSoundID = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ATTRACT_MODE);
	m_attractMusicSoundID = g_audio->PlaySound( m_attractMusicSoundID );
	m_currentScene		  = type;
	m_currentCanvas->SetCurrentSceneNum(type);
}



