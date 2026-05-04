#include "Monster.h"
#include <iostream>
#include <random>

using namespace std;

Monster::Monster(string name, int hp, int power, int defense, string dropItemName, int dropItemPrice)
{
	this->name = name;
	this->hp = hp;
	this->power = power;
	this->defense = defense;
	this->dropItemName = dropItemName;
	this->dropItemPrice = dropItemPrice;
}

Monster Monster::CreateRandomMonster()
{
    static random_device randomDevice;
    static mt19937 generator(randomDevice());
    uniform_int_distribution<int> distribution(0, MONSTER_TABLE_COUNT - 1);

    const MonsterInfo& monsterInfo = MONSTER_TABLE[distribution(generator)];
    return Monster(
        monsterInfo.name,
        monsterInfo.hp,
        monsterInfo.power,
        monsterInfo.defense,
        monsterInfo.dropItemName,
        monsterInfo.dropItemPrice
    );
}

string Monster::GetName() const { return name; }
int Monster::GetHP() const { return hp; }
int Monster::GetPower() const { return power; }
int Monster::GetDefense() const { return defense; }
string Monster::GetDropItemName() const { return dropItemName; }
int Monster::GetDropItemPrice() const { return dropItemPrice; }
	
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
    std::cout << "[Monster] " << name
        << " HP: " << hp
        << " ATK: " << power
        << " DEF: " << defense
        << std::endl;
}

bool Monster::IsDead() const
{
    return hp <= 0;
}
