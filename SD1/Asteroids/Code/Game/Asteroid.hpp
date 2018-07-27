#pragma once
#include <vector>
/*\class  : App
* \group  : <GroupName>
* \brief  : Asteroid class creates and updates variable size random asteroids
* \TODO:  :
* \note   :
* \author : Rakhil Soman
* \version: 1.0
* \date   :
* \contact: srsrakhil@gmail.com
*/
class Asteroid
{
public:
	Disc2					m_disc2;
	int						m_numOfSides;
	float					m_startAngle;
	float					m_innRadius;
	Vector2					m_direction;
	float					m_changeInAngle;
	bool					m_isAlive = true;
	Vector2					m_prevPosition;
	int						m_top = 0;
	bool			    	m_debugMode = false;
	std::vector<Vector2>    m_points;

	Asteroid();
	Asteroid::~Asteroid();
	Asteroid(float ncentreX,float ncentreY,int nnumOfSides,float nstartAngle,float nradius,float ndirectionX,float ndirectionY,float nchangeInAngle);
	void Update(float deltaTime);
	void Render();
	void InitAsteroidPositions();
	void CheckIfPositionOutsideWorld();
	bool HasCollisionOccured(Disc2 entityDisk);
};
