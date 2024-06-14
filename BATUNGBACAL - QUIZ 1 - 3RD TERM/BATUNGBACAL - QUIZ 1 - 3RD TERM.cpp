#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

vector<string> createDeck(bool isEmperorSide) 
{
    vector<string> deck;
    deck.insert(deck.end(), 4, "Civilian");
    deck.push_back(isEmperorSide ? "Emperor" : "Slave");
    return deck;
}

void removeCard(vector<string>& deck, int index) {
    deck.erase(deck.begin() + index);
}

void displayDeck(const vector<string>& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        cout << i + 1 << ". " << deck[i] << endl;
    }
}

string chooseCard(vector<string>& deck) {
    int choice;
    while (true) {
        cout << "Choose a card to play [1-" << deck.size() << "]: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > static_cast<int>(deck.size())) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            cout << "Invalid choice. Please enter a number between 1 and " << deck.size() << endl;
        }
        else {
            break;
        }
    }
    string chosenCard = deck[choice - 1];
    removeCard(deck, choice - 1);
    return chosenCard;
}

string opponentChooseCard(vector<string>& deck) {
    int choice = rand() % deck.size();
    string chosenCard = deck[choice];
    removeCard(deck, choice);
    return chosenCard;
}

int getWager(int mmLeft)
{
    int wager;
    bool validWager = false;

    while (!validWager) {
        cout << "Enter your wager: ";
        cin >> wager;

        if (cin.fail()) {
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You don't have that amount please enter another value. ty" << endl;
        }
        else {
            validWager = true;
        }
    }

    return wager;
}

int evaluateMatchup(const string& playerCard, const string& opponentCard) {
    if (playerCard == "Civilian" && opponentCard == "Slave") {
        return 1;
    }
    else if (playerCard == "Civilian" && opponentCard == "Emperor") {
        return -1;
    }
    else if (playerCard == "Civilian" && opponentCard == "Civilian") {
        return 0;
    }
    else if (playerCard == "Slave" && opponentCard == "Emperor") {
        return 1;
    }
    else if (playerCard == "Slave" && opponentCard == "Civilian") {
        return -1;
    }
    else if (playerCard == "Emperor" && opponentCard == "Civilian") {
        return 1;
    }
    else if (playerCard == "Emperor" && opponentCard == "Slave") {
        return -1;
    }
    else {
        return 0;
    }
}

void playRound(int round, int& moneyEarned, int& mmLeft) {
    bool isPlayerEmperor = ((round - 1) / 3) % 2 == 0;

    vector<string> playerDeck = createDeck(isPlayerEmperor);
    vector<string> opponentDeck = createDeck(!isPlayerEmperor);

    while (true) {
        system("CLS");
   
        cout << "Round: " << round << endl;
        cout << "You are playing as the " << (isPlayerEmperor ? "[Emperor]" : "[Slave]") << endl << endl;

        cout << "==================" << endl;
        cout << "Money Earned: " << moneyEarned << " yen" << endl;
        cout << "Millimeters left: " << mmLeft << " mm" << endl;
        cout << "==================" << endl;

        int wager = getWager(mmLeft);

        cout << endl << "Your deck:" << endl;
        displayDeck(playerDeck);

        string playerCard = chooseCard(playerDeck);
        string opponentCard = opponentChooseCard(opponentDeck);

        cout << "The opponent played: " << opponentCard << endl;

        int result = evaluateMatchup(playerCard, opponentCard);

        if (result == 1) {
            moneyEarned += wager * (isPlayerEmperor ? 100000 : 500000);
            cout << "You won the round! yey." << endl;
        }
        else if (result == -1) {
            mmLeft -= wager;
            cout << "You lost bro!" << endl;
        }
        else {
            cout << "It's a draw!" << endl;
        }

        if (playerCard == "Emperor" || playerCard == "Slave" || opponentCard == "Emperor" || opponentCard == "Slave") {
            break;
        }
    }

    cout << "\nPress Enter to proceed to the next round...";
    cin.ignore();
    cin.get();
}

bool shouldContinue(int round, int mmLeft) {
    return round <= 12 && mmLeft > 0;
}

void determineEnding(int round, int mmLeft, int moneyEarned) {
    if (mmLeft > 0 && moneyEarned >= 20000000) {
        cout << "HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLY. Best Ending" << endl;
    }
    else if (mmLeft > 0) {
        cout << "you did good? I guess. Meh Ending" << endl;
    }
    else {
        cout << "Boo! that's all I have to say for you. Bad Ending" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  

    int round = 1; 
    int mmLeft = 30;
    int moneyEarned = 0;

    while (shouldContinue(round, mmLeft)) 
    {
        playRound(round, moneyEarned, mmLeft);
        round++;
    }

    determineEnding(round, mmLeft, moneyEarned);

    cout << endl;
    return 0;
}