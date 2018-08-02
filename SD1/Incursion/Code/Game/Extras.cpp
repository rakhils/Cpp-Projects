#include "Extras.hpp"

Extras::Extras(Vector2 position, ExtraBonusPickUps type)
{
	UNUSED(type);
	m_centreX					= position.x;
	m_centreY					= position.y;
	m_radius					= ENTITY_WIDTH/2.f;
	m_innerRadius				= m_radius*ENTITY_PHYSICS_RATIO;
	m_collisionDisk.center.x	= m_centreX;
	m_collisionDisk.center.y	= m_centreY;
	m_collisionDisk.radius		= 0.4f;


	/*switch (type)
	{
	case EXTRA_HEALTH:
		textureCord =   g_theRenderer->GetTexCoordsForSpriteIndex(6,IntVector2(4,4));
		break;
	case EXTRA_MISSILE:
		textureCord =   g_theRenderer-> GetTexCoordsForSpriteIndex(8,IntVector2(4,4));
		break;
	default:
		break;
	}*/
}

void Extras::Update(float deltaTime)
{
	if(m_markForDelete)
	{
		return;
	}
	m_scaleFactor += deltaTime*m_scalingDirection;
	if(m_scaleFactor >= m_scalingUpperLimit)
	{
		m_scalingDirection = -1;
	}
	if(m_scaleFactor <= m_scalingLowerLimit)
	{
		m_scalingDirection = +1;
	}
}

void Extras::Render()
{
	if(m_markForDelete)
	{
		return;
	}
	m_texture = g_theRenderer->CreateOrGetTexture(IMAGE_DIRECTORY+IMAGE_EXTRAS);

	g_theRenderer->PushMatrix();
	g_theRenderer->Translate(GetCenter());
	g_theRenderer->Rotate(m_angle);
	g_theRenderer->ScaleUniform(m_scaleFactor);
	AABB2 aabb2t(Vector2(0,0),m_length/2,m_bredth/2);
	Vector2 texCoordsAtMins = m_textureCord.mins;
	Vector2 texCoordsAtMaxs = m_textureCord.maxs;
	g_theRenderer->DrawTexturedAABB(aabb2t, m_texture, texCoordsAtMins, texCoordsAtMaxs,COLOR_WHITE);
	g_theRenderer->PopMatrix();

	Entity::Render();
}

