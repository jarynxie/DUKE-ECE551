#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  ~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;
};

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new std::vector<T> *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T>(numColumns);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new std::vector<T> *[rhs.numRows];
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new std::vector<T>(numColumns);
    *rows[i] = *rhs.rows[i];
  }
}

template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix & rhs) {
  if (this != &rhs) {
    std::vector<T> ** tempData = new std::vector<T> *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      tempData[i] = new std::vector<T>(rhs.numColumns);
      *tempData[i] = *rhs.rows[i];
    }
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    rows = tempData;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
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
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < rhs.numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix answer(numRows, numColumns);
  for (int i = 0; i < rhs.numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*answer.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return answer;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }
  s << "{";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i];
    s << ", ";
  }
  s << rhs[rhs.size() - 1] << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << "," << std::endl;
    }
  }
  s << " ]";
  return s;
}

#endif
