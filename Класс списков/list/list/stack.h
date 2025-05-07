#pragma once
#include "listClass.h" 
#include <cassert> 
#include <iostream>

/// Шаблонный класс Stack на основе DoublyLinkedList
template <typename T>
class Stack : public List<T>
{
public:
    /// Добавление элемента в стек (в начало списка)
    void push(const T& element)
    {
        this->insert_front(element);
    }

    /// Удаление элемента из стека (с начала списка)
    T pop()
    {
        if (this->size() == 0)
            throw std::out_of_range("Стек пустой");
        T val = this->get_node(0);
        this->remove_front();
        return val;
    }
};
