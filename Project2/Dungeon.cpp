#include "Dungeon.h"
#include "Battle.h"
#include "Monster.h"
#include "Item.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace
{
    struct DungeonRoom
    {
        MonsterInfo monsterInfo;
        bool isCleared;
    };

    int GetBossIndex()
    {
        return MONSTER_TABLE_COUNT - 1;
    }

    vector<DungeonRoom> CreateDungeonRooms()
    {
        vector<DungeonRoom> rooms;
        const int bossIndex = GetBossIndex();

        for (int i = 0; i < bossIndex; ++i)
        {
            rooms.push_back({ MONSTER_TABLE[i], false });
        }

        return rooms;
    }

    string BuildRoomHeader(int roomIndex, const MonsterInfo& monsterInfo)
    {
        return "Room " + to_string(roomIndex + 1) + ": " + monsterInfo.name;
    }

    bool RunBattle(Player& player, Inventory<Item>& inventory, const MonsterInfo& monsterInfo,
        const string& battleHeader, bool addDropItem)
    {
        Monster monster = Monster::CreateMonsterFromInfo(monsterInfo);
        Item droppedItem;

        const bool isWin = Battle::Start(player, monster, droppedItem, inventory, battleHeader);
        if (isWin && addDropItem)
        {
            inventory.AddItem(droppedItem);
        }

        return isWin;
    }
}

DungeonResult EnterDungeon(Player& player, Inventory<Item>& inventory)
{
    vector<DungeonRoom> rooms = CreateDungeonRooms();

    cout << "[ Dungeon Floor 1 ]" << endl;

    for (int i = 0; i < static_cast<int>(rooms.size()); ++i)
    {
        const string roomHeader = BuildRoomHeader(i, rooms[i].monsterInfo);
        cout << roomHeader << endl;

        const bool isWin = RunBattle(player, inventory, rooms[i].monsterInfo, roomHeader, true);
        if (!isWin)
        {
            cout << "=== GAME OVER! ===" << endl;
            return DungeonResult::ReturnToMenu;
        }

        rooms[i].isCleared = true;
        cout << roomHeader << " -> Clear!" << endl;
        int choice = -1;
        while(1)
        {
            cout << "1. Continue to next room" << endl;
            cout << "2. Return to menu" << endl;
            cout << "Choose: ";
            cin >> choice;
            cout << endl;
            if (choice == 1)
            {
                break;
            }
            else if (choice == 2)
            {
                cout << "You have returned to the menu." << endl;
				return DungeonResult::ReturnToMenu;
            }
            cout << "Invalid choice. Please select a valid option." << endl;
		}
    }

	cout << "Boss Room Unlocked!" << endl;

    const MonsterInfo& bossInfo = MONSTER_TABLE[GetBossIndex()];
    const string bossHeader = "Boss Room: " + bossInfo.name;
    if (RunBattle(player, inventory, bossInfo, bossHeader, false))
    {
		cout << "=== CONGRATULATIONS! You have cleared the dungeon! ===" << endl;
        return DungeonResult::GameClear;
    }

    cout << "=== GAME OVER! ===" << endl;
    return DungeonResult::ReturnToMenu;
}
