#include <iostream>
#include <cstdlib>
using namespace std;

class HotDogStand {
public:

    HotDogStand();
    HotDogStand(int newID, int newNumSold);
    int GetID();
    void SetID(int newID);
    void JustSold();                  
    int GetNumSold();                
    static int GetTotalSold();       

private:
    static int totalSold;           
    int numSold;                    
    int ID;                         
};

int HotDogStand::totalSold = 0;

HotDogStand::HotDogStand() {
    ID = 0;
    numSold = 0;
}

HotDogStand::HotDogStand(int newID, int newNumSold) {
    ID = newID;
    numSold = newNumSold;
    totalSold += newNumSold;
}

int HotDogStand::GetID() {
    return ID;
}


void HotDogStand::SetID(int newID) {
    ID = newID;
}


void HotDogStand::JustSold() {
    numSold++;
    totalSold++;
}


int HotDogStand::GetNumSold() {
    return numSold;
}

int HotDogStand::GetTotalSold() {
    return totalSold;
}

int main() {
    HotDogStand stand1(1, 5);
    HotDogStand stand2(2, 3);
    HotDogStand stand3(3, 4);

    stand1.JustSold();
    stand2.JustSold();
    stand3.JustSold();
    stand3.JustSold();

    cout << "Stand 1 (ID: " << stand1.GetID() << ") sold: " << stand1.GetNumSold() << " hot dogs." << endl;
    cout << "Stand 2 (ID: " << stand2.GetID() << ") sold: " << stand2.GetNumSold() << " hot dogs." << endl;
    cout << "Stand 3 (ID: " << stand3.GetID() << ") sold: " << stand3.GetNumSold() << " hot dogs." << endl;

    cout << "Total hot dogs sold: " << HotDogStand::GetTotalSold() << endl;

    return 0;
}
