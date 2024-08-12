#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Wizard.h"

using namespace std;

int main() {
    srand(time(0));

    Wizard wizard1("Kimburdu", 250, 0, 10, 15);
    Wizard wizard2("Kimberlu", 250, 0, 10, 15);

    Spell spell1("Skunuruboomboomskrtt", 40, 60, 50);
    Spell spell2("MamaMoBenilde", 40, 60, 50);

    cout << endl << "--- Match Begins ---" << endl;

    while (wizard1.isAlive() && wizard2.isAlive()) {
      
        cout << endl << "--- Turn: " << wizard1.getName() << "'s ---" << endl;
        if (wizard1.getMP() >= 50) {
            spell1.Activate(wizard1, wizard2);
        }
        else {
            wizard1.Attack(wizard2);
        }

        if (!wizard2.isAlive()) {
            break;
        }

       
        cout << endl << "--- Turn: " << wizard2.getName() << "'s ---" << endl;
        if (wizard2.getMP() >= 50) {
            spell2.Activate(wizard2, wizard1);
        }
        else {
            wizard2.Attack(wizard1);
        }
        cout << endl << "--- Current HP & MP ---" << endl;
        cout << wizard1.getName() << " HP: " << wizard1.getHP() << ", MP: " << wizard1.getMP() << endl;
        cout << wizard2.getName() << " HP: " << wizard2.getHP() << ", MP: " << wizard2.getMP() << endl << endl;
    }

   
    if (wizard1.isAlive()) {
        cout << wizard1.getName() << " wins!" << endl;
    }
    else {
        cout << wizard2.getName() << " wins!" << endl;
    }

    return 0;
}
