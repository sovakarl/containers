#ifndef S21LIST_CPP
#define S21LIST_CPP
#include "../include/s21_list.hpp"

using namespace s21;
using namespace NodeList;

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) push_back(0);
};

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) push_back(item);
}

template <typename T>
list<T>::list(const list& l) : list() {
  Node<T>* tmp = l.head;
  while (tmp != nullptr) {
    push_back(tmp->Value);
    tmp = tmp->Next;
  }
};

template <typename T>
list<T>::list(list&& l) {
  head = l.head;
  tail = l.tail;
  l.head = l.tail = nullptr;
}

template <typename T>
list<T>::~list() {
  if (size()) {
    Node<T>* tmp = nullptr;
    while (tail->Previous) {
      tmp = tail->Previous;
      delete tail;
      tail = tmp;
    }
    delete head;
    head = tail = nullptr;
  }
}

template <typename T>
list<T>& list<T>::operator=(const list&& l) {
  Node<T> tmp(l);
  clear();
  *this = tmp;
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(const list& l) {
  if (&l != this) {
    Node<T>* tmp = l.head;
    clear();
    while (tmp) {
      push_back(tmp->Value);
      tmp = tmp->Next;
    }
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  return head->Value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return tail->Value;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {  // итератор в начало
  iterator ptr(head);
  return ptr;
}

template <typename T>
typename list<T>::iterator list<T>::end() {  // итератор в конец
  iterator ptr(nullptr);
  return ptr;
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() {  // итератор в начало
  const_iterator ptr(head);
  return ptr;
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() {  // итератор в конец
  const_iterator ptr(nullptr);
  return ptr;
}

template <typename T>
bool list<T>::empty() {
  return (head == tail && head == nullptr) ? 1 : 0;
};

template <typename T>
typename list<T>::size_type list<T>::size() {
  size_type count = 0;
  Node<T>* tmp = head;
  while (tmp) {
    count++;
    tmp = tmp->Next;
  }
  return count;
};

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return (std::numeric_limits<size_type>::max() * sizeof(size_type)) /
         (sizeof(Node<T>) * 2);
}

template <typename T>
void list<T>::clear() {
  if (size()) {
    Node<T>* tmp;
    while (tail != head) {
      tmp = tail;
      tail = tail->Previous;
      delete tmp;
    }
    delete tail;
    tail = head = nullptr;
  }
};

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  iterator it;
  if (pos.get_p() == head) {
    push_front(value);
    it.set_p(head);
  } else {
    if (pos.get_p() != nullptr) {
      Node<T>* record = new Node<T>(value);
      Node<T>* current = pos.get_p();
      record->Next = current;
      record->Previous = current->Previous;
      current->Previous->Next = record;
      current->Previous = record;
      it.set_p(record);
    } else
      push_back(value);
  }
  return it;
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  for (const auto& arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node<T>* tmp = pos.get_p();
  if (tmp == head)
    pop_front();
  else if (tmp == tail)
    pop_back();
  else if (tmp) {
    tmp->Previous->Next = tmp->Next;
    tmp->Next->Previous = tmp->Previous;
    delete tmp;
    pos.set_p(nullptr);
  }
};

template <typename T>
void list<T>::push_back(const_reference value) {
  Node<T>* tmp = new Node<T>(value);
  if (!tail)
    head = tail = tmp;
  else {
    tail->Next = tmp;
    tmp->Previous = tail;
    tail = tmp;
  }
};

template <typename T>
void list<T>::pop_back() {
  if (size() > 1) {
    Node<T>* tmp = tail;
    tail = tail->Previous;
    tail->Next = nullptr;
    delete tmp;
  } else
    clear();
};

template <typename T>
void list<T>::push_front(const_reference value) {
  Node<T>* tmp = new Node<T>(value);
  if (!head)
    head = tail = tmp;
  else {
    head->Previous = tmp;
    tmp->Next = head;
    head = tmp;
  }
};

template <typename T>
void list<T>::pop_front() {
  if (size() > 1) {
    Node<T>* tmp = head;
    head = head->Next;
    head->Previous = nullptr;
    delete tmp;
  } else
    clear();
};

template <typename T>
void list<T>::swap(list& other) {
  list<T> tmp(other);
  other = *this;
  *this = tmp;
}

template <typename T>
void list<T>::merge(list& other) {
  if (&other != this) {
    auto it = begin();
    Node<T>* tmp = other.head;
    while (it != end() && tmp) {
      if (*it >= tmp->Value) {
        insert(it, tmp->Value);
        tmp = tmp->Next;
      } else
        ++it;
    }
    while (tmp) {
      push_back(tmp->Value);
      tmp = tmp->Next;
    }
    other.clear();
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    iterator it(pos.get_p());
    Node<T>* tmp = other.head;
    while (tmp) {
      if (pos != cend())
        insert(it, tmp->Value);
      else
        (push_back(tmp->Value));
      tmp = tmp->Next;
    }
  }
}

template <typename T>
void list<T>::reverse() {
  Node<T>* tmp = tail;
  while (tmp) {
    std::swap(tmp->Next, tmp->Previous);
    tmp = tmp->Next;
  }
  std::swap(head, tail);
}

template <typename T>
void list<T>::unique() {
  Node<T>* tmp = head;
  iterator it;
  while (tmp->Next) {
    it.set_p(tmp->Next);
    if (tmp->Value == tmp->Next->Value)
      erase(it);
    else
      tmp = tmp->Next;
  }
}

template <typename T>
void list<T>::sort() {
  size_type L_len = size() / 2;
  size_type R_len = size() - L_len;
  list<T> left;
  list<T> right;
  Node<T>* tmp = head;
  for (size_type i = 0; i < L_len; i++, tmp = tmp->Next)
    left.push_back(tmp->Value);
  for (size_type i = 0; i < R_len; i++, tmp = tmp->Next)
    right.push_back(tmp->Value);
  if (L_len > 1) left.sort();
  if (R_len > 1) right.sort();
  left.merge(right);
  swap(left);
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++() {
  pointer = pointer->Next;
  return *this;
};

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator--() {
  pointer = pointer->Previous;
  return *this;
};

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
  iterator result = *this;
  ++*this;
  return result;
};

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--(int) {
  iterator result = *this;
  --*this;
  return result;
};

#endif