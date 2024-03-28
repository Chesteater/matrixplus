#ifndef MATRIXPLUS_MATRIX_OOP_H_
#define MATRIXPLUS_MATRIX_OOP_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>
class Matrix {
public:
  // constructors and destructor
  Matrix();                   // default constructor
  Matrix(int rows, int cols); // parameterized constructor
  Matrix(int rows, int cols, std::initializer_list<double> const &list);
  Matrix(const Matrix &other); // copy constructor
  Matrix(Matrix &&other);      // move constructor
  ~Matrix();                      // destructor

  // some operators overloads

  bool operator==(const Matrix &other) const;
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other);
  double &operator()(int i, int j) const;
  double &operator()(int i, int j);
  Matrix &operator+=(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix &operator-=(const Matrix &other);
  Matrix operator-(const Matrix &other) const;
  Matrix &operator*=(const Matrix &other);
  Matrix operator*(const Matrix &other) const;
  Matrix &operator*=(const double num);
  Matrix operator*(const double num) const;

  // some public methods
  bool EqMatrix(const Matrix &other) const;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);

  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int RowsNew);
  void SetCols(int ColsNew);

private:
  // some private methods
  void CopyHere(const Matrix &from);
  Matrix BiteMatrix(const int row, const int col);
  void SameSize(const Matrix &other) const;
  void IsSquare() const;
  void MemAlloc();
  void FreeMem();
  void Resize(int RowsNew, int ColsNew);
  void RangCheck(int i, int j) const;
  void AboveZero(int i, int j) const;

  // attributes
  int rows_, cols_;
  double **matrix_;
};

Matrix operator*(const double num, const Matrix &other);

#endif // MATRIXPLUS_MATRIX_OOP_H_
