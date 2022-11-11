#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(3);
    assert(il.head->data == 3);
    assert(il.tail->data == 3);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }

  void testLinkedList(void) {
    IntList test;
    // many more tester methods
    /*
    test.addFront(3);

    assert(test[0] == 3 && test.getSize() == 1 && test.head->next == NULL &&
           test.head->prev == NULL && test.tail != NULL && test.tail == test.head);

    test.addBack(5);
    assert(test.getSize() == 2 && test[1] == 5);
    assert(test.head->next->next == NULL && test.tail != NULL && test.tail == test.head);
    assert(test.tail == test.head->next);
    
    IntList il1;
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
    assert(il1.getSize() == 0);

    il1.addFront(4);
    assert(il1.getSize() == 1);
    assert(il1[0] == 4);
    assert(il1.head->data == 4);
    assert(il1.tail->data == 4);

    assert(il1.tail->next == NULL);
    assert(il1.tail->prev == NULL);
    assert(il1.head->prev == NULL);
    assert(il1.head->next == NULL);

    il1.addBack(3);
    assert(il1.getSize() == 2);
    assert(il1.head->data = 4);
    assert(il1.head->next->data == 3);
    assert(il1.head->next->next == NULL);
    assert(il1.tail->data == 3);
    assert(il1.tail->prev->data == 4);
    assert(il1.tail->prev->prev == NULL);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);
    assert(il1[1] == 3);
    */
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  //t.testLinkedList();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
