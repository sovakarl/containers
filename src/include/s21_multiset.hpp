#ifndef S21_MULTISET_HPP
#define S21_MULTISET_HPP
#include "s21_set.hpp"


namespace s21{
template <typename Key>
class multiset:public set<Key>{
    public:
    using MultisetIterator=typename set<Key>::SetIterator;
    using MultisetConstIterator=typename set<Key>::SetConstIterator;

    using key_type=Key;
    using value_type=Key;
    using reference=value_type&;
    using const_reference=const value_type&;
    using iterator=MultisetIterator;
    using const_iterator=MultisetConstIterator;
    using size_type=size_t;
    //using object=typename set<Key>::object;

    multiset();
    multiset(std::initializer_list<value_type> const &items);
    multiset(const multiset &s);
    multiset(multiset &&s);
   ~multiset(){set<Key>::clear();};
    multiset& operator=(multiset &&s);


    iterator begin()const;
    iterator end()const;

    iterator insert(const value_type& value);
    size_type count(const Key& key);

    std::pair<iterator,iterator> equal_range(const Key& key);
    iterator lower_bound(const Key& key);
    iterator upper_bound(const Key& key);
};

#include "../template/s21_multiset.cpp"
}


#endif