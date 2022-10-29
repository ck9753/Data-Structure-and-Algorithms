#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows.resize(r);
  typename std::vector<std::vector<T> >::iterator it = rows.begin();
  while (it != rows.end()) {
    (*it).resize(c);
    ++it;
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = rhs.rows;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert((index >= 0) && (index < numRows));
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert((index >= 0) && (index < numRows));
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if ((rows != rhs.rows) || (numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
    return false;
  }

  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));

  Matrix<T> ans(numRows, numColumns);
  typename std::vector<std::vector<T> >::const_iterator iter_this = rows.begin();

  typename std::vector<std::vector<T> >::const_iterator iter_rhs = rhs.rows.begin();

  typename std::vector<std::vector<T> >::iterator iter_ans = ans.rows.begin();

  while (iter_ans != ans.rows.end()) {
    //typename std::vector<T>::iterator db_iter_ans = (*iter_ans).begin();

    typename std::vector<T>::const_iterator db_iter_this = (*iter_this).begin();

    typename std::vector<T>::const_iterator db_iter_rhs = (*iter_rhs).begin();

    typename std::vector<T>::iterator db_iter_ans = (*iter_ans).begin();

    while (db_iter_ans != (*iter_ans).end()) {
      *db_iter_ans = *db_iter_this + *db_iter_rhs;
      ++db_iter_this;
      ++db_iter_rhs;
      ++db_iter_ans;
    }

    ++iter_this;
    ++iter_rhs;
    ++iter_ans;
  }
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";

  typename std::vector<std::vector<T> >::const_iterator iter;
  for (iter = rhs.rows.begin(); iter != rhs.rows.end(); ++iter) {
    if (iter != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";

    typename std::vector<T>::const_iterator db_iter;

    for (db_iter = (*iter).begin(); db_iter != (*iter).end(); ++db_iter) {
      if (db_iter != (*iter).begin()) {
        s << ", ";
      }

      s << *db_iter;
    }

    s << "}";
  }

  s << " ]";

  return s;
}

#endif
