#include "password.h"
#include <iostream>
#include <cctype> // isalpha

using namespace std;

namespace {
    string password;

    bool isValid() {
        if (password.length() < 8) return false;
        for (char ch : password) {
            if (!isalpha(ch)) return true; // contains at least one non-letter
        }
        return false;
    }
}

namespace Authenticate {
    void inputPassword() {
        do {
            cout << "Enter your password (at least 8 characters and at least one non-letter): ";
            cin >> password;
        } while (!isValid());
    }

    string getPassword() {
        return password;
    }
}

