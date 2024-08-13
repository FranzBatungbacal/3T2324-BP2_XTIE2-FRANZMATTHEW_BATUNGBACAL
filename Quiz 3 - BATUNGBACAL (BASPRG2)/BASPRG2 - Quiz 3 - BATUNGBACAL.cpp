#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Unit.h"


using namespace std;


int main() {
    srand(time(0));

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    system("CLS");

    int classChoice;
    cout << "Choose your class:\n[1] Warrior\n[2] Assassin\n[3] Mage\n";
    cin >> classChoice;
    system("CLS");

    Unit* player;
    if (classChoice == 1) {
        player = new Warrior(playerName);
    }
    else if (classChoice == 2) {
        player = new Assassin(playerName);
    }
    else if (classChoice == 3) {
        player = new Mage(playerName);
    }
    else {
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }

    int level = 1;
    while (player->getHP() > 0) {
        cout << "--- Level " << level << " ---" << endl << endl;
        player->DisplayStats();

        int opponentClass = rand() % 3;
        Unit* opponent;
        if (opponentClass == 0) {
            opponent = new Warrior("Warrior");
        }
        else if (opponentClass == 1) {
            opponent = new Assassin("Assassin");
        }
        else {
            opponent = new Mage("Mage");
        }

        cout << endl << "An opponent appears! " << opponent->getClassName() << endl;
        opponent->DisplayStats();
        Battle(*player, *opponent);
        system("CLS");

        delete opponent;
        level++;
    }

    cout << "Game Over! You reached level " << level - 1 << ".\n";
    delete player;

    return 0;
}