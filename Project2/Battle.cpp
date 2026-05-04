#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>

using namespace std;

bool Battle::Start(Player& player, Monster& monster, Item& droppedItem)
{
    cout << "[Battle Start!] " << player.GetName()
        << "(" << player.GetJob() << ") vs " << monster.GetName() << endl;
    monster.PrintStatus();

    while (player.GetHP() > 0 && !monster.IsDead())
    {
        PlayerTurn(player, monster);

        if (monster.IsDead())
        {
            break;
        }

        MonsterTurn(player, monster);
    }

    if (player.GetHP() <= 0)
    {
        cout << "* Defeat..." << endl;
        return false;
    }

    droppedItem.name = monster.GetDropItemName();
    droppedItem.price = monster.GetDropItemPrice();

    cout << "* Victory!" << endl;
    cout << "->Got : " << droppedItem.name << "!" << endl;
    return true;
}

void Battle::PlayerTurn(Player& player, Monster& monster)
{
    player.Attack();
    const int damage = CalculateDamage(player.GetPower(), monster.GetDefense());
    const int previousHP = monster.GetHP();

    cout << damage << " damage to " << monster.GetName() << "!" << endl;
    monster.TakeDamage(damage);
    cout << monster.GetName() << " HP : " << previousHP
        << " -> " << monster.GetHP() << endl;
}

void Battle::MonsterTurn(Player& player, Monster& monster)
{
    cout << "-- - Monster Turn-- -" << endl;
    const int damage = CalculateDamage(monster.GetPower(), player.GetDefense());
    const int previousHP = player.GetHP();

    cout << monster.GetName() << " attacks!" << endl;
    cout << damage << " damage to " << player.GetName() << "!" << endl;
    player.SetHP(player.GetHP() - damage);
    cout << player.GetName() << " HP : " << previousHP
        << " -> " << player.GetHP() << endl;
}

int Battle::CalculateDamage(int attackPower, int defense)
{
    int damage = attackPower - defense;

    if (damage < 0)
    {
        damage = 1;
    }

    return damage;
}
