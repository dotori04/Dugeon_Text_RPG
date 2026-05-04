#pragma once
#include "Player.h"

class Warrior : public Player
{
public:
	Warrior(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level);
	void Attack(Monster* monster) override;
};
