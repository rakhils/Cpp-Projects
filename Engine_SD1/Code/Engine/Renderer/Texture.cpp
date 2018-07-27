//-----------------------------------------------------------------------------------------------
// Texture.cpp
//
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "Engine/Renderer/Texture.hpp"
#include "Engine/ThirdParty/stb/stb_image.h"


//-----------------------------------------------------------------------------------------------
// Called only by the Renderer.  Use renderer->CreateOrGetTexture() to instantiate textures.
//
Texture::Texture( const std::string& imageFilePath )
	: m_textureID( 0 )
	, m_dimensions(0, 0 )
{
	int numComponents = 0; // Filled in for us to indicate how many color/alpha components the image had (e.g. 3=RGB, 4=RGBA)
	int numComponentsRequested = 0; // don't care; we support 3 (RGB) or 4 (RGBA)

	this->imageData = stbi_load( imageFilePath.c_str(), &m_dimensions.x, &m_dimensions.y, &numComponents, numComponentsRequested );
	m_numOfComponents = numComponents;
	
	PopulateFromData( imageData, m_dimensions, numComponents );
}


//-----------------------------------------------------------------------------------------------
// Creates a texture identity on the video card, and populates it with the given image texel data
//
void Texture::PopulateFromData( unsigned char* imgData, const IntVector2& texelSize, int numComponents )
{
	m_dimensions = texelSize;

	// Enable texturing
	glEnable( GL_TEXTURE_2D );

	// Tell OpenGL that our pixel data is single-byte aligned
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// Ask OpenGL for an unused texName (ID number) to use for this texture
	glGenTextures( 1, (GLuint*) &m_textureID );

	// Tell OpenGL to bind (set) this as the currently active texture
	glBindTexture( GL_TEXTURE_2D, m_textureID );

	// Set texture clamp vs. wrap (repeat)
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP ); // GL_CLAMP or GL_REPEAT
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP ); // GL_CLAMP or GL_REPEAT

   // Set magnification (texel > pixel) and minification (texel < pixel) filters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); // one of: GL_NEAREST, GL_LINEAR
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR

	GLenum bufferFormat = GL_RGBA; // the format our source pixel data is in; any of: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, ...
	if( numComponents == 3 )
		bufferFormat = GL_RGB;

	GLenum internalFormat = bufferFormat; // the format we want the texture to be on the card; allows us to translate into a different texture format as we upload to OpenGL

	glTexImage2D(			// Upload this pixel data to our new OpenGL texture
		GL_TEXTURE_2D,		// Creating this as a 2d texture
		0,					// Which mipmap level to use as the "root" (0 = the highest-quality, full-res image), if mipmaps are enabled
		internalFormat,		// Type of texel format we want OpenGL to use for this texture internally on the video card
		m_dimensions.x,			// Texel-width of image; for maximum compatibility, use 2^N + 2^B, where N is some integer in the range [3,11], and B is the border thickness [0,1]
		m_dimensions.y,			// Texel-height of image; for maximum compatibility, use 2^M + 2^B, where M is some integer in the range [3,11], and B is the border thickness [0,1]
		0,					// Border size, in texels (must be 0 or 1, recommend 0)
		bufferFormat,		// Pixel format describing the composition of the pixel data in buffer
		GL_UNSIGNED_BYTE,	// Pixel color components are unsigned bytes (one byte per color channel/component)
		imgData );		// Address of the actual pixel data bytes/buffer in system memory
}

Rgba Texture::getTexel(int index)
{
	return *(pixels.at(index));
}


Rgba Texture::getTexel(int x,int y)
{
	int pixelStart = y*m_dimensions.x + x;
	return *(pixels.at(pixelStart));
}

void Texture::setTexel(int x, int y, Rgba rgba)
{
	unsigned char r = rgba.r;
	unsigned char g = rgba.g;
	unsigned char b = rgba.b;
	unsigned char a = rgba.a;
	Rgba *rgb;
	rgb = new Rgba(r,g,b,a);
	int pixelStart = y*m_dimensions.x + x;
	pixels[pixelStart] = rgb;
}

void Texture::clearAllData()
{
	stbi_image_free( imageData );
}

void Texture::storeAllData()
{
	for(int i = 0,j=0;i<m_numOfComponents*m_dimensions.x*m_dimensions.y;i+=m_numOfComponents,j++)
	{
		Rgba *rgba;
		rgba = new Rgba(imageData[i],imageData[i+1],imageData[i+2],imageData[i+3]);
		pixels.push_back(rgba);
	}
}

//////////////////////////////////////////////////////////////
/*DATE    : 2017/12/18
*@purpose : For getting texture dimensions
*
*@param   : NIL
*
*@return  : Return dimension of current texture
*/
//////////////////////////////////////////////////////////////

IntVector2 Texture::getDimensions() const
{
	return m_dimensions;
}

