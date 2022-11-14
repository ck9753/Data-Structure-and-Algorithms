
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
    il.addFront(4);  //4
    assert(il.head->data == 4);
    assert(il.tail->data == 4);
    assert(il[0] == 4);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail == il.head);
  }

  void testAddFront_2ele() {
    IntList il;
    il.addFront(4);
    il.addFront(5);  // 5 4
    assert(il.head->data == 5);
    assert(il.head->next->data == 4);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);

    assert(il.tail->data == 4);
    assert(il.tail->prev->data == 5);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 5);
    assert(il[1] == 4);
  }

  void testAddFront_3ele() {
    IntList il;
    il.addFront(4);
    il.addFront(5);
    il.addFront(7);  // 7 5 4
    assert(il.head->data == 7);
    assert(il.head->next->data == 5);
    assert(il.head->next->next->data == 4);
    assert(il.head->next->next == il.tail);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 4);
    assert(il.tail->prev->data == 5);
    assert(il.tail->prev->prev->data == 7);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head->next);
  }
  void testAddBack_empty() {
    IntList il;
    // initList(il);
    il.addBack(3);
    assert(il.head->data == 3);
    assert(il.tail->data == 3);
    assert(il.getSize() == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }

  void testAddBack_2ele() {
    IntList il;
    il.addBack(5);
    il.addBack(4);  // 5 4
    assert(il.head->data == 5);
    assert(il.head->next->data == 4);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);

    assert(il.tail->data == 4);
    assert(il.tail->prev->data == 5);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 5);
    assert(il[1] == 4);
  }

  void testAddBack_3ele() {
    IntList il;
    il.addBack(7);
    il.addBack(5);
    il.addBack(4);  // 7 5 4
    assert(il.head->data == 7);
    assert(il.head->next->data == 5);
    assert(il.head->next->next->data == 4);
    assert(il.head->next->next == il.tail);
    assert(il.head->prev == NULL);

    assert(il.tail->data == 4);
    assert(il.tail->prev->data == 5);
    assert(il.tail->prev->prev->data == 7);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head->next);
  }

  void initList(IntList il) {
    il.head = NULL;
    il.tail = NULL;
  }

  void assign() {
    IntList il;
    IntList myil;

    il.addFront(7);
    il.addBack(4);
    il.addBack(2);  // 7 4 2

    myil = il;

    assert(myil[0] == 7);
    assert(myil[1] == 4);
    assert(myil[2] == 2);
    assert(myil.getSize() == 3);
    assert(myil.head->prev == NULL);
    assert(myil.head->data == 7);
    assert(myil.head->next->data == 4);
    assert(myil.head->next->next->data == 2);

    assert(myil.tail->next == NULL);
    assert(myil.tail->data == 2);
    assert(myil.tail->prev->data == 4);
    assert(myil.tail->prev->prev->data == 7);
    assert(myil.tail->prev->prev->prev == NULL);
    assert(myil.head->next->next == myil.tail);
    assert(myil.head->next->next->next == NULL);
    assert(myil.tail->prev->prev == myil.head);
    assert(myil.head->next->prev == myil.head);
    assert(myil.head->next->next == myil.tail && myil.head->next->next->next == NULL);

    myil = il;
    assert(myil[0] == 7);
    assert(myil[1] == 4);
    assert(myil[2] == 2);
    assert(myil.getSize() == 3);
    assert(myil.head->prev == NULL);
    assert(myil.head->data == 7);
    assert(myil.head->next->data == 4);
    assert(myil.head->next->next->data == 2);

    assert(myil.tail->next == NULL);
    assert(myil.tail->data == 2);
    assert(myil.tail->prev->data == 4);
    assert(myil.tail->prev->prev->data == 7);
    assert(myil.tail->prev->prev->prev == NULL);
    assert(myil.head->next->next == myil.tail);
    assert(myil.head->next->next->next == NULL);
    assert(myil.tail->prev->prev == myil.head);
    assert(myil.head->next->prev == myil.head);
    assert(myil.head->next->next == myil.tail && myil.head->next->next->next == NULL);
  }

  void copy() {
    IntList il;

    il.addFront(7);
    il.addBack(4);
    il.addBack(2);  // 7 4 2

    IntList mylist2(il);
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
    assert(il.getSize() == 3);
    assert(mylist2.head->next == mylist2.tail);
    assert(mylist2.tail->prev == mylist2.head);
    assert(mylist2.tail->prev->next == mylist2.tail);
  }

  void testRemove_itemNotinList() {
    IntList il;
    il.addFront(1);
    il.addBack(2);  //  1 2
    assert(il.getSize() == 2);

    il.remove(3);
    assert(il.getSize() == 2);
    assert(il.head->data == 1);
    assert(il.tail->data == 2);
  }

  void testRemove_emptyList() {
    IntList il;
    assert(il.getSize() == 0);

    il.remove(2);
    assert(il.getSize() == 0);
    assert(il.head == NULL && il.tail == NULL);
  }

  void testRemove_duplEle() {
    IntList il;
    il.addFront(2);
    il.addFront(3);
    il.addFront(2);
    il.addFront(2);
    il.addFront(5);

    il.remove(2);
    assert(il.getSize() == 4);
    assert(il[0] == 5 && il[1] == 2 && il[2] == 3 && il[3] == 2);
    assert(il.head->next->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev->data == 5);
  }

  void testRemove_twice() {
    IntList il;
    il.addBack(2);
    il.addBack(3);

    il.remove(2);
    assert(il.remove(2) == false);
    assert(il.find(2) == -1);
    assert(il.getSize() == 1);
  }

  void testRemove_firstelement() {
    IntList il;

    il.addFront(7);
    il.addBack(5);
    il.addBack(4);
    il.addBack(3);
    il.addBack(2);  // 7 5 4 3 2

    assert(il.getSize() == 5);
    assert(il[0] == 7);
    il.remove(7);  // 5 4 3 2

    assert(il[0] == 5);
    assert(il.head->prev == NULL);
    assert(il.remove(7) == false);
    assert(il.getSize() == 4);
    assert(il.head->data == 5);
    assert(il.head->next->data == 4);
    assert(il.head->next->next->data == 3);
    assert(il.head->next->next->next->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev->data == 5);

    assert(il.head->next->next->next == il.tail);

    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 3);
    assert(il.tail->prev->prev->data == 4);
    assert(il.tail->prev->prev->prev->data == 5);
    assert(il.tail->next == NULL);

    assert(il[0] == 5);
    assert(il[1] == 4);
    assert(il[2] == 3);
    assert(il[3] == 2);
    assert(il.find(5) == 0);
    assert(il.find(4) == 1);
    assert(il.find(3) == 2);
    assert(il.find(2) == 3);
  }

  void testRemove_lastelement() {
    IntList il;
    il.addFront(7);
    il.addBack(5);
    il.addBack(4);
    il.addBack(3);
    il.addBack(2);  // 7 5 4 3 2

    assert(il.getSize() == 5);
    assert(il[4] == 2);
    il.remove(2);

    assert(il[3] == 3);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 4);
  }

  void testRemove_midelement() {
    IntList il;
    il.addFront(7);
    il.addBack(5);
    il.addBack(4);
    il.addBack(3);
    il.addBack(2);

    assert(il.getSize() == 5);
    assert(il[1] == 5);
    il.remove(5);

    assert(il[1] == 4);
    assert(il.head->next->prev == il.head);
    assert(il.getSize() == 4);
  }
  void testRemove() {
    IntList l1;  // l1: 224321
    l1.addFront(1);
    l1.addFront(2);
    l1.addFront(3);
    l1.addFront(4);
    l1.addFront(2);
    l1.addFront(2);

    IntList l2;  //l2: 21
    l2.addFront(1);
    l2.addFront(2);

    IntList l3;  //l3: 21
    l3.addFront(1);
    l3.addFront(2);

    IntList l4;  //l4: 1357
    l4.addBack(1);
    l4.addBack(3);
    l4.addBack(5);
    l4.addBack(7);

    IntList l5;  //l5: 137
    l5.addBack(1);
    l5.addBack(3);
    l5.addBack(7);

    //test l1
    assert(l1.getSize() == 6);

    assert(l1.remove(2) == true);  //l1:24321
    assert(l1.getSize() == 5);

    assert(l1[0] == 2 && l1[3] == 2);
    assert(l1.head->data == 2);
    assert(l1.head->next->data == 4);

    assert(l1.remove(10) == false);
    l1.remove(2);  //l1:4321
    assert(l1.head->data == 4);
    l1.remove(2);  //l1: 431
    assert(l1.head->next->next->data == 1);
    assert(l1.tail->data == 1);
    l1.remove(1);  //l1 : 43
    assert(l1.tail->data == 3);

    //test l2
    l2.remove(2);
    l2.remove(1);  //l2: empty
    assert(l2.getSize() == 0 && l2.head == NULL && l2.tail == NULL);

    //test l3
    l3.remove(2);  //l3: 1
    assert(l3.getSize() == 1 && l3.head == l3.tail && l3.head != NULL);
    assert(l3[0] == 1);
    assert(l3.head->next == NULL && l3.head->prev == NULL);
  }

  void testLinkedList(void) {
    IntList test;
    // many more tester methods
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddBack_empty();
  t.testAddFront_2ele();
  t.testAddFront_3ele();

  t.testAddBack_empty();
  t.testAddBack_2ele();
  t.testAddBack_3ele();

  t.assign();
  t.copy();

  t.testRemove();

  t.testRemove_firstelement();
  t.testRemove_lastelement();
  t.testRemove_midelement();

  t.testRemove_itemNotinList();
  t.testRemove_emptyList();
  t.testRemove_duplEle();
  t.testRemove_twice();
  // t.testLinkedList();

  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
