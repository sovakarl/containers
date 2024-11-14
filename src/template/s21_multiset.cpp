#ifndef S21_MULTISET_CPP
#define S21_MULTISET_CPP
#include "../include/s21_multiset.hpp"

using namespace s21;

template <typename Key>
multiset<Key>::multiset() : set<Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (const auto item : items) insert(item);
}

template <typename Key>
multiset<Key>::multiset(const multiset& s) {
  iterator it = s.begin();
  while (it != s.end()) {
    insert(*it);
    ++it;
  }
}
template <typename Key>
multiset<Key>::multiset(multiset&& s) : set<Key>(std::move(s)) {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& s) {
  set<Key>::clear();
  set<Key>::object.root = s.object.root;
  s.object.root = nullptr;
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() const {
  iterator tmp(set<Key>::object.min(set<Key>::object.root));
  return tmp;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() const {
  iterator tmp(nullptr);
  return tmp;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  std::pair<Key, Key> iner;
  iner.first = iner.second = value;
  set<Key>::object.root =
      set<Key>::object.insertTree_dup(iner, set<Key>::object.root);
  set<Key>::object.balancing(set<Key>::object.searchTree_dup(iner.first));
  iterator result(set<Key>::object.searchTree_dup(iner.first));
  return result;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type result = 0;
  iterator it = begin();
  while (it != end()) {
    if (*it == key) result++;
    ++it;
  }
  return result;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  std::pair<iterator, iterator> result;
  if (set<Key>::contains(key)) {
    iterator first;
    result.first = lower_bound(key);
    iterator second = first = result.first;
    // result.second=upper_bound(key);
    while (first != end()) {
      if (*first != key) break;
      second = first;
      ++first;
    }
    result.second = second;
  } else
    result.second = result.first = end();
  return result;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  iterator it(set<Key>::object.min(set<Key>::object.root));
  iterator result = it;
  while (it != end()) {
    result = it;
    if (*it == key) break;
    ++it;
  }
  return result;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  iterator it(set<Key>::object.max(set<Key>::object.root));
  iterator result = it;
  while (it != begin()) {
    if (*it <= key) break;
    result = it;
    --it;
  }
  return result;
}

#endif