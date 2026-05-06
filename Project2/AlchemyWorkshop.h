#pragma once

#include "Inventory.h"
#include "Item.h"
#include "PotionRecipe.h"
#include <map>
#include <string>
#include <vector>

class AlchemyWorkshop
{
private:
    static const int MAX_STOCK = 3;

    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> potionStock;

    bool HasRecipe(const std::string& potionName) const;
    void AddRecipe();
    bool DispensePotion(const std::string& potionName);
    bool ReturnPotion(const std::string& potionName, Inventory<Item>& inventory);

public:
    AlchemyWorkshop();

    void Open(Inventory<Item>& inventory);
    void ShowAllRecipes() const;
    void SearchByName(const std::string& potionName) const;
    void SearchByIngredient(const std::string& ingredientName) const;
    int GetStock(const std::string& potionName) const;
};
