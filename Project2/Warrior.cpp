#include "Warrior.h"
#include "Monster.h"
#include <iostream>

Warrior::Warrior(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level)
    : Player(name, hp + 30, mp, power, defense, exp, maxExp, level)
{
    job = "Warrior";
}

void Warrior::Attack(Monster* monster)
{
    std::cout << "Warrior attacks with a sword!" << std::endl;

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
