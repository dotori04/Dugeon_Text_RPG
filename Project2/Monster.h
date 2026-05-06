#pragma once
#include <string>

static const int MONSTER_ASCII_FRAME_COUNT = 2;

struct MonsterInfo
{
    std::string name;
    int hp;
    int power;
    int defense;
    std::string dropItemName;
    int dropItemPrice;
    std::string asciiFrames[MONSTER_ASCII_FRAME_COUNT];
};

static const MonsterInfo MONSTER_TABLE[] =
{
    { 
        "Slime", 50, 15, 5, "Slime Jelly", 30,
        {
R"(
      _______
    /         \
   |   o   o   |
   |     w     |
    \_________/ )",
R"(
       _____
      /     \
     |  o o  |
     |   v   |
     |       |
      \_____/

   )"
        }
    },
    //{ "Goblin", 70, 22, 8, "Goblin Tooth", 45 },
    //{ "Skeleton", 90, 28, 12, "Old Bone", 60 },
    {
        "전투 허수아비", 100, 20, 60, "404 Not Found", 1,
        {
R"(        |||||||
       |  o o  |
       |   ^   |
       |  ---  |
      /|_______|\
       |  | |  |
       |  | |  |)",
R"(        |||||||
       |  - -  |
       |   ^   |
       |  ___  |
      \|_______|/
       |  | |  |
       |  | |  |)"
        }
    }
    //name hp atk def dropitem price asciiFrames
};

static const int MONSTER_TABLE_COUNT = sizeof(MONSTER_TABLE) / sizeof(MONSTER_TABLE[0]);

class Monster
{
protected:
    std::string name;
    int hp;
    int power;
    int defense;
    std::string dropItemName;
    int dropItemPrice;
    std::string asciiFrames[MONSTER_ASCII_FRAME_COUNT];

public:
    Monster(std::string name, int hp, int power, int defense, std::string dropItemName, int dropItemPrice,
        const std::string asciiFrames[MONSTER_ASCII_FRAME_COUNT]);
    static Monster CreateRandomMonster();

    std::string GetName() const;
    int GetHP() const;
    int GetPower() const;
    int GetDefense() const;
    std::string GetDropItemName() const;
    int GetDropItemPrice() const;
    std::string GetAsciiFrame(int frameIndex) const;
    int GetAsciiFrameCount() const;

    void SetHP(int hp);
    void SetPower(int power);
    void SetDefense(int defense);

    bool IsDead() const;
    void TakeDamage(int damage);
    void PrintStatus() const;
    virtual ~Monster() {}
};