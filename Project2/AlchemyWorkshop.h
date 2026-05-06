#pragma once

#include "PotionRecipe.h"
#include <string>
#include <vector>

class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;

public:
    AlchemyWorkshop();

    void Open();
    void ShowAllRecipes() const;
    void SearchByName(const std::string& potionName) const;
    void SearchByIngredient(const std::string& ingredientName) const;
};