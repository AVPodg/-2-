#include <isvalidstring.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    
    cout << "input:" << "\n";
    getline(cin, str);

    bool result = isValidParentheses(str);

    if (result) {
        cout << "String true" << "\n";
    } else {
        cout << "String false" << "\n";
    }

    return 0;
}