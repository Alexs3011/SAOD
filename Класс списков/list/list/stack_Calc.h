// Сафошин А.С. ИВТ - 23
#include "stack.h"
#include <sstream>
#include <iostream>

using namespace std;

template <typename T>
/// Постфиксный стековый калькулятор, при делении на ноль бросает исключение, при неправильных данных бросает исключение
class PostfixCalculator : public Stack<T>
{
public:
    ///Вычисление значения постфиксного выражения,
    T evaluatePostfix(const string& postfixExpression)
    {
        //istringstream iss для чтения данных в виде последовательности символов
        istringstream iss(postfixExpression); // Создаем поток ввода из строки с постфиксным выражением
        string token; // Переменная для хранения текущего токена

        while (iss >> token) { // Цикл по каждому токену в строке
            if (isdigit(token[0])) { // isdigit - проверка на число
                this->push(stoi(token)); // Помещаем число в стек, stoi преобразует строку в целое число
            }
            else { // Если токен является оператором
                if (this->size() < 2) { // Проверяем, достаточно ли операндов в стеке
                    throw invalid_argument("Недопустимое постфиксное выражение"); // Бросаем исключение, если операндов недостаточно
                }

                T operand2 = this->pop(); // Получаем второй операнд из стека                             
                T operand1 = this->pop(); // Получаем первый операнд из стека


                T result; // Переменная для хранения результата вычисления

                switch (token[0]) { // Выполняем операцию в зависимости от оператора
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) { // Проверяем деление на ноль
                        // исключение
                        throw runtime_error("Деление на ноль невозможно"); // Выводим сообщение о невозможности деления на ноль                            
                    }
                    result = operand1 / operand2; // Выполняем деление
                    break;
                default:
                    throw runtime_error("Не знаю такого:("); // Выводим сообщение о неизвестном операторе
                }

                this->push(result); // Помещаем результат вычисления обратно в стек
            }
        }

        if (this->size() != 1) { // Проверяем, что в стеке остался только один элемент (результат вычислений)
            throw invalid_argument("Недопустимое постфиксное выражение"); // Бросаем исключение, если в стеке больше одного элемента
        }

        T result = this->pop();  // Получаем окончательный результат из стека
        this->clear(); // Очищаем стек

        return result; // Возвращаем окончательный результат вычислений
    }
};

