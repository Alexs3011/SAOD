//Подсчитать количество цифр в заданном числе с помощью рекурсии и итерации.
#include "funct.h"

int main() {
    runTests();

    setlocale(LC_ALL, "Russian");
    int number;
    cout << "Введите число: ";
    cin >> number;
    number = abs(number); // Знак не важен

    // Замер времени для рекурсивной функции
    float recursiveTime = time([&number]() { countDigitsRecursive(number);});
    int recursiveResult = countDigitsRecursive(number);

    // Замер времени для итеративной функции
    float iterativeTime = time([&number]() { countDigitsIterative(number);});
    int iterativeResult = countDigitsIterative(number);

    cout << "Рекурсивный результат: " << recursiveResult << ", время: " << recursiveTime << " нс" << endl;
    cout << "Итеративный результат: " << iterativeResult << ", время: " << iterativeTime << " нс" << endl;

    return 0;
}