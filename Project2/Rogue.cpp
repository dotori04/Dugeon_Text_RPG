#include <iostream>
#include "Rogue.h"
#include "Monster.h"

Rogue::Rogue(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level)
    : Player(name, hp, mp, power + 30, defense, exp, maxExp, level)
{
    job = "Rogue";
}

void Rogue::Attack(Monster* monster)
{
    std::cout << "Warrior attacks with a sword!" << std::endl;

    int damage = (power - monster->GetDefense())/5;
    if (damage <= 0)
    {
        damage = 1;
    }

    for (int i = 0; i < 5; i++)
    {
    int previousHP = monster->GetHP();
        std::cout << damage << " damage to " << monster->GetName() << "!" << " (" << i + 1 << "/5)" << std::endl;
        monster->TakeDamage(damage);
        std::cout << monster->GetName() << " HP : " << previousHP
            << " -> " << monster->GetHP() << std::endl;
        //previousHP = monster->GetHP();
        if(monster->GetHP() <= 0)
        {
            break;
		}
    }
}