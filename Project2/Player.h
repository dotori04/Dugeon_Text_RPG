#pragma once

#include <string>

class Player
{
protected:
    std::string name;
    std::string job;

    int level;
    int hp;
    int mp;
    int power;
    int defense;

public:
    Player(std::string name, int hp, int mp, int power, int defense);

    std::string GetName() const;
    std::string GetJob() const;
    int GetLevel() const;
    int GetHP() const;
    int GetMP() const;
    int GetPower() const;
    int GetDefense() const;

    void SetHP(int hp);
    void SetMP(int mp);
    void SetPower(int power);
    void SetDefense(int defense);

    void PrintPlayerStatus() const;

    virtual ~Player() {}

    virtual void Attack() = 0;
};

