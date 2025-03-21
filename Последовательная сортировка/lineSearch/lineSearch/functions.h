#include <iostream>
#include <chrono>
#include <functional>
#include <vector>
#include <cassert>
#include <algorithm>
#include <random>
#include <iomanip>
#include <math.h>
#include <fstream>


using namespace std;
using namespace std;

/// Функция для подсчёта времени выполнения кода. 
float time(const function<void()>& func) {
    auto start = chrono::high_resolution_clock::now(); // Засекаем время начала
    func(); // Выполняем переданную функцию
    auto end = chrono::high_resolution_clock::now(); // Засекаем время окончания
    chrono::duration<double> duration = end - start; // Вычисляем разницу
    return duration.count();
}

/// Функция для генерации случайного числа в заданном диапазоне
template <typename T>
T randomNumber(T min, T max) {
    static random_device rd; // Источник случайности
    static mt19937 gen(rd()); // Генератор случайных чисел
    uniform_int_distribution<T> distr(min, max); // Равномерное распределение случайного числа в заданном диапазоне
    return distr(gen);
}

/// Функция для создания массива случайных чисел в заданном диапазоне
template <typename T>
void randomArray(T arr[], size_t size, T min, T max) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = randomNumber(min, max); // Заполняем массив случайными числами
    }
}

/// Функция для создания монотонно возрастающего массива
template <typename T>
void monotonArray(T arr[], size_t size, T min, T max) {
    T current = randomNumber(int(min), int(min + (max - min))); // Начальное значение
    for (size_t i = 0; i < size; i++) {
        arr[i] = current;
        current += randomNumber(1, int((max - min))); // Добавляет случайный прирост
    }
}

/// Вывод массива на экран
template <typename T>
void printArray(const T arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << setprecision(3) << arr[i] << " "; // Вывод с округлением
    }
    cout << endl;
}

// Возвращает булевое значение, отвечающее на вопрос, отсортирован массив array типа T* размера или нет
template <typename T>
bool is_sorted(T* array, size_t size) {
	for (size_t i = 1; i < size; ++i) {
		if (array[i] < array[i - 1]) { // Если каждый следующий массив меньше предыдущего
			return false;  // Если порядок нарушен
		}
	}
	return true; // Если массив отсортирован
}


/// Тест функции сортировки массива is_sorted
void test_is_sorted() {

	// Отсортированные массивы
	int arr_sorted1[] = { 1, 2, 3, 4, 5 }; // Только  положительные элементы
	int arr_sorted2[] = { -5, -3, -1, 0, 2, 4, 6 }; // И положительные, и отрицательные элементы
	int arr_sorted3[] = { 10 }; // Один элемент
	int* arr_sorted4 = nullptr; // Пустой массив


	assert(is_sorted(arr_sorted1, 5) == true);
	assert(is_sorted(arr_sorted2, 7) == true);
	assert(is_sorted(arr_sorted3, 1) == true);
	assert(is_sorted(arr_sorted4, 0) == true);

	// Неотсортированные массивы
	int arr_unsorted1[] = { 1, 3, 2, 4, 5 };
	int arr_unsorted2[] = { 5, 4, 3, 2, 1 }; // Обратный порядок
	int arr_unsorted3[] = { 10, 10, 9, 10 }; // Повторяющиеся элементы, но не по порядку
	int arr_unsorted4[] = { -1, -2, -3, 0 };

	assert(is_sorted(arr_unsorted1, 5) == false);
	assert(is_sorted(arr_unsorted2, 5) == false);
	assert(is_sorted(arr_unsorted3, 4) == false);
	assert(is_sorted(arr_unsorted4, 4) == false);

	// Массив с одинаковыми элементами
	int arr_same_elements[] = { 5, 5, 5, 5, 5 };
	assert(is_sorted(arr_same_elements, 5) == true);

	// Массив с парой одинаковых соседних элементов
	int arr_with_duplicates[] = { 1, 2, 2, 3, 4 };
	assert(is_sorted(arr_with_duplicates, 5) == true);

}

/// Сохранение массива в файл
void saveArrayToFile(const std::string& filename, const int* array, size_t size) {
    std::ofstream file(filename);
    for (size_t i = 0; i < size; ++i) {
        file << array[i] << " ";
    }
}

/// Функция последовательного поиска в массиве
//1.Лучший случай: O(1)
//2.Средний случай:O(n)
//3.Худший случай: O(n)
template <typename T>
T lineSearch(const T arr[], size_t size, T target) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; 
        }
    }
    return size;
}

/// Функция бинарного поиска в отсортированном массиве
//1.Лучший случай: O(1)
//2.Средний случай:O(log n)
//3.Худший случай: O(log n)
template <typename T>
T binarySearch(const T arr[], size_t size, T target) {
    size_t left = 0, right = size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Найденный элемент
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return size; // Элемент не найден
}

/// Функция тестирования последовательного поиска
void test_sequential_search() {

	// Массив для тестирования функции
	int arr1[] = { 10, 20, 30, 40, 50 };
	// Размер массива
	size_t size1 = 5;

	// Элемент находится в середине
	assert(sequential_search(arr1, size1, 30) == 2);

	// Элемент в начале
	assert(sequential_search(arr1, size1, 10) == 0);

	// Элемент в конце
	assert(sequential_search(arr1, size1, 50) == 4);

	// Элемента нет в массиве 
	assert(sequential_search(arr1, size1, 5) == size1);

	// Элемента нет в массиве 
	assert(sequential_search(arr1, size1, 60) == size1);

	// Элемента нет в массиве 
	assert(sequential_search(arr1, size1, 35) == size1);

	// Поиск в массиве из одного элемента (найден)
	int arr2[] = { 100 };
	assert(sequential_search(arr2, 1, 100) == 0);

	// Поиск в массиве из одного элемента (не найден)
	assert(sequential_search(arr2, 1, 200) == 1);

}

/// Тест функции бинарного поиска
void test_binary_search() {
	// Массив для тестирования функции
	int sorted_array[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	// Размер массива
	size_t size_test = 8;
	// Элемент в середине
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 7) == 3);

	// Первый элемент
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 1) == 0);

	// Последний элемент
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 15) == 7);

	// Отсутствующий элемент
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 8) == size_test);

	// Поиск в массиве из одного элемента
	int one_element_array[] = { 42 };
	assert(binary_search_recursive<int>(one_element_array, 0, 0, 42) == 0);
	assert(binary_search_recursive<int>(one_element_array, 0, 0, 0) == size_test);
}

/// Сортировка пузырьком массива arr размера size по возрастанию
//1.Лучший случай: O(n) 
//2.Среднее: O(n2) 
//3.Худшее: O(n2) 
template<typename T>
void bubble_sort(T* arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])// Eсли предыдущий элемент больше следующего
            {
                swap(arr[j], arr[j + 1]);// Меняем местами
            }
    }
}

/// Тест работы функции сортировки пузырьком
void bubble_assert()
{
    // Целые числа
    int* int_arr = new int[7] { 64, 34, 25, 12, 22, 11, 90 };
    int* int_arr_sort = new int[7] { 11, 12, 22, 25, 34, 64, 90 };
    int* int_arr0 = new int[7] { 90, 64, 34, 25, 22, 12, 11 };
    int* int_arr2 = new int[7] { 11, 12, 22, 25, 34, 64, 90 };

    bubble_sort(int_arr, 7);
    bubble_sort(int_arr0, 7);
    bubble_sort(int_arr2, 7);
    for (size_t i = 0; i < 7; i++)
    {
        assert(int_arr[i] == int_arr_sort[i]);
        assert(int_arr0[i] == int_arr_sort[i]);
        assert(int_arr2[i] == int_arr_sort[i]);
    }
    delete[] int_arr;
    delete[] int_arr0;
    delete[] int_arr2;
    delete[] int_arr_sort;


    // Целые числа, повторяющиеся элементы
    int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
    int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

    bubble_sort(int_arr1, 7);
    for (size_t i = 0; i < 7; i++)
    {
        assert(int_arr1[i] == int_arr_sort1[i]);
    }
    delete[] int_arr1;
    delete[] int_arr_sort1;

    // Дробные числа
    double* double_arr = new double[3] { 1.03, 1.01, 1.02 };
    double* double_arr_sort = new double[3] { 1.01, 1.02, 1.03 };
    bubble_sort(double_arr, 3);
    for (size_t i = 0; i < 3; i++)
    {
        assert(double_arr[i] == double_arr_sort[i]);
    }
    delete[] double_arr;
    delete[] double_arr_sort;
}

/// Функция для слияния двух подмассивов arr, где left начало массива = 0, right = размеру массива 
/// mid - середина массива, по которой мы делим (вычисляется в функции merge_sort). По возрастанию
/// Сложность по памяти O(n + m), где n и m - размеры двух массивов
template <typename T>
void merge(T* arr, size_t left, size_t mid, size_t right) {
	size_t n1 = mid - left + 1;// Вычисление размера левого подмассива
	size_t n2 = right - mid;// Вычисление размера правого подмассива

	T* l = new T[n1];// Динамическое выделение памяти для массива L, R
	T* r = new T[n2];

	memcpy(l, &arr[left], n1 * sizeof(T));// Копирование данных во временный массив L
	memcpy(r, &arr[mid + 1], n2 * sizeof(T));// Копирование данных во временный массив R

	size_t i = 0;// Инициализация индексов для объединения двух подмассивов
	size_t j = 0;
	size_t k = left;

	while (i < n1 && j < n2) {// Слияние двух подмассивов в основной массив arr
		if (l[i] <= r[j]) {
			arr[k] = l[i];
			i++;
		}
		else {
			arr[k] = r[j];
			j++;
		}
		k++;
	}

	if (i < n1) {
		memcpy(&arr[k], &l[i], (n1 - i) * sizeof(T)); // Добавление оставшихся элементов из левого подмассива
		k += n1 - i;
	}

	if (j < n2) {
		memcpy(&arr[k], &r[j], (n2 - j) * sizeof(T)); // Добавление оставшихся элементов из правого подмассива
		k += n2 - j;
	}

	delete[] l;
	delete[] r;
}

/// Функция для рекурсивной сортировки слиянием массива arr, где left начало массива = 0, а right = размеру массива по возрастанию
//1.Лучший случай: O(n log n)
//2.Средний случай:O(n log n)
//3.Худший случай: O(n log n)
template <typename T>
void merge_sort(T* arr, size_t left, size_t right) {
	if (left < right) {// Проверка, что левое значение меньше правого

		size_t mid = left + (right - left) / 2;// Вычисление середины массива

		merge_sort(arr, left, mid);// Рекурсивный вызов merge_sort для левой части массива
		merge_sort(arr, mid + 1, right);// Рекурсивный вызов merge_sort для правой части массива

		merge(arr, left, mid, right);// Вызов функции merge для слияния двух отсортированных подмассивов
	}
}


/// Тест работы функции сортировки слиянием
void merge_assert()
{
	// Целые числа
	int* int_arr = new int[7] { 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7] { 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7] { 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7] { 11, 12, 22, 25, 34, 64, 90 };

	merge_sort(int_arr, 0, 6);
	merge_sort(int_arr0, 0, 6);
	merge_sort(int_arr2, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	// Целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	merge_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// Дробные числа
	double* double_arr = new double[3] { 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3] { 1.01, 1.02, 1.03 };
	merge_sort(double_arr, 0, 2);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

///Сортировка методом Шелла массива arr размера size, d - середина, на каждой итерации уменьшаем в 2 раза. По возрастанию
//1.Лучший случай O(n log n)
//2.Средний случай O(n^3/2)
//3.Худший случай O(n^2)
template <typename T>
void shell_sort(T* arr, size_t size)
{
	for (size_t step = size / 2; step > 0; step /= 2) {// Первоначальный шаг - середина, на каждой итерации уменьшаем в 2 раза
		for (size_t i = step; i < size; i++) {// Идём по массиву с середины до конца
			Arr temp = arr[i];
			size_t j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) { // Сравниваем и меняем
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}

	}
}

///Тест работы функции методом Шелла
void shell_assert()
{
	// Целые числа
	int* int_arr = new int[7] { 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr0 = new int[7] { 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr_sort = new int[7] { 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr2 = new int[7] { 11, 12, 22, 25, 34, 64, 90 };

	shell_sort(int_arr, 7);
	shell_sort(int_arr0, 7);
	shell_sort(int_arr2, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	// Целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	shell_sort(int_arr1, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// Дробные числа
	double* double_arr = new double[3] { 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3] { 1.01, 1.02, 1.03 };
	shell_sort(double_arr, 3);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}

/// Меняем местами два элемента a и b
template <typename T>
void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}


/// Разделяем массив arr на две части - больше и меньше опорного элемента
template <typename T>
T partition(T* arr, size_t low, size_t high) {
	// Генерация случайного индекса в диапазоне [low, high]
	std::random_device rd; // Источник случайных чисел
	std::mt19937 gen(rd()); // Генератор случайных чисел Mersenne Twister
	std::uniform_int_distribution<size_t> distrib(low, high); // Равномерное распределение в диапазоне [low, high]
	size_t random_pivot_index = distrib(gen);

	// Поменять местами случайный элемент с arr[high]
	swap(arr[high], arr[random_pivot_index]);

	T pivot = arr[high];// Опорный элемент - последний элемент массива
	size_t i = low - 1;// Индекс для разделения элементов на две группы: меньше опорного и больше опорного
	for (size_t j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);// Меняем местами текущий элемент с элементом на позиции i
		}
	}
	swap(&arr[i + 1], &arr[high]);// Помещаем опорный элемент между двумя группами
	return i + 1;// Возвращаем индекс опорного элемента
}

/// Быстрая сортировка массива arr по возрастанию
//1.Лучший случай: O(n log n)
//2.Средний случай: O(n log n)
//3.Худший случай: O(n^2)
template <typename T>
void quick_sort(T* arr, size_t low, size_t high) {
	if (low < high) {
		T pivot = partition(arr, low, high);	// Выбираем опорный элемент и вызываем функцию partition
		quick_sort(arr, low, pivot - 1); 		// Рекурсивно сортируем элементы меньше опорного
		quick_sort(arr, pivot + 1, high);  		// Рекурсивно сортируем элементы больше опорного
	}
}


/// Тест работы функции сортировки слиянием
void quick_assert()
{
	// Целые числа
	int* int_arr = new int[7] { 64, 34, 25, 12, 22, 11, 90 };
	int* int_arr_sort = new int[7] { 11, 12, 22, 25, 34, 64, 90 };
	int* int_arr0 = new int[7] { 90, 64, 34, 25, 22, 12, 11 };
	int* int_arr2 = new int[7] { 11, 12, 22, 25, 34, 64, 90 };

	quick_sort(int_arr, 0, 6);
	quick_sort(int_arr0, 0, 6);
	quick_sort(int_arr2, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr[i] == int_arr_sort[i]);
		assert(int_arr0[i] == int_arr_sort[i]);
		assert(int_arr2[i] == int_arr_sort[i]);
	}
	delete[] int_arr;
	delete[] int_arr_sort;
	delete[] int_arr0;
	delete[] int_arr2;


	// Целые числа, повторяющиеся элементы
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	quick_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// Дробные числа
	double* double_arr = new double[3] { 1.03, 1.01, 1.02 };
	double* double_arr_sort = new double[3] { 1.01, 1.02, 1.03 };
	quick_sort(double_arr, 0.0, 2.0);
	for (size_t i = 0; i < 3; i++)
	{
		assert(double_arr[i] == double_arr_sort[i]);
	}
	delete[] double_arr;
	delete[] double_arr_sort;
}