#ifndef S21_VECTOR_CPP
#define S21_VECTOR_CPP

#include "../include/s21_vector.hpp"
using namespace s21;

template <typename T>
vector<T>::vector() : capacity_(0), size_(0), pointer(nullptr) {}

template <typename T>
vector<T>::vector(size_type n) {
  size_ = n;
  capacity_ = n;
  pointer = new T[capacity_];
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size()) {
  int i = 0;
  for (auto const item : items) {
    pointer[i] = item;
    i++;
  }
}

template <typename T>
vector<T>::vector(const vector& v) : vector(v.size_) {
  if (v.pointer)
    for (size_type i = 0; i < size_; i++) pointer[i] = v.pointer[i];
}

template <typename T>
vector<T>::vector(vector&& v) {
  pointer = v.pointer;
  size_ = v.size_;
  capacity_ = v.capacity_;
  v.pointer = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  clear();
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) {
  clear();
  size_ = v.size_;
  capacity_ = v.capacity_;
  pointer = new T[capacity_];
  if (v.pointer)
    for (size_type i = 0; i < size_; i++) pointer[i] = v.pointer[i];
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  try {
    if (pos > size_ - 1) throw std::invalid_argument("Invalid argument");
  } catch (const std::invalid_argument& e) {
    throw;
  }
  return *(pointer + pos);
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(pointer + pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return *pointer;
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return *(pointer + size_ - 1);
}

template <typename T>
T* vector<T>::data() {
  return pointer;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return pointer;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return pointer + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() {
  return pointer;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() {
  return pointer + size_;
}

template <typename T>
bool vector<T>::empty() {
  return pointer ? 0 : 1;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  T* result = nullptr;
  if (size > size_) {
    capacity_ = size;
    result = new T[capacity_];
    std::copy(pointer, pointer + size_, result);
    delete[] pointer;
    pointer = result;
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  T* result = nullptr;
  if (capacity_ > size_) {
    result = new T[size_];
    std::copy(pointer, pointer + size_ - 1, result);
    delete[] pointer;
    pointer = result;
    capacity_ = size_;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::clear() {
  if (pointer) delete[] pointer;
  size_ = capacity_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type delt = pos - begin();
  iterator newPos = nullptr;
  if ((pos - begin()) >= 0 && (pos - end()) <= 0) {
    if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
    newPos = begin() + delt;
    for (iterator it = end(); it != newPos; it--) *it = *(it - 1);
    *newPos = value;
    ++size_;
  } else {
    throw std::out_of_range(
        "InsertError: The insertion position is out of range of the vector "
        "memory");
  }
  return newPos;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  vector<value_type> tmp{args...};
  iterator cur_pos = begin() + (pos - cbegin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    cur_pos = insert(cur_pos, tmp[i]);
    ++cur_pos;
  }

  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  for (iterator cur = pos; cur != end(); ++cur) *cur = *(cur + 1);
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
  *(pointer + size_) = value;
  size_++;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_) --size_;
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(pointer, other.pointer);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

#endif