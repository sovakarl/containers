#ifndef S21_ARRAY_HPP
#define S21_ARRAY_HPP

#include <limits>
#include <iostream>
namespace s21{


template<typename T,std::size_t N>
class array{
    public:
    using value_type=T;
    using reference=T&;
    using const_reference=const T&;
    using iterator=T*;
    using const_iterator=const T*;
    using size_type=std::size_t;

    array()=default;
    array(std::initializer_list<value_type> const &items);
    array(const array& a);
    array(array &&a);
    ~array()=default;

    array& operator=(array&&a);

    reference at(size_type pos);
    const_reference at(size_type pos)const;
    reference operator[](size_type pos);
    const_reference front()const;
    const_reference back()const;
    iterator data();

    iterator begin();
    iterator end();

    const_iterator cbegin() const ;
    const_iterator cend() const;

    bool empty();
    size_type size();
    size_type max_size();

    void swap(array & other);
    void fill(const_reference value);


    private:
    T arr[N]={};
    size_type amount=N;

};
#include "../template/s21_array.cpp"
}



#endif