#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
using namespace std;
double f(double);
double df(double);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Лабораторная работа №5" << endl;
    cout << "Цель работы: решение нелинейных уравнений (метод Ньютона)" << endl;
    cout << "Выполнил: Таратонов Вадим Николаевич" << endl;
    cout << "Проверила: Шабунина Зоя Александровна" << endl;
    cout << endl;
    double x0, epsilon, k;


    //считывание данных
    ifstream filein("F:\\FilesForLabs\\ЧМ\\CHM5lab.txt");
    if (!filein.is_open()) {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
        }
        fileout.close();
        cout << "Файл не найден!" << endl;
        return 0;
    }
    else
    {
        filein >> x0;
        filein >> epsilon;
        filein >> k;
    }
    filein.close();

    //выявления ошибок ввода
    if (epsilon < 0 || k < 0)
    {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
            cout << "Файл не найден!" << endl;
            return 0;
        }
        else {
            fileout << "IER = 7" << endl;
            fileout << "Неверно введены данные!" << endl;
        }
        
        cout << "IER = 7" << endl;
        cout << "Неверно введены данные!" << endl;
        return 0;
    }

    
    vector <double> x; //вспомогательный вектор, в котором я буду хранить все значения х полученные в ходе решения
    x.push_back(x0);
    double fx, dfx;
    int l = 1; //переменная количества итераций
    fx = f(x0);
    dfx = df(x0);
    if (dfx == 0)
    {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
            cout << "Файл не найден!" << endl;
            return 0;
        }
        else {
            fileout << "IER = 3" << endl;
            fileout << "Деление на 0!" << endl;
        }
        fileout.close();
        cout << "Деление на 0!" << endl;
        return 0;
    }
    double x1 = x0 - (fx / dfx); //первая итерация
    x.push_back(x1);
    double pogreshnost = abs(x1 - x0);

    //проверка на попадение в корень уравнения сразу
    if (pogreshnost <= epsilon)
    {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
            cout << "Файл не найден!" << endl;
            return 0;
        }
        else
        {
            fileout << "IER = 0" << endl;
            fileout << "Решение получено!" << " Ответ: " << x1 << endl;
            fileout << "Точность полученного решения: " << pogreshnost << endl;
            fileout << "Число итераций: " << l << endl;
        }
        fileout.close();
        cout << endl << endl << "Решение получено!" << " Ответ: " << x1 << endl;
        cout << "Точность полученного решения: " << pogreshnost << endl;
        cout << "Число итераций: " << l << endl;
        return 0;
    }
    
    double x_new, x_old = x1;
    
    //итерационный процесс
    while (pogreshnost > epsilon && l <= k)
    {
        fx = f(x_old);
        dfx = df(x_old);
        if (dfx == 0)
        {
            ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
            if (!fileout.is_open())
            {
                fileout << "IER = 4" << endl;
                fileout << "Файл не найден!" << endl;
                cout << "Файл не найден!" << endl;
                return 0;
            }
            else {
                fileout << "IER = 3" << endl;
                fileout << "Деление на 0!" << endl;
            }
            fileout.close();
            cout<< "IER = 3" << endl;
            cout << "Деление на 0!" << endl;
            return 0;
        }
        else
        {
            x_new = x_old - (fx / dfx);
            x.push_back(x_new);
            pogreshnost = abs(x_new - x_old);
            l++;
            x_old = x_new;
        }
    }

    //проверка на ошибку количеств итераций
    if (l > k)
    {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
            cout << "Файл не найден!" << endl;
            return 0;
        }
        else {
            fileout << "IER = 1" << endl;
            fileout << "Превышено число итераций!" << endl;
        }
        fileout.close();
        cout << "IER = 1" << endl;
        cout << "Превышено число итераций!" << endl;
        return 0;
    }

    //проверка на приближенность к решению
    if (pogreshnost <= epsilon) {
        ofstream fileout("F:\\FilesForLabs\\ЧМ\\CHM5labVivod.txt");
        if (!fileout.is_open())
        {
            fileout << "IER = 4" << endl;
            fileout << "Файл не найден!" << endl;
            cout << "Файл не найден!" << endl;
            return 0;
        }
        else
        {
            fileout << "IER = 0" << endl;
            fileout << "Решение получено!" << " Ответ: " << x_old << endl;
            fileout << "Значение модуля функции в найденном значении: " << abs(f(x_old)) << endl;
            fileout << "Точность полученного решения: " << pogreshnost << endl;
            fileout << "Число итераций: " << l << endl;
        }
        fileout.close();
        cout << endl << endl << "Решение получено!" << " Ответ: " << x_old << endl;
        cout<< "Значение модуля функции в найденном значении: " << abs(f(x_old)) << endl;
        cout << "Точность полученного решения: " << pogreshnost << endl;
        cout << "Число итераций: " << l << endl;
        return 0;
    }
    
    return 0;
}
double f(double x)
{
    return x * x * x*x - 2;
}
double df(double x)
{
    return 4 * x * x*x;
}

