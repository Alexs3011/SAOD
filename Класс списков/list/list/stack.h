#pragma once
#include "listClass.h" 
#include <cassert> 
#include <iostream>

/// ��������� ����� Stack �� ������ DoublyLinkedList
template <typename T>
class Stack : public List<T>
{
public:
    /// ���������� �������� � ���� (� ������ ������)
    void push(const T& element)
    {
        this->insert_front(element);
    }

    /// �������� �������� �� ����� (� ������ ������)
    T pop()
    {
        if (this->size() == 0)
            throw std::out_of_range("���� ������");
        T val = this->get_node(0);
        this->remove_front();
        return val;
    }
};
