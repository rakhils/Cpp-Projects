#pragma once
#include "Game.hpp"

class App
{
public:
	// VARIABLES
	Game *g_theGame = nullptr;
	double m_currTime = GetCurrentTimeSeconds();
	double m_prevTime = m_currTime;

	// FUNCTIONS
	App();
	~App();
	void RunFrame();
	void Update();
	void Render();
	bool IsReadyToQuit();
	void RequestToQuit();
};
