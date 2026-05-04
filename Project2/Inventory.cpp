#include "Inventory.h"
#include <iostream>

using namespace std;

bool Inventory::AddItem(const Item& item)
{
    if (items.size() >= maxCount)
    {
        std::cout << "* Inventory is full." << std::endl;
        return false;
    }

    items.push_back(item);
    cout << "-> Saved to inventory." << endl;
    return true;
}

void Inventory::PrintInventory() const
{
    cout << "[ Inventory (" << items.size() << "/" << maxCount << ") ]" <<  endl;

    if (items.empty())
    {
        cout << "No items." <<  endl;
        return;
    }

    int index = 1;
    for (const Item& item : items)
    {
        cout << index << ". ";
        item.PrintInfo();
        ++index;
    }
}