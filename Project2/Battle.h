#pragma once
#include <string>

class Player;
class Monster;
template <typename Inven>
class Inventory;
struct Item;

class Battle
{
public:
    static bool Start(Player& player, Monster& monster, Item& droppedItem, Inventory<Item>& inventory,
        const std::string& battleHeader = "");

private:
    static void PlayerTurn(Player& player, Monster& monster, Inventory<Item>& inventory, const std::string& battleHeader);
    static void MonsterTurn(Player& player, Monster& monster, const std::string& battleHeader);
    static bool UsePotion(Player& player, Inventory<Item>& inventory);
    static int CalculateDamage(int attackPower, int defense);

};
