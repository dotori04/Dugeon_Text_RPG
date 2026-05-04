#include "AlchemyWorkshop.h"
#include <iostream>
#include <limits>

using namespace std;
AlchemyWorkshop::AlchemyWorkshop()
{
    recipes.push_back(PotionRecipe("HPPotion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Clear Water", 1 }
        }));

    recipes.push_back(PotionRecipe("StaminaPotion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Berry", 1 }
        }));
}


void AlchemyWorkshop::Open()
{
    bool isOpen = true;

    while (isOpen)
    {
        cout << "=== Potion Shop ===" << endl;
        cout << "1. Show all recipes" << endl;
        cout << "2. Search by potion name" << endl;
        cout << "3. Search by ingredient" << endl;
        cout << "0. Go back" << endl;
        cout << endl;
        cout << "Choose: ";

        int choice = -1;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //포션 상점에서 2,3번 선택시 입력 버퍼에 남아있는 문자 제거
        cout << endl;

        switch (choice)
        {
        case 1:
            ShowAllRecipes();
            break;
        case 2:
        {
            string potionName;
            cout << "Search potion name: ";
            getline(cin, potionName);
            SearchByName(potionName);
            break;
        }
        case 3:
        {
            string ingredientName;
            cout << "Search ingredient: ";
            getline(cin, ingredientName);
            SearchByIngredient(ingredientName);
            break;
        }
        case 0:
            isOpen = false;
            
            break;
        default:
            cout << "Invalid choice. Please select a valid menu." << endl;
            break;
        }

        cout << endl;
    }
}

void AlchemyWorkshop::ShowAllRecipes() const
{
    for (const PotionRecipe& recipe : recipes)
    {
        recipe.PrintInfo();
    }
}

void AlchemyWorkshop::SearchByName(const string& potionName) const
{
    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.GetPotionName() == potionName)
        {
            recipe.PrintInfo();
            return;
        }
        else
        {
            break;
        }
    }

    cout << "Could not find recipe." << endl;
}

void AlchemyWorkshop::SearchByIngredient(const string& ingredientName) const
{
    int foundCount = 0;

    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.HasIngredient(ingredientName))
        {
            cout << "-> " << recipe.GetPotionName() << " (";
            recipe.PrintIngredients();
            cout << ")" << endl;
            ++foundCount;
        }
    }

    if (foundCount == 0)
    {
        cout << "Could not find recipe." << endl;
        return;
    }

    cout << "Found " << foundCount << " recipes." << endl;
}