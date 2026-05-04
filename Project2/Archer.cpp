#include "Archer.h"
#include <iostream>
#include "Monster.h"


Archer::Archer(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level) 
    : Player(name, hp, mp, power, defense + 30, exp, maxExp, level)

    {
        job = "Archer";
    }

void Archer::Attack(Monster* monster)
{
    std::cout << "Archer shoots a precise arrow!" << std::endl;

    int damage = (power - monster->GetDefense()) / 3;
    if (damage <= 0)
    {
        damage = 1;
    }

    for (int i = 0; i < 3; i++)
    {
        int previousHP = monster->GetHP();
        std::cout << damage << " damage to " << monster->GetName() << "!" << " (" << i + 1 << "/3)" << std::endl;
        monster->TakeDamage(damage);
		std::cout << monster->GetName() << " HP : " << previousHP
            << " -> " << monster->GetHP() << std::endl;
        if(monster->GetHP() <= 0)
        {
            break;
		}
    }
}
//