// ������� �.�. ��� - 23
#pragma once
#include <stdexcept>
#include <cstddef>

using namespace std;

/// ��������� ����� ����������� ������
template <typename T>
class List {
private:
    /// ���������� ���������: ���� ������
    struct Node {
        T data;       // ������ ����
        Node* prev;   // ��������� �� ���������� ����
        Node* next;   // ��������� �� ��������� ����
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {} // ����������� ���� ������, ����� ��������� ����� �������. 
    };

    size_t _size;  // ������� ���������� ��������� � ������
    Node* head;    // ��������� �� ������ ������� ������
    Node* tail;    // ��������� �� ��������� ������� ������

public:

    /// ����������� �� ���������, ������ ������ ������ (O(1))
    List() : head(nullptr), tail(nullptr), _size(0) {}

    /// ����������: ������� ��� �������� ������, ���������� ������ (O(n))
    ~List() {
        clear();
    }

    /// ����������� �����������: ������ �������� ����� ������ (O(n))
    List(const List& other) : head(nullptr), tail(nullptr), _size(0) { // ������ ���������� ������
        Node* current = other.head; // �������� � ������
        while (current) {
            insert_back(current->data); // �������� ������ �������
            current = current->next;
        }
    }

    /// �������� ����������� ������������: �������� ������� ������ ������ ������� (O(n))
    List& operator=(const List& other) {
        if (this != &other) {
            clear(); // ������� ������ ��������
            Node* current = other.head;
            while (current) {
                insert_back(current->data); // �������� ������ �������
                current = current->next;
            }
        }
        return *this; // ���������� ������ �� ����
    }

    /// ����������� �����������: ��������� ������� ������� ������ (O(1))
    List(List&& other) : head(other.head), tail(other.tail), _size(other._size) { // �������� ��������� � ������
        other.head = nullptr;// ��������
        other.tail = nullptr;
        other._size = 0;
    }

    /// �������� ������������� ������������: ��������� ������� ������� ������ (O(1))
    List& operator=(List&& other)  {
        if (this != &other) {
            clear();
            head = other.head; // ��������� ��������� � ��������
            tail = other.tail;
            _size = other._size;
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    /// ����� �������� �� ��������. ���������� ��������� �� ��������� ���� ��� nullptr (O(n))
    Node* find(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) // ���� ����� ���� ����������
                return current;
            current = current->next; // ����� ��������� � ����������
        }
        return nullptr;
    }

    /// ������� �������� � ������ ������ (O(1))
    void insert_front(const T& value) {
        Node* newNode = new Node(value); // ����� ���� � �������� ��������� 
        newNode->next = head; // ��������� ��� �� ������� ������
        if (head) // ���� ������ �� ������
            head->prev = newNode; // ������ ������ ��������� ����� ����
        head = newNode; // ��������� ������
        if (!tail) // ���� ������ ��� ������
            tail = newNode; // ����� ���� ����������� ���� ���������
        _size++;
    }

    /// ������� �������� � ����� ������ (O(1))
    void insert_back(const T& value) {
        Node* newNode = new Node(value);
        newNode->prev = tail;
        if (tail)
            tail->next = newNode;
        tail = newNode;
        if (!head) 
            head = newNode;
        _size++;
    }

    /// �������� ������� �������� ������ (O(1))
    void remove_front() {
        if (!head) // ���� ������ ������
            throw underflow_error("������ ����");
        Node* toDelete = head; 
        head = head->next; // ��������� ������� ������
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr; // ������ ���� ������
        delete toDelete;
        _size--;
    }

    /// �������� ���������� �������� ������ (O(1))
    void remove_back() {
        if (!tail)
            throw underflow_error("������ ����");
        Node* toDelete = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr; // ������ ���� ������
        delete toDelete;
        _size--;
    }

    /// �������� ����������� �������� (O(1), �� ������ O(n) �� �����)
    void remove(Node* node) {
        if (node->prev) // ���� ���� �� ������
            node->prev->next = node->next; // ���������� �������� ���������� �� ���������
        else
            head = node->next; // ������� ������ �������
        if (node->next) // ���� �� �����
            node->next->prev = node->prev; // ���������� ��������� ��������� �� ����������
        else
            tail = node->prev; // ������� ��������� �������
        delete node;
        _size--;
    }

    /// ����������� ������� ������ � ����� �������� (O(n))
    void concatenate(List& other) {
        Node* current = other.head;
        while (current) {
            insert_back(current->data); // ��������� � ����� �������� ������
            current = current->next;
        }
        other.clear(); // ������� ������ ������
    }

    /// ��������� ������� ������ (O(1))
    size_t size() const {
        return _size;
    }

    /// ������ ������� ������: �������� ���� ����� (O(n))
    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr; // �������� ������ � �����
        _size = 0;
    }

    /// ����� ���� �� ������� (O(n))
    Node* node_at(size_t index) const {
        Node* current = head; // �������� � ������
        size_t i = 0;
        while (current && i < index) { // ���� �� ����� �� ������� ������
            current = current->next;
            i++;
        }
        return current;
    }

    /// ��������� ������ �� ������� �� ������� (O(n)), ����������
    T& get_node(size_t index) {
        Node* node = node_at(index); // ���� ����
        if (!node) // ���� ���
            throw out_of_range("������ ��� ���������");
        return node->data; // ���������� ������
    }

    /// ��������� ������ �� ������� �� ������� (O(n)), ����������� 
    const T& get_node(size_t index) const {
        Node* node = node_at(index);
        if (!node)
            throw out_of_range("������ ��� ���������");
        return node->data;
    }

    /// �������� [] ��� ������� � �������� �� ������� (O(n)) ����������
    T& operator[](size_t index) {
        return get_node(index);
    }

    /// �������� [] ��� ������� � �������� �� ������� (O(n)), ����������� 
    const T& operator[](size_t index) const {
        return get_node(index);
    }

    /// �������� �������� �� ������� (O(n))
    void remove_at(size_t index) {
        if (index >= _size)
            throw out_of_range("������ ��� ���������");
        Node* node = node_at(index); // ���� ������ ����
        remove(node);// �������
    }

    /// ������� �������� �� ������� (O(n))
    void insert_at(size_t index, const T& value) {
        if (index > _size)
            throw out_of_range("������ ��� ���������");

        if (index == 0) { // ���� � ������
            insert_front(value);
        }
        else if (index == _size) { // ���� � �����
            insert_back(value);
        }
        else {
            Node* current = node_at(index);// ������� 
            Node* newNode = new Node(value); // ����� 
            Node* previous = current->prev; // ����������

            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            current->prev = newNode;
            _size++;
        }
    }
};
