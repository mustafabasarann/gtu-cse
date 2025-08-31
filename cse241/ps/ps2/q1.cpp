#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool shoot(int probability) {
    return rand() % 100 < probability;
}

int main() 
{
    srand(time(0));

    const int totalDuels = 10000;
    int winsAaron = 0, winsBob = 0, winsCharlie = 0;

    for (int i = 0; i < totalDuels; i++) 
    {
        bool alive[3] = {true, true, true};

        while ((alive[0] + alive[1] + alive[2]) > 1) 
        {
            if (alive[0]) 
            {
                if (alive[2] && shoot(33)) alive[2] = false;
                else if (alive[1] && shoot(33)) alive[1] = false;
            }

            if (alive[1]) 
            {
                if (alive[2] && shoot(50)) alive[2] = false;
                else if (alive[0] && shoot(50)) alive[0] = false;
            }

            if (alive[2]) 
            {
                if (alive[1]) alive[1] = false;
                else if (alive[0]) alive[0] = false;
            }
        }

        if (alive[0]) winsAaron++;
        if (alive[1]) winsBob++;
        if (alive[2]) winsCharlie++;
    }

    cout << "Aaron won: " << winsAaron << " / " << totalDuels << " (" << (winsAaron * 100.0 / totalDuels) << "%)\n";
    cout << "Bob won: " << winsBob << " / " << totalDuels << " (" << (winsBob * 100.0 / totalDuels) << "%)\n";
    cout << "Charlie won: " << winsCharlie << " / " << totalDuels << " (" << (winsCharlie * 100.0 / totalDuels) << "%)\n";

    return 0;
}

