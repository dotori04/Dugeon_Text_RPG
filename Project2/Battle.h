#pragma once

class Player;
class Monster;
struct Item;

class Battle
{
public:
    static bool Start(Player& player, Monster& monster, Item& droppedItem);

private:
    static void PlayerTurn(Player& player, Monster& monster);
    static void MonsterTurn(Player& player, Monster& monster);
    static int CalculateDamage(int attackPower, int defense);

};