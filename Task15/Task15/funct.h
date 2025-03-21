#pragma once
#include <iostream>
#include <chrono>
#include <cassert>
#include <functional>

using namespace std;
using namespace chrono;

/// ������� ��� �������� ������� ���������� ����. 
float time(const function<void()>& func) {
    auto start = chrono::high_resolution_clock::now(); // �������� ����� ������
    func(); // ��������� ���������� �������
    auto end = chrono::high_resolution_clock::now(); // �������� ����� ���������
    return duration_cast<nanoseconds>(end - start).count(); // ���������� ����� � ������������
}

// ����������� ������� ��� �������� ���������� ���� � �����.
int countDigitsRecursive(int n) {
    if (n < 10) return 1;
    return 1 + countDigitsRecursive(n / 10);
}


// ����������� ������� ��� �������� ���������� ���� � �����.
int countDigitsIterative(int n) {
    int count = 0;
    do {
        count++;
        n /= 10;
    } while (n != 0);
    return count;
}

// �����
void runTests() {
    assert(countDigitsRecursive(0) == 1);
    assert(countDigitsRecursive(5) == 1);
    assert(countDigitsRecursive(10) == 2);
    assert(countDigitsRecursive(123456) == 6);
    assert(countDigitsRecursive(987654321) == 9);

    assert(countDigitsIterative(0) == 1);
    assert(countDigitsIterative(5) == 1);
    assert(countDigitsIterative(10) == 2);
    assert(countDigitsIterative(123456) == 6);
    assert(countDigitsIterative(987654321) == 9);
}