#include <iostream>
#include <random>
#include <vector>
#include <Windows.h>

using namespace std;

int randomRange(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int diceRoll(int& die1, int& die2)
{
    die1 = randomRange(1, 6);
    die2 = randomRange(1, 6);
    cout << "Dice 1: " << die1 << endl;
    cout << "Dice 2: " << die2 << endl;
    return die1 + die2;
}

int betAmount(int bet, int& playerGoldAmount)
{
    playerGoldAmount -= bet;
    return playerGoldAmount;
}


int calculatePayout(int bet, int sum1, int sum2)
{
    if (sum1 > sum2) {
        cout << "You lost. Feelsbad bro" << endl;
        return 0;
    }
    else if (sum1 < sum2) {
        cout << "Nice! you won." << endl;
        return bet * 2;
    }
    else if (sum1 == 2) {
        cout << "Damn! that's so lucky." << endl;
        return bet * 4;
    }
    else {
        cout << "That's unfortunate. No one won." << endl;
        return bet;0
    }
}

void playRound(int& playerGoldAmount)
{
    int bet, dice1, dice2, sum1, sum2, payout;

    cout << "Betting Game!" << endl << endl;
    cout << "Take note that you can not bet ZERO or greater than your current gold.\nEnter the amount you're betting: ";
    cin >> bet;

    while (bet <= 0 || bet > playerGoldAmount)
    {ss
        cout << "You don't have that amount of money.\nEnter your bet: ";
        cin >> bet;
    }

    betAmount(bet, playerGoldAmount);
    cout << endl << "You have " << playerGoldAmount << " gold left.\n";

    sum1 = diceRoll(dice1, dice2);
    cout << "Enemy Roll Sum: " << sum1 << endl << endl;

    sum2 = diceRoll(dice1, dice2);
    cout << "Your Roll Sum: " << sum2 << endl << endl;

    payout = calculatePayout(bet, sum1, sum2);
    playerGoldAmount += payout;
    cout << "Payout: " << payout << endl;
    cout << "You have " << playerGoldAmount << " gold left.\n\n";

    system("pause");
    system("CLS");
    
}

int main()
{
    int playerGold = 1000;

    while (playerGold > 0)
    {
        playRound(playerGold);
    }

    return 0;
}
