#ifndef S21_ARRAY_CPP
#define S21_ARRAY_CPP

#include "../include/s21_array.hpp"

using namespace s21;

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) : array() {
  std::copy(items.begin(), items.end(), arr);
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N>& a) {
  std::copy(a.arr, a.arr + amount, arr);
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N>&& a) : array() {
  std::move(a.arr, a.arr + amount, arr);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  try {
    if (pos > amount - 1) throw std::out_of_range("out_of_range");
  } catch (const std::out_of_range& e) {
    throw;
  }
  return *(arr + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  try {
    if (pos > amount - 1) throw std::out_of_range("out_of_range");
  } catch (const std::out_of_range& e) {
    throw;
  }
  return *(arr + pos);
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& a) {
  for (size_type i = 0; i < amount; i++) arr[i] = std::move(a.arr[i]);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return *(arr + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *arr;
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(arr + amount - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return arr + amount;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return arr + amount;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return amount ? 0 : 1;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return amount;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) {
  T tmp = 0;
  if (amount == other.amount) {
    for (size_type i = 0; i < amount; i++) {
      tmp = other.arr[i];
      other.arr[i] = arr[i];
      arr[i] = tmp;
    }
    std::swap(amount, other.amount);
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < amount; i++) arr[i] = value;
}

#endif