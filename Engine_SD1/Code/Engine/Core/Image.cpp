#include "Image.hpp"

Image::Image(const std::string& imageFilePath)
{
	Renderer *renderer = new Renderer();
	texture = renderer->CreateOrGetTexture(imageFilePath,true);
}

//////////////////////////////////////////////////////////////////////////
//@purpose : Get pixel by row column
Rgba Image::GetTexel(int x, int y) const
{
	return texture->getTexel(x,y);
}

//////////////////////////////////////////////////////////////////////////
//@purpose : Get pixel by array index
Rgba Image::GetTexelByIndex(int index) const
{
	return texture->getTexel(index);
}

void Image::SetTexel(int x, int y, const Rgba& color)
{
	texture->setTexel(x,y,color);
}

