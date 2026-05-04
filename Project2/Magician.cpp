#include <iostream>
#include "Magician.h"
//
Magician::Magician(std::string name, int hp, int mp, int power, int defense)
    : Player(name, hp, mp + 30, power, defense)
{
    job = "Magician";
}

void Magician::Attack()
{
    std::cout << "Magician casts a powerful spell!" << std::endl;
}
