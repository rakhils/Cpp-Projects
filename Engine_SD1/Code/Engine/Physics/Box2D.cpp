#include "Engine/Physics/Box2D.hpp"

// CONSTRUCTOR
Box2D::Box2D()
{

}

// DESTRUCTOR
Box2D::~Box2D()
{

}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : returns normal vector
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
Vector2 Box2D::GetNormalVector()
{
	return m_normal;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : retrns normal velocity
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
Vector2 Box2D::GetNormalVelocity()
{
	return m_velocity;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : returns current position
*
*@param   : NIL
*
*@return  : Position vector
*/
//////////////////////////////////////////////////////////////
Vector2 Box2D::GetPosition()
{
	return m_position;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : Sets the position of Box2D
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Box2D::SetPosition(Vector2 position)
{
	m_position = position;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : Aplly force in normal direction
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Box2D::ApplyForce(float value)
{
	ApplyForce(m_normal.GetNormalized(),value);
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : Apply force in specific direction
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Box2D::ApplyForce(Vector2 forceAxis, float value)
{
	m_acceleration = forceAxis*value/m_mass;
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/09
*@purpose : NIL
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
void Box2D::Update(float deltaTime)
{
	m_position += m_velocity*deltaTime;
	m_velocity += m_acceleration*deltaTime - m_velocity*m_friction;
	m_mesh = AABB2(m_position,0.2f,0.2f);
}
