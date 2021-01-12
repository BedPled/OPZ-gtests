#include <iostream>
#include "lib.h"
using namespace std;

int main() {

    string inExpression;
    string outExpression;

    cout << "Введите выражение: ";
    cin >> inExpression;

    cout << "Выходная строка: ";
    outExpression = makeOPZ(inExpression);
    cout << outExpression;
    cout << endl << "Результат: " << resultOPZ(outExpression) << endl;

    return 0;
}
