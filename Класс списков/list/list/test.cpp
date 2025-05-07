#include <iostream>
#include "listClass.h"
#include <stdexcept>
#include <cstddef>
#include <cassert>

using namespace std;
void test_insert_front() {
    DoublyLinkedList<int> list;

    // Пустой список
    list.insert_front(10);
    assert(list.size() == 1);
    assert(list[0] == 10);

    // Вставка ещё одного элемента
    list.insert_front(20);
    assert(list.size() == 2);
    assert(list[0] == 20);
    assert(list[1] == 10);

    // Вставка ещё одного
    list.insert_front(30);
    assert(list.size() == 3);
    assert(list[0] == 30);
}

void test_insert_back() {
    DoublyLinkedList<int> list;

    // Пустой список
    list.insert_back(5);
    assert(list.size() == 1);
    assert(list[0] == 5);

    // Вставка ещё одного
    list.insert_back(15);
    assert(list.size() == 2);
    assert(list[1] == 15);

    // Вставка ещё одного
    list.insert_back(25);
    assert(list.size() == 3);
    assert(list[2] == 25);
}

void test_remove_front() {
    DoublyLinkedList<int> list;

    // Удаление из пустого списка
    try {
        list.remove_front();
        assert(false); // должно выбросить исключение
    }
    catch (const underflow_error&) {
        // ожидаемая ошибка
    }

    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);

    list.remove_front();
    assert(list.size() == 2);
    assert(list[0] == 2);

    list.remove_front();
    assert(list.size() == 1);
    assert(list[0] == 3);

    list.remove_front();
    assert(list.size() == 0);

    // Теперь опять удаляем из пустого
    try {
        list.remove_front();
        assert(false);
    }
    catch (const underflow_error&) {}
}

void test_remove_back() {
    DoublyLinkedList<int> list;

    // Удаление из пустого списка
    try {
        list.remove_back();
        assert(false);
    }
    catch (const underflow_error&) {}

    list.insert_back(10);
    list.insert_back(20);
    list.insert_back(30);

    list.remove_back();
    assert(list.size() == 2);
    assert(list[1] == 20);

    list.remove_back();
    assert(list.size() == 1);
    assert(list[0] == 10);

    list.remove_back();
    assert(list.size() == 0);
}

void test_at() {
    DoublyLinkedList<int> list;

    list.insert_back(100);
    list.insert_back(200);
    list.insert_back(300);

    assert(list.at(0) == 100);
    assert(list.at(1) == 200);
    assert(list.at(2) == 300);

    // Проверка выхода за границы
    try {
        list.at(3);
        assert(false);
    }
    catch (const out_of_range&) {}

    try {
        list.at(100);
        assert(false);
    }
    catch (const out_of_range&) {}
}

void test_operator_square_brackets() {
    DoublyLinkedList<int> list;

    list.insert_back(11);
    list.insert_back(22);
    list.insert_back(33);

    assert(list[0] == 11);
    assert(list[1] == 22);
    assert(list[2] == 33);

    // Изменение через оператор []
    list[1] = 222;
    assert(list[1] == 222);

    // Проверка выхода за границы
    try {
        int x = list[3];
        (void)x; // подавляем предупреждение
        assert(false);
    }
    catch (const out_of_range&) {}
}

void test_remove_at() {
    DoublyLinkedList<int> list;

    list.insert_back(7);
    list.insert_back(8);
    list.insert_back(9);

    list.remove_at(1);
    assert(list.size() == 2);
    assert(list[0] == 7);
    assert(list[1] == 9);

    list.remove_at(1);
    assert(list.size() == 1);
    assert(list[0] == 7);

    list.remove_at(0);
    assert(list.size() == 0);

    // Попытка удалить из пустого
    try {
        list.remove_at(0);
        assert(false);
    }
    catch (const out_of_range&) {}
}

void test_insert_at() {
    DoublyLinkedList<int> list;

    list.insert_at(0, 100); // вставка в начало
    assert(list.size() == 1);
    assert(list[0] == 100);

    list.insert_at(1, 300); // вставка в конец
    assert(list.size() == 2);
    assert(list[1] == 300);

    list.insert_at(1, 200); // вставка в середину
    assert(list.size() == 3);
    assert(list[1] == 200);

    assert(list[0] == 100);
    assert(list[1] == 200);
    assert(list[2] == 300);

    // Ошибка переполнения
    try {
        list.insert_at(5, 500);
        assert(false);
    }
    catch (const out_of_range&) {}
}

void test_find() {
    DoublyLinkedList<int> list;

    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);

    auto node = list.find(2);
    assert(node != nullptr);
    assert(node->data == 2);

    node = list.find(4);
    assert(node == nullptr);

    node = list.find(1);
    assert(node->data == 1);
}

void test_concatenate() {
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;

    list1.insert_back(1);
    list1.insert_back(2);
    list2.insert_back(3);
    list2.insert_back(4);

    list1.concatenate(list2);

    assert(list1.size() == 4);
    assert(list1[0] == 1);
    assert(list1[1] == 2);
    assert(list1[2] == 3);
    assert(list1[3] == 4);

    assert(list2.size() == 0); // второй список очищается
}

void test_clear() {
    DoublyLinkedList<int> list;

    list.insert_back(10);
    list.insert_back(20);
    list.insert_back(30);

    list.clear();
    assert(list.size() == 0);

    // После очистки можно вставлять заново
    list.insert_back(5);
    assert(list.size() == 1);
    assert(list[0] == 5);
}