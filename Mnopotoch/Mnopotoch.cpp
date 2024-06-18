// Mnopotoch.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;





void DoWork(int &a)
{
    /*for (int i = 0; i < 10; i++)
    {
        cout << "ID потока в DoWork:" << this_thread::get_id() << ". Номер итерации" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

    }*/

    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "========\t" << "DoWork стартовал\t======" << endl;

    /*this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "A+B: "<< a + b << endl;*/

    a += 2;

    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "========\t" << "DoWork завершился\t======" << endl;
    
}

int main()
{
   /* cout << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));*/

    setlocale(LC_ALL, "ru");
    int a = 5;

    thread thread1 (DoWork, ref(a));

    for (int i = 0; i < 10; i++) {
        cout << "ID потока в main:" << this_thread::get_id() << ". Номер итерации" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    thread1.join();
    cout << a;
}



