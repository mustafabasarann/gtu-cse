#include <iostream>
#include <vector>

int main() {
    int current = 0;
    int numSuitors;

    std::cout << "Enter the number of suitors: ";
    std::cin >> numSuitors;

    if (numSuitors <= 0) {
        std::cout << "Not enough suitors." << std::endl;
        return 0;
    }

    std::vector<int> suitors(numSuitors);
    for (int i = 0; i < numSuitors; i++) {
        suitors[i] = i + 1;
    }

    while (suitors.size() > 1) {
        current = (current + 2) % suitors.size(); 
        suitors.erase(suitors.begin() + current);
    }

    std::cout << "To win the princess, you should stand in position " << suitors[0] << std::endl;
    return 0;
}

