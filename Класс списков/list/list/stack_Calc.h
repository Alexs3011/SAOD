// ������� �.�. ��� - 23
#include "stack.h"
#include <sstream>
#include <iostream>

using namespace std;

template <typename T>
/// ����������� �������� �����������, ��� ������� �� ���� ������� ����������, ��� ������������ ������ ������� ����������
class PostfixCalculator : public Stack<T>
{
public:
    ///���������� �������� ������������ ���������,
    T evaluatePostfix(const string& postfixExpression)
    {
        //istringstream iss ��� ������ ������ � ���� ������������������ ��������
        istringstream iss(postfixExpression); // ������� ����� ����� �� ������ � ����������� ����������
        string token; // ���������� ��� �������� �������� ������

        while (iss >> token) { // ���� �� ������� ������ � ������
            if (isdigit(token[0])) { // isdigit - �������� �� �����
                this->push(stoi(token)); // �������� ����� � ����, stoi ����������� ������ � ����� �����
            }
            else { // ���� ����� �������� ����������
                if (this->size() < 2) { // ���������, ���������� �� ��������� � �����
                    throw invalid_argument("������������ ����������� ���������"); // ������� ����������, ���� ��������� ������������
                }

                T operand2 = this->pop(); // �������� ������ ������� �� �����                             
                T operand1 = this->pop(); // �������� ������ ������� �� �����


                T result; // ���������� ��� �������� ���������� ����������

                switch (token[0]) { // ��������� �������� � ����������� �� ���������
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
                    if (operand2 == 0) { // ��������� ������� �� ����
                        // ����������
                        throw runtime_error("������� �� ���� ����������"); // ������� ��������� � ������������� ������� �� ����                            
                    }
                    result = operand1 / operand2; // ��������� �������
                    break;
                default:
                    throw runtime_error("�� ���� ������:("); // ������� ��������� � ����������� ���������
                }

                this->push(result); // �������� ��������� ���������� ������� � ����
            }
        }

        if (this->size() != 1) { // ���������, ��� � ����� ������� ������ ���� ������� (��������� ����������)
            throw invalid_argument("������������ ����������� ���������"); // ������� ����������, ���� � ����� ������ ������ ��������
        }

        T result = this->pop();  // �������� ������������� ��������� �� �����
        this->clear(); // ������� ����

        return result; // ���������� ������������� ��������� ����������
    }
};

