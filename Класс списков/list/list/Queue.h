#pragma once
#include "listClass.h"
#include <cassert>
#include <iostream>

template <typename T>
/// ����� �������, ����������� �� ������ ������
class Queue : public List<T>
{
public:
    /// �������� ������� � ����� �������
    void enqueue(const T& element) {
        this->insert_back(element);
    }

    /// ������� ������� �� ������ �������
    T dequeue() {
        if (this->size() == 0) {
            throw std::out_of_range("������� �����");
        }
        T value = this->get_node(0);
        this->remove_front();
        return value;
    }

    /// ��������, ����� �� �������
    bool isEmpty() const {
        return this->size() == 0;
    }

    /// ������ ������� �������
    T get_head() const {
        if (this->size() == 0)
        {
            throw std::out_of_range("������� �����");
        }
        return this->get_node(this->size() - 1);
    }

    /// ��������� ������� �������
    T get_tail() const {
        if (this->size() == 0) {
            throw std::out_of_range("������� �����");
        }
        return this->get_node(this->size() - 1);
    }

    /// ������� ����� ��������� � �������
    size_t size() const {
        return List<T>::size();
    }

    /// �������� �������
    void clear() {
        List<T>::clear();
    }
};