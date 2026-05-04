#pragma once

#include <vector>
#include "Item.h"

class Inventory
{
private:
    std::vector<Item> items;
    int maxCount = 10;

public:
    bool AddItem(const Item& item);
    void PrintInventory() const;
};