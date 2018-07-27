//-----------------------------------------------------------------------------------------------
// Texture.hpp
//
#pragma once
#include <string>
#include <map>
#include <vector>

#include "Engine/Math/IntVector2.hpp"
#include "Engine/Core/Rgba.hpp"

//---------------------------------------------------------------------------
class Texture
{
	friend class Renderer; // Textures are managed by a Renderer instance

private:
	Texture( const std::string& imageFilePath ); // Use renderer->CreateOrGetTexture() instead!
	void PopulateFromData( unsigned char* imageData, const IntVector2& texelSize, int numComponents );

public:
	Rgba getTexel(int index);
	Rgba getTexel(int x,int y);
	void setTexel(int x,int y,Rgba rgba);
	void clearAllData();
	void storeAllData();
	IntVector2 getDimensions() const;

private:
	unsigned int		m_textureID;
	IntVector2			m_dimensions;
	int					m_numOfComponents;
	unsigned char*		imageData = nullptr;
	
	std::vector <Rgba*> pixels;
};


