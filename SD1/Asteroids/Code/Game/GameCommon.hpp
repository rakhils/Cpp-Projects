#pragma once
#include "Engine\Input\InputSystem.hpp"
#include "Engine\Renderer\Renderer.hpp"
#include "Game\Game.hpp"

extern Renderer*    g_theRenderer;
extern InputSystem* g_theInput;
extern Game*        g_theGame;
extern float        MAX_DELTA_VALUE;
extern float		SCREEN_WIDTH;
extern float		SCREEN_HEIGHT;
extern float		ENITY_VS_PHYSICS_FACTOR;
extern float		WINDOWS_WIDTH;

extern Vector2		ENEMY_INIT_POSITION;
extern float		ENEMY_INIT_ANGLE;
extern float		ENEMY_MIN_DISTANCE_TO_SHOOT;
extern float		ENEMY_RELOAD_TIME;
extern float		ENEMY_MAX_SPEED;
extern int			ENEMY_MAX_HEALTH;


extern float		PLAYER_MAX_SPEED;
extern float 		PLAYER_MAX_ANGULAR_SPEED;
extern float		PLAYER_DESTROY_DISPLAY_FRAME_TIME;
extern int			PLAYER_MAX_HEALTH;