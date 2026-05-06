#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Inventory.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

namespace
{
    void ClearConsole()
    {
        system("cls");
    }

    string BuildAnimationTitle(const string& battleHeader, const string& message)
    {
        return battleHeader.empty()
            ? message
            : battleHeader + "\n" + message;
    }

    void PlayMonsterAnimation(const Monster& monster, const string& title)
    {
        const int playCount = monster.GetAsciiFrameCount() * 2;

        for (int i = 0; i < playCount; ++i)
        {
            ClearConsole();
            cout << title << endl;
            cout << monster.GetAsciiFrame(i) << endl;
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(180));
        }
    }

    void PlayMonsterAnimationWithBattleLog(const Monster& monster, const string& battleLog)
    {
        const int playCount = monster.GetAsciiFrameCount() * 2;

        for (int i = 0; i < playCount; ++i)
        {
            ClearConsole();
            cout << battleLog;
            cout << endl;
            cout << monster.GetAsciiFrame(i) << endl;
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(180));
        }
    }

    void PrintMonsterAscii(const Monster& monster)
    {
        cout << monster.GetAsciiFrame(0) << endl;
        cout << endl;
    }
}

bool Battle::Start(Player& player, Monster& monster, Item& droppedItem, Inventory<Item>& inventory,
    const string& battleHeader)
{
    PlayMonsterAnimation(monster, BuildAnimationTitle(battleHeader, "A monster appeared!"));

    if (!battleHeader.empty())
    {
        cout << battleHeader << endl;
    }

    cout << "[Battle Start!] " << player.GetName()
        << "(" << player.GetJob() << ") vs " << monster.GetName() << endl;
    PrintMonsterAscii(monster);
    monster.PrintStatus();

    while (player.GetHP() > 0 && !monster.IsDead())
    {
        PlayerTurn(player, monster, inventory, battleHeader);

        if (monster.IsDead())
        {
            break;
        }

        MonsterTurn(player, monster, battleHeader);
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
    player.SetExp(30);
    cout << "EXP: " << player.GetExp() << " / " << player.GetMaxExp() << endl;
    player.levelUp();
    
    return true;
}

void Battle::PlayerTurn(Player& player, Monster& monster, Inventory<Item>& inventory, const string& battleHeader)
{
    bool isTurnFinished = false;

    while (!isTurnFinished)
    {
		cout << monster.GetName() << " HP: " << monster.GetHP() << endl;
        cout << "-- - Player Turn-- -" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Item" << endl;
        cout << "Choose: ";

        int choice = -1;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            ostringstream attackLogStream;
            streambuf* originalCoutBuffer = cout.rdbuf(attackLogStream.rdbuf());

            player.Attack(&monster);

            cout.rdbuf(originalCoutBuffer);

            const string attackLog =
                (battleHeader.empty() ? "" : battleHeader + "\n")
                + "-- - Player Turn-- -\n"
                "1. Attack\n"
                "2. Use Item\n"
                "Choose: 1\n\n"
                + attackLogStream.str();

            PlayMonsterAnimationWithBattleLog(monster, attackLog);
            isTurnFinished = true;
            break;
        }
        case 2:
            isTurnFinished = UsePotion(player, inventory);
            break;
        default:
            cout << "Invalid choice. Please select a valid battle menu." << endl;
            break;
        }
    }
}

void Battle::MonsterTurn(Player& player, Monster& monster, const string& battleHeader)
{
    cout << "-- - Monster Turn-- -" << endl;
    PlayMonsterAnimation(monster, BuildAnimationTitle(battleHeader, monster.GetName() + " attacks!"));

    const int damage = CalculateDamage(monster.GetPower(), player.GetDefense());
    const int previousHP = player.GetHP();

    cout << monster.GetName() << " attacks!" << endl;
    cout << damage << " damage to " << player.GetName() << "!" << endl;
    player.SetHP(player.GetHP() - damage);
    cout << player.GetName() << " HP : " << previousHP
        << " -> " << player.GetHP() << endl;
}

bool Battle::UsePotion(Player& player, Inventory<Item>& inventory)
{
    cout << "[ Item ]" << endl;
    inventory.PrintInventory();
    cout << "0. Back" << endl;
    cout << "Choose item number: ";

    int itemIndex = -1;
    cin >> itemIndex;
    cout << endl;

    if (itemIndex == 0)
    {
        return false;
    }

    const Item* selectedItem = inventory.GetItemAt(itemIndex);
    if (selectedItem == nullptr)
    {
        cout << "* Invalid item number." << endl;
        return false;
    }

    const string itemName = selectedItem->name;

    if (itemName == "HP Potion")
    {
        const int previousHP = player.GetHP();
        player.SetHP(min(player.GetHP() + 50, player.GetMaxHP()));
        inventory.RemoveItemAt(itemIndex);

        cout << "* Used HP Potion." << endl;
        cout << player.GetName() << " HP : " << previousHP
            << " -> " << player.GetHP() << endl;
		inventory.AddItem(Item{ "Empty "+itemName, 0});
        return true;
    }

    if (itemName == "MP Potion")
    {
        const int previousMP = player.GetMP();
        player.SetMP(min(player.GetMP() + 50, player.GetMaxMP()));
        inventory.RemoveItemAt(itemIndex);

        cout << "* Used MP Potion." << endl;
        cout << player.GetName() << " MP : " << previousMP
            << " -> " << player.GetMP() << endl;
        inventory.AddItem(Item{ "Empty " + itemName, 0 });
        return true;
    }

    cout << "* This item cannot be used in battle." << endl;
    return false;
}

int Battle::CalculateDamage(int attackPower, int defense)
{
    int damage = attackPower - defense;

    if (damage <= 0)
    {
        damage = 1;
    }

    return damage;
}
