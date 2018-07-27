#pragma once
#include "Engine/Math/AABB2.hpp"

/*\class  : Box2D
*		   
* \group  : <GroupName>
*		   
* \brief  :
*		   
* \TODO:  :
*		   
* \note   :
*		   
* \author : Rakhil Soman
*		   
* \version: 1.0
*		   
* \date   : 2/9/2018 5:58:00 PM
*
* \contact: srsrakhil@gmail.com
*/
 
class Box2D
{

public:
	//Member_Variables
	AABB2 m_mesh;
	float m_mass = 50.0f;
	float m_friction = 0.01f;
	Vector2 m_position;
	Vector2 m_normal;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	
	//Static_Member_Variables


	//Methods
	Box2D();
	~Box2D();

	Vector2 GetNormalVector();
	Vector2 GetLateralVelocity();
	Vector2 GetNormalVelocity();
	Vector2 GetPosition();

	void SetPosition(Vector2 position);
	void TurnTowards(Vector2 vector);

	void ApplyForce(float value);
	void ApplyForce(Vector2 forceAxis,float value);
	void ApplyFriction(float frictionValue);

	void Update(float deltaTime);

	
	
	//Static_Methods

protected:
	//Member_Variables

	//Static_Member_Variables

	//Methods

	//Static_Methods

private:
	//Member_Variables

	//Static_Member_Variables

	//Methods

	//Static_Methods

};