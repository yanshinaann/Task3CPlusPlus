//+ итератор и копи-конструктор

#ifndef UNTITLED_CYCLIC_LIST_H
#define UNTITLED_CYCLIC_LIST_H


#include <string>
#include <sstream>

template <typename _Type>
class CyclicList
{
public:
    CyclicList()
    {
        size = 0;
        headElement = new ListElement();
        tailElement = headElement;
    }

    CyclicList(_Type firstElementData)
    {
        CyclicList();
        pushElement(firstElementData);
    }

    // Конструктор копирования
    CyclicList(const CyclicList &cyclicList) :
            size(cyclicList.size), headElement(cyclicList.headElement), tailElement(cyclicList.tailElement)
    {
        std::cout << "Copy constructor worked here!\n";
    }

    void pushElement(_Type elementData)
    {
        ListElement* newElement = new ListElement();
        newElement->data = elementData;

        if (size != 0)
        {
            tailElement->nextElement = newElement;
            tailElement=newElement;
        }
        else
        {
            headElement = tailElement = newElement;
        }
        tailElement->nextElement = headElement;
        size++;

    }
    int length() { return size; }

    _Type getLastElement() { return tailElement->data; }

    _Type getElementByIndex(int index) { return selectElementByIndex(index)->data; }

    void addElementByIndex(int index, _Type elementData)
    {
        if (size)
        {
            ListElement* selectedElement = selectElementByIndex(index-1);
            ListElement* newElement = new ListElement();
            newElement->data = elementData;

            newElement->nextElement = selectedElement->nextElement;
            selectedElement->nextElement = newElement;
            if (!index)
            {
                //first
                headElement = newElement;
            }

            size++;
        }
        else
        {
            if (index)
            {
                throw "No elements in list";
            }
            else
            {
                pushElement(elementData);
            }
        }
    }

    void deleteElementByIndex(int index)
    {
        if (size)
        {
            ListElement* selectedElement = selectElementByIndex(index-1);
            if (index == size - 1)
            {
                deleteLastElement();
            }
            else
            {
                ListElement* delElement = selectedElement->nextElement;
                selectedElement->nextElement = delElement->nextElement;
                delete delElement;
                if (!index)
                {
                    headElement = selectedElement->nextElement;
                }
                size--;
            }
        }
        else
        {
            throw "No elements in list to delete";
        }
    }

    void deleteLastElement()
    {
        if (!size)
        {
            throw "No elements in list to delete";
        }
        else if (size == 1)
        {
            delete headElement;
        }
        else
        {
            ListElement* selected = selectElementByIndex(size-2);
            selected->nextElement = headElement;
            delete tailElement;
            tailElement = selected;
        }
        size--;
    }

    std::string printAll()
    {
        std::string result = "";

        ListElement* element = headElement;
        for (int i = 0; i < size; i++)
        {
            std::ostringstream oss;
            oss<<element->data;
            result.append(oss.str() + " ");

            element=element->nextElement;
        }

        return result;
    }

    ~CyclicList()
    {
        while (size != 0)
        {
            ListElement* next = headElement->nextElement;
            delete headElement;
            headElement = next;
            size--;
        }
        delete tailElement;
    }
private:
    class ListElement
    {
    public:
        _Type data;
        ListElement* nextElement;
        ListElement()
        {
            nextElement = nullptr;
        }
    };

    int size;
    ListElement* headElement, *tailElement;

    ListElement* selectElementByIndex(int index)
    {
        if (index < -1 || index >= size)
        {
            throw "Bad index";
        }
        ListElement* selected = headElement;
        if (index == -1 || index + 1 == size) return tailElement;
        int num = 0;
        while (num < index)
        {
            selected=selected->nextElement;
            num++;
        }
        return selected;
    }
};
#endif //UNTITLED_CYCLIC_LIST_H
