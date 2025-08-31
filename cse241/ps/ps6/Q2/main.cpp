#include <iostream>
#include "user.h"
#include "password.h"

using namespace std;

int main() {
    Authenticate::inputUserName();
    Authenticate::inputPassword();

    cout << "\nUsername accepted: " << Authenticate::getUserName() << endl;
    cout << "Password accepted: " << Authenticate::getPassword() << endl;

    return 0;
}

