#ifndef S21LIST
#define S21LIST
#include <iostream>
#include <limits>

namespace s21{

namespace NodeList{
template <typename T> struct Node{
    T Value;
    Node<T>* Next;
    Node<T>* Previous;
    Node(T data):Value(data),Next(nullptr),Previous(nullptr){};
};
};
using namespace NodeList;

template <typename T> class list{
    public:
    using value_type=T;
    using reference=T&;
    using const_reference=const T&;
    using size_type=size_t;
    
    class iterator;
    class const_iterator;
    list():head(nullptr),tail(nullptr){};
    list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &l);
    list(list &&l);
    ~list();
    list& operator=(const list&& l);
    list& operator=(const list& l);

    const_reference front();
    const_reference back();

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();


    bool empty();
    size_type size();
    size_type max_size();

    void clear();// очищает содержимое
    iterator insert(iterator pos, const_reference value);//вставляет в pos

    template <class... Args>
    iterator insert_many(const_iterator pos, Args &&...args);
    template <class... Args>
    
    void insert_many_back(Args &&...args);
    template <class... Args>
    void insert_many_front(Args &&...args);
    
    void erase(iterator pos);//стирает элемент в позиции pos
    void push_back(const_reference value);//добавляет элемент в конец
    void pop_back();// удаляет последний элемент
    void push_front(const_reference value);// добавляет элемент в начало
    void pop_front();// удаляет первый элемент
    void swap(list& other);// меняет местами содержимое
    void merge(list& other);// объединяет отсортированные листы
    void splice(const_iterator pos,list& other);// безопасная вставка
    void reverse();//меняет порядок расположения элементов на противоположный
    void unique();//удаляет последовательные дубликаты
    void sort();// сортировка

    private:
        Node<T>* head;
        Node<T>* tail;

};

template <typename T>
class list<T>::iterator {
    public:
        iterator(Node<T>* value):pointer(value){}
        iterator():iterator(nullptr){};
        ~iterator(){pointer=nullptr;}
        Node<T>* get_p(void){return pointer;};
        void set_p(Node<T>* ptr){pointer=ptr;}
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        reference operator*(){return pointer->Value;}
        iterator& operator=(const iterator& value){
            pointer=value.pointer;
            return *this;
        }
        bool operator==(const iterator value){return value.pointer==pointer?1:0;}
        bool operator!=(const iterator value){return pointer==value.pointer?0:1;}

    protected:
    Node<T>* pointer;
};

template <typename T>
class list<T>::const_iterator:public list<T>::iterator {
    public:
    using iterator::iterator;
    const_reference operator*(){return iterator::pointer->Value;}
};

#include "../template/s21_list.cpp"


};
#endif