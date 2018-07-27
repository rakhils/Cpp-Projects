#pragma once
/*\class  : App
* \group  : <GroupName>
* \brief  : Asteroid class to create and manage asteroids 
* \TODO:  :
* \note   :
* \author : Rakhil Soman
* \version: 1.0
* \date   :
* \contact: srsrakhil@gmail.com
*/
#include "Engine/Math/Disc2.hpp"
#include "Engine/Math/Vector2.hpp"
class Bullet
{
	
public :
	Disc2   m_disc2;
	float   m_angle				= 0.f;
	float   m_velocity			= 10.f;
	long    m_timeFromstart		= 0;
	bool    m_isAlive			= true;
	bool    m_debugMode			= false;
	float   m_timeToLive		= 0;
	Vector2 velocityVect;

	Bullet::Bullet();
	Bullet::Bullet(float centreX,float centreY,float angle,float velocity,float timeToLive); 

	void Render();
	void Update(float deltaTime);
	void CheckIfBoundsOutsideWorld();
	bool HasCollisionOccured(Disc2 disc);
};