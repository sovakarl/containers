#ifndef S21_STACK
#define S21_STACK
#include "s21_list.hpp"
namespace s21{

template <typename T>
class stack{
    public:
    using value_type=T;
    using reference=T&;
    using const_reference=const T&;
    using size_type=size_t;

    stack():object(){object.reverse();};
    stack(std::initializer_list<value_type> const &items):object(items){object.reverse();};
    stack(const stack &q):object(q.object){};
    stack(stack &&q):object(std::move(q.object)){};
    stack& operator =(stack &&q){object=q.object;}
    ~stack(){object.clear();}

    const_reference top(){return object.front();}

    bool empty(){return object.empty();}
    size_type size(){return object.size();}

    void push(const_reference value){object.push_front(value);}
    void pop(){object.pop_front();}
    void swap(stack& other){object.swap(other.object);}
    private:
        list<T> object;
};


};


#endif
