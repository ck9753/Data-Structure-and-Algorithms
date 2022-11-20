#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * l;
    Node * r;
    Node() : key(0), l(NULL), r(NULL) {}
    Node(const K k) : key(k), l(NULL), r(NULL) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs);
  BstSet & operator=(const BstSet & rhs);
  virtual ~BstSet();
  virtual void add(const K & key);
  virtual bool contains(const K & key) const;
  virtual void remove(const K & key);
  Node * copyHelper(Node * current);
  Node * addnode(Node * current, const K & key);
  void destroy(Node * current);
  void inOrder(Node * current);
  void inOrderPrint();
};

// copy constructor
template<typename K>
BstSet<K>::BstSet(const BstSet & rhs) {
  root = copyHelper(rhs.root);
}

// copy helper function
template<typename K>
typename BstSet<K>::Node * BstSet<K>::copyHelper(Node * current) {
  if (current == NULL) {
    return NULL;
  }

  Node * cpNode = new Node(current->key);
  cpNode->l = copyHelper(current->l);
  cpNode->r = copyHelper(current->r);
  return cpNode;
}

// assignment operator
template<typename K>
BstSet<K> & BstSet<K>::operator=(const BstSet & rhs) {
  if (this != &rhs) {
    destroy(root);
    root = copyHelper(rhs.root);
  }
  return *this;
}

// destructor
template<typename K>
BstSet<K>::~BstSet() {
  destroy(root);
}

// destroy
template<typename K>
void BstSet<K>::destroy(Node * current) {
  if (current == NULL) {
    return;
  }

  destroy(current->l);
  destroy(current->r);
  delete current;
}

// add
template<typename K>
void BstSet<K>::add(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key == (*current)->key) {
      return;
    }
    if (key < (*current)->key) {
      current = &(*current)->l;
    }
    else {
      current = &(*current)->r;
    }
  }
  *current = new Node(key);
}

// contains
template<typename K>
bool BstSet<K>::contains(const K & key) const {
  Node * current = root;
  if (current == NULL) {
    return false;
  }
  while (current != NULL) {
    if (key == current->key) {
      return true;
    }
    else if (key < current->key) {
      current = current->l;
    }
    else {
      current = current->r;
    }
  }
  return false;
}

// remove
template<typename K>
void BstSet<K>::remove(const K & key) {
  Node ** current = &root;
  Node * tmp = NULL;
  while (*current != NULL) {
    if (key == (*current)->key) {
      if ((*current)->l == NULL) {
        tmp = (*current)->r;
        delete *current;
        (*current) = tmp;
      }

      else if ((*current)->r == NULL) {
        tmp = (*current)->l;
        delete *current;
        (*current) = tmp;
      }

      else {
        Node ** r_Node = current;
        current = &(*current)->l;

        while ((*current)->r != NULL) {
          current = &(*current)->r;
        }
        (*r_Node)->key = (*current)->key;
        tmp = (*current)->l;
        delete (*current);
        *current = tmp;
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

template<typename K>
void BstSet<K>::inOrder(Node * current) {
  if (current != NULL) {
    inOder(current->l);
    std::cout << current->key << " ";
    inOder(current->r);
  }
}

template<typename K>
void BstSet<K>::inOrderPrint() {
  inOrder(root);
  std::cout << std::endl;
}
