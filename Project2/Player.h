#pragma once

#include <string>

class Monster;

class Player
{
protected:
    std::string name;
    std::string job;

    int hp;
    int mp;
    int maxHp;
    int maxMp;
    int power;
    int defense;
    int exp;
    int maxExp;
    int level;

public:
    Player(std::string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level);

    std::string GetName() const;
    std::string GetJob() const;
    int GetLevel() const;
    int GetHP() const;
    int GetMP() const;
    int GetMaxHP() const;
    int GetMaxMP() const;
    int GetPower() const;
    int GetDefense() const;
    int GetExp() const;
    int GetMaxExp() const;
    int levelUp();

    void SetHP(int hp);
    void SetMP(int mp);
    void SetMaxHP(int maxHp);
    void SetMaxMP(int maxMp);
    void SetPower(int power);
    void SetDefense(int defense);
    void SetExp(int exp);
    void SetMaxExp(int maxExp);
    void SetLevel(int level);

    void PrintPlayerStatus() const;

    virtual ~Player() {}

    virtual void Attack(Monster* monster) = 0;
};