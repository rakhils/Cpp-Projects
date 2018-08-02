#pragma once
#include "GameCommon.hpp"

class Canvas
{
	
public:
	SceneType			m_currentScene;
	float				m_incursionTextFinalX = 200;
	float				m_changeFrom0to256			= 0;
	float				m_direction					= 1;
	int					m_selectedLevel = 0;
	bool				m_switchLevelUp = false;
	bool				isQuitTriggered = false;
	float				m_titleStartX = -10;
	float				m_titleStartY = 700;
	float				m_titleFinalX = 300;
	int					charIndexOnFlow = 0;
	int					m_titleIndex = 0;
	bool				isTitleAnimMoving = false;
	bool				isTilteAnimEnded = false;
	int					m_cursorIndex = 0;
	AABB2				m_titleAnimLetterBox;

	Canvas();
	void Update(float deltaTime);
	void Render();
	void DoTitleAnimation(float deltaTime);
	void SetCurrentSceneNum(SceneType sceneNum);
	void DrawChar(char value,int length, Vector2 pos);
	void DrawString(char value[],int length,Vector2 pos);
	void DrawString(char value[],int start,int length, Vector2 pos,int height);
	AABB2 GetTexCoordsForSpriteCoords(const IntVector2& spriteCoords,const IntVector2 m_spriteLayout);
	AABB2 GetTexCoordsForSpriteIndex(int spriteIndex,const IntVector2 m_spriteLayout);

};