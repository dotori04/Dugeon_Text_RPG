#pragma once
#include "Player.h"
#include <string>

class Magician : public Player
{
public:
	Magician(std::string name, int hp, int mp, int power, int defense);
	void Attack() override;
};