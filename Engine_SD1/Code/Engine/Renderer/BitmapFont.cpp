#include "BitmapFont.hpp"

BitmapFont::BitmapFont(const std::string& fontName, SpriteSheet& glyphSheet, float baseAspect) 
	:m_spriteSheet(&glyphSheet), m_name(fontName)
{
	m_baseAspect = baseAspect;
}

AABB2 BitmapFont::GetUVsForGlyph(int glyphUnicode) const
{
	int width  = m_spriteSheet->getTexture()->getDimensions().x;
	int heigth = m_spriteSheet->getTexture()->getDimensions().y;

	int posX = glyphUnicode%width;
	int posY = glyphUnicode/heigth;

	IntVector2 spriteCoords(posX,posY);
	IntVector2 m_spriteLayout(width,heigth);

	float BottomLeftX = (spriteCoords.x       * 1.0f/m_spriteLayout.x);
	float BottomLeftY = (spriteCoords.y		  * 1.0f/m_spriteLayout.y);
	float TopRigthX   = ((spriteCoords.x + 1) * 1.0f/m_spriteLayout.x);
	float TopRightY   = ((spriteCoords.y + 1) * 1.0f/m_spriteLayout.y);
	AABB2 aabb2(BottomLeftX,BottomLeftY,TopRigthX,TopRightY);

	return aabb2;
}

float BitmapFont::GetStringWidth(const std::string& asciiText, float cellHeight, float aspectScale)
{
	return asciiText.length()*aspectScale*cellHeight;
}


