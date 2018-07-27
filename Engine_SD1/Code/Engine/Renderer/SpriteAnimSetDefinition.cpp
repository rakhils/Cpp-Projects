#include "SpriteAnimSetDefinition.hpp"

SpriteAnimSetDefinition::SpriteAnimSetDefinition()
{
	m_spriteSheetFileName = "";
	m_spriteLayout = IntVector2(0,0);
}

SpriteAnimSetDefinition::SpriteAnimSetDefinition(XMLElement& element)
{
	//<SpriteAnimSet spriteSheet = "player/BODY1.png" spriteLayout = "13,21">
		//<SpriteAnim name = "WalkSouth"      spriteIndexes = "130,131,132,133,134,135,136,137,138" / >
	//<SpriteAnimSet spriteSheet = "player/BODY1.png" spriteLayout = "13,21">
	
	m_spriteSheetFileName = ParseXmlAttribute(element,"spriteSheet",m_spriteSheetFileName);
	m_spriteLayout		  = ParseXmlAttribute(element,"spriteLayout",m_spriteLayout);
}

SpriteAnimationDefinition* SpriteAnimSetDefinition::getSpriteAnimationDefinition(std::string name)
{
	std::map<std::string,SpriteAnimationDefinition*>::iterator it;
	it = m_spriteAnimationDefinition.find(name);
	return it->second;
}

