#pragma once
#include <string>

struct MonsterInfo
{
	std::string name;
	int hp;
	int power;
	int defense;
	std::string dropItemName;
	int dropItemPrice;
};

static const MonsterInfo MONSTER_TABLE[] =
{
	{ "Slime", 50, 15, 5, "Slime Jelly", 30 },
	{ "Goblin", 70, 22, 8, "Goblin Tooth", 45 },
	{ "Skeleton", 90, 28, 12, "Old Bone", 60 },
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
public:
	Monster(std::string name, int hp, int power, int defense, std::string dropItemName, int dropItemPrice);
	static Monster CreateRandomMonster();

	std::string GetName() const;
	int GetHP() const;
	int GetPower() const;
	int GetDefense() const;
	std::string GetDropItemName() const;
	int GetDropItemPrice() const;
	void SetHP(int hp);
	void SetPower(int power);
	void SetDefense(int defense);
	//void PrintMonsterStatus() const;
	bool IsDead() const;
	void TakeDamage(int damage);
	void PrintStatus() const;
	virtual ~Monster() {}

};
