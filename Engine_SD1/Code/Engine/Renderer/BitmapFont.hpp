#pragma once
#include <string>

#include "Engine/Math/AABB2.hpp"
#include "Engine/Renderer/SpriteSheet.hpp"
#include "Engine/Renderer/Renderer.hpp"

class BitmapFont
{
	friend class Renderer;

public:
	AABB2 GetUVsForGlyph( int glyphUnicode ) const;
	float GetGlyphAspect( int glyphUnicode ) const { int temValue = glyphUnicode;temValue = 1;return m_baseAspect; }
	float GetStringWidth( const std::string& asciiText, float cellHeight, float aspectScale );

private:
	explicit BitmapFont( const std::string& fontName,  SpriteSheet& glyphSheet,float baseAspect );

	SpriteSheet *m_spriteSheet = nullptr;
	float m_baseAspect = 1.0f;
	std::string m_name;

};