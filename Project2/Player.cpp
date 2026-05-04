#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name, int hp, int mp, int power, int defense)
{
    this->name = name;
    this->job = "None";
    this->hp = hp;
    this->mp = mp;
    this->power = power;
    this->defense = defense;
}

string Player::GetName() const { return name; }
string Player::GetJob() const { return job; }
int Player::GetLevel() const { return level; }
int Player::GetHP() const { return hp; }
int Player::GetMP() const { return mp; }
int Player::GetPower() const { return power; }
int Player::GetDefense() const { return defense; }

void Player::SetHP(int hp) { this->hp = hp; }
void Player::SetMP(int mp) { this->mp = mp; }
void Player::SetPower(int power) { this->power = power; }
void Player::SetDefense(int defense) { this->defense = defense; }

void Player::PrintPlayerStatus() const
{
    cout << "--------------------------------------------" << endl;
    cout << "Name: " << name << " | Job: " << job << " | Lv.1" << endl;
    cout << "HP : " << hp << " | " << "MP : " << mp << " | "
        << "ATK: " << power << " | " << "DEF: " << defense << endl;
    cout << "--------------------------------------------" << endl;
     
}