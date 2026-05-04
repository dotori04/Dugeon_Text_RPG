#pragma once

#include <string>
#include <iostream>

struct Item
{
	std::string name;
	int price = 0;
	void PrintInfo() const
	{
		std::cout << name << " (" << price << "G)" << std::endl;
	}
};