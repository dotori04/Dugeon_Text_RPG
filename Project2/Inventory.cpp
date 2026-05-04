#include "Inventory.h"
#include <iostream>

bool Inventory::AddItem(const Item& item)
{
    if (items.size() >= maxCount)
    {
        std::cout << "* Inventory is full." << std::endl;
        return false;
    }

    items.push_back(item);
    std::cout << "-> Saved to inventory." << std::endl;
    return true;
}

void Inventory::PrintInventory() const
{
    std::cout << "[ Inventory (" << items.size() << "/" << maxCount << ") ]" << std::endl;

    if (items.empty())
    {
        std::cout << "No items." << std::endl;
        return;
    }

    int index = 1;
    for (const Item& item : items)
    {
        std::cout << index << ". ";
        item.PrintInfo();
        ++index;
    }
}