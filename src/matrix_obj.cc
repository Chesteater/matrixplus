#include <algorithm>

#include "matrix_oop.h"

Matrix::Matrix() : rows_(1), cols_(1) { MemAlloc(); }

Matrix::Matrix(int rows, int cols) : matrix_() {
  AboveZero(rows, cols);
  rows_ = rows;
  cols_ = cols;
  MemAlloc();
}

Matrix::Matrix(const Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemAlloc();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other(i, j);
    }
  }
}

Matrix::Matrix(Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void Matrix::FreeMem() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void Matrix::MemAlloc() {
  matrix_ = new double *[rows_ * cols_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

Matrix::~Matrix() { FreeMem(); }

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int RowsNew) { Resize(RowsNew, cols_); }

void Matrix::SetCols(int ColsNew) { Resize(rows_, ColsNew); }

void Matrix::Resize(int RowsNew, int ColsNew) {
  AboveZero(RowsNew, ColsNew);
  Matrix temp((*this));
  FreeMem();
  rows_ = RowsNew;
  cols_ = ColsNew;
  MemAlloc();
  for (int i = 0; i < std::min(temp.rows_, RowsNew); ++i) {
    for (int j = 0; j < std::min(temp.cols_, ColsNew); ++j) {
      matrix_[i][j] = temp(i, j);
    }
  }
}

Matrix::Matrix(int rows, int cols,
                     std::initializer_list<double> const &list)
    : Matrix(rows, cols) {
  RangCheck(rows, cols);
  AboveZero(rows, cols);
  if (matrix_ != nullptr) {
    if (rows_ * cols_ == (int)list.size()) {
      int i = 0, j = 0;
      for (auto element : list) {
        if (i == rows_)
          break;
        matrix_[i][j] = element;
        if (j == cols_ - 1) {
          j = 0;
          ++i;
        } else {
          ++j;
        }
      }
    } else {
      throw std::runtime_error("Invalid size of matrix!");
    }
  } else {
    throw std::runtime_error("Invalid matrix!");
  }
}
