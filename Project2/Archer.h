#pragma once
#include "Player.h"
#include <string>


class Archer : public Player
{
public:
	Archer(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level);
	void Attack(Monster* monster) override;
};