#ifndef S21_MAP_CPP
#define S21_MAP_CPP
#include "../include/s21_map.hpp"

#include "../include/BP_tree.hpp"

using namespace s21;

template <typename Key, typename T>
map<Key, T>::map() : object(){};

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (const auto item : items) insert(item);
}

template <typename Key, typename T>
map<Key, T>::map(const map& m) : object(m.object) {}

template <typename Key, typename T>
map<Key, T>::map(map&& m) : object(std::move(m.object)) {}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) {
  clear();
  object.root = m.object.root;
  m.object.root = nullptr;
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map& m) {
  clear();
  merge(m);
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& k) {
  NodeTree::Node<Key, T>* tmp = object.searchTree(k);
  try {
    if (!tmp) throw std::invalid_argument("Invalid argument");
  } catch (const std::invalid_argument& e) {
    throw;
  }
  return tmp->value.second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  std::pair<Key, T> value;
  value.first = key;
  value.second = 0;
  NodeTree::Node<Key, T>* result = object.searchTree(key);
  if (!result) {
    object.insertTree(value, object.root);
    result = object.searchTree(key);
  }
  return result->value.second;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  iterator tmp(object.min(object.root));
  return tmp;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  iterator tmp(nullptr);
  return tmp;
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  bool result = object.root ? 0 : 1;
  return result;
};

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return empty() ? 0 : object.sizeTree(0, object.root);
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return (std::numeric_limits<size_type>::max() * sizeof(size_type)) /
         (sizeof(NodeTree::Node<Key, T>));
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  if (!empty()) {
    object.clearTree(object.root);
    object.root = nullptr;
  }
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  std::pair<iterator, bool> result;
  result.second = contains(value.first) ? 0 : 1;
  object.root = object.insertTree(value, object.root);
  result.first = object.searchTree(value.first);
  object.balancing(object.searchTree(value.first));
  return result;
};

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<Key, T> value;
  value.first = key;
  value.second = obj;
  return insert(value);
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  NodeTree::Node<Key, T>* tmp = nullptr;
  std::pair<iterator, bool> result;
  if (contains(key)) {
    tmp = object.searchTree(key);
    tmp->value.second = obj;
    result.first = tmp;
    result.second = false;
  } else
    result = insert(key, obj);
  return result;
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (contains(pos.ptr->value.first)) object.deleteKnot(pos.ptr);
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  std::swap(object.root, other.object.root);
};

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  map<Key, T>::MapIterator it = other.begin();
  while (it != other.end()) {
    insert(*it);
    ++it;
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return object.searchTree(key) ? 1 : 0;
};

template <typename Key, typename T>
typename map<Key, T>::MapIterator& map<Key, T>::MapIterator::operator++() {
  tree<Key, T> tmp;
  ptr = tmp.next(ptr);
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::MapIterator& map<Key, T>::MapIterator::operator--() {
  tree<Key, T> tmp;
  ptr = tmp.prev(ptr);
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator&
map<Key, T>::MapConstIterator::operator++() {
  tree<Key, T> tmp;
  ptr = tmp.next(ptr);
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator&
map<Key, T>::MapConstIterator::operator--() {
  tree<Key, T> tmp;
  ptr = tmp.prev(ptr);
  return *this;
}
#endif