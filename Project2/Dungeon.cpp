#include "Dungeon.h"
#include "Battle.h"
#include "Monster.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

struct DungeonRoom
{
    MonsterInfo monsterInfo;
    bool isCleared;
};


bool EnterDungeon(Player& player, Inventory<Item>& inventory)
{
    const int bossIndex = MONSTER_TABLE_COUNT - 1;

    vector<DungeonRoom> rooms;
    for (int i = 0; i < bossIndex; ++i)
    {
        rooms.push_back({ MONSTER_TABLE[i], false });
    }

    cout << "[ Dungeon Floor 1 ]" << endl;

    for (int i = 0; i < static_cast<int>(rooms.size()); ++i)
    {   
        const string roomHeader = "Room " + to_string(i + 1) + ": " + rooms[i].monsterInfo.name;
        cout << roomHeader << endl;

        Monster monster = Monster::CreateMonsterFromInfo(rooms[i].monsterInfo);
        Item droppedItem;

        bool isWin = Battle::Start(player, monster, droppedItem, inventory, roomHeader);
        if (!isWin)
        {
            cout << "=== GAME OVER! ===" << endl;
            return true;
        }

        rooms[i].isCleared = true;
        inventory.AddItem(droppedItem);
        cout << roomHeader << " -> Clear!" << endl;
    }

	cout << "Boss Room Unlocked!" << endl;

    const MonsterInfo& bossInfo = MONSTER_TABLE[bossIndex];
    const string bossHeader = "Boss Room: " + bossInfo.name;
	Monster boss = Monster::CreateMonsterFromInfo(bossInfo);
    Item droppedItem;

	bool isBossWin = Battle::Start(player, boss, droppedItem, inventory, bossHeader);
    if (isBossWin)
    {
		cout << "=== CONGRATULATIONS! You have cleared the dungeon! ===" << endl;
        return false;
    }
    else
    {
        cout << "=== GAME OVER! ===" << endl;
		return true;
    }
}
