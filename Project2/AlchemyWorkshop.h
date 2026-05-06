#pragma once

#include "PotionRecipe.h"
#include <map>
#include <string>
#include <vector>

struct Item;
template <typename Inven>
class Inventory;

class AlchemyWorkshop
{
private:
    static const int MAX_STOCK = 3;

    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> potionStock;

public:
    AlchemyWorkshop();

    void Open(Inventory<Item>& inventory);
    void AddRecipe(const PotionRecipe& recipe);
    void ShowAllRecipes() const;
    void SearchByName(const std::string& potionName) const;
    void SearchByIngredient(const std::string& ingredientName) const;
    bool DispensePotion(const std::string& name);
    bool ReturnPotion(const std::string& name);
    int GetStock(const std::string& name) const;
};
