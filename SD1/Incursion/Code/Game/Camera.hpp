#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Core/Time.hpp"
#include "Engine/Math/MathUtil.hpp"

#include "Game/GameCommon.hpp"

class Camera
{
public:
	// VARIABLES
	Vector2			m_worldPosition;
	float			m_orientationDegrees			= 0;
	float			m_numTilesInViewVertically		= 0;
	float			m_numTilesInViewHorizontally	= 0;
	float			m_cameraRatio					= ASPECT_RATIO;
	float			m_tileWidth						= TILE_WIDTH;
	Vector2			m_positionVector;
	Vector2			m_minPosition;
	Vector2			m_maxPosition;

	float			m_currentTime;
	float			m_screenShakeTime;

	
	Camera();
	~Camera();
	void ResetCamera();
	void SetOrtographicPosition(Vector2 positionVector,Vector2 minsPosition,Vector2 maxPosition);
	void SetOrtographicPosition(Vector2 minPosition,Vector2 maxPosition);
	void SetDefaultOrthoPosition();
	void DoScreenShake(float time);
};