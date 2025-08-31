#include "user.h"
#include <iostream>
#include <cctype> // isalpha

using namespace std;

namespace {
    string username;

    bool isValid() {
        if (username.length() != 8) return false;
        for (char ch : username) {
            if (!isalpha(ch)) return false;
        }
        return true;
    }
}

namespace Authenticate {
    void inputUserName() {
        do {
            cout << "Enter your username (exactly 8 letters): ";
            cin >> username;
        } while (!isValid());
    }

    string getUserName() {
        return username;
    }
}

