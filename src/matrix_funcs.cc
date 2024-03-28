#include <string.h>

#include <cmath>

#include "matrix_oop.h"
bool Matrix::EqMatrix(const Matrix &other) const {
  constexpr double eps = 1e-7;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other(i, j)) > eps) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix &other) {
  SameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  SameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  Matrix temp(rows_, other.cols_);

  for (int i = 0; i < temp.rows_; ++i) {
    for (int j = 0; j < temp.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        temp(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = temp;
}

void Matrix::RangCheck(int i, int j) const {
  if (i > rows_ || j > cols_) {
    throw std::out_of_range("index is outside the matrix");
  }
}

void Matrix::AboveZero(int i, int j) const {
  if (i < 0 || j < 0) {
    throw std::out_of_range("index is outside the matrix");
  }
}

void Matrix::SameSize(const Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions");
  }
}

void Matrix::IsSquare() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("the matrix is not square");
  }
}

Matrix Matrix::Transpose() {
  Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      temp(j, i) = matrix_[i][j];
    }
  }
  return temp;
}

Matrix Matrix::CalcComplements() {
  Matrix result(rows_, cols_);
  IsSquare();
  if (rows_ == 1) {
    result(0, 0) = matrix_[0][0] * matrix_[0][0];
  } else {
    double minus = 1;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if ((i + j) % 2) {
          minus = -1;
        } else {
          minus = 1;
        }
        result(i, j) = BiteMatrix(i, j).Determinant() * minus;
      }
    }
  }
  return result;
}

double Matrix::Determinant() {
  IsSquare();
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    int minus = 1;
    for (int i = 0; i < rows_; ++i) {
      Matrix temp = BiteMatrix(0, i);
      result += matrix_[0][i] * temp.Determinant() * minus;
      minus = -minus;
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  double det = Determinant();
  Matrix res;
  if (det == 0)
    throw std::invalid_argument("matrix determinant is 0");
  if (rows_ == 1 && cols_ == 1) {
    res.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    res = Transpose().CalcComplements() * (1 / det);
  }
  return res;
}

Matrix Matrix::BiteMatrix(const int row, const int col) {
  Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, m = 0; i < rows_; ++i) {
    if (i == row) {
      continue;
    } else {
      for (int j = 0, n = 0; j < cols_; ++j) {
        if (j == col) {
          continue;
        } else {
          result(m, n) = matrix_[i][j];
          ++n;
        }
      }
      ++m;
    }
  }
  return result;
}

void Matrix::CopyHere(const Matrix &from) {
  rows_ = from.rows_;
  cols_ = from.cols_;
  Resize(from.rows_, from.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = from(i, j);
    }
  }
}
