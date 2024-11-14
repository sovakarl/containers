#ifndef S21_SET_CPP
#define S21_SET_CPP
#include "../include/s21_set.hpp"

#include "../include/BP_tree.hpp"

using namespace s21;

template <typename Key>
set<Key>::set() : object(){};

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) : set() {
  for (const auto item : items) insert(item);
}

template <typename Key>
set<Key>::set(const set& m) : object(m.object) {}

template <typename Key>
set<Key>::set(set&& m) : object(std::move(m.object)) {}

template <typename Key>
set<Key>& set<Key>::operator=(set&& m) {
  clear();
  object.root = m.object.root;
  m.object.root = nullptr;
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() const {
  iterator tmp(object.min(object.root));
  return tmp;
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() const {
  iterator tmp(nullptr);
  return tmp;
}

template <typename Key>
bool set<Key>::empty() {
  bool result = object.root ? 0 : 1;
  return result;
};

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return empty() ? 0 : object.sizeTree(0, object.root);
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return (std::numeric_limits<size_type>::max() * sizeof(size_type)) /
         (sizeof(NodeTree::Node<Key, Key>));
}

template <typename Key>
void set<Key>::clear() {
  if (!empty()) {
    object.clearTree(object.root);
    object.root = nullptr;
  }
}

template <typename Key>
typename std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  std::pair<iterator, bool> result;
  std::pair<Key, Key> iner;
  iner.first = iner.second = value;
  result.second = contains(iner.first) ? 0 : 1;
  object.root = object.insertTree(iner, object.root);
  result.first = object.searchTree(iner.first);
  object.balancing(object.searchTree(iner.first));
  return result;
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (object.searchRoot(pos.ptr)) object.deleteKnot(pos.ptr);
}

template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(object.root, other.object.root);
};

template <typename Key>
void set<Key>::merge(set& other) {
  set<Key>::SetIterator it = other.begin();
  while (it != other.end()) {
    insert(*it);
    ++it;
  }
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  iterator res(object.searchTree(key));
  return res;
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return object.searchTree(key) ? 1 : 0;
};

template <typename Key>
typename set<Key>::SetIterator& set<Key>::SetIterator::operator++() {
  tree<Key, Key> tmp;
  ptr = tmp.next(ptr);
  return *this;
}

template <typename Key>
typename set<Key>::SetIterator& set<Key>::SetIterator::operator--() {
  tree<Key, Key> tmp;
  ptr = tmp.prev(ptr);
  return *this;
}

template <typename Key>
typename set<Key>::SetConstIterator& set<Key>::SetConstIterator::operator++() {
  tree<Key, Key> tmp;
  ptr = tmp.next(ptr);
  return *this;
}

template <typename Key>
typename set<Key>::SetConstIterator& set<Key>::SetConstIterator::operator--() {
  tree<Key, Key> tmp;
  ptr = tmp.prev(ptr);
  return *this;
}

#endif