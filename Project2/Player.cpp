#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name, int hp, int mp, int power, int defense, int exp, int maxExp, int level)
{
    this->name = name;
    this->job = "None";
    this->hp = hp;
    this->mp = mp;
    this->maxHp = hp;
    this->maxMp = mp;
    this->power = power;
    this->defense = defense;
    this->exp = exp;
    this->maxExp = maxExp;
    this->level = level;
}

string Player::GetName() const { return name; }
string Player::GetJob() const { return job; }
int Player::GetLevel() const { return level; }
int Player::GetHP() const { return hp; }
int Player::GetMP() const { return mp; }
int Player::GetMaxHP() const { return maxHp; }
int Player::GetMaxMP() const { return maxMp; }
int Player::GetPower() const { return power; }
int Player::GetDefense() const { return defense; }
int Player::GetExp() const { return exp; }
int Player::GetMaxExp() const { return maxExp; }

int Player::levelUp()
{
    if (exp >= maxExp)
    {
        level++;
        exp -= maxExp;
        maxExp += 50;
        maxHp += 20;
        maxMp += 10;
        hp = maxHp;
        mp = maxMp;
        power += 5;
        defense += 5;
        cout << "* Level Up! You are now level " << level << "!" << endl;
        return level;
    }

    cout << "* Not enough EXP to level up." << endl;
    return level;
}

void Player::SetHP(int hp) { this->hp = hp; }
void Player::SetMP(int mp) { this->mp = mp; }
void Player::SetMaxHP(int maxHp) { this->maxHp = maxHp; }
void Player::SetMaxMP(int maxMp) { this->maxMp = maxMp; }
void Player::SetPower(int power) { this->power = power; }
void Player::SetDefense(int defense) { this->defense = defense; }
void Player::SetExp(int exp) { this->exp += exp; }
void Player::SetMaxExp(int maxExp) { this->maxExp = maxExp; }
void Player::SetLevel(int level) { this->level = level; }

void Player::PrintPlayerStatus() const
{
    cout << "--------------------------------------------" << endl;
    cout << "Name: " << name << " | Job: " << job << " | Lv." << level << endl;
    cout << "HP : " << hp << "/" << maxHp << " | "
        << "MP : " << mp << "/" << maxMp << " | "
        << "ATK: " << power << " | " << "DEF: " << defense << endl;
    cout << "EXP: " << exp << " / " << maxExp << endl;
    cout << "--------------------------------------------" << endl;
}