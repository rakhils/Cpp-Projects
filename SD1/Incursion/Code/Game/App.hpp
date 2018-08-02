#pragma once
#include "Game.hpp"

class App
{
public:
	// VARIABLES
	Game *g_theGame = nullptr;
	double currTime = GetCurrentTimeSeconds();
	double prevTime = currTime;

	// FUNCTIONS
	App();
	~App();
	void RunFrame();
	void Update();
	void Render();
	bool IsReadyToQuit();
};
