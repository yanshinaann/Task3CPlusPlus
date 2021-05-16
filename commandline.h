
#ifndef UNTITLED_COMMANDLINE_H
#define UNTITLED_COMMANDLINE_H

#include <iostream>
#include <string>
#include "cyclic_list.h"

using namespace std;

template <typename _T>
void workWithConsole()
{
    int exit = 0;
    CyclicList<_T> cl;
    CyclicList<_T> cyclicList(cl);
    while (!exit)
    {
        int a;
        cout << "Select action: 1. Push element | " <<
             "2. Add element by index | " <<
             "3. Delete element by index | " <<
             "4. Print all | " <<
             "5. Exit |\n";
        cin >> a;
        switch (a)
        {
            case 5:
                exit++;
                break;
            case 1:
                try
                {
                    _T data;
                    cin >> data;
                    cyclicList.pushElement(data);
                }
                catch (const char *message)
                {
                    cerr << message << "\n";
                }
                break;
            case 2:
                try
                {
                    int index;
                    cout << "Index: ";
                    cin >> index;
                    _T data;
                    cout << "Element: ";
                    cin >> data;
                    cyclicList.addElementByIndex(index, data);
                }
                catch (const char *message)
                {
                    cerr << message << "\n";
                }
                break;
            case 3:
                try
                {
                    int index;
                    cout << "Index: ";
                    cin >> index;
                    cyclicList.deleteElementByIndex(index);
                }
                catch (const char *message)
                {
                    cerr << message << "\n";
                }
                break;
            case 4:
                cout << cyclicList.printAll() <<"\n";
                break;

        }
    }
}

#endif //UNTITLED_COMMANDLINE_H
