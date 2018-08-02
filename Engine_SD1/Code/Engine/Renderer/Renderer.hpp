#pragma once
#include <unordered_map>

#include "Engine\Math\Vector2.hpp"
#include "Engine\Math\AABB2.hpp"
#include "Engine\Math\IntVector2.hpp"
#include "Engine\Core\Rgba.hpp"
#include "Engine\Core\Vertex.hpp"
#include "Engine\Renderer\Texture.hpp"
#include "Engine\Renderer\BitmapFont.hpp"


enum DrawPrimitiveType
{
	PRIMITIVE_POINTS,		// in OpenGL, for example, this becomes GL_POINTS
	PRIMITIVE_LINES,		// in OpenGL, for example, this becomes GL_LINES
	PRIMITIVE_TRIANGES,		// in OpenGL, for example, this becomes GL_TRIANGLES
	PRIMITIVE_QUADS,		// in OpenGL, for example, this becomes GL_QUADS
	NUM_PRIMITIVE_TYPES
};

enum TextDrawMode
{
	TEXT_DRAW_SHRINK_TO_FIT,
	TEXT_DRAW_WORD_WRAP1,
	TEXT_DRAW_WORD_WRAP,
	TEXT_DRAW_OVERRUN
};

class BitmapFont;
class Renderer
{

public:
	Vector2 m_topRight;
	Vector2 m_bottomLeft;
	SpriteSheet *fontSheet = nullptr;
	std::map< std::string, BitmapFont* > m_loadedFonts;
	std::map< std::string, Texture *> m_textureMap;

	Renderer();
	~Renderer();
	
	void BeginFrame();
	void EndFrame();
	void ClearScreen();
	
	// TEXTURE OPENGL FUNCTIONS
	void EnableTexture();
	void BindTexture(Texture *texture);
	void DisableTexture();
	void EnableAdditiveBlending();
	void DisableAdditiveBlending();
	
	// FUNCTIONS FOR CHANGING AXIS
	void SetOrthoPosition(Vector2 mins,Vector2 maxs);
	void SetOrtho( const Vector2& bottomLeft, const Vector2& topRight );
	void PushMatrix();
	void PopMatrix();
	void Scale(float scaleX, float scaleY);
	void ScaleUniform( float uniformScale );
	void Translate( const Vector2& translation );
	void Rotate( float degrees );
	void MatrixMode();

	void SetColor(float R, float G, float B);
	void SetColor(Rgba rgba);

	// FUNCTION TO DRAW LINES,LINE ARRAYS AND POINTS
	void DrawLines(Vector2 *pointArray,int length);
	void DrawLines(Vector2 *pointArray,int length,bool skip);
	void DrawLines(Vector2 point1, Vector2 point2, int length, bool skip);
	void DrawLines(std::vector<Vector2>& points,Rgba rgba,bool skip);

	void DrawLine(Vector2 *point1,Vector2 *point2);
	void DrawLine(Vector2 point1,Vector2 point2,Rgba rgba);
	void DrawLine(Vector2 point1,Vector2 point2);
	void DrawFeatheredLine(Vector2 point1,Vector2 point2,Rgba startColor,Rgba finalColor);
	void DrawLine(float x1,float y1,float x2,float y2);
	
	// FUNCTION TO DRAW CIRCLE
	void DrawDottedCircle(float centreX,float centreY,float radius);
	void DrawCircle(float centreX,float centreY,float nradius);
	void DrawCircle(Vector2 centre,float nradius);
	void DrawCircle(float centreX,float centreY,float nradius,int numofSize);
	
	// FUNCTION TO DRAW RECTANGLE
	void DrawRectangle(float centreX,float centreY,float legnth,float bredth,float angle);
	void DrawRectangle(float x1,float y1,float x2,float y2);
	void DrawSolidRectangle(float x1, float y1, float x2, float y2);

	Texture   * CreateOrGetTexture(const std::string& imageFilePath);
	Texture   * CreateOrGetTexture(const std::string& imageFilePath,bool shouldStore);
	BitmapFont* CreateOrGetBitmapFont( const char* bitmapFontName );

	// FUNCTION TO DRAW - AABB
	void DrawTexturedAABB( const AABB2& bounds, const Texture *texture,const Vector2& texCoordsAtMins, const Vector2& texCoordsAtMaxs, const Rgba& tint ); 
	void DrawAABB( const AABB2& bounds, const Rgba& color );
	void DrawAABB( const AABB2& bounds, const Rgba& color1,const Rgba& color2 );

	// FUNCTIONS TO DRAW TEXT
	void DrawTextOnPoint(char value[],int start,int length, Vector2 pos,int height);
	void DrawTextOnPoint(char value[],int start,int length, Vector2 pos,float height,Rgba rgba);
	void DrawTextOnPoint(std::string str,int start,int length, Vector2 pos,float height,Rgba rgba);
	void DrawInt(int value, Vector2 pos,int height);

	// FUNCTIONS TO CREATE TEXT INSIDE A BOX
	void DrawText2D( const Vector2& drawMins,const std::string& asciiText,float cellHeight,Rgba tint,float aspectScale = 1.f, const BitmapFont* font = nullptr );
	void DrawTextInBox2D(AABB2 aabb2,std::string text,float aspectRation,float height,Vector2 alignment,TextDrawMode drawMode);

	// DRAWING USING DRAWARRAYS
	void Renderer::DrawMeshImmediate( const Vertex_3DPCU* verts, int numVerts, DrawPrimitiveType drawPrimitive );

	// DRAWING WITHOU DRAWARRAYS
	void Renderer::DrawMeshImmediate( const Vertex_3DPCU* verts, int numVerts, DrawPrimitiveType drawPrimitive,int mode);
};