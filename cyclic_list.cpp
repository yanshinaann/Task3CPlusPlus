

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

    int length()
    {
        return size;
    }

    _Type getLastElement()
    {
        return tailElement->data;
    }

    _Type getElementByIndex(int index)
    {
        return selectElementByIndex(index)->data;
    }

    void addElementByIndex(int index, _Type elementData)
    {

        if (size)
        {
            ListElement* selectedElement;
            ListElement* newElement = new ListElement();
            newElement->data = elementData;
            if (index == 0)
            {
                selectedElement = headElement;
                headElement = newElement;
                headElement->nextElement = selectedElement;
            }
            else if (index == size - 1 || size == 1)
            {
                delete newElement;
                pushElement(elementData);
            }
            else
            {
                selectedElement = selectElementByIndex(index-1);
                newElement->nextElement = selectedElement->nextElement;
                selectedElement->nextElement = newElement;
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
            if (size == 1 || &tailElement == &(selectedElement->nextElement))
            {
                // index == size - 1 || size == 1
                deleteLastElement();
            }
            else if (&headElement == &(selectedElement->nextElement))
            {
                // index == 0
                selectedElement = headElement;
                // tailElement->nextElement = headElement->nextElement;
                // headElement = tailElement->nextElement;

                headElement = headElement->nextElement;
                tailElement->nextElement = headElement;
                delete selectedElement;
                size--;
            }
            else
            {
                // selectedElement = selectElementByIndex(index-1);
                ListElement* delElement = selectedElement->nextElement;
                selectedElement->nextElement = selectedElement->nextElement->nextElement;
                delete delElement;
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
            ListElement* selected = selectElementByIndex(size-1);
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
            // result.append(std::to_string(element->data) + " ");

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
            // data = NULL;
            nextElement = nullptr;
        }
    };
    ListElement* headElement, *tailElement;
    int size;
    ListElement* selectElementByIndex(int index)
    {
        if (index < 0)
        {
            throw "Bad index";
        }
        ListElement* selected = headElement;
        int num = 0;
        while (num < index)
        {
            selected=selected->nextElement;
            num++;
        }
        return selected;
    }
};