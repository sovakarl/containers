#ifndef S21_MAP
#define S21_MAP
#include <utility>
#include <limits>
#include "BP_tree.hpp"
#include <iostream>


namespace s21{


template <typename Key,typename T >
class map{
    public:
    class MapIterator;
    class MapConstIterator;

    using key_type=Key;
    using mapped_type=T;
    using value_type=std::pair<const key_type,mapped_type>;
    using reference =value_type &;
    using const_reference=const value_type &;
    using iterator=MapIterator;
    using const_iterator=MapConstIterator;
    using size_type=std::size_t;

    map();
    map(std::initializer_list<value_type> const &items);
    map(const map &m);
    map(map &&m);
    ~map(){clear();};
    
    map& operator=(map &&m);
    map& operator=(map &m);

    T& at(const Key& k);
    T& operator[](const Key& key);

    iterator begin();
    iterator end();


    bool empty();
    size_type size();
    size_type max_size();

    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const Key& key, const T& obj);
    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);


    void erase(iterator pos);
    void swap(map& other);
    void merge(map& other);

    bool contains(const Key& key);

    private:
        tree<Key,T> object;
};

template <typename Key,typename T>
class map<Key,T>::MapIterator{
    friend class map;
    public:
        MapIterator(NodeTree::Node<Key,T>* src){ptr=src;};
        MapIterator():MapIterator(nullptr){};

        std::pair<Key,T> operator *(){return ptr->value;}
        value_type* operator->(){return ptr->value;}
        MapIterator& operator ++(); 
        MapIterator& operator --();

        bool operator ==(MapIterator src){return ptr==src.ptr?1:0;};
        bool operator !=(MapIterator src){return *this==src?0:1;};
    private:
        NodeTree::Node<Key,T>* ptr;
};

template <typename Key,typename T>
class map<Key,T>::MapConstIterator{
    public:
        MapConstIterator(NodeTree::Node<Key,T>* src){ptr=src;};
        MapConstIterator():MapConstIterator(nullptr){};

        const std::pair<Key,T> operator *(){return ptr->value;}
        const value_type* operator->(){return ptr->value;};
        MapConstIterator& operator ++();
        MapConstIterator& operator --();
    private:
        NodeTree::Node<Key,T>* ptr;
};

#include "../template/s21_map.cpp"

};


#endif