#ifndef BP_TREE_CPP
#define BP_TREE_CPP
#include "../include/BP_tree.hpp"

template <typename Key, typename T>
tree<Key, T>::tree() {
  root = nullptr;
}

template <typename Key, typename T>
tree<Key, T>::tree(const tree& other) : tree() {
  treeCopy(other.root);
}

template <typename Key, typename T>
tree<Key, T>::tree(tree&& other) : tree() {
  if (other.root) {
    root = other.root;
    other.root = nullptr;
  }
}

template <typename Key, typename T>
tree<Key, T>::~tree() {
  if (root) {
    clearTree(root);
    root = nullptr;
  }
}

template <typename Key, typename T>
void tree<Key, T>::treeCopy(NodeTree::Node<Key, T>* other) {
  if (other->left) treeCopy(other->left);
  if (other->right) treeCopy(other->right);
  root = insertTree(other->value, root);
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::searchRoot(NodeTree::Node<Key, T>* src) {
  if (src)
    while (src->p) src = src->p;
  return src;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::min(NodeTree::Node<Key, T>* src) const {
  if (src)
    while (src->left) src = src->left;
  return src;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::max(NodeTree::Node<Key, T>* src) const {
  if (src)
    while (src->right) src = src->right;
  return src;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::next(NodeTree::Node<Key, T>* src) {
  NodeTree::Node<Key, T>* res = nullptr;
  if (src) {
    if (src->right)
      res = min(src->right);
    else {
      res = src->p;
      while (res && src == res->right) {
        src = res;
        res = res->p;
      }
    }
  }
  return res;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::prev(NodeTree::Node<Key, T>* src) {
  NodeTree::Node<Key, T>* res = nullptr;
  if (src) {
    if (src->left)
      res = max(src->left);
    else {
      res = src->p;
      while (res && src == res->left) {
        src = res;
        res = res->p;
      }
    }
  }
  return res;
}

template <typename Key, typename T>
void tree<Key, T>::leftRotate(NodeTree::Node<Key, T>* src) {
  NodeTree::Node<Key, T>* knot = src->right;
  NodeTree::Node<Key, T>* G = src->p;
  if (knot) {     // если правый лист существует
    knot->p = G;  // меняем родителя для правого узла
    if (G) {
      if (src == G->left)
        G->left = knot;  //меняем наследнека у дедушки
      else
        G->right = knot;
    }
    src->p = knot;
    src->right = knot->left;
    knot->left = src;
    if (src == root) root = knot;
  }
}

template <typename Key, typename T>
void tree<Key, T>::rightRotate(NodeTree::Node<Key, T>* src) {
  NodeTree::Node<Key, T>* knot = src->left;
  NodeTree::Node<Key, T>* G = src->p;
  if (knot) {          // если левый лист существует
    knot->p = src->p;  // меняем родителя для левого узла
    if (G) {
      if (src == G->left)
        G->left = knot;  //меняем наследнека у дедушки
      else
        G->right = knot;
    }
    src->p = knot;
    src->left = knot->right;
    knot->right = src;
    if (src == root) root = knot;
  }
}

template <typename Key, typename T>
void tree<Key, T>::balancing(NodeTree::Node<Key, T>* src) {
  NodeTree::Node<Key, T>* P = src ? src->p : nullptr;  // отец
  NodeTree::Node<Key, T>* G = P ? P->p : nullptr;      // дедушка
  NodeTree::Node<Key, T>* U =
      G ? (G->right == P ? G->left : G->right) : nullptr;  // дядя
  if (src == root)
    src->color = BLACK;
  else {
    if (P->color == READ &&
        src->color == READ) {  // иначе балансировки не будет
      if (U && U->color == READ) {  // дядя красный
        P->color = U->color = BLACK;
        G->color = READ;  // дед в любом случае красный
        balancing(G);  // балансировка деда он стал крассным
      } else if (!U || U->color == BLACK) {  // дядя черный
        if ((G->left == P && P->right == src) ||
            (G->right == P && P->left == src)) {  // P G X не на одной линии
          if (P->right == src)
            leftRotate(P);
          else
            rightRotate(P);
          src->color = BLACK;
        } else
          P->color = BLACK;
        if (G->right == U)
          rightRotate(G);
        else
          leftRotate(G);
        G->color = READ;  // дед в любом случае красный
      }
    }
  }
}

template <typename Key, typename T>
void tree<Key, T>::delBalancing(NodeTree::Node<Key, T>* src) {
  // у отца всегда хотя бы один предок лист
  Node<Key, T>* B = src->left ? src->left : src->right;  // брат
  Node<Key, T>* GS1 = B->right;  // внук правый
  Node<Key, T>* GS2 = B->left;   // внук левый
  if (src) {  // балансируе не пустое дерево
    if (B->color == BLACK) {  // черный брат
      if (!GS1 && !GS2) {
        B->color = READ;  // внуки черные
        src->color = BLACK;
      } else if (!GS1 || GS1->color == BLACK) {
        if (src->right == B)
          leftRotate(src);
        else
          rightRotate(src);
        src->color = BLACK;
      } else {  // красный брат
        if (src->right == B)
          leftRotate(src);
        else
          rightRotate(src);
        src->color = READ;
      }
    } else {
      if (src->right == B)
        leftRotate(src);
      else
        rightRotate(src);
      src->color = READ;
      B->color = BLACK;
      delBalancing(src);
    }
  }
}
template <typename Key, typename T>
void tree<Key, T>::clearTree(NodeTree::Node<Key, T>* src) {
  if (src->left) clearTree(src->left);
  if (src->right) clearTree(src->right);
  delete src;
}

template <typename Key, typename T>
typename tree<Key, T>::size_type tree<Key, T>::sizeTree(
    size_type res, NodeTree::Node<Key, T>* src) {
  if (src) {
    res++;
    if (src->left) res = sizeTree(res, src->left);
    if (src->right) res = sizeTree(res, src->right);
  }
  return res;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::insertTree(const value_type& value,
                                                 NodeTree::Node<Key, T>* src) {
  if (!src)
    src = new Node<Key, T>(value);
  else {
    if (src->value.first > value.first) {
      src->left = insertTree(value, src->left);
      src->left->p = src;
    } else if (src->value.first < value.first) {
      src->right = insertTree(value, src->right);
      src->right->p = src;
    }
  }
  return src;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::insertTree_dup(
    const value_type& value, NodeTree::Node<Key, T>* src) {
  if (!src)
    src = new Node<Key, T>(value);
  else {
    if (src->value.first > value.first) {
      src->left = insertTree_dup(value, src->left);
      src->left->p = src;
    } else {
      src->right = insertTree_dup(value, src->right);
      src->right->p = src;
    }
  }
  return src;
}

template <typename Key, typename T>
void tree<Key, T>::deleteKnot(NodeTree::Node<Key, T>* src) {
  Node<Key, T>* P = src->p;  // отец
  Node<Key, T>* tmp = nullptr;
  if (src->left && src->right) {  // 2 бейбика КЧ
    tmp = min(src->right);
    src->value = tmp->value;
    deleteKnot(tmp);
  } else if (src->color == READ) {  // красный узел
    if (P->left == src)
      P->left = nullptr;
    else
      P->right = nullptr;
    delete src;
  } else {                            // черный узел
    if (!src->left && !src->right) {  // нет детей
      if (src == root) {
        delete src;
        root = nullptr;
      } else {
        if (P->left == src)
          P->left = nullptr;
        else
          P->right = nullptr;
        delete src;
        delBalancing(P);
      }
    } else {  // есть один красный
      if (src->left) {
        src->value = src->left->value;
        delete src->left;
        src->left = nullptr;
      } else {
        src->value = src->right->value;
        delete src->right;
        src->right = nullptr;
      }
    }
  }
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::searchTree(const Key& key) {
  Node<Key, T>* tmp = root;
  while (tmp) {
    if (tmp->value.first == key)
      break;
    else if (tmp->value.first > key)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }
  return tmp;
}

template <typename Key, typename T>
NodeTree::Node<Key, T>* tree<Key, T>::searchTree_dup(const Key& key) {
  Node<Key, T>* tmp = root;
  while (tmp) {
    if (tmp->value.first == key) {
      if (tmp->right && tmp->right->value.first == key) tmp = tmp->right;
      break;
    } else if (tmp->value.first > key)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }
  return tmp;
}
#endif