#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap<K, V>() : root(NULL) {}

  // copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copyHelper(rhs.root); }
  Node * copyHelper(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * copyNode = new Node(current->key, current->value);
    copyNode->left = copyHelper(current->left);
    copyNode->right = copyHelper(current->right);
    return copyNode;
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copyHelper(rhs.root);
    }
    return *this;
  }

  // destructor
  ~BstMap<K, V>() { destroy(root); }

  // destroy
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  // add new pair of key-value
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key == (*current)->key) {
        (*current)->value = value;
        return;
      }
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("the key does not exist!\n");
  }

  virtual void remove(const K & key) {
    Node ** current = &root;
    Node * temp = NULL;
    while (*current != NULL) {
      if ((*current)->key == key) {
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          (*current) = temp;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          (*current) = temp;
        }
        else {
          Node ** replaceNode = current;

          current = &(*current)->left;

          while ((*current)->right != NULL) {
            current = &(*current)->right;
          }
          (*replaceNode)->key = (*current)->key;
          (*replaceNode)->value = (*current)->value;
          temp = (*current)->left;
          delete (*current);
          *current = temp;
        }
      }
      else if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
  }

  void inOrder(Node * current) {
    if (current != NULL) {
      inOrder(current->left);
      std::cout << "(" << current->key << ", " << current->value << ") ";
      inOrder(current->right);
    }
  }

  void inOrderPrint() {
    inOrder(root);
    std::cout << std::endl;
  }
};
