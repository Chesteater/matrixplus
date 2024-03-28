#include "matrix_oop.h"

Matrix &Matrix::operator=(const Matrix &other) {
  Resize(other.rows_, other.cols_);
  CopyHere(other);
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) {
  if (this != &other) {
    FreeMem();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool Matrix::operator==(const Matrix &other) const {
  return EqMatrix(other);
}

Matrix Matrix::operator+(const Matrix &other) const {
  Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

Matrix Matrix::operator*(const double num) const {
  Matrix res(*this);

  res.MulNumber(num);
  return res;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &Matrix::operator()(int i, int j) const {
  RangCheck(i, j);
  AboveZero(i + 1, j + 1);
  return matrix_[i][j];
}

Matrix operator*(const double num, const Matrix &other) {
  return other * num;
}

double &Matrix::operator()(int i, int j) {
  RangCheck(i, j);
  AboveZero(i + 1, j + 1);
  return matrix_[i][j];
}
