#include <iostream>
#include <string>
#include <vector>
#include "lib.h"

using namespace std;

int priority(char a) {
    switch (a) {
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
        case ')':
            return 1;
        default:
            return 0;
    }
}
bool isNumber(char a) {
    for (int i = 0; i < 10; i++) {
        if ((int)a == (i + 48)) {
            return true;
        }
    }
    return false;
}
bool isOperation(char a) {
    switch (a) {
        case '*':
        case '/':
        case '+':
        case '-':
            return true;
        default: return false;
    };
}
bool isBrackets(char a) {
    switch (a) {
        case '(':
        case ')':
            return true;
        default: return false;
    };
}

int operation(int a, int b, char operation) {
    if (operation == '*') {
        return a * b;
    } else if (operation == '/') {
        return a / b;
    } else if (operation == '+') {
        return a + b;
    } else if (operation == '-') {
        return a - b;
    }
}
int makeNumber(string a) {
    bool flag = false;
    int i = 0;
    if (a[0] == '-') {
        flag = true;
        i++;
    }
    int result = 0;
    while (i < a.length()) {
        result *= 10;
        result += (int)a[i] - 48;
        i++;
    }
    if (flag) {
        result *= -1;
    }
    return result;
}

string makeOPZ(string inExpression) {
    vector<char> stack;
    vector<string> opzExpression;
    string outExpression = "";

    for (int i = 0; i < inExpression.length(); i++) {
        if (isNumber(inExpression[i])) { // выводим число
            outExpression += inExpression[i];
            if (!isNumber(inExpression[i+1])){
                outExpression += " ";
            }
        } else if (isOperation(inExpression[i])) { // обрабатываем операцию
            if (!stack.empty()) {
                while (priority(stack.back()) >= priority(inExpression[i])) {
                    outExpression += (char)stack.back();
                    outExpression += " ";
                    stack.pop_back();
                }
            }
            stack.push_back(inExpression[i]);
        } else if (isBrackets(inExpression[i])) { // обрабатываем скобки
            if (inExpression[i] == '(') { // пихаем в стек
                stack.push_back(inExpression[i]);
            } else if (!stack.empty()) {
                while(stack.back() != '(') {// достаём из стека пока не увидим (
                    outExpression += (char)stack.back();
                    outExpression += " ";
                    stack.pop_back();
                }
                stack.pop_back(); // удаление ( из стека
            }
        } else {
            cout << "всё плохо";
        }
    }

    while (!stack.empty()) {
        outExpression += (char)stack.back();
        outExpression += " ";
        stack.pop_back();
    }

    return outExpression;
}
int resultOPZ(string outExpression) {
    vector<string> opzExpression;
    vector<string> opzExpressionHelp;

    int len = outExpression.length() - 1;
    string help = "";

    while (len >= 0) {
        if (outExpression[len] != ' ') {
            help = outExpression[len] + help;
        } else if (len == 0 || help != ""){
            opzExpression.push_back(help);
            help = "";
        }
        len--;
    }
    opzExpression.push_back(help); // развёрнутая строка поделённая на объекты

    int num1;
    int num2;

    while (!opzExpression.empty()) {
        if (isOperation(opzExpression.back()[0])) {
            num1 = makeNumber(opzExpressionHelp.back());
            opzExpressionHelp.pop_back();

            num2 = makeNumber(opzExpressionHelp.back());
            opzExpressionHelp.pop_back();

            opzExpressionHelp.push_back(to_string(operation(num2, num1, opzExpression.back()[0])));
            opzExpression.pop_back();
        } else {
            opzExpressionHelp.push_back(opzExpression.back());
            opzExpression.pop_back();
        }
    }

    return makeNumber(opzExpressionHelp.back());
}