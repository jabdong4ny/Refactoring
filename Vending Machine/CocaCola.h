#pragma once
#include <iostream>
#include "Item.h"
class CocaCola : public Item
{
public:
	CocaCola() {
		setName("CocaCola");
		std::cout << "name = " << m_name << std::endl;
	}
};

