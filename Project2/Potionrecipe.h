#pragma once

#include <string>
#include <vector>

struct Ingredient
{
    std::string name;
    int count;
};

class PotionRecipe
{
private:
    std::string potionName;
    std::vector<Ingredient> ingredients;

public:
    PotionRecipe(const std::string& potionName, const std::vector<Ingredient>& ingredients);

    const std::string& GetPotionName() const;
    bool HasIngredient(const std::string& ingredientName) const;

    void PrintInfo() const;
    void PrintIngredients() const;
};