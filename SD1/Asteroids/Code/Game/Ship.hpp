#pragma once
#include <vector>
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Disc2.hpp"

class Ship
{
public:
	bool				 m_isPlayerShip						= false;
	bool				 m_isAlive							= true;
	bool				 m_debugMode						= false;
	float				 m_health							= 5;
	
	Disc2				 m_disc2;
	Vector2				 m_forward;
	float				 m_innRadius						= 0.f;
	float				 m_angle							= 0.f;
	bool				 m_hasTail							= false;
	int					 m_rotationDirection				= 0;
	float				 m_angularVelocity					= 20.f;
	int					 m_flickeringValue					= 0;

	bool				 m_destroyStarted					= false;
	bool				 m_destroyEnded						= false;
	int					 m_destroyCount						= 0;
	
	float				 m_speed;
	std::vector<Vector2> m_posPositions;
	int					 m_lastBulletFiredTime			    = 0;


	Ship();
	~Ship();

	void		Update(float deltaTime);
	void		Render();

	void		ReduceHealth();
	void		ApplyLinearAcceleration(float MAX_SPEED,float deltaTime);
	void		ApplyAngularAcceleration(int direction);
	Vector2		GetNosePosition();
	void		CheckAndSetPositionInsideBounds();
	void		UpdateDestructionPoints(float deltaTime);
	bool		HasCollisionOccured(Disc2 entityDisc2);
};
