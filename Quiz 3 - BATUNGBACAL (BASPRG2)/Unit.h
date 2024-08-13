#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Unit {
protected:
    string name;
    int hp;
    int maxHp;
    int pow;
    int vit;
    int agi;
    int dex;
    string className;

public:
    Unit(const string& name, int hp, int pow, int vit, int agi, int dex, const string& className)
        : name(name), hp(hp), maxHp(hp), pow(pow), vit(vit), agi(agi), dex(dex), className(className) {}

    virtual ~Unit() {}

    virtual int GetDamageBonus(const Unit& defender) const = 0;

    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getPOW() const { return pow; }
    int getVIT() const { return vit; }
    int getAGI() const { return agi; }
    int getDEX() const { return dex; }
    string getClassName() const { return className; }
    string getName() const { return name; }

    void TakeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    void Heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

    void AddStats(int pow, int vit, int agi, int dex) {
        this->pow += pow;
        this->vit += vit;
        this->agi += agi;
        this->dex += dex;
    }

    virtual void DisplayStats() const {
        
        cout << endl << "--- Stats ---" << endl;
        cout << "Name: " << name << endl;
        cout << "Class: " << className << endl;
        cout << "HP: " << hp << "/" << maxHp << endl;
        cout << "POW: " << pow << endl;
        cout << "VIT: " << vit << endl;
        cout << "AGI: " << agi << endl;
        cout << "DEX: " << dex << endl;
    }
};

class Warrior : public Unit {
public:
    Warrior(const string& name)
        : Unit(name, 100, 20, 10, 5, 10, "Warrior") {}

    int GetDamageBonus(const Unit& defender) const override {
        if (defender.getClassName() == "Assassin") return 150;
        if (defender.getClassName() == "Mage") return 100;
        return 100;
    }
};

class Assassin : public Unit {
public:
    Assassin(const string& name)
        : Unit(name, 80, 15, 5, 20, 15, "Assassin") {}

    int GetDamageBonus(const Unit& defender) const override {
        if (defender.getClassName() == "Mage") return 150;
        if (defender.getClassName() == "Warrior") return 100;
        return 100;
    }
};

class Mage : public Unit {
public:
    Mage(const string& name)
        : Unit(name, 60, 25, 5, 10, 10, "Mage") {}

    int GetDamageBonus(const Unit& defender) const override {
        if (defender.getClassName() == "Warrior") return 150;
        if (defender.getClassName() == "Assassin") return 100;
        return 100;
    }
};

#include "Unit.h"

int CalculateDamage(const Unit& attacker, const Unit& defender) {
    int baseDamage = attacker.getPOW() - defender.getVIT();
    if (baseDamage < 1) baseDamage = 1;
    int bonusDamage = attacker.GetDamageBonus(defender);
    return baseDamage * bonusDamage / 100;
}

int CalculateHitRate(const Unit& attacker, const Unit& defender) {
    int hitRate = (attacker.getDEX() * 100) / defender.getAGI();
    if (hitRate < 20) hitRate = 20;
    if (hitRate > 80) hitRate = 80;
    return hitRate;
}

bool Attack(Unit& attacker, Unit& defender) {
    int hitRate = CalculateHitRate(attacker, defender);
    if (rand() % 100 < hitRate) {
        int damage = CalculateDamage(attacker, defender);
        defender.TakeDamage(damage);
        cout << attacker.getName() << " hits " << defender.getName() << " for " << damage << " damage!" << endl;
        return true;
    }
    else {
        cout << attacker.getName() << " misses " << defender.getName() << "!" << endl;
        return false;
    }
}

void Battle(Unit& player, Unit& opponent) {
    while (player.getHP() > 0 && opponent.getHP() > 0) {
        if (player.getAGI() >= opponent.getAGI()) {
            Attack(player, opponent);
            if (opponent.getHP() > 0) {
                Attack(opponent, player);
            }
        }
        else {
            Attack(opponent, player);
            if (player.getHP() > 0) {
                Attack(player, opponent);
            }
        }
        cout << "--- Turn End ---" << endl;
        player.DisplayStats();
        opponent.DisplayStats();
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    if (player.getHP() > 0) {
        cout << player.getName() << " wins!" << endl;
        if (opponent.getClassName() == "Warrior") {
            player.AddStats(3, 3, 0, 0);
        }
        else if (opponent.getClassName() == "Assassin") {
            player.AddStats(0, 0, 3, 3);
        }
        else if (opponent.getClassName() == "Mage") {
            player.AddStats(5, 0, 0, 0);
        }
        player.Heal(player.getMaxHP() * 0.3);
    }
    else {
        cout << opponent.getName() << " wins!" << endl;
    }
}

