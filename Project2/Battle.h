#pragma once

class Player;
class Monster;
template <typename Inven>
class Inventory;
struct Item;

class Battle
{
public:
    static bool Start(Player& player, Monster& monster, Item& droppedItem, Inventory<Item>& inventory);

private:
    static void PlayerTurn(Player& player, Monster& monster, Inventory<Item>& inventory);
    static void MonsterTurn(Player& player, Monster& monster);
    static bool UsePotion(Player& player, Inventory<Item>& inventory);
    static int CalculateDamage(int attackPower, int defense);

};