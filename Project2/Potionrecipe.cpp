#include "PotionRecipe.h"
#include <iostream>

using namespace std;
PotionRecipe::PotionRecipe(const string& potionName, const vector<Ingredient>& ingredients)
    : potionName(potionName), ingredients(ingredients)
{
}

const string& PotionRecipe::GetPotionName() const
{
    return potionName;
}

bool PotionRecipe::HasIngredient(const string& ingredientName) const
{
    for (const Ingredient& ingredient : ingredients)
    {
        if (ingredient.name == ingredientName)
        {
            return true;
        }
    }

    return false;
}

void PotionRecipe::PrintInfo() const
{
    cout << "-> " << potionName << ": ";
    PrintIngredients();
    cout << endl;
}

void PotionRecipe::PrintIngredients() const
{
    for (size_t i = 0; i < ingredients.size(); ++i)
    {
        cout << ingredients[i].name << " x" << ingredients[i].count;

        if (i + 1 < ingredients.size())
        {
            cout << ", ";
        }
    }
}