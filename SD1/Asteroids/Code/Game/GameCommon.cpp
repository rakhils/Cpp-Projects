#include "GameCommon.hpp"

Renderer* g_theRenderer							= nullptr;
InputSystem* g_theInput							= nullptr;
Game*        g_theGame							= nullptr;
float        MAX_DELTA_VALUE					= 0.016f;
float        ENITY_VS_PHYSICS_FACTOR			= 0.7f;
float        SCREEN_HEIGHT						= 1000.f;
float        SCREEN_WIDTH						= 1000.f;
float		 WINDOWS_WIDTH						= 1000.f;

Vector2		 ENEMY_INIT_POSITION(100,			 500);
float		 ENEMY_INIT_ANGLE					= 0.f;
float		 ENEMY_MIN_DISTANCE_TO_SHOOT		= 1;
float		 ENEMY_RELOAD_TIME					= 3000;
float		 ENEMY_MAX_SPEED					= 7;

float		 PLAYER_MAX_SPEED					= 10;
float        PLAYER_MAX_ANGULAR_SPEED			= 0.1f;
float		 PLAYER_DESTROY_DISPLAY_FRAME_TIME  = 1000;
int			 PLAYER_MAX_HEALTH					= 10;
int			 ENEMY_MAX_HEALTH					= 10;
