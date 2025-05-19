/*mymatrix.h*/

//  @author Muhammad Hakim
//  @date CS 251, Spring 2023.
//  @brief Project 3 - Matrices, University of Illinois Chicago
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
      if (R < 1)
          throw invalid_argument("mymatrix::constructor: # of rows");
      if (C < 1)
          throw invalid_argument("mymatrix::constructor: # of cols");

      Rows = new ROW[R];  // an array with R ROW structs:
      NumRows = R;

      // initialize each row to have C columns:
      for (int r = 0; r < NumRows; ++r)
      {
          Rows[r].Cols = new T[C];  // an array with C elements of type T:
          Rows[r].NumCols = C;

          // initialize the elements to their default value:
          for (int c = 0; c < Rows[r].NumCols; ++c)
          {
              Rows[r].Cols[c] = T{};  // default value for type T:
          }
      }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
      NumRows = other.NumRows;
      Rows = new ROW[NumRows];
      for (int r = 0; r < NumRows; ++r)
      {
          Rows[r].NumCols = other.Rows[r].NumCols;
          Rows[r].Cols = new T[Rows[r].NumCols];

          for (int c = 0; c < Rows[r].NumCols; ++c)
          {
              Rows[r].Cols[c] = other.Rows[r].Cols[c];
          }
      }

  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
      return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
      if (r < 0 || r >= NumRows)
          throw invalid_argument("mymatrix::numcols: row");

      return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int c) {
      if (r < 0 || r >= NumRows) {
          throw invalid_argument("mymatrix::growcols: row");
      }
      if (c < 1) {
          throw invalid_argument("mymatrix::growcols: columns");
      }

      auto& row = Rows[r];
      if (c <= row.NumCols) {
          return;
      }

      auto new_row = make_unique<T[]>(c);
      copy(row.Cols, row.Cols + row.NumCols, new_row.get());
      fill(new_row.get() + row.NumCols, new_row.get() + c, T{});
      row.Cols = new_row.release();
      row.NumCols = c;
  }





  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
      if (R < 1)
          throw invalid_argument("mymatrix::grow: # of rows");
      if (C < 1)
          throw invalid_argument("mymatrix::grow: # of cols");

      if (R <= NumRows) { // Grow columns if necessary and return
          for (int i = 0; i < NumRows; i++) {
              growcols(i, C);
          }
          return;
      }

      // Grow existing rows if necessary
      for (int i = 0; i < NumRows; i++) {
          if (C > Rows[i].NumCols) {
              Rows[i].Cols = static_cast<T*>(realloc(Rows[i].Cols, C * sizeof(T)));
              if (Rows[i].Cols == nullptr) {
                  throw bad_alloc();
              }
              // Initialize new columns to default value of T
              for (int j = Rows[i].NumCols; j < C; j++) {
                  Rows[i].Cols[j] = T{};
              }
              Rows[i].NumCols = C;
          }
      }

      // Add new rows if necessary
      int numNewRows = R - NumRows;
      if (numNewRows > 0) {
          ROW* newRows = static_cast<ROW*>(realloc(Rows, R * sizeof(ROW)));
          if (newRows == nullptr) {
              throw bad_alloc();
          }
          Rows = newRows;
          for (int i = NumRows; i < R; i++) {
              T* newCols = static_cast<T*>(malloc(C * sizeof(T)));
              if (newCols == nullptr) {
                  throw bad_alloc();
              }
              // Initialize new columns to default value of T
              for (int j = 0; j < C; j++) {
                  newCols[j] = T{};
              }
              Rows[i].Cols = newCols;
              Rows[i].NumCols = C;
          }
          NumRows = R;
      }
  }




  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
      int total = 0;
      for (int r = 0; r < numrows(); ++r)
      {
          total += numcols(r);
      }
      return total;
  }



  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
      if (r < 0 || r >= NumRows)
          throw invalid_argument("mymatrix::at: row");
      if (c < 0 || c >= Rows[r].NumCols)
          throw invalid_argument("mymatrix::at: col");

      return Rows[r].Cols[c];
  }



  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
      if (r < 0 || r >= NumRows)
          throw invalid_argument("mymatrix::(): row");
      if (c < 0 || c >= Rows[r].NumCols)
          throw invalid_argument("mymatrix::(): col");

      return Rows[r].Cols[c];
  }


  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
      mymatrix<T> result(*this); // create a copy of the original matrix

      // multiply each element in the copy by the scalar
      for (int i = 0; i < result.NumRows; i++)
      {
          int numCols = result.numcols(i);
          for (int j = 0; j < numCols; j++)
          {
              result.Rows[i].Cols[j] *= scalar;
          }
      }

      return result;
  }




  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
      // Check if the matrices are rectangular
      if (this->numcols(0) != other.numrows())
          throw runtime_error("mymatrix::*: size mismatch");
      for (int i = 0; i < this->numrows(); i++) {
          if (this->Rows[i].NumCols != this->numcols(0))
              throw runtime_error("mymatrix::*: this not rectangular");
      }
      for (int j = 0; j < other.numrows(); j++) {
          if (other.Rows[j].NumCols != other.numcols(0))
              throw runtime_error("mymatrix::*: other not rectangular");
      }

      // Perform matrix multiplication
      int numRows = this->numrows();
      int numCols = other.numcols(0);
      mymatrix<T> result(numRows, numCols);
      for (int i = 0; i < numRows; i++) {
          for (int j = 0; j < numCols; j++) {
              T sum = 0;
              for (int k = 0; k < this->numcols(0); k++) {
                  sum += this->Rows[i].Cols[k] * other.Rows[k].Cols[j];
              }
              result.Rows[i].Cols[j] = sum;
          }
      }

      return result;
  }





  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
