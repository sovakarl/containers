#ifndef S21_VECTOR_HPP
#define S21_VECTOR_HPP

#include <limits>
#include <iostream>
namespace s21{

template<typename T>
class vector{

    public:
    using value_type=T;
    using reference=T&;
    using const_reference=const T&;
    using iterator=T*;
    using const_iterator=const T*;
    using size_type=std::size_t;

    vector();
    vector(size_type n);
    vector(std::initializer_list<value_type> const &items);
    vector(const vector& v);
    vector(vector &&v);
    ~vector();
    vector& operator=(vector &&v);

    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    iterator data();

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    bool empty();
    size_type size();
    size_type max_size();
    void reserve(size_type size);
    size_type capacity();
    void shrink_to_fit();



    void clear();
    iterator insert(iterator pos, const_reference value);

    template <typename... Args>
    iterator insert_many(const_iterator pos, Args &&...args);

    template <typename... Args>
    void insert_many_back(Args &&...args);
    
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(vector& other);
  
    private:
    size_type capacity_;
    size_type size_;
    T* pointer;

};
#include "../template/s21_vector.cpp"
}


#endif