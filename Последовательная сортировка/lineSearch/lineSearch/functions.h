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

/// ������� ��� �������� ������� ���������� ����. 
float time(const function<void()>& func) {
    auto start = chrono::high_resolution_clock::now(); // �������� ����� ������
    func(); // ��������� ���������� �������
    auto end = chrono::high_resolution_clock::now(); // �������� ����� ���������
    chrono::duration<double> duration = end - start; // ��������� �������
    return duration.count();
}

/// ������� ��� ��������� ���������� ����� � �������� ���������
template <typename T>
T randomNumber(T min, T max) {
    static random_device rd; // �������� �����������
    static mt19937 gen(rd()); // ��������� ��������� �����
    uniform_int_distribution<T> distr(min, max); // ����������� ������������� ���������� ����� � �������� ���������
    return distr(gen);
}

/// ������� ��� �������� ������� ��������� ����� � �������� ���������
template <typename T>
void randomArray(T arr[], size_t size, T min, T max) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = randomNumber(min, max); // ��������� ������ ���������� �������
    }
}

/// ������� ��� �������� ��������� ������������� �������
template <typename T>
void monotonArray(T arr[], size_t size, T min, T max) {
    T current = randomNumber(int(min), int(min + (max - min))); // ��������� ��������
    for (size_t i = 0; i < size; i++) {
        arr[i] = current;
        current += randomNumber(1, int((max - min))); // ��������� ��������� �������
    }
}

/// ����� ������� �� �����
template <typename T>
void printArray(const T arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << setprecision(3) << arr[i] << " "; // ����� � �����������
    }
    cout << endl;
}

// ���������� ������� ��������, ���������� �� ������, ������������ ������ array ���� T* ������� ��� ���
template <typename T>
bool is_sorted(T* array, size_t size) {
	for (size_t i = 1; i < size; ++i) {
		if (array[i] < array[i - 1]) { // ���� ������ ��������� ������ ������ �����������
			return false;  // ���� ������� �������
		}
	}
	return true; // ���� ������ ������������
}


/// ���� ������� ���������� ������� is_sorted
void test_is_sorted() {

	// ��������������� �������
	int arr_sorted1[] = { 1, 2, 3, 4, 5 }; // ������  ������������� ��������
	int arr_sorted2[] = { -5, -3, -1, 0, 2, 4, 6 }; // � �������������, � ������������� ��������
	int arr_sorted3[] = { 10 }; // ���� �������
	int* arr_sorted4 = nullptr; // ������ ������


	assert(is_sorted(arr_sorted1, 5) == true);
	assert(is_sorted(arr_sorted2, 7) == true);
	assert(is_sorted(arr_sorted3, 1) == true);
	assert(is_sorted(arr_sorted4, 0) == true);

	// ����������������� �������
	int arr_unsorted1[] = { 1, 3, 2, 4, 5 };
	int arr_unsorted2[] = { 5, 4, 3, 2, 1 }; // �������� �������
	int arr_unsorted3[] = { 10, 10, 9, 10 }; // ������������� ��������, �� �� �� �������
	int arr_unsorted4[] = { -1, -2, -3, 0 };

	assert(is_sorted(arr_unsorted1, 5) == false);
	assert(is_sorted(arr_unsorted2, 5) == false);
	assert(is_sorted(arr_unsorted3, 4) == false);
	assert(is_sorted(arr_unsorted4, 4) == false);

	// ������ � ����������� ����������
	int arr_same_elements[] = { 5, 5, 5, 5, 5 };
	assert(is_sorted(arr_same_elements, 5) == true);

	// ������ � ����� ���������� �������� ���������
	int arr_with_duplicates[] = { 1, 2, 2, 3, 4 };
	assert(is_sorted(arr_with_duplicates, 5) == true);

}

/// ���������� ������� � ����
void saveArrayToFile(const std::string& filename, const int* array, size_t size) {
    std::ofstream file(filename);
    for (size_t i = 0; i < size; ++i) {
        file << array[i] << " ";
    }
}

/// ������� ����������������� ������ � �������
//1.������ ������: O(1)
//2.������� ������:O(n)
//3.������ ������: O(n)
template <typename T>
T lineSearch(const T arr[], size_t size, T target) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; 
        }
    }
    return size;
}

/// ������� ��������� ������ � ��������������� �������
//1.������ ������: O(1)
//2.������� ������:O(log n)
//3.������ ������: O(log n)
template <typename T>
T binarySearch(const T arr[], size_t size, T target) {
    size_t left = 0, right = size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // ��������� �������
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return size; // ������� �� ������
}

/// ������� ������������ ����������������� ������
void test_sequential_search() {

	// ������ ��� ������������ �������
	int arr1[] = { 10, 20, 30, 40, 50 };
	// ������ �������
	size_t size1 = 5;

	// ������� ��������� � ��������
	assert(sequential_search(arr1, size1, 30) == 2);

	// ������� � ������
	assert(sequential_search(arr1, size1, 10) == 0);

	// ������� � �����
	assert(sequential_search(arr1, size1, 50) == 4);

	// �������� ��� � ������� 
	assert(sequential_search(arr1, size1, 5) == size1);

	// �������� ��� � ������� 
	assert(sequential_search(arr1, size1, 60) == size1);

	// �������� ��� � ������� 
	assert(sequential_search(arr1, size1, 35) == size1);

	// ����� � ������� �� ������ �������� (������)
	int arr2[] = { 100 };
	assert(sequential_search(arr2, 1, 100) == 0);

	// ����� � ������� �� ������ �������� (�� ������)
	assert(sequential_search(arr2, 1, 200) == 1);

}

/// ���� ������� ��������� ������
void test_binary_search() {
	// ������ ��� ������������ �������
	int sorted_array[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	// ������ �������
	size_t size_test = 8;
	// ������� � ��������
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 7) == 3);

	// ������ �������
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 1) == 0);

	// ��������� �������
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 15) == 7);

	// ������������� �������
	assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 8) == size_test);

	// ����� � ������� �� ������ ��������
	int one_element_array[] = { 42 };
	assert(binary_search_recursive<int>(one_element_array, 0, 0, 42) == 0);
	assert(binary_search_recursive<int>(one_element_array, 0, 0, 0) == size_test);
}

/// ���������� ��������� ������� arr ������� size �� �����������
//1.������ ������: O(n) 
//2.�������: O(n2) 
//3.������: O(n2) 
template<typename T>
void bubble_sort(T* arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])// E��� ���������� ������� ������ ����������
            {
                swap(arr[j], arr[j + 1]);// ������ �������
            }
    }
}

/// ���� ������ ������� ���������� ���������
void bubble_assert()
{
    // ����� �����
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


    // ����� �����, ������������� ��������
    int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
    int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

    bubble_sort(int_arr1, 7);
    for (size_t i = 0; i < 7; i++)
    {
        assert(int_arr1[i] == int_arr_sort1[i]);
    }
    delete[] int_arr1;
    delete[] int_arr_sort1;

    // ������� �����
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

/// ������� ��� ������� ���� ����������� arr, ��� left ������ ������� = 0, right = ������� ������� 
/// mid - �������� �������, �� ������� �� ����� (����������� � ������� merge_sort). �� �����������
/// ��������� �� ������ O(n + m), ��� n � m - ������� ���� ��������
template <typename T>
void merge(T* arr, size_t left, size_t mid, size_t right) {
	size_t n1 = mid - left + 1;// ���������� ������� ������ ����������
	size_t n2 = right - mid;// ���������� ������� ������� ����������

	T* l = new T[n1];// ������������ ��������� ������ ��� ������� L, R
	T* r = new T[n2];

	memcpy(l, &arr[left], n1 * sizeof(T));// ����������� ������ �� ��������� ������ L
	memcpy(r, &arr[mid + 1], n2 * sizeof(T));// ����������� ������ �� ��������� ������ R

	size_t i = 0;// ������������� �������� ��� ����������� ���� �����������
	size_t j = 0;
	size_t k = left;

	while (i < n1 && j < n2) {// ������� ���� ����������� � �������� ������ arr
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
		memcpy(&arr[k], &l[i], (n1 - i) * sizeof(T)); // ���������� ���������� ��������� �� ������ ����������
		k += n1 - i;
	}

	if (j < n2) {
		memcpy(&arr[k], &r[j], (n2 - j) * sizeof(T)); // ���������� ���������� ��������� �� ������� ����������
		k += n2 - j;
	}

	delete[] l;
	delete[] r;
}

/// ������� ��� ����������� ���������� �������� ������� arr, ��� left ������ ������� = 0, � right = ������� ������� �� �����������
//1.������ ������: O(n log n)
//2.������� ������:O(n log n)
//3.������ ������: O(n log n)
template <typename T>
void merge_sort(T* arr, size_t left, size_t right) {
	if (left < right) {// ��������, ��� ����� �������� ������ �������

		size_t mid = left + (right - left) / 2;// ���������� �������� �������

		merge_sort(arr, left, mid);// ����������� ����� merge_sort ��� ����� ����� �������
		merge_sort(arr, mid + 1, right);// ����������� ����� merge_sort ��� ������ ����� �������

		merge(arr, left, mid, right);// ����� ������� merge ��� ������� ���� ��������������� �����������
	}
}


/// ���� ������ ������� ���������� ��������
void merge_assert()
{
	// ����� �����
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


	// ����� �����, ������������� ��������
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	merge_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// ������� �����
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

///���������� ������� ����� ������� arr ������� size, d - ��������, �� ������ �������� ��������� � 2 ����. �� �����������
//1.������ ������ O(n log n)
//2.������� ������ O(n^3/2)
//3.������ ������ O(n^2)
template <typename T>
void shell_sort(T* arr, size_t size)
{
	for (size_t step = size / 2; step > 0; step /= 2) {// �������������� ��� - ��������, �� ������ �������� ��������� � 2 ����
		for (size_t i = step; i < size; i++) {// ��� �� ������� � �������� �� �����
			Arr temp = arr[i];
			size_t j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) { // ���������� � ������
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}

	}
}

///���� ������ ������� ������� �����
void shell_assert()
{
	// ����� �����
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


	// ����� �����, ������������� ��������
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	shell_sort(int_arr1, 7);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// ������� �����
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

/// ������ ������� ��� �������� a � b
template <typename T>
void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}


/// ��������� ������ arr �� ��� ����� - ������ � ������ �������� ��������
template <typename T>
T partition(T* arr, size_t low, size_t high) {
	// ��������� ���������� ������� � ��������� [low, high]
	std::random_device rd; // �������� ��������� �����
	std::mt19937 gen(rd()); // ��������� ��������� ����� Mersenne Twister
	std::uniform_int_distribution<size_t> distrib(low, high); // ����������� ������������� � ��������� [low, high]
	size_t random_pivot_index = distrib(gen);

	// �������� ������� ��������� ������� � arr[high]
	swap(arr[high], arr[random_pivot_index]);

	T pivot = arr[high];// ������� ������� - ��������� ������� �������
	size_t i = low - 1;// ������ ��� ���������� ��������� �� ��� ������: ������ �������� � ������ ��������
	for (size_t j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);// ������ ������� ������� ������� � ��������� �� ������� i
		}
	}
	swap(&arr[i + 1], &arr[high]);// �������� ������� ������� ����� ����� ��������
	return i + 1;// ���������� ������ �������� ��������
}

/// ������� ���������� ������� arr �� �����������
//1.������ ������: O(n log n)
//2.������� ������: O(n log n)
//3.������ ������: O(n^2)
template <typename T>
void quick_sort(T* arr, size_t low, size_t high) {
	if (low < high) {
		T pivot = partition(arr, low, high);	// �������� ������� ������� � �������� ������� partition
		quick_sort(arr, low, pivot - 1); 		// ���������� ��������� �������� ������ ��������
		quick_sort(arr, pivot + 1, high);  		// ���������� ��������� �������� ������ ��������
	}
}


/// ���� ������ ������� ���������� ��������
void quick_assert()
{
	// ����� �����
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


	// ����� �����, ������������� ��������
	int* int_arr1 = new int[7] { 64, 34, 22, 22, 22, 11, 90 };
	int* int_arr_sort1 = new int[7] { 11, 22, 22, 22, 34, 64, 90 };

	quick_sort(int_arr1, 0, 6);
	for (size_t i = 0; i < 7; i++)
	{
		assert(int_arr1[i] == int_arr_sort1[i]);
	}
	delete[] int_arr1;
	delete[] int_arr_sort1;

	// ������� �����
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