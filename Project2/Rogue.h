#pragma once
#include "Player.h"
#include <string>


class Rogue : public Player
{
public:
	Rogue(std::string name, int hp, int mp, int power, int defense);
	void Attack() override;
};