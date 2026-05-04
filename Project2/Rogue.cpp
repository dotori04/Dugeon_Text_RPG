#include <iostream>
#include "Rogue.h"


Rogue::Rogue(std::string name, int hp, int mp, int power, int defense)
    : Player(name, hp, mp, power + 30, defense)
{
    job = "Rogue";
}

void Rogue::Attack()
{
    std::cout << "Rogue strikes swiftly with daggers!" << std::endl;
}