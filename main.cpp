#include <iostream>
#include <windows.h>
using namespace std;

template <typename T>
class Element
{
public:
    T value;
    Element* next;
    Element* prev;
    Element() : value(), next(nullptr), prev(nullptr) {}
    Element(T value) : value(value), next(nullptr), prev(nullptr) {}
    ~Element() = default;
};

template <typename T>
class doubly_linked_list
{
private:
    Element<T>* _head;
    Element<T>* _tail;
    int _size;
public:
    doubly_linked_list() : _head(nullptr), _tail(nullptr), _size(0) {}
    ~doubly_linked_list()
    {
        Element<T>* temp = _head;
        while (temp != nullptr)
        {
            temp = temp->next;
            delete _head;
            _head = temp;
        }
        _tail = nullptr;
    }

    void push_back(T value)
    {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr)
        {
            _head = temp;
            _tail = temp;
        }
        else
        {
            _tail->next = temp;
            temp->prev = _tail;
            _tail = temp;
        }
        _size++;
    }
    void push_front(T value)
    {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr)
        {
            _head = temp;
            _tail = temp;
        }
        else
        {
            temp->prev = nullptr;
            temp->next = _head;
            _head->prev = temp;
            _head = temp;
        }
        _size++;
    }
    void pop_back()
    {
        if (_head == nullptr)
        {
            return;
        }
        else if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Element<T>* temp = _head;
            while (temp->next != _tail)
            {
                temp = temp->next;
            }
            delete _tail;
            _tail = temp;
            _tail->next = nullptr;
        }
        _size--;
    }
    void pop_front()
    {
        if (_head == nullptr)
        {
            return;
        }
        else if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Element<T>* temp = _head;
            _head = _head->next;
            _head->prev = nullptr;
            delete temp;
        }
        _size--;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > _size)
        {
            return;
        }
        else if (index == 0)
        {
            push_front(value);
        }
        else if (index == _size)
        {
            push_back(value);
        }
        else
        {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Element<T>* new_elem = new Element<T>(value);
            new_elem->next = temp->next;
            temp->next->prev = new_elem;
            new_elem->prev = temp;
            temp->next = new_elem;
            _size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= _size)
        {
            return;
        }
        else if (index == 0)
        {
            pop_front();
        }
        else if (index == _size - 1)
        {
            pop_back();
        }
        else
        {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Element<T>* to_delete = temp->next;
            temp->next = temp->next->next;
            temp->next->prev = temp;
            delete to_delete;
            _size--;
        }
    }
    void remove_by_value(T value)
    {
        Element<T>* temp = _head;
        int index = 0;
        while (temp != nullptr)
        {
            if (temp->value == value)
            {
                remove(index);
                return;
            }
            temp = temp->next;
            index++;
        }
    }
    void print()
    {
        Element<T>* temp = _head;
        while (temp != nullptr)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void dev_print()
    {
        int index = 0;
        Element<T>* temp = _head;
        while (temp != nullptr)
        {
            cout << "Element[" << index << "]: " << (long long)temp << endl;
            cout << "Value: " << temp->value << endl;
            cout << "Next element: " << (long long)temp->next << endl << endl;
            temp = temp->next;
            index++;
        }
        cout << endl;
    }
    int size()
    {
        return _size;
    }

    // Clone operation
    doubly_linked_list<T>* clone()
    {
        doubly_linked_list<T>* new_list = new doubly_linked_list<T>();
        Element<T>* temp = _head;
        while (temp != nullptr)
        {
            new_list->push_back(temp->value);
            temp = temp->next;
        }
        return new_list;
    }

    // Operator + overload
    doubly_linked_list<T>* operator+(const doubly_linked_list<T>& other)
    {
        doubly_linked_list<T>* new_list = new doubly_linked_list<T>();
        Element<T>* temp = _head;
        while (temp != nullptr)
        {
            new_list->push_back(temp->value);
            temp = temp->next;
        }
        temp = other._head;
        while (temp != nullptr)
        {
            new_list->push_back(temp->value);
            temp = temp->next;
        }
        return new_list;
    }

    // Operator * overload
    doubly_linked_list<T>* operator*(const doubly_linked_list<T>& other)
    {
        doubly_linked_list<T>* new_list = new doubly_linked_list<T>();
        Element<T>* temp1 = _head;
        while (temp1 != nullptr)
        {
            Element<T>* temp2 = other._head;
            while (temp2 != nullptr)
            {
                if (temp1->value == temp2->value)
                {
                    new_list->push_back(temp1->value);
                    break;
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
        return new_list;
    }
};

template <typename T>
class Array
{
private:
    Element<T>* _head;
    Element<T>* _tail;
    int _size;
    int _capacity;
    int _grow;

    void resize(int new_size)
    {
        if (new_size > _capacity)
        {
            while (_capacity < new_size)
            {
                _capacity += _grow;
            }
        }
        else if (new_size < _capacity)
        {
            while (_capacity > new_size)
            {
                _capacity -= _grow;
            }
        }
    }

    void push_back(T value)
    {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr)
        {
            _head = temp;
            _tail = temp;
        }
        else
        {
            _tail->next = temp;
            temp->prev = _tail;
            _tail = temp;
        }
        _size++;
    }

    void push_front(T value)
    {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr)
        {
            _head = temp;
            _tail = temp;
        }
        else
        {
            temp->next = _head;
            _head->prev = temp;
            _head = temp;
        }
        _size++;
    }

    void pop_back()
    {
        if (_head == nullptr)
        {
            return;
        }
        else if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Element<T>* temp = _tail;
            _tail = _tail->prev;
            _tail->next = nullptr;
            delete temp;
        }
        _size--;
    }

    void pop_front()
    {
        if (_head == nullptr)
        {
            return;
        }
        else if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            Element<T>* temp = _head;
            _head = _head->next;
            _head->prev = nullptr;
            delete temp;
        }
        _size--;
    }

public:
    Array(int grow = 1) : _head(nullptr), _tail(nullptr), _size(0), _capacity(0), _grow(grow) {}

    ~Array()
    {
        RemoveAll();
    }

    int GetSize() const
    {
        return _size;
    }

    void SetSize(int size, int grow = 1)
    {
        _grow = grow;
        resize(size);
        while (_size > size)
        {
            pop_back();
        }
        while (_size < size)
        {
            if (_size % _grow == 0)
            {
                resize(_size + _grow);
            }
            push_back(T());
        }
    }

    int GetUpperBound() const
    {
        return _size - 1;
    }

    bool IsEmpty() const
    {
        return _size == 0;
    }

    void FreeExtra()
    {
        resize(_size);
    }

    void RemoveAll()
    {
        while (_head != nullptr)
        {
            Element<T>* temp = _head;
            _head = _head->next;
            delete temp;
        }
        _tail = nullptr;
        _size = 0;
        _capacity = 0;
    }

    T GetAt(int index) const
    {
        if (index < 0 || index >= _size)
        {
            throw out_of_range("Index out of range");
        }
        Element<T>* temp = _head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->value;
    }

    void SetAt(int index, T value)
    {
        if (index < 0 || index >= _size)
        {
            throw out_of_range("Index out of range");
        }
        Element<T>* temp = _head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        temp->value = value;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= _size)
        {
            throw out_of_range("Index out of range");
        }
        Element<T>* temp = _head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->value;
    }

    void Add(T value)
    {
        if (_size >= _capacity)
        {
            resize(_size + 1);
        }
        push_back(value);
    }

    void Append(const Array<T>& other)
    {
        Element<T>* temp = other._head;
        while (temp != nullptr)
        {
            Add(temp->value);
            temp = temp->next;
        }
    }

    Array<T>& operator=(const Array<T>& other)
    {
        if (this != &other)
        {
            RemoveAll();
            Element<T>* temp = other._head;
            while (temp != nullptr)
            {
                Add(temp->value);
                temp = temp->next;
            }
            _capacity = other._capacity;
            _grow = other._grow;
        }
        return *this;
    }

    T* GetData()
    {
        T* data = new T[_size];
        Element<T>* temp = _head;
        for (int i = 0; i < _size; ++i)
        {
            data[i] = temp->value;
            temp = temp->next;
        }
        return data;
    }

    void InsertAt(int index, T value)
    {
        if (index < 0 || index > _size)
        {
            throw out_of_range("Index out of range");
        }
        if (index == 0)
        {
            push_front(value);
        }
        else if (index == _size)
        {
            push_back(value);
        }
        else
        {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; ++i)
            {
                temp = temp->next;
            }
            Element<T>* new_elem = new Element<T>(value);
            new_elem->next = temp->next;
            new_elem->prev = temp;
            temp->next->prev = new_elem;
            temp->next = new_elem;
            _size++;
        }
    }

    void RemoveAt(int index)
    {
        if (index < 0 || index >= _size)
        {
            throw out_of_range("Index out of range");
        }
        if (index == 0)
        {
            pop_front();
        }
        else if (index == _size - 1)
        {
            pop_back();
        }
        else
        {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; ++i)
            {
                temp = temp->next;
            }
            Element<T>* to_delete = temp->next;
            temp->next = temp->next->next;
            temp->next->prev = temp;
            delete to_delete;
            _size--;
        }
    }

};


int main()
{
    Array<int> arr;
    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    cout << "Array size: " << arr.GetSize() << endl;
    cout << "Array elements: ";
    for (int i = 0; i < arr.GetSize(); ++i)
    {
        cout << arr[i] << " ";
    }
	cout << endl;
    
    arr.RemoveAt(2);

    Array<int> arr2;
    arr2 = arr;
    arr2.Append(arr);
    cout << "Array 2 old elements: ";
    for (int i = 0; i < arr2.GetSize(); ++i)
    {
        cout << arr2[i] << " ";
    }
	cout << endl;

    arr2.SetSize(5, 2);
    arr2.InsertAt(1, 4);
	arr2.FreeExtra();
    
    cout << "Array 2 memory: " << arr2.GetData() << endl;
    cout << "Array 2 size: " << arr2.GetSize() << endl;
    cout << "Array 2 elements: ";
    for (int i = 0; i < arr2.GetSize(); ++i)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}