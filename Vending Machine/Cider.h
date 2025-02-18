#pragma once
#include <iostream>
#include "Item.h"

class Cider : public Item
{
public:
	Cider() {
		setName("Cider");
		std::cout << "name = " << m_name << std::endl;
	}
};

