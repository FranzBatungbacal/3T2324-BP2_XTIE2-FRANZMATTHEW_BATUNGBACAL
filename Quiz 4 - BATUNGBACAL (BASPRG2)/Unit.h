#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
    int mp;
    string className;

public:
    Unit(const string& name, int hp, int pow, int vit, int agi, int dex, int mp, const string& className);
    virtual ~Unit() {}

    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getPOW() const { return pow; }
    int getVIT() const { return vit; }
    int getAGI() const { return agi; }
    int getDEX() const { return dex; }
    int getMP() const { return mp; }
    std::string GetClassName() const { return className; }
    std::string GetName() const { return name; }

    void TakeDamage(int damage);
    void Heal(int amount);
    void AddMP(int amount);
    void UseMP(int amount);

    virtual void DisplayStats() const;
};

class Action {
protected:
    int mpCost;

public:
    Action(int mpCost) : mpCost(mpCost) {}
    virtual ~Action() {}

    virtual void Execute(Unit& actor, vector<Unit*>& targets) = 0;
    virtual bool CanExecute(const Unit& actor) const {
        return actor.getMP() >= mpCost;
    }
};

class BasicAttack : public Action {
public:
    BasicAttack() : Action(0) {}

    void Execute(Unit& actor, vector<Unit*>& targets) override;
};

class SingleTargetSkill : public Action {
public:
    SingleTargetSkill() : Action(5) {}

    void Execute(Unit& actor, vector<Unit*>& targets) override;
};

class MultiTargetSkill : public Action {
public:
    MultiTargetSkill() : Action(4) {}

    void Execute(Unit& actor, vector<Unit*>& targets) override;
};

class Heal : public Action {
public:
    Heal() : Action(3) {}

    void Execute(Unit& actor, vector<Unit*>& targets) override;
};

class Warrior : public Unit {
public:
    Warrior(const string& name);
};

class Assassin : public Unit {
public:
    Assassin(const string& name);
};

class Mage : public Unit {
public:
    Mage(const string& name);
};

vector<Unit*> CreateTeamBenilde();
vector<Unit*> CreateTeamOverwatch();
