// list.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "listClass.h"
#include <stdexcept>
#include <cstddef>
#include <cassert>
#include "stack_Calc.h"
#include "Queue.h"
using namespace std;

void test_insert_front() {
    List<int> list;

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
    List<int> list;

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
    List<int> list;

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
    List<int> list;

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
    List<int> list;

    list.insert_back(100);
    list.insert_back(200);
    list.insert_back(300);

    assert(list.get_node(0) == 100);
    assert(list.get_node(1) == 200);
    assert(list.get_node(2) == 300);

    // Проверка выхода за границы
    try {
        list.get_node(3);
        assert(false);
    }
    catch (const out_of_range&) {}

    try {
        list.get_node(100);
        assert(false);
    }
    catch (const out_of_range&) {}
}

void test_operator_square_brackets() {
    List<int> list;

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
    List<int> list;

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
    List<int> list;

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
    List<int> list;

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
    List<int> list1;
    List<int> list2;

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
    List<int> list;

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

/// Тестирование метода push
void test_push() {
    Stack<int> stack;

    stack.push(10);
    assert(stack[0] == 10); // верхний элемент

    stack.push(20);
    assert(stack[0] == 20); // теперь 20 сверху
    assert(stack[1] == 10); // 10 под ним

    stack.push(30);
    assert(stack[0] == 30);
    assert(stack[1] == 20);
    assert(stack[2] == 10);

    Stack<std::string> sstack;
    sstack.push("first");
    assert(sstack[0] == "first");

    sstack.push("second");
    assert(sstack[0] == "second");
    assert(sstack[1] == "first");

}

/// Тестирование метода pop
void test_pop() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    assert(stack.size() == 2);
    assert(stack[0] == 2);

    stack.pop();
    assert(stack.size() == 1);
    assert(stack[0] == 1);

    stack.pop();
    assert(stack.size() == 0);
}

void assert_calc()
{
    PostfixCalculator<int> calculator;

    // Ожидаемый результат: (3 + 4) * 2 = 14
    assert(calculator.evaluatePostfix("3 4 + 2 *") == 14);

    // Ожидаемый результат: 5 + (2 * 3) = 11
    assert(calculator.evaluatePostfix("5 2 3 * +") == 11);

    // Ожидаемый результат: (8 / 4) - 6 = -4
    assert(calculator.evaluatePostfix("8 4 / 6 -") == -4);

    // Ожидаемый результат: 1 + (2 * 3) - 4 = 3
    assert(calculator.evaluatePostfix("1 2 3 * + 4 -") == 3);

    assert(calculator.evaluatePostfix("8 6 -") == 2);

    assert(calculator.evaluatePostfix("8 6 *") == 48);

    assert(calculator.evaluatePostfix("8 6 +") == 14);

    assert(calculator.evaluatePostfix("6 2 /") == 3);

    //Деление на 0
    try {
        calculator.evaluatePostfix("3 0 /"); // Вызываем метод evaluatePostfix с делением на ноль
        // Если исключение не было выброшено, делаем проверку assert, чтобы тест не проходил
        assert(false);
    }
    catch (const std::runtime_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
        // Если исключение было выброшено, тест проходит
    }
}

///Тестирование метода enqueue 
void test_enqueue() {

    Queue<int> queue;

    queue.enqueue(1);
    assert(queue.get_tail() == 1);

    queue.enqueue(2);
    assert(queue.get_tail() == 2);

    queue.enqueue(3);
    assert(queue.get_tail() == 3);

    Queue<double> queue1;

    queue1.enqueue(1.1);
    assert(queue1.get_tail() == 1.1);

    queue1.enqueue(2.2);
    assert(queue1.get_tail() == 2.2);

    queue1.enqueue(3.3);
    assert(queue1.get_tail() == 3.3);
}

///Тестирование метода dequeue
void test_dequeue() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.dequeue();
    assert(queue.size() == 2);
    assert(queue.get_tail() == 3);

    queue.dequeue();
    assert(queue.size() == 1);
    assert(queue.get_tail() == 3);


    Queue<double> queue1;

    queue1.enqueue(1.1);
    queue1.enqueue(2.2);
    queue1.enqueue(3.3);

    queue1.dequeue();
    assert(queue1.size() == 2);
    assert(queue1.get_tail() == 3.3);

    queue1.dequeue();
    assert(queue1.size() == 1);
    assert(queue1.get_tail() == 3.3);

    bool exceptionThrown = false;
    try {
        queue1.get_tail();
    }
    catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

int main() {
    setlocale(LC_ALL, "Russian");
    test_insert_front();
    test_insert_back();
    test_remove_front();
    test_remove_back();
    test_at();
    test_operator_square_brackets();
    test_remove_at();
    test_insert_at();
    test_find();
    test_concatenate();
    test_clear();
    assert_calc();
    test_enqueue();
    test_dequeue;
    cout << "Все гуд!";
    return 0;
}