#include <iostream>
#include <cmath> 
using namespace std;

class MyInteger {
private:
    int value;

public:
    MyInteger(int val = 0) {
        value = val;
    }

    void SetValue(int val) {
        value = val;
    }

    int GetValue() const {
        return value;
    }

    int operator[](int index) const {
        if (index < 0) return -1;

        int temp = value;

        for (int i = 0; i < index; ++i) {
            temp /= 10;
            if (temp == 0) return -1; 
        }

        return temp % 10;
    }
};

int main() {
    MyInteger num(418);

    cout << num[0] << " " << num[1] << " " << num[2] << " " << num[3] << endl;
    cout << num[3] << endl;
    cout << num[-1] << endl;

    return 0;
}

