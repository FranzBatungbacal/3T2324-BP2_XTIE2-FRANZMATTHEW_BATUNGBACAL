#include "Unit.h"

using namespace std;

Unit::Unit(const string& name, int hp, int pow, int vit, int agi, int dex, int mp, const string& className)
    : name(name), hp(hp), maxHp(hp), pow(pow), vit(vit), agi(agi), dex(dex), mp(mp), className(className) {}

void Unit::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void Unit::Heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}

void Unit::AddMP(int amount) {
    mp += amount;
}

void Unit::UseMP(int amount) {
    mp -= amount;
    if (mp < 0) mp = 0;
}

void Unit::DisplayStats() const {
    cout << endl << "Name: " << name << endl;
    cout << "Class: " << className << endl;
    cout << "HP: " << hp << "/" << maxHp << endl;
    cout << "POW: " << pow << endl;
    cout << "VIT: " << vit << endl;
    cout << "AGI: " << agi << endl;
    cout << "DEX: " << dex << endl;
    cout << "MP: " << mp << endl;
}

void BasicAttack::Execute(Unit& actor, vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = targets[rand() % static_cast<int>(targets.size())];
    int baseDamage = actor.getPOW() + static_cast<int>(rand() % static_cast<int>(actor.getPOW() * 0.2));
    int damage = (baseDamage - target->getVIT() > 1) ? baseDamage - target->getVIT() : 1;
    int hitRate = (actor.getDEX() * 100) / target->getAGI();
    if (hitRate < 20) hitRate = 20;
    if (hitRate > 80) hitRate = 80;
    if (rand() % 100 < hitRate) {
        if (rand() % 100 < 20) {
            damage = round(damage * 1.2);
            cout << actor.GetName() << " critically hits " << target->GetName() << " for " << damage << " damage" << endl;
        }
        else {
            cout << actor.GetName() << " hits " << target->GetName() << " for " << damage << " damage" << endl;
        }
        target->TakeDamage(damage);
    }
    else {
        cout << actor.GetName() << " misses " << target->GetName() << endl;
    }
}

void SingleTargetSkill::Execute(Unit& actor, vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = *std::min_element(targets.begin(), targets.end(), [](Unit* a, Unit* b) {
        return a->getHP() < b->getHP();
        });
    int baseDamage = actor.getPOW() + static_cast<int>(rand() % static_cast<int>(actor.getPOW() * 0.2));
    int damage = (baseDamage * 2.2 - target->getVIT() > 1) ? static_cast<int>(baseDamage * 2.2 - target->getVIT()) : 1;
    std::cout << actor.GetName() << " uses Single Target Skill on " << target->GetName() << " for " << damage << " damage!\n";
    target->TakeDamage(damage);
    actor.UseMP(mpCost);
}

void MultiTargetSkill::Execute(Unit& actor, vector<Unit*>& targets) {
    for (Unit* target : targets) {
        int baseDamage = actor.getPOW() + static_cast<int>(rand() % static_cast<int>(actor.getPOW() * 0.2));
        int damage = (baseDamage * 0.9 - target->getVIT() > 1) ? static_cast<int>(baseDamage * 0.9 - target->getVIT()) : 1;
        cout << actor.GetName() << " uses Multi Target Skill on " << target->GetName() << " for " << damage << " damage" << endl;
        target->TakeDamage(damage);
    }
    actor.UseMP(mpCost);
}

void Heal::Execute(Unit& actor, std::vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = *std::min_element(targets.begin(), targets.end(), [](Unit* a, Unit* b) {
        return a->getHP() < b->getHP();
        });
    int healAmount = static_cast<int>(target->getMaxHP() * 0.3);
    cout << actor.GetName() << " uses Heal on " << target->GetName() << " for " << healAmount << " HP" << endl;
    target->Heal(healAmount);
    actor.UseMP(mpCost);
}

Warrior::Warrior(const string& name)
    : Unit(name, 100, 20, 10, 5, 10, 10, "Warrior") {}

Assassin::Assassin(const string& name)
    : Unit(name, 80, 15, 5, 20, 15, 10, "Assassin") {}

Mage::Mage(const string& name)
    : Unit(name, 60, 25, 5, 10, 10, 10, "Mage") {}

vector<Unit*> CreateTeamBenilde() {
    Unit* Trez = new Warrior("Trez");
    Unit* Mari = new Assassin("Mari");
    Unit* Andrei = new Mage("Andrei");

    Trez->AddMP(5);
    Mari->AddMP(5);
    Andrei->AddMP(3);

    return { Trez, Mari, Andrei };
}

vector<Unit*> CreateTeamOverwatch() {
    Unit* Reinhardt = new Warrior("Reinhardt");
    Unit* Tracer = new Assassin("Tracer");
    Unit* Mercy = new Mage("Mercy");

    Reinhardt->AddMP(5);
    Tracer->AddMP(5);
    Mercy->AddMP(3);

    return { Reinhardt, Tracer, Mercy };
}
