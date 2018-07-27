#pragma once
#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Rgba.hpp"

struct Vertex_3DPCU 
{
public:
	
	Rgba m_rgba;
	Vector2 m_uvs;
	Vector2 m_position;

	Vertex_3DPCU(){};
	Vertex_3DPCU(Vector2 point)
	{
		m_position = point;
	}
	void setPoint(Vector2 point)
	{
		m_position = point;
	}
	void setPoint(float x,float y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void setRGBA(Rgba rgba)
	{
		m_rgba = rgba;
	}

	void setUV(Vector2 uv)
	{
		m_uvs = uv;
	}
};
