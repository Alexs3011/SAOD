#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <random>
#include <iomanip>


using namespace std;

/// ������� ��� �������� ������� ��������� ����.
/// ��������� �����-�������(������-������� � C++ � ��� ��������� �������, ������� ����� ���� ���������� ����� � ����� �� �������������.)
void time(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now(); // �������� ����� ������. auto ������������ ��� ��������������� ����������� ���� ����������
    func(); // ��������� ���������� �������
    auto end = std::chrono::high_resolution_clock::now(); // �������� ����� ���������
    chrono::duration<double> duration = end - start; // ��������� �������
    cout << "����� ������ ����: " << duration.count() << " ������" << endl;
}

/// ������� ��� ��������� ���������� ����� � �������� ���������. ��������� ������� ���������� �����
template <typename T>
T randomNumber(T min, T max) {
    static random_device rd; // �������� ��������� ����� 
    static mt19937 gen(rd()); // ��������� �������� �����. ���������� random_divice ��� ������ ���������� ��� ������ �������
    uniform_int_distribution<T> dist(min, max); // ����������� ������������� ���������� ����� � ������� ���������
    return dist(gen);
}

/// ������� ��� �������� ������� ���������� ������� � �������� ���������
template <typename T>
vector <T> randomArray(size_t size, T min, T max) {
    vector<T> arr(size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = randomNumber(min, max);
    }
    return arr;
}

/// ������� ��� �������� ��������������������� ������� 
template <typename T>
vector <T> monotonArray(size_t size, T min, T max) {
    vector <T> arr(size);
    T current = randomNumber(min, min + (max - min) / size); // ��������� ��������. ������������ ������ �������, ����� �� �������� ������� ������.
    for (size_t i = 0; i < size; i++) {
        arr[i] = current;
        current += getRandomNumber(1, (max - min) / size); // ��������� ��������� �������. ������������ ���, ����� �� ����� �� ������� max
    }
    return arr;
}

/// ����� ������� arr ������� size �� �����
template <typename T>
void printArray(T* arr, size_t size) {
    for (size_t i = 0; i < size; i++)					// ���� �� 0 �� ����� �������
        cout << setprecision(3) << arr[i] << " ";		// ���������� ����� � ����������� � �����
    cout << endl;
}

/// �����
template <typename T>
void testSort(T* arr, size_t size) {
    vector <T> arrSort (arr, arr + size);
    sort(arr.begin(), arr.end());
    assert(arrSort == arr);
}

//void testSort(T* arr, size_t size) {
//    // ������ ����� �������
//    std::vector<T> arrSort(arr, arr + size);
//
//    // ��������� ������������ ������
//    std::sort(arr, arr + size);
//
//    // ���������, ��� ��� ������� ������ ����������
//    assert(std::equal(arrSort.begin(), arrSort.end(), arr));
//
//    std::cout << "Test passed: array is sorted correctly.\n";
//}

// ������� ��������� ������ � �������
int lineSearch(const vector<int>& vec, int target) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i; // ���������� ������ ���������� ��������
        }
    }
    return -1; // ���� ������� �� ������
}