#pragma once
#include <string>
#include <typeinfo>

class Item
{
public:
	void setName(std::string name)
	{
		m_name = name;
	};

	void defaultName() {
		m_name = typeid(this).name();
	};

	std::string getname() {
		return m_name;
	}
protected:
		std::string m_name;
};

