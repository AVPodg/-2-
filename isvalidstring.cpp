#include <isvalidstring.h>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool checkstring (string s){
    stack<char> stk;
    for (char c : s) {
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            if (stk.size() == 0) {
                return false;
            }
            stk.pop();
        } 
    }
    return stk.size() == 0;
}