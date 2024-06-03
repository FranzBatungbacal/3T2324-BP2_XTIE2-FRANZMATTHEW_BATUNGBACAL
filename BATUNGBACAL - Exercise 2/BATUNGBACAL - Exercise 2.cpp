#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int randomRange(int _min, int _max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(_min, _max);

    return distrib(gen);
}

void getRandomItems(vector<string>& items)
{
    string choices[] = { "RedPotion", "Elixir", "EmptyBottle", "BluePotion" };
    int _choicesCount = (end(choices) - begin(choices)) - 1;
    for (int i = 0; i < 10; i++)
    {
        items.push_back(choices[randomRange(0, _choicesCount)]);
    }
}


// Ex 2-2
void displayInventory(const vector<string>& items)
{
    cout << "You opened a goodie bag and got! " << endl << endl;
    for (const string& item : items)
        cout << item << " ";
    cout << endl << endl;
}

// Ex 2-3
int countItem(const vector<string>& items)
{
    array<int, 4> inventoryCount = { 0, 0, 0, 0 };

    for (const string& item : items) {
        if (item == "RedPotion") {
            inventoryCount[0]++;
        }
        else if (item == "Elixir") {
            inventoryCount[1]++;
        }
        else if (item == "EmptyBottle") {
            inventoryCount[2]++;
        }
        else if (item == "BluePotion") {
            inventoryCount[3]++;
        }
    }

    int redPotionCount = inventoryCount[0];
    int elixirCount = inventoryCount[1];
    int emptyBottleCount = inventoryCount[2];
    int bluePotionCount = inventoryCount[3];

    cout << "Your current inventory: " << endl << endl;
    cout << "Red Potion: " << redPotionCount << endl;
    cout << "Elixir: " << elixirCount << endl;
    cout << "Empty Bottle: " << emptyBottleCount << endl;
    cout << "Blue Potion: " << bluePotionCount << endl;
    cout << endl;

    int totalItems = redPotionCount + elixirCount + emptyBottleCount + bluePotionCount;

    cout << "You currently hold " << totalItems << " items in your inventory." << endl;
    return totalItems;
}

// Ex 2-4
void removeItem(vector<string>& items)
{
    char userAnswer;
    string userItemRemove;
    bool validAnswer;

    do {

        cout << "Do you want to get rid of something to free up some space? [Y/N]  ";
        cin >> userAnswer;

        if (userAnswer == 'Y') {
            cout << "What item do you wish to remove: ";
            cin >> userItemRemove;

            auto itemPlace = find(items.begin(), items.end(), userItemRemove);
            if (itemPlace != items.end()) {
                items.erase(itemPlace);
                cout << "You have removed " << userItemRemove << " from your inventory." << endl << endl;
            }
            else {
                cout << "The item is not in your inventory. Please check your spelling!" << endl;
            }
            validAnswer = false;
        }

        else if (userAnswer == 'N') {
            cout << "You have decided to keep all items." << endl;
            validAnswer = false;
        }
    } while (validAnswer);
}

int main()
{
    vector<string> items;
    getRandomItems(items);
    displayInventory(items);
    system("pause");
    system("CLS");

    //Items
    countItem(items);
    removeItem(items);

    return 0;
}
