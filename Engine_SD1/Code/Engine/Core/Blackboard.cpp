#include "Blackboard.hpp"

void Blackboard::PopulateFromXmlElementAttributes(const XMLElement& element)
{
	std::string name = element.GetText();
}

//////////////////////////////////////////////////////////////////////////
//@purpose : Inserting value into map
void Blackboard::SetValue(const std::string& keyName, const std::string& newValue)
{
	m_keyValuePairs.insert(std::map<std::string,std::string>::value_type(keyName,newValue));
}

bool Blackboard::GetValue(const std::string& keyName, bool defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		if(value.compare("true"))
		{
			return true;
		}
		return false;
	}
	return defaultValue;
}

int Blackboard::GetValue(const std::string& keyName, int defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		return stoi(value);
	}
	return defaultValue;
}

IntRange Blackboard::GetValue(const std::string& keyName, const IntRange& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		IntRange intR;
		intR.SetFromText(value.c_str());
		return intR;
	}
	return defaultValue;
}

FloatRange Blackboard::GetValue(const std::string& keyName, const FloatRange& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		FloatRange flR;
		flR.SetFromText(value.c_str());
		return flR;
	}
	return defaultValue;
}

IntVector2 Blackboard::GetValue(const std::string& keyName, const IntVector2& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		IntVector2 intV;
		intV.SetFromText(value.c_str());
		return intV;
	}
	return defaultValue;
}

float Blackboard::GetValue(const std::string& keyName, float defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		return stof(value);
	}
	return defaultValue;
}

std::string Blackboard::GetValue(const std::string& keyName, std::string defaultValue) const
{

	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		return value;
	}
	return defaultValue;
}

std::string Blackboard::GetValue(const std::string& keyName, const char* defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		return value;
	}
	std::string returnValue;
	returnValue.append(defaultValue);
	return returnValue;
}

Rgba Blackboard::GetValue(const std::string& keyName, const Rgba& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		Rgba rgba;
		rgba.SetFromText(value.c_str());
		return rgba;
	}
	return defaultValue;
}

Vector2 Blackboard::GetValue(const std::string& keyName, const Vector2& defaultValue) const
{
	std::map<std::string,std::string>::const_iterator iter = m_keyValuePairs.find(keyName);
	if(iter!=m_keyValuePairs.end())
	{
		std::string value = iter->first;
		Vector2 vector2;
		vector2.SetFromText(value.c_str());
		return vector2;
	}
	return defaultValue;
}
