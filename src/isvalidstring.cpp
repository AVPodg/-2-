#include "isvalidstring.h"
#include <stack>
#include <string>

bool isValidParentheses(std::string s) {
    std::stack<char> stk;
    
    for (char c : s) {
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            if (stk.empty()) {
                return false;
            }
            stk.pop();
        }
    }
    
    return stk.empty();
}