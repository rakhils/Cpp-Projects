#pragma once
#include "Engine/Math/Vector2.hpp"

#include "Game/Map.hpp"
#include "Game/Tank.hpp"
#include "Game/GameCommon.hpp"
#include "Game/Canvas.hpp"

class Game
{
public:
	bool				m_isQuitTriggered			= false;
	
	SoundID				m_attractMusicSoundID;
	SoundID				m_gamePlaySoundID;
	std::vector<Map *>  m_mapList;
	Map*				m_currentMap				= nullptr;  
	Canvas*				m_currentCanvas				= nullptr;
	
	Game();
	~Game();
	SceneType			m_currentScene;

	void InitLevels();
	void Render();
	void Update(float deltaTime);
	void EnterIntoAttractMode(SceneType type);
	
};