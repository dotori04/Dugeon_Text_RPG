#include "AlchemyWorkshop.h"
#include "Inventory.h"
#include "Item.h"
#include <iostream>
#include <limits>

using namespace std;

AlchemyWorkshop::AlchemyWorkshop()
{
    /*AddRecipe(PotionRecipe("HPPotion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Clear Water", 1 }
    }));

    AddRecipe(PotionRecipe("StaminaPotion", {
        Ingredient{ "Herb", 1 },
        Ingredient{ "Berry", 1 }
    }));*/
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
        cout << "4. Add new recipe" << endl;
        cout << "5. Dispense potion" << endl;
        cout << "6. Return empty bottle" << endl;
        cout << "0. Go back" << endl;
        cout << endl;
        cout << "Choose: ";

        int choice = -1;
        if (!(cin >> choice))
        {
            if (cin.eof())
            {
                isOpen = false;
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl << endl;
            continue;
        }

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
        {
            string potionName;
            vector<Ingredient> ingredients;
            while(1)
            {
                cout << "New potion name: ";
                getline(cin, potionName);
                if (!potionName.empty())
                {
                    break;
                }
                else
                {
                    cout << "Potion name cannot be empty. Please enter again." << endl;
                }
            }
            for (int i = 0; i < 2; ++i)
            {
                Ingredient ingredient;

                cout << "Ingredient " << i + 1 << " name: ";
                getline(cin, ingredient.name);
                if(ingredient.name.empty())
                {
                    cout << "Ingredient name cannot be empty. Please enter again." << endl;
                    --i;
                    continue;
				}

                cout << "Ingredient " << i + 1 << " count: ";
                cin >> ingredient.count;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(ingredient.count <= 0)
                {
                    cout << "Ingredient count must be positive. Please enter again." << endl;
                    --i;
                    continue;
                }

                ingredients.push_back(ingredient);
            }

            AddRecipe(PotionRecipe(potionName, ingredients));
            cout << "-> Recipe added: " << potionName
                << " (stock: " << GetStock(potionName) << ")" << endl;
            break;
        }
        case 5:
        {
            string potionName;

            cout << "Potion name to dispense: ";
            getline(cin, potionName);

            if (potionName.empty())
            {
                cout << "Potion name cannot be empty." << endl;
                break;
            }

            if (DispensePotion(potionName))
            {
                inventory.AddItem(Item{ potionName, 0 });
            }
            break;
        }
        case 6:
        {
            string potionName;

            cout << "Potion name to return bottle: ";
            getline(cin, potionName);

            if (potionName.empty())
            {
                cout << "Potion name cannot be empty." << endl;
                break;
            }

            cout << potionName << " stock before return: "
                << GetStock(potionName) << endl;

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

void AlchemyWorkshop::AddRecipe(const PotionRecipe& recipe)
{
    recipes.push_back(recipe);
    potionStock[recipe.GetPotionName()] = MAX_STOCK;
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

bool AlchemyWorkshop::DispensePotion(const string& name)
{
    auto iter = potionStock.find(name);

    if (iter == potionStock.end())
    {
        cout << "-> Potion not found." << endl;
        return false;
    }

    if (iter->second <= 0)
    {
        cout << "-> Dispense failed: out of stock!" << endl;
        return false;
    }

    iter->second--;
    cout << "-> Dispense " << name
        << " (stock: " << iter->second << ")" << endl;
    return true;
}

bool AlchemyWorkshop::ReturnPotion(const string& name)
{
    auto iter = potionStock.find(name);

    if (iter == potionStock.end())
    {
        cout << "-> Potion not found." << endl;
        return false;
    }

    if (iter->second >= MAX_STOCK)
    {
        cout << "-> Return failed: stock is full!" << endl;
        return false;
    }

    iter->second++;
    cout << "-> Return empty bottle"
        << " (stock: " << iter->second << ")" << endl;
    return true;
}

int AlchemyWorkshop::GetStock(const string& name) const
{
    auto iter = potionStock.find(name);

    if (iter == potionStock.end())
    {
        return 0;
    }

    return iter->second;
}
