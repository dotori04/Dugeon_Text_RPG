#include "Warrior.h"
#include <iostream>

Warrior::Warrior(std::string name, int hp, int mp, int power, int defense)
    : Player(name, hp + 30, mp, power, defense)
{
    job = "Warrior";
}

void Warrior::Attack()
{
    std::cout << "Warrior attacks with a sword!" << std::endl;
}