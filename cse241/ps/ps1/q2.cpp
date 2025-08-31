#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int humanTurn(int humanTotalScore) {
    int turnScore = 0;
    bool continueRolling = true;
    char decision;

    cout << "\n[ Player's Turn ]\n";

    while (continueRolling) {
        int roll = rand() % 6 + 1;
        cout << "You rolled: " << roll << endl;

        if (roll != 1) {
            turnScore += roll;
            cout << "Turn points: " << turnScore 
                 << " (Total if hold: " << humanTotalScore + turnScore << ")\n";

            if (humanTotalScore + turnScore >= 100) {
                continueRolling = false;
            } else {
                cout << "Roll again? (r/h): ";
                cin >> decision;
                continueRolling = (decision == 'r');
            }
        } else {
            cout << "Rolled a 1! No points earned this turn.\n";
            turnScore = 0;
            continueRolling = false;
        }
    }

    cout << "Player's turn ended. Points gained: " << turnScore << endl;
    return turnScore;
}

int computerTurn(int computerTotalScore) {
    int turnScore = 0;
    bool rolling = true;

    cout << "\n[ Computer's Turn ]\n";

    for (; rolling && turnScore < 20 && computerTotalScore + turnScore < 100; ) {
        int roll = rand() % 6 + 1;
        cout << "Computer rolled: " << roll << endl;

        if (roll == 1) {
            cout << "Computer got unlucky! Rolled a 1.\n";
            turnScore = 0;
            rolling = false;
        } else {
            turnScore += roll;
            cout << "Computer's current points: " << turnScore 
                 << " (Potential total: " << computerTotalScore + turnScore << ")\n";
        }
    }

    cout << "Computer's turn ended. Points gained: " << turnScore << endl;
    return turnScore;
}

int main() {
    srand(time(0));
    int playerScore = 0, compScore = 0;

    while (playerScore < 100 && compScore < 100) {
        playerScore += humanTurn(playerScore);
        cout << "[Player's Total]: " << playerScore << endl;

        if (playerScore >= 100) {
            cout << "\nYou win!\n";
            break;
        }

        compScore += computerTurn(compScore);
        cout << "[Computer's Total]: " << compScore << endl;

        if (compScore >= 100) {
            cout << "\n Computer wins! \n";
            break;
        }
    }

    cout << "\nFinal Results:\n";
    cout << "Player: " << playerScore << "\nComputer: " << compScore << endl;

    return 0;
}
