#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

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
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & d, Node * p1, Node * p2) : data(d), next(p1), prev(p2){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();

  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
};

// addFront
template<typename T>
void LinkedList<T>::addFront(const T & item) {
  head = new Node(item, head, NULL);
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
  size++;
}

// addBack
template<typename T>
void LinkedList<T>::addBack(const T & item) {
  head = new Node(item, NULL, tail);
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
  size++;
}

// remove
template<typename T>
bool LinkedList<T>::remove(const T & item) {
  if (head == NULL) {
    return false;
  }
  else {
    Node * p = head;
    while (p != NULL) {
      if (p->data != item) {
        p = p->next;
      }
      else {
        if (head == tail && tail == p) {
          head = NULL;
          tail = NULL;
        }
        else if (tail == p) {
          tail = p->prev;
          tail->next = NULL;
        }
        else if (head == p) {
          head = p->next;
          head->prev = NULL;
        }

        else {
          p->prev->next = p->next;
          p->next->prev = p->prev;
        }
        delete p;
        size--;
        return true;
      }
    }
    return false;
  }
}

// index operator []
template<typename T>
T & LinkedList<T>::operator[](int index) {
  Node * p = head;
  int i = index;
  while ((p != NULL) && (i > 0)) {
    p = p->next;
    i--;
  }
  if (p == NULL) {
    throw err();
  }
  return p->data;
}

// const index operator []
template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  Node * p = head;
  int i = index;
  while ((p != NULL) && (i > 0)) {
    p = p->next;
    i--;
  }
  if (p == NULL) {
    throw err();
  }
  return p->data;
}

// find
template<typename T>
int LinkedList<T>::find(const T & item) {
  if (head == NULL) {
    return -1;
  }

  int i = 0;
  Node * p = head;
  while (p != NULL) {
    if (p->data == item) {
      return i;
    }
    p = p->next;
    i++;
  }
  return -1;
}

// copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  size = rhs.size;
  head = NULL;
  tail = NULL;

  Node * h = rhs.head;

  while (h != NULL) {
    addBack(h->data);
    h = h->next;
  }
}

// operator =
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  if (this != &rhs) {
    LinkedList<T> temp(rhs);

    Node * saved_head = head;
    head = temp.head;
    temp.head = saved_head;

    Node * saved_tail = tail;
    tail = temp.tail;
    temp.tail = saved_tail;
    size = temp.size;
  }

  return *this;
}

// destructor
template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * temp = head->next;

    delete head;
    head = temp;
  }

  head = NULL;
  tail = NULL;
  size = 0;
}

// getSize
template<typename T>
int LinkedList<T>::getSize() const {
  int s = 0;

  for (Node * p = head; p != NULL; p = p->next) {
    s++;
  }

  return s;
}

#endif
