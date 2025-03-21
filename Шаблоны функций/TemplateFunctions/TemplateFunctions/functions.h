#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <random>
#include <iomanip>


using namespace std;

/// Функция для подсчёта времени выполения кода.
/// Принимает лямда-функцию(Лямбда-функция в C++ — это анонимная функция, которая может быть определена прямо в месте ее использования.)
void time(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now(); // Засекаем время начала. auto используется для автоматического определения типа переменной
    func(); // Выполняем переданную функцию
    auto end = std::chrono::high_resolution_clock::now(); // Засекаем время окончания
    chrono::duration<double> duration = end - start; // Вычисляем разницу
    cout << "Время работы кода: " << duration.count() << " секунд" << endl;
}

/// Функция для генерации случайного числа в заданном диапазоне. Принимает границы случайного числа
template <typename T>
T randomNumber(T min, T max) {
    static random_device rd; // Получаем случайное число 
    static mt19937 gen(rd()); // Генератор случаных чисел. Используем random_divice для разных резуьтатов при каждом запуске
    uniform_int_distribution<T> dist(min, max); // Равномерное распределение случайного числа в заанном диапазоне
    return dist(gen);
}

/// Функция для создания массива случайными числами в заданном диапазоне
template <typename T>
vector <T> randomArray(size_t size, T min, T max) {
    vector<T> arr(size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = randomNumber(min, max);
    }
    return arr;
}

/// Функция для создания монотоновозрастаюзего массива 
template <typename T>
vector <T> monotonArray(size_t size, T min, T max) {
    vector <T> arr(size);
    T current = randomNumber(min, min + (max - min) / size); // Начальное значение. Ограничиваем первый элемент, чтобы не начинать слишком высоко.
    for (size_t i = 0; i < size; i++) {
        arr[i] = current;
        current += getRandomNumber(1, (max - min) / size); // добавляет случайный прирост. ограничивает шаг, чтобы не выйти за пределы max
    }
    return arr;
}

/// Вывод массива arr размера size на экран
template <typename T>
void printArray(T* arr, size_t size) {
    for (size_t i = 0; i < size; i++)					// цикл от 0 до конца массива
        cout << setprecision(3) << arr[i] << " ";		// происходит вывод с округлением в цикле
    cout << endl;
}

/// Тесты
template <typename T>
void testSort(T* arr, size_t size) {
    vector <T> arrSort (arr, arr + size);
    sort(arr.begin(), arr.end());
    assert(arrSort == arr);
}

//void testSort(T* arr, size_t size) {
//    // Создаём копию массива
//    std::vector<T> arrSort(arr, arr + size);
//
//    // Сортируем оригинальный массив
//    std::sort(arr, arr + size);
//
//    // Проверяем, что оба массива теперь одинаковые
//    assert(std::equal(arrSort.begin(), arrSort.end(), arr));
//
//    std::cout << "Test passed: array is sorted correctly.\n";
//}

// Функция линейного поиска в векторе
int lineSearch(const vector<int>& vec, int target) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i; // Возвращаем индекс найденного элемента
        }
    }
    return -1; // Если элемент не найден
}