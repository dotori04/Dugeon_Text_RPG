#pragma once

#include "Player.h"
#include "Inventory.h"
#include "Item.h"

enum class DungeonResult
{
    ReturnToMenu,
    GameClear
};

DungeonResult EnterDungeon(Player& player, Inventory<Item>& inventory);

