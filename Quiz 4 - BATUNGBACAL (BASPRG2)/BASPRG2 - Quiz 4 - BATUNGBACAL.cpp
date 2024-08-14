#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Unit.h"
#include "Unit.h"
#include "Battle.h"

using namespace std;

int main() {
    srand(time(0));

    vector<Unit*> playerTeam = CreateTeamBenilde();
    vector<Unit*> enemyTeam = CreateTeamOverwatch();

    cout << endl << "--- Player Team ---" << endl;
    for (Unit* unit : playerTeam) {
        unit->DisplayStats();
    }

    cout << endl << "--- Enemy Team ---" << endl;
    for (Unit* unit : enemyTeam) {
        unit->DisplayStats();
    }

    Battle(playerTeam, enemyTeam);

    for (Unit* unit : playerTeam) {
        delete unit;
    }

    for (Unit* unit : enemyTeam) {
        delete unit;
    }
}