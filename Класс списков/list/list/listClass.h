// Сафошин А.С. ИВТ - 23
#pragma once
#include <stdexcept>
#include <cstddef>

using namespace std;

/// Шаблонный класс двусвязного списка
template <typename T>
class List {
private:
    /// Внутренняя структура: узел списка
    struct Node {
        T data;       // данные узла
        Node* prev;   // указатель на предыдущий узел
        Node* next;   // указатель на следующий узел
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {} // конструктор узла списка, когда создается новый элемент. 
    };

    size_t _size;  // текущее количество элементов в списке
    Node* head;    // указатель на первый элемент списка
    Node* tail;    // указатель на последний элемент списка

public:

    /// Конструктор по умолчанию, создаёт пустой список (O(1))
    List() : head(nullptr), tail(nullptr), _size(0) {}

    /// Деструктор: удаляет все элементы списка, освобождая память (O(n))
    ~List() {
        clear();
    }

    /// Конструктор копирования: создаёт глубокую копию списка (O(n))
    List(const List& other) : head(nullptr), tail(nullptr), _size(0) { // список изначально пустой
        Node* current = other.head; // начинаем с головы
        while (current) {
            insert_back(current->data); // копируем каждый элемент
            current = current->next;
        }
    }

    /// Оператор копирующего присваивания: замещает текущий список копией другого (O(n))
    List& operator=(const List& other) {
        if (this != &other) {
            clear(); // очищаем старые элементы
            Node* current = other.head;
            while (current) {
                insert_back(current->data); // копируем каждый элемент
                current = current->next;
            }
        }
        return *this; // возвращаем ссылку на себя
    }

    /// Конструктор перемещения: переносит ресурсы другого списка (O(1))
    List(List&& other) : head(other.head), tail(other.tail), _size(other._size) { // копируем указатели и рамзер
        other.head = nullptr;// обнуляем
        other.tail = nullptr;
        other._size = 0;
    }

    /// Оператор перемещающего присваивания: принимает ресурсы другого списка (O(1))
    List& operator=(List&& other)  {
        if (this != &other) {
            clear();
            head = other.head; // переносим указатели и обнуляем
            tail = other.tail;
            _size = other._size;
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    /// Поиск элемента по значению. Возвращает указатель на найденный узел или nullptr (O(n))
    Node* find(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) // если данев узла совпадаюат
                return current;
            current = current->next; // иначе переходим к следующему
        }
        return nullptr;
    }

    /// Вставка элемента в начало списка (O(1))
    void insert_front(const T& value) {
        Node* newNode = new Node(value); // новый узел с заданным значением 
        newNode->next = head; // указываем его на текущую голову
        if (head) // если список не пустой
            head->prev = newNode; // старой голове указываем новый узел
        head = newNode; // обновляем голову
        if (!tail) // если список был пустой
            tail = newNode; // хвост тоже становиться этим элементом
        _size++;
    }

    /// Вставка элемента в конец списка (O(1))
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

    /// Удаление первого элемента списка (O(1))
    void remove_front() {
        if (!head) // если список пустой
            throw underflow_error("Список пуст");
        Node* toDelete = head; 
        head = head->next; // следующий элемент голова
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr; // список стал пустым
        delete toDelete;
        _size--;
    }

    /// Удаление последнего элемента списка (O(1))
    void remove_back() {
        if (!tail)
            throw underflow_error("Список пуст");
        Node* toDelete = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr; // список стал пустым
        delete toDelete;
        _size--;
    }

    /// Удаление конкретного элемента (O(1), но обычно O(n) на поиск)
    void remove(Node* node) {
        if (node->prev) // если узел не голова
            node->prev->next = node->next; // подключаем напрямую предыдущий на следующий
        else
            head = node->next; // удаляем первый элемент
        if (node->next) // если не хвост
            node->next->prev = node->prev; // подключаем наппрямую следующий на предыдущий
        else
            tail = node->prev; // удаляем последний элемент
        delete node;
        _size--;
    }

    /// Объеденение другого списка в конец текущего (O(n))
    void concatenate(List& other) {
        Node* current = other.head;
        while (current) {
            insert_back(current->data); // Вставляем в конец текущего списка
            current = current->next;
        }
        other.clear(); // очищаем другой список
    }

    /// Получение размера списка (O(1))
    size_t size() const {
        return _size;
    }

    /// Полная очистка списка: удаление всех узлов (O(n))
    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr; // обнуляем голову и хвост
        _size = 0;
    }

    /// Поиск узла по индексу (O(n))
    Node* node_at(size_t index) const {
        Node* current = head; // начинаем с головы
        size_t i = 0;
        while (current && i < index) { // пока не дошли до нужного индека
            current = current->next;
            i++;
        }
        return current;
    }

    /// Получение ссылки на элемент по индексу (O(n)), изменяемая
    T& get_node(size_t index) {
        Node* node = node_at(index); // ищем узел
        if (!node) // если нет
            throw out_of_range("Индекс вне диапазона");
        return node->data; // возвращаем ссылку
    }

    /// Получение ссылки на элемент по индексу (O(n)), константная 
    const T& get_node(size_t index) const {
        Node* node = node_at(index);
        if (!node)
            throw out_of_range("Индекс вне диапазона");
        return node->data;
    }

    /// Оператор [] для доступа к элементу по индексу (O(n)) изменяемая
    T& operator[](size_t index) {
        return get_node(index);
    }

    /// Оператор [] для доступа к элементу по индексу (O(n)), константная 
    const T& operator[](size_t index) const {
        return get_node(index);
    }

    /// Удаление элемента по индексу (O(n))
    void remove_at(size_t index) {
        if (index >= _size)
            throw out_of_range("Индекс вне диапазона");
        Node* node = node_at(index); // ищем нужный узел
        remove(node);// удаляем
    }

    /// Вставка элемента по индексу (O(n))
    void insert_at(size_t index, const T& value) {
        if (index > _size)
            throw out_of_range("Индекс вне диапазона");

        if (index == 0) { // если в начало
            insert_front(value);
        }
        else if (index == _size) { // если в конец
            insert_back(value);
        }
        else {
            Node* current = node_at(index);// текущий 
            Node* newNode = new Node(value); // новый 
            Node* previous = current->prev; // предыдущий

            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            current->prev = newNode;
            _size++;
        }
    }
};
