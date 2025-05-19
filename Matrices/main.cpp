// Matrices.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  @author Muhammad Hakim
//  @date CS 251, Spring 2023.
//  @brief Project 3 - Matrices, University of Illinois Chicago

#include <iostream>
#include <time.h>
#include "mymatrix.h"

// Gives a random number 1 - 10
int randNumGen()
{
	srand(time(NULL)); // Use current time to seed the random number generator
	int randNum = rand() % 10 + 1; // Random number 1-10
	return randNum;
}

int main()
{
    mymatrix<int> M(4, 4); // 4x4 matrix, initialized to 0

    int randomNum = randNumGen(); // Random number 1-10
    int randomRow = randomNum % M.numrows(); // Random row index

    cout << "Random Number 1-10: " << randomNum << endl;
    cout << "Random Row Index: " << randomRow << endl;

    cout << endl << "[matrix M]:" << endl;
    M._output();

    // Test the "at" function
    cout << endl << "[at TEST]: " << M.at(randomRow, randomRow) << " at (" << randomRow << ", " << randomRow << ")" << endl;

    // Test the "numrows" function
    cout << endl << "[numrows TEST] Number of Rows: " << M.numrows() << endl;

    // Test the "numcols" function
    cout << endl << "[numcols TEST] Number of Columns in Row " << randomRow << ": " << M.numcols(randomRow) << endl;

    // Test the "size" function
    cout << endl << "[size TEST] Size of Matrix: " << M.size() << endl;

    // Test the "growcols" function
    cout << endl << "[growcols TEST]: " << endl;
    M.growcols(randomRow, randomNum); // grow row (1-4) to have (1-10) columns

    cout << "[matrix M]:" << endl;
    M._output();

    // Create a new matrix for testing
    unique_ptr<mymatrix<int>> M2 = make_unique<mymatrix<int>>(6, 6);

    (*M2)(0, 0) = 1;
    (*M2)(1, 1) = 2;
    (*M2)(2, 2) = 3;
    (*M2)(3, 3) = 4;
    (*M2)(4, 4) = 5;
    (*M2)(5, 5) = 6;

    cout << endl << "[matrix M2]:" << endl;
    M2->_output();

    // Test the "grow" function
    cout << endl << "[grow TEST]: " << endl;
    M2->grow(randomNum, randomNum);

    cout << "[matrix M2]:" << endl;
    M2->_output();

    // Test the "numrows" function again
    cout << endl << "[numrows TEST] Number of Rows: " << M2->numrows() << endl;

    // Test the "numcols" function again
    cout << endl << "[numcols TEST] Number of Columns in Row " << randomRow << ": " << M2->numcols(randomRow) << endl;

    // Test the "size" function again
    cout << endl << "[size TEST] Size of Matrix: " << M2->size() << endl;

    // Test the "operator*" function
    cout << endl << "[operator* TEST] Matrix M * 2 : " << endl;

    mymatrix<int> M3 = M * 2;

    cout << endl << "[matrix M3]:" << endl;
    M3._output();

    // Test the matrix multiplication
    cout << endl << "[matrix multiplication TEST]: " << endl << endl;

    mymatrix<int> M4(3, 4);
    mymatrix<int> M5(4, 2);
    mymatrix<int> M6;

    M4(0, 0) = 5;
    M4(0, 1) = 8;
    M4(0, 2) = 3;
    M4(0, 3) = 4;
    M4(1, 0) = 2;
    M4(1, 1) = 7;
    M4(1, 2) = 9;
    M4(1, 3) = 3;
    M4(2, 0) = 1;
    M4(2, 1) = 2;
    M4(2, 2) = 4;
    M4(2, 3) = 5;

    cout << "[matrix M4]:" << endl;
    M4._output();

    M5(0, 0) = 2;
    M5(0, 1) = 1;
    M5(1, 0) = 5;
    M5(1, 1) = 3;
    M5(2, 0) = 2;
    M5(2, 1) = 7;
    M5(3, 0) = 8;
    M5(3, 1) = 9;

    cout << endl << "[matrix M5]:" << endl;
    M5._output();

    M6 = M4 * M5;

    cout << endl << "[matrix M6 (M4 * M5)]:" << endl;
    M6._output();

    // Additional test cases
    cout << endl << "[ADDITIONAL TEST CASES]: " << endl << endl;

    // Test the "growcols" function
    cout << "[growcols TEST] Growing the matrix M: " << endl << endl;

    mymatrix<int> M7(3, 3);
    M7(0, 0) = 1;
    M7(0, 1) = 2;
    M7(0, 2) = 3;
    M7(1, 0) = 4;
    M7(1, 1) = 5;
    M7(1, 2) = 6;
    M7(2, 0) = 7;
    M7(2, 1) = 8;
    M7(2, 2) = 9;

    cout << "[matrix M7]:" << endl;
    M7._output();

    M7.growcols(1, 5);

    cout << endl << "[matrix M7 after growing column 1 to have 5 elements]:" << endl;
    M7._output();


    return 0;
}