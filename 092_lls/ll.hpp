#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
class err : public std::exception {
 public:
  virtual const char * what() const throw() { return "Error for the requested item\n"; }
};
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d) : data(d), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * t = rhs.head;
    while (t != NULL) {
      addBack(t->data);
      t = t->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList l(rhs);
      std::swap(l.head, head);
      std::swap(l.tail, tail);
      std::swap(l.size, size);
    }
    return *this;
  }
  ~LinkedList() {
    Node * traverse = head;
    Node * tmp = NULL;
    while (traverse != NULL) {
      tmp = traverse->next;
      delete traverse;
      traverse = tmp;
    }
  }
  void addFront(const T & item) {
    Node * n = new Node(item);
    n->next = head;
    if (head != NULL) {
      head->prev = n;
    }
    else {
      tail = n;
    }
    head = n;
    size += 1;
  }
  void addBack(const T & item) {
    Node * n = new Node(item);
    n->prev = tail;
    if (tail != NULL) {
      tail->next = n;
    }
    else {
      head = n;
    }
    tail = n;
    size += 1;
  }
  bool remove(const T & item) {
    Node * t = head;
    while ((t != NULL) && (t->data != item)) {
      t = t->next;
    }
    if (t == NULL) {
      return false;
    }
    Node * nn = t->next;
    Node * pn = t->prev;
    if (nn != NULL) {
      nn->prev = pn;
    }
    else {
      tail = pn;
    }
    if (pn != NULL) {
      pn->next = nn;
    }
    else {
      head = nn;
    }
    size--;
    delete t;
    return true;
  }
  T & operator[](int index) {
    try {
      if (index < 0 || index > size - 1) {
        throw err();
      }
    }
    catch (err & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * t = head;
    for (int i = 0; i < index; i++) {
      t = t->next;
    }
    return t->data;
  }
  const T & operator[](int index) const {
    try {
      if (index < 0 || index > size - 1) {
        throw err();
      }
    }
    catch (err & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * t = head;
    for (int i = 0; i < index; i++) {
      t = t->next;
    }
    return t->data;
  }
  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  int getSize() const { return size; }
  friend void testList(void);
};

#endif
