#include <isvalidstring.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    
    cout << "Ввод: ";
    getline(cin, str);

    bool result = checkstring(str);

    if (result) {
        cout << "Строка допустима" << "\n";
    } else {
        cout << "Строка недопустима" << "\n";
    }

    return 0;
}