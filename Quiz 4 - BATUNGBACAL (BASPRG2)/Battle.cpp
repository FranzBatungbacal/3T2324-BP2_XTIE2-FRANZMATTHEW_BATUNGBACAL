#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "Battle.h"

using namespace std;

void Battle(vector<Unit*>& playerTeam, vector<Unit*>& enemyTeam) {
    vector<Unit*> turnOrder;
    for (Unit* unit : playerTeam) {
        turnOrder.push_back(unit);
    }
    for (Unit* unit : enemyTeam) {
        turnOrder.push_back(unit);
    }
    sort(turnOrder.begin(), turnOrder.end(), [](Unit* a, Unit* b) {
        return a->getAGI() > b->getAGI();
        });

    while (!playerTeam.empty() && !enemyTeam.empty()) {
        for (auto it = turnOrder.begin(); it != turnOrder.end();) {
            Unit* actor = *it;
            if (actor->getHP() <= 0) {
                it = turnOrder.erase(it);
                continue;
            }

            vector<Unit*> targets;
            if (std::find(playerTeam.begin(), playerTeam.end(), actor) != playerTeam.end()) {
                targets = enemyTeam;
            }
            else {
                targets = playerTeam;
            }

            if (targets.empty()) break;

            cout << endl << "--- " << actor->GetName() << "'s Turn ---" << endl;
            actor->DisplayStats();

            if (find(playerTeam.begin(), playerTeam.end(), actor) != playerTeam.end()) {
                int actionChoice;
                cout << "Choose an action: " << endl;
                cout << "1. Basic Attack\n2. Single Target Skill\n3. Multi Target Skill\n4. Heal\n";
                cin >> actionChoice;

                Action* action;
                if (actionChoice == 1) {
                    action = new BasicAttack();
                }
                else if (actionChoice == 2) {
                    action = new SingleTargetSkill();
                }
                else if (actionChoice == 3) {
                    action = new MultiTargetSkill();
                }
                else if (actionChoice == 4) {
                    action = new Heal();
                }
                else {
                    cout << "Invalid action. Skipping turn." << endl;
                    it++;
                    continue;
                }

                if (action->CanExecute(*actor)) {
                    action->Execute(*actor, targets);
                }
                else {
                    cout << "Not enough MP. Skipping turn." << endl;
                }

                delete action;
            }
            else {
                if (rand() % 2 == 0 && actor->getMP() >= 5) {
                    Action* action = new SingleTargetSkill();
                    if (action->CanExecute(*actor)) {
                        action->Execute(*actor, targets);
                    }
                    delete action;
                }
                else {
                    Action* action = new BasicAttack();
                    action->Execute(*actor, targets);
                    delete action;
                }
            }

            it++;

            // Clear screen with a message
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        }

        playerTeam.erase(remove_if(playerTeam.begin(), playerTeam.end(), [](Unit* unit) {
            return unit->getHP() <= 0;
            }), playerTeam.end());

        enemyTeam.erase(remove_if(enemyTeam.begin(), enemyTeam.end(), [](Unit* unit) {
            return unit->getHP() <= 0;
            }), enemyTeam.end());
    }

    if (playerTeam.empty()) {
        cout << "Player team loses!" << endl;
    }
    else {
        cout << "Player team wins!" << endl;
    }
}
