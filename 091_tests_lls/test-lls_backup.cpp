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
  void testAddFront_empty() {
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

  void testAddBack_empty() {
    IntList il;
    initList(il);
    il.addBack(3);
    assert(il.head->data == 3);
    assert(il.tail->data == 3);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }

  void initList(IntList il) {
    il.head = NULL;
    il.tail = NULL;
  }

  void testLinkedList(void) {
    IntList test;
    // many more tester methods

    test.addFront(4);  // 4
    assert(test.head->data == 4);
    assert(test.tail->data == 4);
    assert(test[0] == 4);
    assert(test.getSize() == 1);
    assert(test.head->next == NULL);
    assert(test.head->prev == NULL);
    assert(test.tail->next == NULL);
    assert(test.tail->prev == NULL);
    assert(test.tail == test.head);

    test.addFront(5);  // 5 4
    assert(test.head->next->data == 4);
    assert(test.head->data == 5);
    assert(test.head->prev == NULL);
    assert(test[0] == 5);
    assert(test[1] == 4);

    assert(test.tail->data == 4);
    assert(test.tail->next == NULL);
    assert(test.tail->prev->data == 5);
    assert(test.tail->prev == test.head);
    assert(test.getSize() == 2);

    test.addFront(7);  // 7 5 4
    assert(test.head->data == 7);
    assert(test.head->next->data == 5);
    assert(test.head->next->next == test.tail);
    assert(test.head->prev == NULL);

    assert(test.getSize() == 3);
    assert(test.tail->data == 4);
    assert(test.tail->next == NULL);
    assert(test.tail->prev == test.head->next);

    test.addBack(3);  // 7 5 4 3
    assert(test.getSize() == 4);
    assert(test.tail->data == 3);
    assert(test.tail->next == NULL);
    assert(test.tail->prev->data == 4);
    assert(test.tail->prev == test.head->next->next);

    assert(test.head->data == 7);
    assert(test.head->next->next->next == test.tail);
    assert(test.head->next->next->next->data == 3);

    test.addBack(2);  // 7 5 4 3 2

    test.remove(5);  // 7 4 3 2
    assert(test.getSize() == 4);
    assert(test.head->data == 7);
    assert(test.head->next->data == 4);
    assert(test.head->next->next->data == 3);
    assert(test.head->next->next->next->data == 2);
    assert(test.head->next->next->next->next == NULL);
    assert(test.head->next->prev = test.head);
    assert(test.head->prev == NULL);

    assert(test.tail->data == 2);
    assert(test.tail->prev->data == 3);
    assert(test.tail->prev->prev->data == 4);
    assert(test.tail->prev->prev->prev->data == 7);
    assert(test.tail->prev->prev->prev->prev == NULL);
    assert(test.tail->next == NULL);
    assert(test.tail->prev->prev->prev == test.head);

    // 7 4 3 2
    int node3index = test.find(3);
    assert(node3index == 2);
    assert(test.find(7) == 0);
    assert(test.find(4) == 1);
    assert(test.find(2) == 3);
    assert(test[0] == 7);
    assert(test[1] == 4);
    assert(test[2] == 3);
    assert(test[3] == 2);

    test.remove(3);  // 7 4 2
    assert(test.head->next->data == 4);
    assert(test.tail->prev->data == 4);
    assert(test.getSize() == 3);
    assert(test[0] == 7);
    assert(test[1] == 4);
    assert(test[2] == 2);
    assert(test.find(7) == 0);
    assert(test.find(4) == 1);
    assert(test.find(2) == 2);

    // assign
    IntList mylist1;
    mylist1 = test;
    assert(mylist1[0] == 7);
    assert(mylist1[1] == 4);
    assert(mylist1[2] == 2);
    assert(mylist1.getSize() == 3);
    assert(mylist1.head->prev == NULL);
    assert(mylist1.head->data == 7);
    assert(mylist1.head->next->data == 4);
    assert(mylist1.head->next->next->data == 2);

    assert(mylist1.tail->next == NULL);
    assert(mylist1.tail->data == 2);
    assert(mylist1.tail->prev->data == 4);
    assert(mylist1.tail->prev->prev->data == 7);
    assert(mylist1.tail->prev->prev->prev == NULL);
    assert(mylist1.head->next->next == mylist1.tail);
    assert(mylist1.head->next->next->next == NULL);
    assert(mylist1.tail->prev->prev == mylist1.head);
    assert(mylist1.head->next->prev == mylist1.head);
    assert(mylist1.head->next->next == mylist1.tail &&
           mylist1.head->next->next->next == NULL);

    mylist1.remove(4);
    assert(test.getSize() == 3);
    assert(mylist1.getSize() == 2);
    assert(mylist1.remove(4) == false);

    mylist1 = test;
    assert(mylist1[0] == 7);
    assert(mylist1[1] == 4);
    assert(mylist1[2] == 2);
    assert(mylist1.getSize() == 3);
    assert(mylist1.head->prev == NULL);
    assert(mylist1.head->data == 7);
    assert(mylist1.head->next->data == 4);
    assert(mylist1.head->next->next->data == 2);

    assert(mylist1.tail->next == NULL);
    assert(mylist1.tail->data == 2);
    assert(mylist1.tail->prev->data == 4);
    assert(mylist1.tail->prev->prev->data == 7);
    assert(mylist1.tail->prev->prev->prev == NULL);
    assert(mylist1.head->next->next == mylist1.tail);
    assert(mylist1.head->next->next->next == NULL);
    assert(mylist1.tail->prev->prev == mylist1.head);
    assert(mylist1.head->next->prev == mylist1.head);
    assert(mylist1.head->next->next == mylist1.tail &&
           mylist1.head->next->next->next == NULL);

    mylist1.remove(7);
    assert(test.getSize() == 3);
    assert(mylist1.getSize() == 2);
    assert(mylist1.remove(7) == false);

    // copy
    IntList mylist2(test);
    assert(mylist2[0] == 7);
    assert(mylist2[1] == 4);
    assert(mylist2[2] == 2);
    assert(mylist2.getSize() == 3);
    assert(mylist2.head->prev == NULL);
    assert(mylist2.head->data == 7);
    assert(mylist2.head->next->data == 4);
    assert(mylist2.head->next->next->data == 2);

    assert(mylist2.tail->next == NULL);
    assert(mylist2.tail->data == 2);
    assert(mylist2.tail->prev->data == 4);
    assert(mylist2.tail->prev->prev->data == 7);
    assert(mylist2.tail->prev->prev->prev == NULL);
    assert(mylist2.head->next->next == mylist2.tail);
    assert(mylist2.head->next->next->next == NULL);
    assert(mylist2.tail->prev->prev == mylist2.head);
    assert(mylist2.head->next->prev == mylist2.head);
    assert(mylist2.head->next->next == mylist2.tail &&
           mylist2.head->next->next->next == NULL);

    mylist2.remove(4);
    assert(test.getSize() == 3);
    assert(mylist2.getSize() == 2);
    assert(mylist2.remove(4) == false);
    assert(mylist2.head->next == mylist2.tail);
    assert(mylist2.tail->prev == mylist2.head);
    assert(mylist2.tail->prev->next == mylist2.tail);

    test.addBack(1);   //7 4 2 1
    test.addFront(9);  // 9 7 4 2 1

    test.remove(9);  // 7 4 2 1
    assert(test.getSize() == 4);
    assert(test[0] == 7);
    assert(test[1] == 4);
    assert(test[2] == 2);
    assert(test[3] == 1);
    assert(test.head->data == 7);
    assert(test.head->prev == NULL);
    assert(test.head->next->data == 4);
    assert(test.head->next->next->data == 2);
    assert(test.head->next->next->next->data == 1);

    assert(test.tail->data == 1);
    assert(test.tail->prev->data == 2);
    assert(test.tail->prev->prev->data == 4);
    assert(test.tail->prev->prev->prev->data == 7);

    test.remove(1);  // 7 4 2
    assert(test.getSize() == 3);
    assert(test[0] == 7);
    assert(test[1] == 4);
    assert(test[2] == 2);
    assert(test.head->data == 7);
    assert(test.head->prev == NULL);
    assert(test.head->next->data == 4);
    assert(test.head->next->next->data == 2);

    assert(test.tail->data == 2);
    assert(test.tail->prev->data == 4);
    assert(test.tail->prev->prev->data == 7);
    assert(test.tail->next == NULL);
    assert(test.tail->prev == test.head->next);

    test.addBack(2);  //7 4 2 2
    test.remove(2);   // 7 4 2
    assert(test.getSize() == 3);
    assert(test.find(7) == 0);
    assert(test.find(4) == 1);
    assert(test.find(2) == 2);

    assert(test.tail->data == 2);

    test.remove(7);  // 4 2
    assert(test.getSize() == 2);
    //    assert(test.find(7) == false);
    assert(test.find(4) == 0);
    assert(test.find(2) == 1);
    assert(test[0] == 4);
    assert(test[1] == 2);
    //test.~IntList();
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddBack_empty();
  // t.testAddFront_empty();
  //  t.testAddFront_nonEmpty();
  t.testLinkedList();

  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
