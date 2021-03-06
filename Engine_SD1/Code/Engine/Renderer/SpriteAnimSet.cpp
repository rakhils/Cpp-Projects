#include "SpriteAnimSet.hpp"

SpriteAnimSet::SpriteAnimSet(SpriteAnimSetDefinition *spriteAnimationSetDef)
{
	m_spirteAnimSetDef = spriteAnimationSetDef;
	Renderer *render   = new Renderer();
	const std::string imageFilePath = "Data/Images/"+m_spirteAnimSetDef->m_spriteSheetFileName;
	const Texture *texture   = render->CreateOrGetTexture(imageFilePath);
	SpriteSheet *spriteSheet = new SpriteSheet(*texture,m_spirteAnimSetDef->m_spriteLayout.x,m_spirteAnimSetDef->m_spriteLayout.y);


	std::map<std::string,SpriteAnimationDefinition*> spriteAnimMap =  m_spirteAnimSetDef->m_spriteAnimationDefinition;
	std::map<std::string,SpriteAnimationDefinition*>::iterator it  =  spriteAnimMap.begin();
	while(it!=spriteAnimMap.end())
	{
		std::string name = it->first;
		SpriteAnimationDefinition* spriteAnimDef = it->second;
		std::vector<int> spriteIndex = spriteAnimDef->m_spriteIndexes;
		SpriteAnimation *spriteAnimation = new SpriteAnimation(spriteSheet,3,spriteIndex);
		m_spriteAnimation.insert(std::map<std::string,SpriteAnimation*>::value_type(name,spriteAnimation));
		spriteAnimation->m_name = name;
		it++;
	}
	m_currentAnimation = m_spriteAnimation["Idle"];
	delete render;
}

SpriteAnimSet::SpriteAnimSet()
{

}

//////////////////////////////////////////////////////////////
//@purpose : Destructor
//////////////////////////////////////////////////////////////

SpriteAnimSet::~SpriteAnimSet()
{

}

void SpriteAnimSet::SetAnimation(std::string name)
{
	if(m_spriteAnimation[name] != nullptr)
	{
		m_currentAnimation = m_spriteAnimation[name];
	}
}

//////////////////////////////////////////////////////////////
/*DATE    : 2018/02/25
*@purpose : Returns the current playing animation
*
*@param   : NIL
*
*@return  : NIL
*/
//////////////////////////////////////////////////////////////
std::string SpriteAnimSet::GetCurrentAnimationByName()
{
	return m_currentAnimation->m_name;
}

void SpriteAnimSet::update(float deltaTime)
{
	m_currentAnimation->Update(deltaTime);
}

AABB2 SpriteAnimSet::GetCurrentUVs() const
{
	return m_currentAnimation->GetCurrentTexCoords();
}
