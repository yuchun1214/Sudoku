#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

#include <exception>
#include <cmath>
#include "./matrix.cpp"

using namespace DS;

class Sudoku : protected __sparse_mat
{
private:
    bool ruleCheck(int row, int col, int answerMat[][9]);
    bool legal(int element);
    bool legal(int i, int j);
    void shiftToNextPos(int &i, int &y, bool forward);
    bool checkRow(int row, int col);
    bool checkCol(int row, int col);
    bool checkSquare(int row, int col);
    int solving(int i, int j, int subjectMat[][9]);

    void findFirstZeroElementPos(int *i, int *j, int subjectMat[][9]);
    int answerMat[9][9];
public:
    Sudoku();

    template <class T>
    Sudoku(T matArray);

    // generate
    void generate();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();

   void outPutPattern(bool solve);
};


#endif // SUDOKU_H
