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
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T> *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
    }
  }

  Matrix(const Matrix<T> & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T> *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
      *rows[i] = *rhs.rows[i];
    }
  }

  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix<T> & rhs) {
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

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
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
  Matrix<T> operator+(const Matrix<T> & rhs) const;
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> answer(numRows, numColumns);
  for (int i = 0; i < rhs.numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*answer.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return answer;
}

std::ostream &
operator<<(std::ostream & s, const Matrix & rhs) {
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
