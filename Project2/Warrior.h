#pragma once
#include "Player.h"

class Warrior : public Player
{
public:
	Warrior(std::string name, int hp, int mp, int power, int defense);
	void Attack() override;
};