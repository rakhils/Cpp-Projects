#include "Canvas.hpp"
#include "GameCommon.hpp"

Canvas::Canvas()
{
	
}

void Canvas::Update(float deltaTime)
{
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_S) || ((g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ENTER) 
		|| g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_SPACE)) && m_cursorIndex < 3))
	{
		m_switchLevelUp = true;
		m_selectedLevel = m_cursorIndex;
		SoundID soundid = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_DESTROY);
		g_audio->PlaySound( soundid );
	}

	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_DOWN_ARROW))
	{
		m_cursorIndex++;
		m_cursorIndex = m_cursorIndex % 5;
		SoundID test = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_QUIT_GAME);
		g_audio->PlaySound( test );
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_SPACE) || g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ENTER))
	{
		if(m_cursorIndex == 4)
		{
			isQuitTriggered = true;
		}
	}
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_UP_ARROW))
	{
		m_cursorIndex--;
		if(m_cursorIndex == -1)
		{
			m_cursorIndex = 4;
		}
		m_cursorIndex = m_cursorIndex % 5;
		SoundID test = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_QUIT_GAME);
		g_audio->PlaySound( test );
	}
	
	if(g_theInput->wasKeyJustPressed(InputSystem::KEYBOARD_ESCAPE))
	{
		isQuitTriggered = true;
	}


	switch(m_currentScene)
	{
		case Attract:
		{
			
			DoTitleAnimation(deltaTime);
		}
		break;
		case Victory:
		{

	
		}
		break;
	}
	if(m_changeFrom0to256 >= 255)
	{
		m_direction = -1;
	}
	if(m_changeFrom0to256 <= 0)
	{
		m_direction = 1;
	}
	m_changeFrom0to256 += m_direction;
}

void Canvas::Render()
{
	switch(m_currentScene)
	{
		case Attract:
		{
			//=====DRAW INCURSION======

			AABB2 position(Vector2(450.0f,650.0f),250.0f,25.0f);
			Vector2 minPosition = Vector2(0.0f,1.0f);
			Vector2 maxPosition = Vector2(1.0f,0.0f);
			Texture *texture = g_theRenderer->CreateOrGetTexture("Data\\Images\\PressS.png");
			Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(m_changeFrom0to256));
			g_theRenderer->DrawTexturedAABB(position,texture,minPosition,maxPosition,tint);


			AABB2 position1(Vector2(200.0f, 550.0f - (m_cursorIndex*50.0f)),35.0f,30.0f);
			Texture *texture1 = g_theRenderer->CreateOrGetTexture("Data\\Images\\Etank.png");
			Rgba tint1(static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255),static_cast<unsigned char>(255));
			g_theRenderer->DrawTexturedAABB(position1,texture1,minPosition,maxPosition,tint1);


			Vector2 cursorPosition(250.0f,530.0f);
			Vector2 cursorEndPosition(700.0f,580.0f);

			cursorPosition.y   -= m_cursorIndex*50;
			cursorEndPosition.y-= m_cursorIndex*50;
			
			g_theRenderer->DrawRectangle(cursorPosition.x,cursorPosition.y,cursorEndPosition.x,cursorEndPosition.y);

			DrawString("NEW GAME L1    ",0,15,		Vector2(250.0f,550.0f),15);
			DrawString("NEW GAME L2    ",0,15,		Vector2(250.0f,500.0f),15);
			DrawString("NEW GAME L3    ",0,15,		Vector2(250.0f,450.0f),15);
			DrawString("HIGHSCORE      ",0,15,		Vector2(250.0f,400.0f),15);
			DrawString("QUIT           ",0,15,		Vector2(250.0f,350.0f),15);

			float controlsTextY = 280;
			DrawString("===============",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| CONTROLS    |",15,		Vector2(000.0f,controlsTextY-=30.0f)); 
			DrawString("| ------------|",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| DRIVE       |",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| AIM         |",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| SHOOT       |",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| PAUSE       |",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("| QUIT        |",15,		Vector2(000.0f,controlsTextY-=30.0f));
			DrawString("==============|",15,		Vector2(000.0f,controlsTextY-=30.0f));
			//=========================
			controlsTextY = 280;
			DrawString("===============",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("CONTROLLER    |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("----------    |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("LEFT STICK    |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("RIGTH STICK   |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("RIGHT TRIGGER |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("START         |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("BACK          |",15,		Vector2(300.0f,controlsTextY-=30.0f));
			DrawString("===============",15,		Vector2(300.0f,controlsTextY-=30.0f));
			controlsTextY = 280;
			DrawString("===============", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("KEYBOARD      |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("----------    |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("ARROW KEYS    |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("A D           |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("SPACE         |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("ESCAPE        |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("ESCAPE        |", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("===============", 15,		Vector2(600.0f, controlsTextY -= 30.0f));
			DrawString("INCURSION",0,m_titleIndex,Vector2(150.0f,800.0f),30);
		}
		break;
		case Victory:
		{
			DrawString("VICTORY",0,7,			Vector2(300.0f,500.0f),35);
		}
		break;
	}
}

//TITLE ANIMATION OF "INCURSION"
void Canvas::DoTitleAnimation(float deltaTime)
{
	static float startX = -10;
	static float endY = 800;
	static float startY = 1100;
	static float currentPosY = -100;
	static float currentPosX = 150;


	static bool animationEnded = false;
	static bool animationOnProcess = true;
	static bool takeNextChar = true;
	static char str[10] = "INCURSION";
	
	if(m_titleIndex >= 9)
	{
		return;
	}
	
	DrawString(str,m_titleIndex,(m_titleIndex+1),Vector2(static_cast<float>(currentPosX),static_cast<float>(currentPosY)),30);
	currentPosY-=deltaTime*500;
	if(currentPosY < endY)
	{
		m_titleIndex++;
		currentPosX += 60;
		currentPosY = startY;
		SoundID soundid = g_audio->CreateOrGetSound(SOUND_DIRECTORY+SOUND_ETANK_FIRE);
		g_audio->PlaySound( soundid );
	}
}

void Canvas::SetCurrentSceneNum(SceneType sceneNum)
{
	m_currentScene = sceneNum;
}

void Canvas::DrawChar(char value,int length, Vector2 pos)//,float length)
{
		char ch = value;
		length = 1;
		pos.x += 20;
		int index = (int)ch;
		AABB2 aabb2 = GetTexCoordsForSpriteIndex(index,IntVector2(16,16));
		Vector2 minPosition = Vector2(aabb2.mins.x, aabb2.maxs.y);
		Vector2 maxPosition = Vector2(aabb2.maxs.x, aabb2.mins.y);
		AABB2 position(pos,10,10);
		Texture *texture = g_theRenderer->CreateOrGetTexture("Data\\Images\\font2.png");
		Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(255));
		g_theRenderer->DrawTexturedAABB(position,texture,minPosition,maxPosition,tint);
}

void Canvas::DrawString(char value[],int length, Vector2 pos)
{
	DrawString(value,0,length,pos,10);
}


void Canvas::DrawString(char value[],int start,int length, Vector2 pos,int height)
{
	for(int i = start;i<length;i++)
	{
		char ch = value[i];
		pos.x += height*2;
		int index = (int)ch;
		AABB2 aabb2 = GetTexCoordsForSpriteIndex(index,IntVector2(16,16));
		Vector2 minPosition = Vector2(aabb2.mins.x, aabb2.maxs.y);
		Vector2 maxPosition = Vector2(aabb2.maxs.x, aabb2.mins.y);
		AABB2 position(pos,static_cast<float>(height),static_cast<float>(height));
		Texture *texture = g_theRenderer->CreateOrGetTexture("Data\\Images\\font2.png");
		Rgba tint(static_cast<unsigned char>(255),static_cast<unsigned char>(0),static_cast<unsigned char>(0),static_cast<unsigned char>(255));
		g_theRenderer->DrawTexturedAABB(position,texture,minPosition,maxPosition,tint);
	}
}

AABB2 Canvas::GetTexCoordsForSpriteCoords(const IntVector2& spriteCoords,const IntVector2 m_spriteLayout)
{
	float BottomLeftX = spriteCoords.x * 1.0f/m_spriteLayout.x;
	float BottomLeftY = ((spriteCoords.y) * 1.0f/m_spriteLayout.y);
	float TopRigthX = ((spriteCoords.x + 1) * 1.0f/m_spriteLayout.x);
	float TopRightY = ((spriteCoords.y + 1)*1.0f/m_spriteLayout.y);
	AABB2 aabb2(BottomLeftX,BottomLeftY,TopRigthX,TopRightY);
	return aabb2;
}

AABB2 Canvas::GetTexCoordsForSpriteIndex(int spriteIndex,const IntVector2 m_spriteLayout) 
{
	int posX = spriteIndex%m_spriteLayout.x;
	int posY = spriteIndex/m_spriteLayout.y;
	IntVector2 spriteCoords(posX,posY);
	return GetTexCoordsForSpriteCoords(spriteCoords,m_spriteLayout);
}

