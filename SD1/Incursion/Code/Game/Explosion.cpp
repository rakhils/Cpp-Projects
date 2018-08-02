#include "Game/Explosion.hpp"


Explosion::Explosion()
{
}

Explosion::Explosion(Vector2 position, float radius)
{
	Explosion(position,radius,1.0f);
}

Explosion::Explosion(Vector2 position, float radius, float duration)
{
	m_centreX		= position.x;
	m_centreY		= position.y;
	m_radius		= radius;
	m_markForDelete = false;
	m_duration		= duration;
}

void Explosion::Update(float deltaSecond)
{
	if(m_explosionAnimation!=nullptr)
	{
		m_explosionAnimation->Update(deltaSecond);
		if(m_explosionAnimation->m_isFinished)
		{
			m_markForDelete = true;
		}
	}
}

void Explosion::Render()
{
	if(m_markForDelete)
	{
		return;
	}
	Texture *explosionTexture = g_theRenderer->CreateOrGetTexture("Data\\Images\\explosion.png");
	if(g_explosionSpriteSheet == nullptr)
	{
		g_explosionSpriteSheet = new SpriteSheet(*explosionTexture,EXPLOSION_ANIM_SPRITE_NUMCOLS,EXPLOSION_ANIM_SPRITE_NUMRAWS);
	}

	if(m_explosionAnimation==nullptr)
	{
		int totalSprites     = EXPLOSION_ANIM_SPRITE_NUMCOLS * EXPLOSION_ANIM_SPRITE_NUMRAWS;
		m_explosionAnimation = new SpriteAnimation(g_explosionSpriteSheet,m_duration,SPRITE_ANIM_MODE_PLAY_TO_END,0,totalSprites - 1);
	}

	AABB2 aabb2(Vector2(m_centreX,m_centreY),m_radius/2,m_radius/2);// g_explosionAnim->GetCurrentTexCoords();
	Vector2 minPosition = m_explosionAnimation->GetCurrentTexCoords().mins;
	Vector2 maxPosition = m_explosionAnimation->GetCurrentTexCoords().maxs;
	Rgba tint((unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)255);
	g_theRenderer->EnableAdditiveBlending();
	g_theRenderer->DrawTexturedAABB(aabb2, explosionTexture, minPosition , maxPosition,tint);
	g_theRenderer->DisableAdditiveBlending();
}

