#include "Archer.h"
#include <iostream>


Archer::Archer(std::string name, int hp, int mp, int power, int defense)
    : Player(name, hp, mp, power, defense + 30)
{
    job = "Archer";
}

void Archer::Attack()
{
    std::cout << "Archer shoots a precise arrow!" << std::endl;
}
//