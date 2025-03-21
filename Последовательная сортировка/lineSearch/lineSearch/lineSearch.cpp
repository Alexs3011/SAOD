#include <iostream>
#include <vector>
#include <algorithm> 
#include "functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    size_t size = 1000000000;
    int min = 1;
    int max = 500;
    float t = 0;

    float minTime = 0.000000000005;
    long long* arr = new long long[size];
    randomArray<long long>(arr, size, min, max);

    for (int i = 0; i < 1000000000000; i++) {
        int a = randomNumber(1, 500);

        t = time([&arr, size, a] {
            lineSearch<long long>(arr, size, a);
            });
        if (t > minTime) {
            minTime = t;
        }
        //delete[] arr;
    }
    cout << minTime;
    delete[] arr;
    return 0;
}
/* long long* arr = new long long[size];
    randomArray<long long>(arr, size, min, max);
    long long* arr2 = new long long[size];
    monotonArray<long long>(arr2, size, min, max);

    int a = randomNumber(1, 500);*/