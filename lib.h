#pragma once

int priority(char a);
bool isNumber(char a);
bool isOperation(char a);
bool isBrackets(char a);
int operation(int a, int b, char operation);
int makeNumber(std::string a);
std::string makeOPZ(std::string inExpression);
int resultOPZ(std::string outExpression);