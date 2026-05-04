#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Rogue.h"
#include "Archer.h"
#include "Monster.h"
#include "Battle.h"
#include "Inventory.h"
#include "Item.h"
#include "AlchemyWorkshop.h"

using namespace std;

void ClearConsole()
{
    system("cls");
}

void printStatus(string name, int stat[])
{
    cout << "============================================" << endl;
    cout << name << "'s Stats" << endl;
    cout << "============================================" << endl;
    cout << "HP : " << stat[0] << "  " << "MP : " << stat[1] << endl;
    cout << "ATK : " << stat[2] << "  " << "DEF : " << stat[3] << endl;
    cout << "============================================" << endl;
}

int main()
{
	AlchemyWorkshop workshop;
    Player* player = nullptr;
    Inventory inventory;
    string name;
    const int SIZE = 4;
    int stat[SIZE] = { 0 };

    cout << "============================================" << endl;
    cout << "    [ Dungeon Escape Text RPG ]" << endl;
    cout << "============================================" << endl;
    cout << " Enter your hero's name: ";
    cin >> name;
    cout << endl;

    while (1)
    {
        cout << "Enter HP and MP: ";
        cin >> stat[0] >> stat[1];
        cout << endl;

        if (stat[0] >= 50 && stat[1] >= 50)
        {
            break;
        }

        cout << "HP and MP must be at least 50. Please enter again." << endl;
    }

    while (1)
    {
        cout << "Enter Attack and Defense : ";
        cin >> stat[2] >> stat[3];
        cout << endl;

        if (stat[2] >= 20 && stat[3] >= 20)
        {
            break;
        }

        cout << "Attack and Defense must be at least 20. Please enter again." << endl;
    }

    printStatus(name, stat);

    int HP_Potion = 5;
    int MP_Potion = 5;
    cout << "* You received " << HP_Potion << " HP Potions and "
        << MP_Potion << " MP Potions." << endl;
    cout << "=============================================" << endl;
    cout << "<Character Upgrade>" << endl;
    cout << "1. HP UP    2. MP UP   3.ATK UP" << endl;
    cout << "4. DEF UP   5. Show Stats  0. Start Game" << endl;
    cout << "=============================================" << endl;

    bool isGameStart = false;
    while (!isGameStart)
    {
        int choice = -1;
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (HP_Potion <= 0)
            {
                cout << "* No HP Potions left!" << endl;
                break;
            }

            stat[0] += 20;
            HP_Potion--;
            cout << "* HP increased by 20. (HP Potion left: " << HP_Potion << ")" << endl;
            break;
        case 2:
            if (MP_Potion <= 0)
            {
                cout << "* No MP Potions left!" << endl;
                break;
            }

            stat[1] += 20;
            MP_Potion--;
            cout << "* MP increased by 20. (MP Potion left: " << MP_Potion << ")" << endl;
            break;
        case 3:
            stat[2] *= 2;
            cout << "* Attack doubled." << endl;
            break;
        case 4:
            stat[3] *= 2;
            cout << "* Defense doubled." << endl;
            break;
        case 5:
            printStatus(name, stat);
            break;
        case 0:
            isGameStart = true;
            cout << "Game Started!" << endl;
            ClearConsole();
            break;
        default:
            cout << "Invalid choice. Please select a valid upgrade menu." << endl;
            break;
        }
    }

    cout << "<Job Selection>" << endl;
    cout << name << ", choose your job!" << endl;
    cout << "1. Warrior   2. Mage   3. Rogue   4. Archer" << endl;

    bool jobselected = false;
    while (!jobselected)
    {
        int jobChoice = -1;
        cin >> jobChoice;

        switch (jobChoice)
        {
        case 1:
            player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
            cout << "* You have chosen the Warrior job!" << endl;
            jobselected = true;
            break;
        case 2:
            player = new Magician(name, stat[0], stat[1], stat[2], stat[3]);
            cout << "* You have chosen the Magician job!" << endl;
            jobselected = true;
            break;
        case 3:
            player = new Rogue(name, stat[0], stat[1], stat[2], stat[3]);
            cout << "* You have chosen the Rogue job!" << endl;
            jobselected = true;
            break;
        case 4:
            player = new Archer(name, stat[0], stat[1], stat[2], stat[3]);
            cout << "* You have chosen the Archer job!" << endl;
            jobselected = true;
            break;
        default:
            cout << "Invalid choice. Please select a valid job." << endl;
            break;
        }
    }

    player->Attack();
    player->PrintPlayerStatus();
    ClearConsole();

    bool isPlaying = true;
    while (isPlaying)
    {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Enter Dungeon" << endl;
        cout << "2. Show Inventory" << endl;
		cout << "3. Potion Shop" << endl;
		cout << "4. Show Status" << endl;
        cout << "0. Quit" << endl;
        cout << endl;
        cout << "Choose: ";

        int menuChoice = -1;
        cin >> menuChoice;
        cout << endl;

        switch (menuChoice)
        {
        case 1:
        {
			ClearConsole();
            Monster monster = Monster::CreateRandomMonster();
            Item droppedItem;

            if (Battle::Start(*player, monster, droppedItem))
            {
                inventory.AddItem(droppedItem);
             
            }
            else
            {
                isPlaying = false;
            }

            cout << endl;
            break;
        }
        case 2:
			ClearConsole();
            inventory.PrintInventory();
            cout << endl;
            break;
		case 3:
            ClearConsole();
            workshop.Open();
            break;
        case 4:
			ClearConsole();
            player->PrintPlayerStatus();
            break;
        case 0:
            isPlaying = false;
            cout << "Game Ended." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid menu." << endl;
            cout << endl;
            break;
        }
    }

    delete player;
    return 0;
}
