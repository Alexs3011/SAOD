// TemplateFunctions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "functions.h"

using namespace std;
void hello() {
    cout << "Hello World!\n";
}

int main()
{
    time([]() {
        cout << "Hello World!\n";
        });


}
