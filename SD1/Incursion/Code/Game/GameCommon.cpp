#include "GameCommon.hpp"


Renderer *			g_theRenderer					=	nullptr;
InputSystem *		g_theInput						=	nullptr;
SpriteSheet *		g_TerrainTile					=	nullptr;
SpriteSheet *		g_explosionSpriteSheet			=	nullptr;
SpriteAnimation *	g_explosionAnim					=	nullptr;
AudioSystem *		g_audio							=	nullptr;
bool				g_isQuitTriggered				=	false;
float				MAX_DELTA						=	0.016f;
float				ASPECT_RATIO					=   16.f/9.f;
float				TILE_WIDTH						=	2.f;
float				TILES_VIEWED_VERTICALLY			=   7.f;

std::string			SOUND_DIRECTORY					=	"Data/Audio/";

std::string			SOUND_PAUSE						=	"Pause.mp3";
std::string			SOUND_ATTRACT_MODE				=	"AttractMusic.mp3";
std::string			SOUND_PTANK_FIRE				=	"TestSound.mp3";
std::string			SOUND_PTANK_HIT					=	"PlayerHit.wav";
std::string			SOUND_ETANK_FIRE				=	"EnemyShoot.wav";
std::string			SOUND_ETANK_HIT					=	"EnemyHit.wav";
std::string			SOUND_PTANK_DESTROY				=	"PlayerDied.wav";
std::string			SOUND_ETANK_DESTROY				=	"EnemyDied.wav";
std::string			SOUND_VICTORY					=	"Victory.mp3";
std::string			SOUND_QUIT_GAME					=	"QuitGame.mp3";
std::string			SOUND_GAME_PLAY					=	"GamePlayMusic.mp3";

std::string			SOUND_NUKE						=	"TestSound.mp3";
std::string			SOUND_LEVELUP					=	"TestSound.mp3";
std::string			SOUND_PICKUP_HEALTH				=	"TestSound.mp3";

std::string			IMAGE_DIRECTORY					=	"Data/Images/";
std::string			IMAGE_EXTRAS					=	"Extras.png";
std::string			IMAGE_ALLY_TANK					=	"AllyTank.png";
std::string			ALLY_TANK_MESSAGE				=	"ATANK : ";


float				ENTITY_WIDTH					=	2.f;
float				ENTITY_HEIGHT					=	2.f;

float				TANK_ANGULAR_VELOCITY			=	90.f;
float				TANK_SPEED						=   3.f;
float				VIEW_RANGE						=   4.f;
float				PLAYER_BULLET_HEALTH			=   3.f;
float				PLAYER_TANK_HEALTH				=   10.f;
float				PLAYER_RANGE					=   10.f;
float				PLAYER_BULLET_SHOOT_INTERVAL	=   10.f;


float				ENTITY_PHYSICS_RATIO			=	0.8f;

float				ENEMY_TANK_SPEED				=   2.5f;
float				ENEMY_TURRET_RANGE				=   20;
float				ENEMY_TURRET_HEALTH				=   1;
float				ENEMY_TANK_HEALTH				=   3;

float				BULLET_SPEED					=  5.f;
float				BULLET_RADIUS					=  0.1f;

float				EXPLOSION_TIME					=  1.f;
int					EXPLOSION_ANIM_SPRITE_NUMCOLS	=  5;
int					EXPLOSION_ANIM_SPRITE_NUMRAWS	=  5;

int					MAX_LEVELS						=  3;

Vector2				LEVEL1_DIMENSIONS(20.f,30.f);
Vector2				LEVEL2_DIMENSIONS(30.f,20.f);
Vector2				LEVEL3_DIMENSIONS(20.f,30.f);

int					SCREENSHAKE_CAMERA_DELTA_X		=  20;
int					SCREENSHAKE_CAMERA_DELTA_Y		=  20;
int					GAME_PAUSE_QUAD_MAX_ALPHA		=  100;



Rgba COLOR_WHITE((unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)255);
Rgba COLOR_RED	((unsigned char)255,(unsigned char)0,  (unsigned char)0,  (unsigned char)255);
Rgba COLOR_GREEN((unsigned char)0,  (unsigned char)255,(unsigned char)0,  (unsigned char)255);
Rgba COLOR_BLUE	((unsigned char)0,  (unsigned char)0,  (unsigned char)255,(unsigned char)255);
Rgba COLOR_BLACK((unsigned char)0,  (unsigned char)0,  (unsigned char)0,  (unsigned char)255);


