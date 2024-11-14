#ifndef BP_TREE_HPP
#define BP_TREE_HPP
#include <utility>

namespace s21{
template <typename Key,typename T> class map;
template <typename Key> class set;
template <typename Key> class multiset;}


enum tree_color{BLACK,READ};

namespace NodeTree{
template <typename Key,typename T>
struct Node{
    std::pair<Key,T> value;
    tree_color color;
    Node<Key,T>* p;
    Node<Key,T>* left;
    Node<Key,T>* right;
    Node(std::pair<Key,T> V):value(V),color(READ),p(nullptr),left(nullptr),right(nullptr){};
    Node(Node<Key,T>& src):value(src.value),color(src.color),p(src.p),left(src.left),right(src.right){};
};
};
using namespace NodeTree;
template <typename Key,typename T >
class tree{
    friend  class s21::map<Key,T>;
    friend  class s21::set<Key>;
    friend  class s21::multiset<Key>;
    
    private:
    using key_type=Key;
    using mapped_type=T;
    using value_type=std::pair<const key_type,mapped_type>;
    using reference =value_type &;
    using const_reference=const value_type &;
    using size_type=std::size_t;

    tree();
    tree(Node<Key,T>* src){root=src;}
    tree(const tree & other);
    tree(tree&& other);
    ~tree();
    
    Node<Key,T>* root;

    Node<Key,T>* searchRoot(Node<Key,T>* src);// поиск корня 

    void treeCopy(Node<Key,T>* other);// копирования дерева

    Node<Key,T>* min(Node<Key,T>* src)const;// мин элемент в поддереве
    Node<Key,T>* max(Node<Key,T>* src)const;// макс элемент в поддереве

    Node<Key,T>* next(Node<Key,T>* src);// след 
    Node<Key,T>* prev(Node<Key,T>* src);// пред

    void leftRotate(Node<Key,T>* src);
    void rightRotate(Node<Key,T>* src);
    
    void balancing(Node<Key,T>* src);
    void delBalancing(Node<Key,T>* src);

    void clearTree(Node<Key,T>* src);
    size_type sizeTree(size_type res,Node<Key,T>* src);
    Node<Key,T>* insertTree(const value_type& value,Node<Key,T>* src);

    Node<Key,T>* insertTree_dup(const value_type& value,Node<Key,T>* src);// вставка дубликатов
    Node<Key,T>* searchTree_dup(const Key& key);// поиск последнего дубликата

    void deleteKnot(Node<Key,T>* src);
    Node<Key,T>* searchTree(const Key& key);
};

#include "../template/BP_tree.cpp"

#endif
