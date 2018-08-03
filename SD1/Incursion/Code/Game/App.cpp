#include "Game/App.hpp"

#include "Engine/Core/Time.hpp"
#include "Engine/Math/MathUtil.hpp"

#include "Game/Game.hpp"
#include "Game/GameCommon.hpp"

App::App()
{
	g_theRenderer = new Renderer();
	g_theInput 	  = new InputSystem();
	g_audio       = new AudioSystem();
	g_theGame     = new Game();
}

App::~App()
{
	delete g_theGame;
	g_theGame = nullptr;

	delete g_audio;
	g_audio = nullptr;

	delete g_theInput;
	g_theInput = nullptr;

	delete g_theRenderer;
	g_theRenderer = nullptr;
}

void App::RunFrame()
{
	g_theRenderer->BeginFrame();
	g_theInput->BeginFrame();
	g_audio->BeginFrame();
	Update();
	Render();
	g_audio->EndFrame();
	g_theInput->EndFrame();
	g_theRenderer->EndFrame();
}

void App::Update()
{
	float deltaTime = static_cast<float>(GetCurrentTimeSeconds() - m_prevTime);
	m_prevTime		= GetCurrentTimeSeconds();
	deltaTime		= ClampFloat(deltaTime, 0, MAX_DELTA);
	g_theGame->Update(deltaTime);
	g_isQuitTriggered = g_theGame->m_isQuitTriggered;
}

void App::Render()
{
	g_theGame->Render();
}

bool App::IsReadyToQuit()
{
	return g_isQuitTriggered;//g_theInput->isKeyPressed(VK_ESCAPE);
}

void App::RequestToQuit()
{
	g_isQuitTriggered = true;
}

