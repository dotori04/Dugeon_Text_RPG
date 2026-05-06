#include "AlchemyWorkshop.h"
#include <iostream>
#include <limits>

using namespace std;

AlchemyWorkshop::AlchemyWorkshop()
{
    recipes.push_back(PotionRecipe("HP Potion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Clear Water", 1 }
        }));
    potionStock["HP Potion"] = MAX_STOCK;

    recipes.push_back(PotionRecipe("MP Potion", {
        Ingredient{ "Magic Herb", 1 },
        Ingredient{ "Clear Water", 1 }
        }));
    potionStock["MP Potion"] = MAX_STOCK;

    recipes.push_back(PotionRecipe("Stamina Potion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Berry", 1 }
        }));
    potionStock["Stamina Potion"] = MAX_STOCK;
}

void AlchemyWorkshop::Open(Inventory<Item>& inventory)
{
    bool isOpen = true;

    while (isOpen)
    {
        cout << "=== Potion Shop ===" << endl;
        cout << "1. Show all recipes" << endl;
        cout << "2. Search by potion name" << endl;
        cout << "3. Search by ingredient" << endl;
        cout << "4. Add recipe" << endl;
        cout << "5. Dispense potion" << endl;
        cout << "6. Return empty bottle" << endl;
        cout << "0. Go back" << endl;
        cout << endl;
        cout << "Choose: ";

        int choice = -1;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        case 4:
            AddRecipe();
            break;
        case 5:
        {
            string potionName;
            cout << "Potion name: ";
            getline(cin, potionName);

            if (DispensePotion(potionName))
            {
                inventory.AddItem(Item{ potionName, 0 });
            }
            break;
        }
        case 6:
        {
            string potionName;
            cout << "Returned bottle potion name: ";
            getline(cin, potionName);
            ReturnPotion(potionName);
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
        cout << "   Stock: " << GetStock(recipe.GetPotionName()) << endl;
    }
}

void AlchemyWorkshop::SearchByName(const string& potionName) const
{
    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.GetPotionName() == potionName)
        {
            recipe.PrintInfo();
            cout << "Stock: " << GetStock(potionName) << endl;
            return;
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

bool AlchemyWorkshop::HasRecipe(const string& potionName) const
{
    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.GetPotionName() == potionName)
        {
            return true;
        }
    }

    return false;
}

void AlchemyWorkshop::AddRecipe()
{
    string potionName;
    cout << "Potion name: ";
    getline(cin, potionName);

    if (potionName.empty())
    {
        cout << "Recipe name cannot be empty." << endl;
        return;
    }

    if (HasRecipe(potionName))
    {
        cout << "Recipe already exists." << endl;
        return;
    }

    vector<Ingredient> ingredients;
    for (int i = 0; i < 2; ++i)
    {
        Ingredient ingredient;

        cout << "Ingredient " << i + 1 << " name: ";
        getline(cin, ingredient.name);

        cout << "Ingredient " << i + 1 << " count: ";
        cin >> ingredient.count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ingredient.name.empty() || ingredient.count <= 0)
        {
            cout << "Invalid ingredient." << endl;
            return;
        }

        ingredients.push_back(ingredient);
    }

    recipes.push_back(PotionRecipe(potionName, ingredients));
    potionStock[potionName] = MAX_STOCK;

    cout << "-> Recipe added." << endl;
    cout << "-> " << potionName << " stock initialized to " << MAX_STOCK << "." << endl;
}

bool AlchemyWorkshop::DispensePotion(const string& potionName)
{
    if (!HasRecipe(potionName))
    {
        cout << "Dispense failed: recipe not found." << endl;
        return false;
    }

    int& stock = potionStock[potionName];
    if (stock <= 0)
    {
        cout << "Dispense failed: out of stock!" << endl;
        return false;
    }

    --stock;
    cout << "-> Dispense " << potionName << " (stock: " << stock << ")" << endl;
    return true;
}

bool AlchemyWorkshop::ReturnPotion(const string& potionName)
{
    if (!HasRecipe(potionName))
    {
        cout << "Return failed: recipe not found." << endl;
        return false;
    }

    int& stock = potionStock[potionName];
    if (stock >= MAX_STOCK)
    {
        cout << "Return failed: stock is already full." << endl;
        return false;
    }

    ++stock;
    cout << "-> Return empty bottle (stock: " << stock << ")" << endl;
    return true;
}

int AlchemyWorkshop::GetStock(const string& potionName) const
{
    const auto stockIter = potionStock.find(potionName);
    if (stockIter == potionStock.end())
    {
        return 0;
    }

    return stockIter->second;
}
