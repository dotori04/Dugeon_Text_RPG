#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include "Item.h"

template <typename Inven>
class Inventory
{
private:
    Inven* pItems;
    int size;
    int capacity;

    void Resize(int newCapacity);
    static bool CompareByPrice(const Inven& itemA, const Inven& itemB);

public:
    Inventory();
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);
    ~Inventory();

    bool AddItem(const Inven& item, bool shouldPrintMessage = true);
    bool RemoveItemByName(const std::string& itemName);
    bool RemoveItemAt(int itemIndex);
    const Inven* GetItemAt(int itemIndex) const;
    void PrintInventory() const;
    void InventorySort();
    void SortItems();
};

template <typename Inven>
Inventory<Inven>::Inventory()
{
    size = 0;
    capacity = 10;
    pItems = new Inven[capacity];
}

template <typename Inven>
Inventory<Inven>::Inventory(const Inventory& other)
{
    size = other.size;
    capacity = other.capacity;
    pItems = new Inven[capacity];

    for (int i = 0; i < size; ++i)
    {
        pItems[i] = other.pItems[i];
    }
}

template <typename Inven>
Inventory<Inven>& Inventory<Inven>::operator=(const Inventory& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] pItems;

    size = other.size;
    capacity = other.capacity;
    pItems = new Inven[capacity];

    for (int i = 0; i < size; ++i)
    {
        pItems[i] = other.pItems[i];
    }

    return *this;
}

template <typename Inven>
Inventory<Inven>::~Inventory()
{
    delete[] pItems;
}

template <typename Inven>
void Inventory<Inven>::Resize(int newCapacity)
{
    if (newCapacity <= capacity)
    {
        return;
    }

    Inven* pNewItems = new Inven[newCapacity];

    for (int i = 0; i < size; ++i)
    {
        pNewItems[i] = pItems[i];
    }

    delete[] pItems;
    pItems = pNewItems;
    capacity = newCapacity;
}

template <typename Inven>
bool Inventory<Inven>::CompareByPrice(const Inven& itemA, const Inven& itemB)
{
    return itemA.price < itemB.price;
}

template <typename Inven>
bool Inventory<Inven>::AddItem(const Inven& item, bool shouldPrintMessage)
{
    if (size >= capacity)
    {
        const int oldCapacity = capacity;

        if (shouldPrintMessage)
        {
            std::cout << "Adding item... (" << size << "/" << capacity << " full)" << std::endl;
        }

        Resize(capacity * 2);

        if (shouldPrintMessage)
        {
            std::cout << "-> Inventory auto-expanded! (" << oldCapacity
                << " -> " << capacity << ")" << std::endl;
        }
    }

    pItems[size] = item;
    ++size;

    if (shouldPrintMessage)
    {
        std::cout << "-> Item added" << std::endl;
    }

    return true;
}

template <typename Inven>
bool Inventory<Inven>::RemoveItemByName(const std::string& itemName)
{
    for (int i = 0; i < size; ++i)
    {
        if (pItems[i].name == itemName)
        {
            return RemoveItemAt(i + 1);
        }
    }

    return false;
}

template <typename Inven>
bool Inventory<Inven>::RemoveItemAt(int itemIndex)
{
    const int arrayIndex = itemIndex - 1;

    if (arrayIndex < 0 || arrayIndex >= size)
    {
        return false;
    }

    for (int i = arrayIndex; i < size - 1; ++i)
    {
        pItems[i] = pItems[i + 1];
    }

    --size;
    return true;
}

template <typename Inven>
const Inven* Inventory<Inven>::GetItemAt(int itemIndex) const
{
    const int arrayIndex = itemIndex - 1;

    if (arrayIndex < 0 || arrayIndex >= size)
    {
        return nullptr;
    }

    return &pItems[arrayIndex];
}

template <typename Inven>
void Inventory<Inven>::PrintInventory() const
{
    std::cout << "[ Inventory (" << size << "/" << capacity << ") ]" << std::endl;

    if (size == 0)
    {
        std::cout << "No items." << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        std::cout << i + 1 << ". ";
        pItems[i].PrintInfo();
    }

}

template <typename Inven>
void Inventory<Inven>::InventorySort()
{
    SortItems();
}

template <typename Inven>
void Inventory<Inven>::SortItems()
{
    std::sort(pItems, pItems + size, CompareByPrice);
}
