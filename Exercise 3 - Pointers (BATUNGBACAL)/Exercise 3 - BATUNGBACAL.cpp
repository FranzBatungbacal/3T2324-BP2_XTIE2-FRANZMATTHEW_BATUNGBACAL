#include <iostream>
#include <random>
using namespace std;

int randomRange(int _min, int _max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(_min, _max);

    return distrib(gen);
}

struct Item
{
    string name;
    int gold;
};

Item* generateRandomItem() {

    Item* lootedItem = new Item();

    switch (randomRange(0, 4))
    {
    case 0:
        lootedItem->name = "Mithril Ore";
        lootedItem->gold = 100;
        break;

    case 1:
        lootedItem->name = "Sharp Talon";
        lootedItem->gold = 50;
        break;

    case 2:
        lootedItem->name = "Thick Leather";
        lootedItem->gold = 25;
        break;

    case 3:
        lootedItem->name = "Jellopy";
        lootedItem->gold = 5;
        break;

    default:
        lootedItem->name = "Cursed Stone";
        lootedItem->gold = 0;
        break;
    }

    return lootedItem;
}

void enterDungeon(int& gold, int& floor, int& bonusMultiplier, bool& canExplore)
{
    string userAnswer;
    int dungeonGold = 0;

    while (true)
    {
        if (gold < 25)
        {
            cout << "You don't have sufficient resources to go back into the dungeon." << endl;
            canExplore = false;
            return;
        }
        cout << "You've entered the dungeon and spent 25 gold." << endl;
        gold -= 25;

        cout << endl << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();

        while (true)
        {
            cout << " = = = = = = = = = = = = " << endl << endl;
            cout << "FLOOR: " << floor << endl << endl;
            cout << "BONUS MULTIPLIER: x" << bonusMultiplier << endl << endl;

            Item* randomItem = generateRandomItem();
            cout << "You got " << randomItem->name << endl;

            if (randomItem->gold <= 0)
            {
                cout << "Shit! You picked up the Cursed Stone and have fallen." << endl;


                cout << endl << "Press Enter to continue..." << endl;
                cin.ignore();
                cin.get();

                floor = 1;
                bonusMultiplier = 1;
                delete randomItem;
                break;
            }
            else
            {
                dungeonGold += randomItem->gold * bonusMultiplier; 
                cout << "Current gold: " << (gold + dungeonGold) << endl; 

                while (true)
                {
                    cout << "Do you want to go through the dungeon again? (Y/N)" << endl;
                    cin >> userAnswer;

                    if (userAnswer == "Y")
                    {
                        bonusMultiplier++;
                        floor++;
                        delete randomItem;
                        break;
                    }
                    else if (userAnswer == "N")
                    {
                        gold += dungeonGold;
                        cout << endl << "You now have " << gold << endl;
                        bonusMultiplier = 1;
                        floor = 1;

                        if (gold >= 500)
                        {
                            cout << "Well done traveler! You have reached your target gold! The whole town now knows the tales of your impressive feats." << endl;
                            canExplore = false;
                            delete randomItem;
                            return;
                        }
                        canExplore = false; // Add this line to stop the exploration
                        delete randomItem;
                        return; // Add this line to return immediately
                    }
                    else
                    {
                        cout << "Invalid Answer! Please choose from either 'Y' or 'N'" << endl;
                    }
                }


                cout << endl << "Press Enter to continue..." << endl;
                cin.ignore();
                cin.get();
            }
        }
    }
}

int main()
{
    int bonusMultiplier = 1;
    int gold = 50;
    int floor = 1;
    bool canExplore = true;

    cout << "You're an explorer with 50 gold to your name. Are you ready?" << endl << endl;

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    while (canExplore)
    {
        enterDungeon(gold, floor, bonusMultiplier, canExplore);
    }

    return 0;
}
