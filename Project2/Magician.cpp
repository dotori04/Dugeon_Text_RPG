#include <iostream>
#include "Magician.h"
#include "Monster.h"
//
Magician::Magician(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level)
    : Player(name, hp, mp + 30, power, defense, exp, maxExp, level)
{
    job = "Magician";
}

void Magician::Attack(Monster* monster)
{
    std::cout << "Magician casts a powerful spell!" << std::endl;

    int damage = power - monster->GetDefense();
    if (damage <= 0)
    {
        damage = 1;
    }

    const int previousHP = monster->GetHP();
    std::cout << damage << " damage to " << monster->GetName() << "!" << std::endl;
    monster->TakeDamage(damage);
    std::cout << monster->GetName() << " HP : " << previousHP
        << " -> " << monster->GetHP() << std::endl;
}