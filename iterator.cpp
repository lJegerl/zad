#include "List.h"
#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>
using namespace std;


unsigned counting(ListIterator* li) {
    unsigned cnt = 0;
    if (li->first())
        do {
            cnt++;
            cerr << li->currentItem() << " ";
        } while (li->next());
        cerr << endl;
        return cnt;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(0));
    unsigned capacity, count;
    cout << "Введите объём стека: ";
    cin >> capacity;
    List list(capacity);
    cout << "Введите кколичество элементов для заполнения стека: ";
    cin >> count;
    for (auto i = 0; i < count; i++) {
        int x = rand() % 5;
        if (list.append(x))
            cout << x << " ";
    }
    cout << endl;

    ListIterator* litS3 = list.createIterator(Iterators::STEP, 3);
    ListIterator* litV4 = list.createIterator(Iterators::VALUE, 4);
    ListIterator* litPred = list.createIterator(Iterators::PREDICATE, 4);

    cout << counting((ListIteratorStep*)litS3) << endl;
    cout << counting((ListIteratorValue*)litV4) << endl;
}