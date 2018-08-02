#pragma once
#include <string>

#include "Engine\Core\Rgba.hpp"
#include "Engine\Audio\AudioSystem.hpp"
#include "Engine\Input\InputSystem.hpp"
#include "Engine\Renderer\Renderer.hpp"
#include "Engine\Renderer\SpriteSheet.hpp"
#include "Engine\Renderer\SpriteAnimation.hpp"

enum SceneType
{
	Attract,
	GamePlay,
	Victory,
};
#define UNUSED(x) (void)(x);
extern Renderer*			g_theRenderer;
extern InputSystem*			g_theInput;
extern SpriteSheet *		g_TerrainTile;
extern SpriteAnimation *	g_explosionAnim;
extern SpriteSheet *		g_explosionSpriteSheet;
extern AudioSystem *		g_audio;

extern float				MAX_DELTA;
extern float				ASPECT_RATIO;
extern float				TILE_WIDTH;
extern float				TILES_VIEWED_VERTICALLY;
extern bool					g_isQuitTriggered;

extern std::string			SOUND_DIRECTORY;
extern std::string			SOUND_PAUSE;
extern std::string			SOUND_ATTRACT_MODE;
extern std::string			SOUND_PTANK_FIRE;
extern std::string			SOUND_PTANK_HIT;
extern std::string			SOUND_ETANK_FIRE;
extern std::string			SOUND_ETANK_HIT;
extern std::string			SOUND_PTANK_DESTROY;
extern std::string			SOUND_ETANK_DESTROY;
extern std::string			SOUND_VICTORY;
extern std::string			SOUND_QUIT_GAME;
extern std::string			SOUND_LEVELUP;
extern std::string			SOUND_PICKUP_HEALTH;
extern std::string			SOUND_NUKE;
extern std::string			SOUND_GAME_PLAY;

extern std::string			IMAGE_DIRECTORY;
extern std::string			IMAGE_EXTRAS;
extern std::string			IMAGE_ALLY_TANK;
extern std::string			ALLY_TANK_MESSAGE;

extern Rgba					COLOR_WHITE;
extern Rgba					COLOR_RED;
extern Rgba					COLOR_GREED;
extern Rgba					COLOR_BLUE;
extern Rgba					COLOR_BLACK;

extern float				ENTITY_WIDTH;
extern float				ENTITY_HEIGHT;
extern float				TANK_ANGULAR_VELOCITY;
extern float				TANK_SPEED;
extern float				PLAYER_TANK_HEALTH;

extern float				VIEW_RANGE;
extern float				ENTITY_PHYSICS_RATIO;

extern float				ENEMY_TANK_SPEED;
extern float				ENEMY_TURRET_RANGE;
extern float				ENEMY_TANK_HEALTH;
extern float				ENEMY_TURRET_HEALTH;

extern float				PLAYER_BULLET_HEALTH;
extern float				PLAYER_RANGE;
extern float				PLAYER_BULLET_SHOOT_INTERVAL;
extern float				ENEMY_BULLET_HEALTH;
extern float				BULLET_SPEED;
extern float				BULLET_RADIUS;

extern float				EXPLOSION_TIME;
extern int					EXPLOSION_ANIM_SPRITE_NUMCOLS;
extern int					EXPLOSION_ANIM_SPRITE_NUMRAWS;

extern int					MAX_LEVELS;

extern int					SCREENSHAKE_CAMERA_DELTA_X;
extern int					SCREENSHAKE_CAMERA_DELTA_Y;
extern int					GAME_PAUSE_QUAD_MAX_ALPHA;

extern Vector2				LEVEL1_DIMENSIONS;
extern Vector2				LEVEL2_DIMENSIONS;
extern Vector2				LEVEL3_DIMENSIONS;