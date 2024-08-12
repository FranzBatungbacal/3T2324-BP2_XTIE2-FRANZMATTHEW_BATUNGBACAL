#pragma once

#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>    

using namespace std;

class Wizard {
private:
    string name;
    int hp;
    int mp;
    int minDamage;
    int maxDamage;

public:
    Wizard(const string& name, int hp, int mp, int minDamage, int maxDamage)
        : name(name), hp(hp), mp(mp), minDamage(minDamage), maxDamage(maxDamage) {}

    void Attack(Wizard& target) {
        int damage = minDamage + rand() % (maxDamage - minDamage + 1);
        int mpGenerated = 10 + rand() % (20 - 10 + 1);

        target.hp -= damage;
        this->mp += mpGenerated;

        cout << name << " attacks " << target.name << " for " << damage << " damage" << endl;
        cout << name << " generates " << mpGenerated << " MP." << endl << endl;
    }

    bool isAlive() const {
        return hp > 0;
    }

    int getHP() const {
        return hp;
    }

    int getMP() const {
        return mp;
    }

    void takeDamage(int damage) {
        hp -= damage;
    }

    void addMP(int mp) {
        this->mp += mp;
    }

    void useMP(int mp) {
        this->mp -= mp;
    }

    string getName() const {
        return name;
    }
};

class Spell {
private:
    string name;
    int minDamage;
    int maxDamage;
    int mpCost;

public:
    Spell(const string& name, int minDamage, int maxDamage, int mpCost)
        : name(name), minDamage(minDamage), maxDamage(maxDamage), mpCost(mpCost) {}

    void Activate(Wizard& caster, Wizard& target) {
        if (caster.getMP() >= mpCost) {
            int damage = minDamage + rand() % (maxDamage - minDamage + 1);
            caster.useMP(mpCost);
            target.takeDamage(damage);

            cout << caster.getName() << " casts " << name << " on " << target.getName() << " for " << damage << " damage." << endl;
        }
        else {
            cout << caster.getName() << " does not have enough MP to cast " << name << "." << endl;
        }
    }
};
