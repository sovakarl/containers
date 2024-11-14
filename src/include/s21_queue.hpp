#ifndef S21QUEUE
#define S21QUEUE
#include "s21_list.hpp"

namespace s21{
template <typename T>
class queue{
    public:
    using value_type=T;
    using reference=T&;
    using const_reference=const T&;
    using size_type=size_t;

    queue():object(){};
    queue(std::initializer_list<value_type> const &items):object(items){};
    queue(const queue &q):object(q.object){};
    queue(queue &&q):object(std::move(q.object)){};
    queue& operator =(queue &&q){object=q.object;}
    ~queue(){object.clear();}

    const_reference front(){return object.front();}
    const_reference back(){return object.back();}

    bool empty(){return object.empty();}
    size_type size(){return object.size();}

    void push(const_reference value){object.push_back(value);}
    void pop(){object.pop_front();}
    void swap(queue& other){object.swap(other.object);}
    private:
        list<T> object;

};


}

#endif