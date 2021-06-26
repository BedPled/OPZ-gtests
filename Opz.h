//
// Created by BedTed on 6/26/2021.
//

#ifndef OPZ_OPZ_H
#define OPZ_OPZ_H

#include "Operation.h"
#include <set>
#include <vector>

using namespace std;

class Opz {
vector <char> operationsChars;
vector <int> operationsPriority;
vector <AOperation*> operations;

private:
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

    bool isNumber(char a) {
        for (int i = 0; i < 10; i++) {
            if ((int)a == (i + 48)) {
                return true;
            }
        }
        return false;
    }

    AOperation * backOperation (char a) {
        for (int i = 0; i < operationsChars.size(); ++i) {
            if (operationsChars[i] == a) return operations[i];
        }
        return nullptr;
    }

    bool isOperation (char a) {
        for (int i = 0; i < operationsChars.size(); ++i) {
            if (operationsChars[i] == a) return true;
        }
        return false;
    }

    bool isBrackets(char a) {
        switch (a) {
            case '(':
            case ')':
                return true;
            default: return false;
        }
    }
public:
int priority (char a) {
    for (int i = 0; i < operationsChars.size(); ++i) {
        if (operationsChars[i] == a)
            return operationsPriority[i];
    }
    return 0;
}

    int OPZ_Operation(int a, int b, AOperation *c) {
        return c->operation(a,b);
    }

    Opz() {
        operationsChars.push_back('-');
        operationsPriority.push_back(2);

        operationsChars.push_back('+');
        operationsPriority.push_back(2);

        operationsChars.push_back('*');
        operationsPriority.push_back(3);

        operationsChars.push_back('/');
        operationsPriority.push_back(3);
    }

    void addOperation (int priority, char operation, AOperation *op) {
        operationsChars.push_back(operation);
        operationsPriority.push_back(priority);
        operations.push_back(op);
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

                opzExpressionHelp.push_back(to_string(OPZ_Operation(num2, num1, backOperation(opzExpression.back()[0]) )));
                opzExpression.pop_back();
            } else {
                opzExpressionHelp.push_back(opzExpression.back());
                opzExpression.pop_back();
            }
        }

        return makeNumber(opzExpressionHelp.back());
    }

};


#endif //OPZ_OPZ_H
