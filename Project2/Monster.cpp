#include "Monster.h"
#include <iostream>
#include <random>

using namespace std;

Monster::Monster(string name, int hp, int power, int defense, string dropItemName, int dropItemPrice,
    const string asciiFrames[MONSTER_ASCII_FRAME_COUNT])
{
    this->name = name;
    this->hp = hp;
    this->power = power;
    this->defense = defense;
    this->dropItemName = dropItemName;
    this->dropItemPrice = dropItemPrice;

    for (int i = 0; i < MONSTER_ASCII_FRAME_COUNT; ++i)
    {
        this->asciiFrames[i] = asciiFrames[i];
    }
}

Monster Monster::CreateRandomMonster(int floor)
{
    //static random_device randomDevice;/*
    //static mt19937 generator(randomDevice());
    //uniform_int_distribution<int> distribution(0, MONSTER_TABLE_COUNT - 1);*/

    const MonsterInfo& monsterInfo = MONSTER_TABLE[floor];
    return Monster(
        monsterInfo.name,
        monsterInfo.hp,
        monsterInfo.power,
        monsterInfo.defense,
        monsterInfo.dropItemName,
        monsterInfo.dropItemPrice,
        monsterInfo.asciiFrames
    );
}

Monster Monster::CreateMonsterFromInfo(const MonsterInfo& info)
{
    return Monster(
        info.name,
        info.hp,
        info.power,
        info.defense,
        info.dropItemName,
        info.dropItemPrice,
        info.asciiFrames
    );
}

string Monster::GetName() const { return name; }
int Monster::GetHP() const { return hp; }
int Monster::GetPower() const { return power; }
int Monster::GetDefense() const { return defense; }
string Monster::GetDropItemName() const { return dropItemName; }
int Monster::GetDropItemPrice() const { return dropItemPrice; }

string Monster::GetAsciiFrame(int frameIndex) const
{
    if (frameIndex < 0)
    {
        frameIndex = 0;
    }

    return asciiFrames[frameIndex % MONSTER_ASCII_FRAME_COUNT];
}

int Monster::GetAsciiFrameCount() const
{
    return MONSTER_ASCII_FRAME_COUNT;
}

void Monster::SetHP(int hp) { this->hp = hp; }
void Monster::SetPower(int power) { this->power = power; }
void Monster::SetDefense(int defense) { this->defense = defense; }

void Monster::TakeDamage(int damage)
{
    if (damage < 0)
    {
        damage = 0;
    }

    hp -= damage;

    if (hp < 0)
    {
        hp = 0;
    }
}

void Monster::PrintStatus() const
{
    cout << "[Monster] " << name
        << " HP: " << hp
        << " ATK: " << power
        << " DEF: " << defense
        << endl;
}

bool Monster::IsDead() const
{
    return hp <= 0;
}