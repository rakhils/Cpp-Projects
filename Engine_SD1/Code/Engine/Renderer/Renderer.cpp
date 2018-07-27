#include "Engine/Renderer/Renderer.hpp"
#include <windows.h>			// #include this (massive, platform-specific) header in very few places
#include <gl/gl.h>	
#include <stdio.h>
#include "Engine\Math\Vector2.hpp"
#include "Engine\Math\MathUtil.hpp"
#include "Engine\Core\Rgba.hpp"
#include "Engine\ThirdParty\stb\stb_image.h"

#include "Engine/Renderer/Texture.hpp"
#include "Engine/ThirdParty/stb/stb_image.h"
#include "Engine\Core\Vertex.hpp"
#pragma comment( lib, "opengl32" )

Renderer::Renderer()
{
	m_bottomLeft = Vector2(0,0);
	m_topRight = Vector2(1000,1000);
}

Renderer::~Renderer()
{

}

void Renderer::BeginFrame()
{
	glLoadIdentity();
	SetOrtho(m_bottomLeft, m_topRight);
	glClearColor( 0.f, 0.f, 0.0f, 1.f );
	ClearScreen();
}

Texture * Renderer::CreateOrGetTexture(const std::string& imageFilePath)
{
	return CreateOrGetTexture(imageFilePath,false);
}

Texture * Renderer::CreateOrGetTexture(const std::string& imageFilePath,bool m_storeValue)
{
	if(m_textureMap.find(imageFilePath) != m_textureMap.end())
	{
		return m_textureMap[imageFilePath];
	}

	Texture *texture = new Texture(imageFilePath);
	if(m_storeValue)
	{
		texture->storeAllData();
	}
	texture->clearAllData();
	m_textureMap[imageFilePath] = texture;
	return texture;
}

BitmapFont* Renderer::CreateOrGetBitmapFont(const char* bitmapFontName)
{
	if (fontSheet == nullptr)
	{
		std::string path = "Data/Font/";
		path.append(bitmapFontName);
		path.append(".png");
		Texture *texture = CreateOrGetTexture(path);
		fontSheet = new SpriteSheet(*texture, 16, 16);
	}
	BitmapFont *bitMapFont = new BitmapFont(bitmapFontName, *fontSheet, 1);
	m_loadedFonts[bitmapFontName] = bitMapFont;
	return bitMapFont;
}

void Renderer::EndFrame()
{
	HWND hWnd = GetActiveWindow();
	HDC hDC = GetDC( hWnd );
	SwapBuffers( hDC );
}

void Renderer::EnableTexture()
{
	glEnable(GL_TEXTURE_2D);
}

void Renderer::BindTexture(Texture *texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
}

void Renderer::DisableTexture()
{
	glDisable(GL_TEXTURE_2D);
}

void Renderer::SetOrtho( const Vector2& bottomLeft, const Vector2& topRight )
{
	glOrtho( bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, 0.f, 1.f );
}

//////////////////////////////////////////////////////////////
/*DATE    : 2017/12/20
*@purpose : Adding matrix mode for isometric projections
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Renderer::MatrixMode()
{
	glMatrixMode(GL_MODELVIEW);
}

void Renderer::ClearScreen()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

void Renderer::PushMatrix()
{
	glPushMatrix();
}

void Renderer::PopMatrix()
{
	glPopMatrix();
}

//////////////////////////////////////////////////////////////
/*DATE    : 2017/12/20
*@purpose : Scale non uniform
*
*@param   : ScaleX component ,ScaleY component
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Renderer::Scale(float scaleX, float scaleY)
{
	glScalef(scaleX,scaleY,0);
}

void Renderer::ScaleUniform( float uniformScale )
{
	glScalef(uniformScale,uniformScale,0);
}

void Renderer::Translate( const Vector2& translation )
{
	glTranslatef(translation.x,translation.y,0);
}

void Renderer::Rotate( float degrees )
{
	glRotatef(degrees,0,0,1);
}

void Renderer::DrawLines(Vector2 *pointArray,int length,bool skip)
{
	int incrementValue = 1;
	if(skip)
	{
		incrementValue = 2;
	}

	Vertex_3DPCU *lineVertex = new Vertex_3DPCU[2];
	lineVertex->setPoint(pointArray[0]);
	(lineVertex + 1)->setPoint(pointArray[1]);

	DrawMeshImmediate(lineVertex,2,PRIMITIVE_LINES);
}

void Renderer::DrawLines(Vector2 point1,Vector2 point2, int length, bool skip)
{
	int incrementValue = 1;
	if (skip)
	{
		incrementValue = 2;
	}

	Vertex_3DPCU *lineVertex = new Vertex_3DPCU[2];
	lineVertex->setPoint(point1);
	(lineVertex + 1)->setPoint(point2);

	DrawMeshImmediate(lineVertex, 2, PRIMITIVE_LINES);
}

void Renderer::DrawLines(Vector2 *pointArray,int length)
{
	DrawLines(pointArray,length,true);
}

void Renderer::DrawLines(std::vector<Vector2>& points, Rgba rgba,bool skip)
{
	Vertex_3DPCU *lineVertex = new Vertex_3DPCU[points.size()];
	for(int index = 0;index < points.size();index++)
	{
		(lineVertex + index)->setPoint(points.at(index));
		(lineVertex + index)->setRGBA(rgba);
		//(lineVertex + index + 1)->setPoint(points.at(index + 1));
	}
	DrawMeshImmediate(lineVertex, points.size(), PRIMITIVE_LINES);
}

void Renderer::DrawLine(Vector2 *point1,Vector2 *point2)
{
	Vertex_3DPCU line[2];
	line[0].setPoint(*point1);
	line[1].setPoint(*point2);

	DrawMeshImmediate(line,2,PRIMITIVE_LINES);
}

void Renderer::DrawLine(Vector2 point1,Vector2 point2)
{
	Vertex_3DPCU line[2];
	line[0].setPoint(point1);
	line[1].setPoint(point2);

	DrawMeshImmediate(line,2,PRIMITIVE_LINES);
}

void Renderer::DrawLine(float x1,float y1,float x2,float y2)
{
	Vertex_3DPCU line[2];
	line[0].setPoint(x1,y1);
	line[1].setPoint(x2,y2);

	DrawMeshImmediate(line,2,PRIMITIVE_LINES);
}

void Renderer::DrawLine(Vector2 point1, Vector2 point2, Rgba rgba)
{
	Vertex_3DPCU line[2];
	line[0].setPoint(point1.x,point1.y);
	line[1].setPoint(point2.x,point2.y);

	line[0].m_rgba = rgba;
	line[1].m_rgba = rgba;

	DrawMeshImmediate(line,2,PRIMITIVE_LINES);
}

void Renderer::DrawFeatheredLine(Vector2 point1, Vector2 point2, Rgba startColor, Rgba finalColor)
{
	Vertex_3DPCU line[2];
	line[0].setPoint(point1);
	line[0].setRGBA(startColor);
	line[1].setPoint(point2);
	line[1].setRGBA(finalColor);
	DrawMeshImmediate(line,2,PRIMITIVE_LINES);
}

void Renderer::SetColor(float R,float G,float B)
{
	glColor3f(R,G,B);
}

void Renderer::SetColor(Rgba rgba)
{
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;
	float A = 0.0f;
	rgba.GetAsFloats(R,G,B,A);
	glColor4f(R,G,B,A);
}

void Renderer::EnableAdditiveBlending()
{
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}

void Renderer::DisableAdditiveBlending()
{
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

//////////////////////////////////////////////////////////////
/*DATE    : 2017/12/18
*@purpose : Setting mins and max of current screen view
*
*@param   : Maxs and Min position of camera scren
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////

void Renderer::SetOrthoPosition(Vector2 mins, Vector2 maxs)
{
	m_bottomLeft = mins;
	m_topRight = maxs;
}

void Renderer::DrawDottedCircle(float centreX,float centreY,float nradius)
{
	const int MAX_NUM_VERTEX = 40;
	Vertex_3DPCU line[MAX_NUM_VERTEX];
	float nangle = 360.0f/(float)20.0f;
	for(int i=0,j=0;i<=20;i++)
	{
		float startX =  centreX + (nradius)*CosDegrees(i*nangle);
		float startY =  centreY + (nradius)*SinDegrees(i*nangle);

		float endX =  centreX + (nradius)*CosDegrees((i+1)*nangle);
		float endY =  centreY + (nradius)*SinDegrees((i+1)*nangle);
		if(i%2==0)
		{
			line[j++].setPoint(startX,startY);
			line[j++].setPoint(endX,endY);
		}
	}
	DrawMeshImmediate(line,MAX_NUM_VERTEX,PRIMITIVE_LINES);
}

void Renderer::DrawCircle(float centreX,float centreY,float radius)
{
	DrawCircle(centreX,centreY,radius,10);
}

void Renderer::DrawCircle(float centreX,float centreY,float nradius,int numofSize)
{
	const int MAX_NUM_VERTEX = 40;
	Vertex_3DPCU line[MAX_NUM_VERTEX];
	float nangle = 360.0f/(float)20.0f;
	for(int i=0,j=0;i<=20;i++)
	{
		float startX =  centreX + (nradius)*CosDegrees(i*nangle);
		float startY =  centreY + (nradius)*SinDegrees(i*nangle);

		float endX =  centreX + (nradius)*CosDegrees((i+1)*nangle);
		float endY =  centreY + (nradius)*SinDegrees((i+1)*nangle);
		line[j++].setPoint(startX,startY);
		line[j++].setPoint(endX,endY);
	}
	SetColor(Rgba::WHITE);
	DrawMeshImmediate(line,MAX_NUM_VERTEX,PRIMITIVE_LINES);
}

void Renderer::DrawCircle(Vector2 centre, float nradius)
{
	DrawCircle(centre.x,centre.y,nradius);
}

void Renderer::DrawRectangle(float centreX,float centreY,float length,float bredth,float angle)
{
	float RX = centreX + length/2*CosDegrees(angle);
	float RY = centreY + length/2*SinDegrees(angle);

	float RXTX = RX + bredth/2*CosDegrees(90+angle);
	float RYTY = RY + bredth/2*SinDegrees(90+angle);

	float RXBX = RX + bredth/2*CosDegrees(270+angle);
	float RYBY = RY + bredth/2*SinDegrees(270+angle);

	float LX = centreX + length/2*CosDegrees(180+angle);
	float LY = centreY + length/2*SinDegrees(180+angle);

	float LXTX = LX + bredth/2*CosDegrees(90+angle);
	float LYTY = LY + bredth/2*SinDegrees(90+angle);
		  
	float LXBX = LX + bredth/2*CosDegrees(270+angle);
	float LYBY = LY + bredth/2*SinDegrees(270+angle);
	const int MAX_NUM_VERTEX = 5;

	Vertex_3DPCU rectangle[MAX_NUM_VERTEX];
	rectangle[0].setPoint(LXTX,LYTY);
	rectangle[1].setPoint(RXTX,RYTY);
	rectangle[2].setPoint(RXBX,RYBY);
	rectangle[3].setPoint(LXBX,LYBY);
	rectangle[4].setPoint(LXTX,LYTY);
	DrawMeshImmediate(rectangle,MAX_NUM_VERTEX,PRIMITIVE_LINES);
}

void Renderer::DrawRectangle(float x1, float y1, float x2, float y2)
{
	float LXBX = x1;
	float LYBY = y1;

	float LXTX = x1;
	float LYTY = y2;

	float RXTX = x2;
	float RYTY = y2;

	float RXBX = x2;
	float RYBY = y1;


	const int MAX_NUM_VERTEX = 8;
	Vertex_3DPCU rectangle[MAX_NUM_VERTEX];
	rectangle[0].setPoint(LXBX,LYBY);
	rectangle[1].setPoint(RXBX,RYBY);

	rectangle[2].setPoint(RXBX,RYBY);
	rectangle[3].setPoint(RXTX,RYTY);

	rectangle[4].setPoint(RXTX,RYTY);
	rectangle[5].setPoint(LXTX,LYTY);

	rectangle[6].setPoint(LXTX,LYTY);
	rectangle[7].setPoint(LXBX,LYBY);
	DrawMeshImmediate(rectangle,MAX_NUM_VERTEX,PRIMITIVE_LINES);
}

void Renderer::DrawSolidRectangle(float x1, float y1, float x2, float y2)
{
	DrawRectangle(x1,y1,x2,y2);
}

void Renderer::DrawTexturedAABB(const AABB2& bounds,const Texture *texture, const Vector2& texCoordsAtMins, const Vector2& texCoordsAtMaxs, const Rgba& tint)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);

	const int MAX_NUM_VERTEX = 6;
	Vertex_3DPCU rectangle[6];

	rectangle[0].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMaxs.y));
	rectangle[0].setPoint(bounds.maxs.x,bounds.maxs.y);
	rectangle[0].setRGBA(tint);

	rectangle[1].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMaxs.y));
	rectangle[1].setPoint(bounds.mins.x,bounds.maxs.y);
	rectangle[1].setRGBA(tint);

	rectangle[2].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMins.y));
	rectangle[2].setPoint(bounds.mins.x,bounds.mins.y);
	rectangle[2].setRGBA(tint);

	//////////////////////////////////////////////////////////////////////////

	rectangle[3].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMins.y));
	rectangle[3].setPoint(bounds.mins.x,bounds.mins.y);
	rectangle[3].setRGBA(tint);


	rectangle[4].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMins.y));
	rectangle[4].setPoint(bounds.maxs.x,bounds.mins.y);
	rectangle[4].setRGBA(tint);


	rectangle[5].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMaxs.y));
	rectangle[5].setPoint(bounds.maxs.x,bounds.maxs.y);
	rectangle[5].setRGBA(tint);

	DrawMeshImmediate(rectangle,MAX_NUM_VERTEX,PRIMITIVE_TRIANGES);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
}

void Renderer::DrawAABB(const AABB2& bounds, const Rgba& color)
{
	const int MAX_NUM_VERTEX = 4;
	Vertex_3DPCU rectangle[4];
	Vector2 texCoordsAtMins(0,1);
	Vector2 texCoordsAtMaxs(1,0);

	rectangle[0].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMins.y));
	rectangle[0].setPoint(bounds.mins.x,bounds.mins.y);
	rectangle[0].setRGBA(color);

	rectangle[1].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMaxs.y));
	rectangle[1].setPoint(bounds.mins.x,bounds.maxs.y);
	rectangle[1].setRGBA(color);

	rectangle[2].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMaxs.y));
	rectangle[2].setPoint(bounds.maxs.x,bounds.maxs.y);
	rectangle[2].setRGBA(color);

	rectangle[3].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMins.y));
	rectangle[3].setPoint(bounds.maxs.x,bounds.mins.y);
	rectangle[3].setRGBA(color);
	DrawMeshImmediate(rectangle,MAX_NUM_VERTEX,PRIMITIVE_QUADS);
}

void Renderer::DrawAABB(const AABB2& bounds, const Rgba& color1,const Rgba& color2)
{
	const int MAX_NUM_VERTEX = 4;
	Vertex_3DPCU rectangle[4];
	Vector2 texCoordsAtMins(0,1);
	Vector2 texCoordsAtMaxs(1,0);

	rectangle[0].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMins.y));
	rectangle[0].setPoint(bounds.mins.x,bounds.mins.y);
	rectangle[0].setRGBA(color1);
	rectangle[1].setUV(Vector2(texCoordsAtMins.x, texCoordsAtMaxs.y));
	rectangle[1].setPoint(bounds.mins.x,bounds.maxs.y);
	rectangle[1].setRGBA(color1);
	rectangle[2].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMaxs.y));
	rectangle[2].setPoint(bounds.maxs.x,bounds.maxs.y);
	rectangle[2].setRGBA(color2);
	rectangle[3].setUV(Vector2(texCoordsAtMaxs.x, texCoordsAtMins.y));
	rectangle[3].setPoint(bounds.maxs.x,bounds.mins.y);
	rectangle[3].setRGBA(color2);
	DrawMeshImmediate(rectangle,MAX_NUM_VERTEX,PRIMITIVE_QUADS);
}

void Renderer::DrawTextOnPoint(char value[],int start,int length, Vector2 position,float height,Rgba rgba)
{
	for(int index = start;index<length;index++)
	{
		char ch			= value[index];
		position.x		+= height*2;
		int spriteIndex = (int)ch;

		BitmapFont *bitmapFont = CreateOrGetBitmapFont("font2");
		AABB2 aabb2 = bitmapFont->m_spriteSheet->GetTexCoordsForSpriteIndex(spriteIndex);
		Vector2 minPosition = Vector2(aabb2.mins.x, aabb2.mins.y);
		Vector2 maxPosition = Vector2(aabb2.maxs.x, aabb2.maxs.y);
		AABB2 textPosition(position,static_cast<float>(height),static_cast<float>(height));
		
		DrawTexturedAABB(textPosition,bitmapFont->m_spriteSheet->getTexture(),minPosition,maxPosition,rgba);
	}
}

void Renderer::DrawTextOnPoint(char value[],int start,int length, Vector2 pos,int height)
{
	DrawTextOnPoint(value,start,length,pos,height,Rgba::WHITE);
}

void Renderer::DrawTextOnPoint(std::string str, int start, int length, Vector2 pos, float height, Rgba rgba)
{
	char *charArray = &str[0];
	DrawTextOnPoint(charArray,start,length,pos,height,rgba);
}

void Renderer::DrawInt(int value, Vector2 pos,int height)
{
	std::string strValue ;
	int j = 0;
	while(value>0)
	{
		char val = '0' + value%10;
		strValue += val;
		value = value/10;
		j++;
	}
	strValue[j] = '\0';
	std::reverse(strValue.begin(),strValue.end());
	DrawTextOnPoint(strValue,0,static_cast<int>(strValue.length()),pos,height,Rgba::WHITE);
}

void Renderer::DrawTextInBox2D(AABB2 aabb2, std::string text, float aspectRatio, float height, Vector2 alignment, TextDrawMode drawMode)
{
	float length = aspectRatio*height*text.size();
	float boxHeight = aabb2.maxs.y - aabb2.mins.y;
	float boxWidth  = aabb2.maxs.x - aabb2.mins.x;
	float size = static_cast<float>(text.size());
	float lengthOfEach  = length/text.size();
	Vector2 startPosition(0,0);
	startPosition = Vector2(aabb2.mins.x + lengthOfEach/2,aabb2.GetCenter().y);
	float offset = 0;
	float offsetDown = 0;

	AABB2 actualAABB2(aabb2.mins.x,aabb2.mins.y,aabb2.maxs.x,aabb2.maxs.y);
	
	BitmapFont *bitMapFont = CreateOrGetBitmapFont("font2");
	switch(drawMode)	
	{
		case TEXT_DRAW_SHRINK_TO_FIT:
			if(height > boxHeight)
			{
				float scaleFactor = height/boxHeight;
				length = length/scaleFactor;
				height = height/scaleFactor;
			}
			if(length > boxWidth)
			{
				float scaleFactor = length/boxWidth;
				length = length/scaleFactor;
				height = height/scaleFactor;
			}
			lengthOfEach = length/text.size();
			

			if(alignment.x == 0 && alignment.y == 0)
			{
				offsetDown = actualAABB2.maxs.y - actualAABB2.mins.y - height/2;
			}


			if(alignment.x == .5f && alignment.y == 0.5)
			{
				if(length < boxWidth)
				{
					float midPoint = boxWidth/2;
					offset = midPoint-length/2.0f;
				}

				if(height < boxHeight)
				{
					float midPoint = boxHeight/2;
					offsetDown = midPoint-height/2.0f;
				}
			}

			if(alignment.x == 1 && alignment.y == 1)
			{
				if(length < boxWidth)
				{
					offset = boxWidth-length;
				}
				if(height < boxHeight)
				{
					offsetDown = height/2;//actualAABB2.maxs.y - actualAABB2.mins.y;
				}
			}

			startPosition = Vector2(aabb2.mins.x + lengthOfEach/2 + offset,aabb2.mins.y+offsetDown);
			DrawText2D(startPosition,text,height,Rgba(255,0,0,255),aspectRatio,bitMapFont);
			break;
		case TEXT_DRAW_WORD_WRAP: // area wise shrink
			{

				float widthAllowedToDraw = actualAABB2.maxs.x - actualAABB2.mins.x;
				float heightAllowedToDraw = actualAABB2.maxs.y - actualAABB2.mins.y;
				
				//float actualTotalNumOnRigth = widthAllowedToDraw/height;
				//float actualTotalNumOnDown  = heightAllowedToDraw/height;
				
				float totalCharAllowedToDraw = widthAllowedToDraw*heightAllowedToDraw; // calculating the area available to draw
				float value = totalCharAllowedToDraw/size;// total area divided by number of characters
				height = sqrt(value);// heigth * widht both are same taking square root
				
				float numOfCharAllowedToDrawRight = widthAllowedToDraw/height;

				if(numOfCharAllowedToDrawRight >= size)
				{
					numOfCharAllowedToDrawRight = size;
				}
				
				int index = static_cast<int>(numOfCharAllowedToDrawRight);
				int minValue = 0;
				float startHeigth = actualAABB2.maxs.y;// - height/2;
				for(; minValue < size; index += static_cast<int>(numOfCharAllowedToDrawRight))
				{
					std::string str = text.substr(minValue,static_cast<int>(numOfCharAllowedToDrawRight));
					startPosition = Vector2(actualAABB2.mins.x + height/2,startHeigth);
				
					DrawText2D(startPosition,str,height,Rgba(255,0,0,255),aspectRatio,bitMapFont);
					minValue = index;
					startHeigth -= height;
				}
			}
			break;
		case TEXT_DRAW_WORD_WRAP1:
		{
			/*int numOfStepDown = 1;
			for(int index = 0;index < size;index++)
			{
				if(text[index] == '\n')
				{
					numOfStepDown++;
				}
			}
			float newHeigth = height*numOfStepDown;

			if(newHeigth > boxHeight)
			{
				float scaleFactor = height/boxHeight;
				length = length/scaleFactor;
				height = height/scaleFactor;
			}
			

			lengthOfEach = length/text.size();
			int lastIndex = 0;
			float startHeigth = actualAABB2.maxs.y;// - height/2;
			startPosition = Vector2(aabb2.mins.x + height/2,startHeigth);
			for(int index = 0;index < size;index++)
			{
				if(text[index] == '\n')
				{
					startPosition.y = startHeigth;
					DrawText2D(startPosition,text.substr(lastIndex,index-lastIndex),height,Rgba(255,0,0,255),aspectRatio,bitMapFont);
					lastIndex = index;
					startHeigth -= height;
				}
			}
			//startHeigth -= height;
			startPosition.y = startHeigth;
			DrawText2D(startPosition,text.substr(lastIndex,size),height,Rgba(255,0,0,255),aspectRatio,bitMapFont);
			
			break;*/
		}
		break;
		case TEXT_DRAW_OVERRUN:
			//if(alignment.x == 0 && alignment.y == 0)
			{
				offsetDown = actualAABB2.maxs.y - actualAABB2.mins.y - height/2;
			}


			if(alignment.x == .5f && alignment.y == 0.5)
			{
				//if(length < boxWidth)
				{
					float midPoint = boxWidth/2;
					offset = midPoint-length/2.0f;
				}

				//if(height < boxHeight)
				{
					float midPoint = boxHeight/2;
					offsetDown = midPoint-height/2.0f;
				}
			}

			if(alignment.x == 1 && alignment.y == 1)
			{
				//if(length < boxWidth)
				{
					offset = boxWidth-length;
				}
				//if(height < boxHeight)
				{
					offsetDown = height/2;//actualAABB2.maxs.y - actualAABB2.mins.y;
				}
			}

			startPosition = Vector2(aabb2.mins.x + lengthOfEach/2 + offset,aabb2.mins.y+offsetDown);
			DrawText2D(startPosition,text,height,Rgba(255,0,0,255),aspectRatio,bitMapFont);
			break;
	}
}

void Renderer::DrawText2D(const Vector2& drawMins, const std::string& asciiText, float cellHeight, Rgba tint, float aspectScale /*= 1.f*/, const BitmapFont* font /*= nullptr */)
{
	DrawTextOnPoint(asciiText,(int)0,static_cast<int>(asciiText.length()),drawMins,static_cast<int>(cellHeight),Rgba::WHITE);
}

int g_openGlPrimitiveTypes[ NUM_PRIMITIVE_TYPES ] =
{
	GL_POINTS,			// called PRIMITIVE_POINTS		in our engine
	GL_LINES,			// called PRIMITIVE_LINES		in our engine
	GL_TRIANGLES,		// called PRIMITIVE_TRIANGES	in our engine
	GL_QUADS			// called PRIMITIVE_QUADS		in our engine
};

void Renderer::DrawMeshImmediate(const Vertex_3DPCU* verts, int numVerts, DrawPrimitiveType drawPrimitive, int v)
{
	switch (drawPrimitive)
	{
	case PRIMITIVE_POINTS:
		break;
	case PRIMITIVE_LINES:
		glBegin(GL_LINES);
		for (int index = 0; index < numVerts - 1; index++)
		{
			SetColor(verts->m_rgba);
			glVertex2f(verts->m_position.x, verts->m_position.y);
			verts++;
			SetColor((verts)->m_rgba);
			glVertex2f((verts)->m_position.x, (verts)->m_position.y);
		}
		break;
	case PRIMITIVE_TRIANGES:
		break;
	case PRIMITIVE_QUADS:
		glBegin(GL_QUADS);
		for (int index = 0; index < numVerts; index++)
		{
			SetColor(verts->m_rgba);
			glTexCoord2f(verts->m_uvs.x, verts->m_uvs.y);
			glVertex2f(verts->m_position.x, verts->m_position.y);
			verts++;
		}
		break;
	case NUM_PRIMITIVE_TYPES:
		break;
	default:
		break;
	}
	glEnd();
}

void Renderer::DrawMeshImmediate( const Vertex_3DPCU* vertexes, int numVertexes, DrawPrimitiveType primitiveType )
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glVertexPointer(	2, GL_FLOAT,			sizeof( Vertex_3DPCU ), &vertexes[ 0 ].m_position );
	glColorPointer(		4, GL_UNSIGNED_BYTE,	sizeof( Vertex_3DPCU ), &vertexes[ 0 ].m_rgba );
	glTexCoordPointer(	2, GL_FLOAT,			sizeof( Vertex_3DPCU ), &vertexes[ 0 ].m_uvs );

	GLenum glPrimitiveType = g_openGlPrimitiveTypes[ primitiveType ];
	glDrawArrays( glPrimitiveType, 0, numVertexes );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

