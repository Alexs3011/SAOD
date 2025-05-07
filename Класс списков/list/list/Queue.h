#pragma once
#include "listClass.h"
#include <cassert>
#include <iostream>

template <typename T>
/// Класс очередь, наследуется от класса списка
class Queue : public List<T>
{
public:
    /// Добавить элемент в конец очереди
    void enqueue(const T& element) {
        this->insert_back(element);
    }

    /// Удалить элемент из начала очереди
    T dequeue() {
        if (this->size() == 0) {
            throw std::out_of_range("Очередь пуста");
        }
        T value = this->get_node(0);
        this->remove_front();
        return value;
    }

    /// Проверка, пуста ли очередь
    bool isEmpty() const {
        return this->size() == 0;
    }

    /// Первый элемент очереди
    T get_head() const {
        if (this->size() == 0)
        {
            throw std::out_of_range("Очередь пуста");
        }
        return this->get_node(this->size() - 1);
    }

    /// Последний элемент очереди
    T get_tail() const {
        if (this->size() == 0) {
            throw std::out_of_range("Очередь пуста");
        }
        return this->get_node(this->size() - 1);
    }

    /// Текущее число элементов в очереди
    size_t size() const {
        return List<T>::size();
    }

    /// Очистить очередь
    void clear() {
        List<T>::clear();
    }
};