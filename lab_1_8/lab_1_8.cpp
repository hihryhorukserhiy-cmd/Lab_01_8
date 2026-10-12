#include <iostream>
#include <Windows.h>
#include "Set.h"

using namespace std;

Set makeSet()
{
    Set s;
    s.Init();
    return s;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== 1. Робота з вкладеним класом Set::BitString ===\n";
    Set::BitString bs1, bs2;
    bs1.Init(0, 15);
    bs2.Init(0, 7);

    cout << "bs1: "; bs1.Display();
    cout << "bs2: "; bs2.Display();

    Set::BitString bsAnd = bs1.And(bs2);
    cout << "bs1 AND bs2: "; bsAnd.Display();

    cout << "\n=== 2. Демонстрація зовнішнього класу Set ===\n";
    Set A = makeSet();
    A.Include(3);
    A.Include(15);
    A.Include(48);
    cout << "Множина A: "; A.Display();

    Set B = makeSet();
    B.Include(15);
    B.Include(30);
    B.Include(48);
    cout << "Множина B: "; B.Display();

    Set A_union_B = A.Union(B);
    cout << "Об'єднання (A U B): "; A_union_B.Display();

    Set A_inter_B = A.Intersection(B);
    cout << "Перетин (A ∩ B): "; A_inter_B.Display();

    Set A_diff_B = A.Difference(B);
    cout << "Різниця (A \\ B): "; A_diff_B.Display();

    cout << "\n=== 3. Демонстрація динамічної пам'яті (-> та масив) ===\n";
    Set* ptrSet = new Set();
    ptrSet->Init();
    ptrSet->Include(10);
    ptrSet->Include(20);
    ptrSet->Include(60);
    cout << "Множина через покажчик: "; ptrSet->Display();
    ptrSet->Exclude(20);
    cout << "Після Exclude(20): "; ptrSet->Display();
    delete ptrSet;

    int n = 2;
    Set* arr = new Set[n];
    arr[0].Init();
    arr[0].Include(1);
    arr[1].Init();
    arr[1].Include(2);
    arr[1].Include(3);

    for (int i = 0; i < n; i++)
    {
        cout << "arr[" << i << "] = ";
        arr[i].Display();
    }
    delete[] arr;

    cout << "\n=== 4. Інтерактивне введення множини ===\n";
    Set userSet;
    userSet.Read();
    cout << "Введена множина: "; userSet.Display();

    return 0;
}