#include "Camera.hpp"

Camera::Camera()
{
	m_numTilesInViewVertically = TILES_VIEWED_VERTICALLY;
	m_numTilesInViewHorizontally = m_cameraRatio*m_numTilesInViewVertically;
}

Camera::~Camera()
{

}

void Camera::ResetCamera()
{
	m_numTilesInViewVertically = TILES_VIEWED_VERTICALLY;
	m_numTilesInViewHorizontally = m_cameraRatio*m_numTilesInViewVertically;
}

void Camera::SetOrtographicPosition(Vector2 positionVector,Vector2 minsPosition,Vector2 maxPosition)
{
	this->m_positionVector = positionVector;

	float minX = minsPosition.x + m_numTilesInViewHorizontally;
	float minY = minsPosition.y + m_numTilesInViewVertically;

	float maxX = maxPosition.x - m_numTilesInViewHorizontally;
	float maxY = maxPosition.y - m_numTilesInViewVertically;

	positionVector.x = ClampFloat(positionVector.x,minX,maxX);
	positionVector.y = ClampFloat(positionVector.y,minY,maxY);
	m_positionVector = positionVector;
	Vector2 minPosition1(positionVector.x - (m_numTilesInViewHorizontally) , positionVector.y - (m_numTilesInViewVertically));
	Vector2 maxPosition1(positionVector.x + (m_numTilesInViewHorizontally) , positionVector.y + (m_numTilesInViewVertically));
	m_minPosition = minPosition1;
	m_maxPosition = maxPosition1;
	g_theRenderer->SetOrthoPosition(minPosition1,maxPosition1);
	
}

void Camera::SetOrtographicPosition(Vector2 minPosition,Vector2 maxPosition)
{
	m_positionVector = (minPosition+maxPosition)/2;
	g_theRenderer->SetOrthoPosition(minPosition,maxPosition);
}

void Camera::SetDefaultOrthoPosition()
{
	g_theRenderer->SetOrthoPosition(m_minPosition,m_maxPosition);
}

void Camera::DoScreenShake(float time)
{
	m_currentTime = static_cast<float>(GetCurrentTimeSeconds());
	m_screenShakeTime = time;
}


