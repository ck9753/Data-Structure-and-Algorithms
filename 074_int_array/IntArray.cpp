#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]), numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * x = new int[rhs.numElements];
    for (int i = 0; i < numElements; i++) {
      x[i] = rhs.data[i];
    }

    delete[] data;

    numElements = rhs.numElements;
    data = x;
  }

  return *this;
}
const int & IntArray::operator[](int index) const {
  assert((index >= 0) && (index < numElements));
  return data[index];
}
int & IntArray::operator[](int index) {
  assert((index >= 0) && (index < numElements));
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }

  for (int j = 0; j < numElements; j++) {
    if (data[j] != rhs.data[j]) {
      return false;
    }
  }

  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (*this == rhs) {
    return false;
  }
  else {
    return true;
  }
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";

  for (int j = 0; j < rhs.size(); j++) {
    s << rhs[j];
    if (j != rhs.size() - 1) {
      s << ", ";
    }
  }

  s << "}";
  return s;
}
