#ifndef S21_SET_HPP
#define S21_SET_HPP

#include <utility>
#include <limits>
#include "BP_tree.hpp"
#include <iostream>

namespace s21{
template <typename Key>
class set{
    public:
    class SetIterator;
    class SetConstIterator;

    using key_type=Key;
    using value_type=Key;
    using reference=value_type&;
    using const_reference=const value_type&;
    using iterator=SetIterator;
    using const_iterator=SetConstIterator;
    using size_type=std::size_t;

    set();
    set(std::initializer_list<value_type> const &items);
    set(const set &s);
    set(set &&s);
    ~set(){clear();};
    set& operator=(set &&s);

    iterator begin()const;
    iterator end()const;

    bool empty();
    size_type size();
    size_type max_size();

    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    void swap(set& other);
    void merge(set& other);

    iterator find(const Key& key);
    bool contains(const Key& key);

    protected:
    tree<Key,Key> object;
};

template <typename Key>
class set<Key>::SetIterator{
    friend class set;
    public:
        SetIterator(NodeTree::Node<Key,Key>* src){ptr=src;};
        SetIterator():SetIterator(nullptr){};

        reference operator *(){return ptr->value.first;};
        SetIterator& operator ++(); 
        SetIterator& operator --();

        bool operator ==(SetIterator src)const{return ptr==src.ptr?1:0;};
        bool operator !=(SetIterator src)const{return ptr!=src.ptr?1:0;};
    private:
        NodeTree::Node<Key,Key>* ptr;
};

template <typename Key>
class set<Key>::SetConstIterator{
    friend class set;
    public:
        SetConstIterator(NodeTree::Node<Key,Key>* src){ptr=src;};
        SetConstIterator():SetConstIterator(nullptr){};

        const_reference operator *(){return ptr->value.first;};
        SetConstIterator& operator ++(); 
        SetConstIterator& operator --();

        bool operator ==(SetConstIterator src){return ptr==src.ptr?1:0;};
        bool operator !=(SetConstIterator src){return ptr!=src.ptr?1:0;};
    private:
        NodeTree::Node<Key,Key>* ptr;
};
#include "../template/s21_set.cpp"

}
#endif