#ifndef __SUDOKU_CPP__
#define __SUDOKU_CPP__

// #define DEBUG

#include "sudoku.h"

Sudoku::Sudoku() : __sparse_mat::__sparse_mat(9, 9, 0) {
}

template<class T>
Sudoku::Sudoku(T matArray) : __sparse_mat::__sparse_mat(9, 9, matArray) {

}

void Sudoku::outPutPattern(bool solve = false) {

    if(!solve) {
        deque<deque<int> > array = matToArray();
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << array[i][j] << " ";
            }
            cout << array[i][8] << "\n";
        }
    }else{
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 8; j++){
                cout<<answerMat[i][j]<<" ";
            }
            cout<<answerMat[i][8]<<"\n";
        }
    }
}

void Sudoku::swapNum(int x, int y) {
    if (!matNodes.size())
        throw("You Need To Using mread First to Input the Matrix");
    for (int i = 0; i < matNodes.size(); ++i) {
        //        cout<<matNodes[i]<<endl;
        if (matNodes[i]->Value() == x) {
            matNodes[i]->Value(y);
        } else if (matNodes[i]->Value() == y) {
            matNodes[i]->Value(x);
        }
    }
}

void Sudoku::swapRow(int x, int y) {
    if (!matNodes.size())
        throw("You Need To Using mread First to Input the Matrix");
    for (int i = 0; i < matNodes.size(); ++i) {
        if (matNodes[i]->Row() < 3 * (x + 1) && matNodes[i]->Row() >= 3 * x) {
            // recognize the row is in which section.
            matNodes[i]->Row((matNodes[i]->Row() + (x - y) * ((x - y) ? -3 : 3)));
        } else if (matNodes[i]->Row() < 3 * (y + 1) && matNodes[i]->Row() >= 3 * y) {
            // recognize the row is in which section.
            matNodes[i]->Row((matNodes[i]->Row() + (x - y) * ((x - y) ? 3 : -3)));
        }
    }
}

void Sudoku::swapCol(int x, int y) {
    if (!matNodes.size())
        throw("You Need To Using mread First to Input the Matrix");
    for (int i = 0; i < matNodes.size(); ++i) {
        if (matNodes[i]->Col() < 3 * (x + 1) && matNodes[i]->Col() >= 3 * x) {
            // recognize the col is in which section.
            matNodes[i]->Col((matNodes[i]->Col() + (x - y) * ((x - y) ? -3 : 3)));
        } else if (matNodes[i]->Col() < 3 * (y + 1) && matNodes[i]->Col() >= 3 * y) {
            // recognize the col is in which section.
            matNodes[i]->Col((matNodes[i]->Col() + (x - y) * ((x - y) ? 3 : -3)));
        }
    }
}

void Sudoku::flip(int x) {
    if (x) {
        for (int i = 0; i < matNodes.size(); ++i) {
            matNodes[i]->Col(8 - matNodes[i]->Col());
        }
    } else {
        for (int i = 0; i < matNodes.size(); ++i) {
            matNodes[i]->Row(8 - matNodes[i]->Row());
        }
    }
}

void Sudoku::rotate(int x) {
    int times = x % 4;
    for (int i = 0; i < times; ++i) {
        Transpose();
        flip(1);
    }
}

void Sudoku::generate() {
    String transformCode;
    deque<String> codes;
    //    while(true){
    cin >> transformCode;
    codes = transformCode.split(" ");
    for (int i = 0; i < codes.size(); ++i) {
        cout << codes[i] << endl;
    }
    //    }
}

bool Sudoku::checkRow(int row, int col) {

#ifdef DEBUG
    cout << "\n\n\033[1;41m[Check Row]\033[0m" << endl;
    cout << "Target : " << answerMat[row][col] << endl;
#endif
    // fix row and iterator col
    for (int i = 0; i < 9; ++i) {
#ifdef DEBUG
        cout << answerMat[row][i] << " ";
#endif
        if (answerMat[row][i] == answerMat[row][col] && col != i) {
#ifdef DEBUG
            printf("(col, row)(%d, %d) has two same value\nSo, return false\n", col, i);
#endif
            return false;
        }
    }

#ifdef DEBUG
    cout << "\n\n\033[1;41m[END]\033[0m" << endl;
#endif

    return true;
}

bool Sudoku::checkCol(int row, int col) {

#ifdef DEBUG
    cout << "\n\n\033[1;43m[Check Col]\033[0m" << endl;
    cout << "Target : " << answerMat[row][col] << endl;
#endif
    // fix col and iterate row
    for (int i = 0; i < 9; ++i) {
#ifdef DEBUG
        cout << answerMat[i][col] << endl;
#endif
        if (answerMat[i][col] == answerMat[row][col] && row != i) {
#ifdef DEBUG
            printf("(col, row)(%d, %d) has two same value\nSo, return false\n", col, i);
#endif
            return false;
        }
    }

#ifdef DEBUG
    cout << "\n\n\033[1;43m[END]\033[0m" << endl;
#endif

    return true;
}

bool Sudoku::checkSquare(int row, int col) {
    int squareColStartNum = 3 * (int)floor((float)col / 3.0);
    int squareColEndNum = squareColStartNum + 3;

    int squareRowStartNum = 3 * (int)floor((float)row / 3.0);
    int squareRowEndNum = squareRowStartNum + 3;

#ifdef DEBUG
    cout << "\n\n\033[1;47m[Check Square]\033[0m" << endl;
    cout << "Check NUM : " << answerMat[row][col] << endl;
    for (int i = squareRowStartNum; i < squareRowEndNum; ++i) {
        for (int j = squareColStartNum; j < squareColEndNum; ++j)
            cout << answerMat[i][j] << " ";
        cout << endl;
    }
#endif
    for (int i = squareRowStartNum; i < squareRowEndNum; ++i) {
        for (int j = squareColStartNum; j < squareColEndNum; ++j)
            if (answerMat[i][j] == answerMat[row][col] && i != row && j != col) {
#ifdef DEBUG
                printf("Check Square find a same value %d\n", answerMat[i][j]);
                printf("value(%d, %d) and Target(%d, %d) are the same\n", i % 3, j % 3, row % 3, col % 3);
                printf("So, Return false\n");
#endif
                return false;
            }
    }

#ifdef DEBUG
    cout << "\033[1;47m[End]\033[0m" << endl;
#endif

    return true;
}

bool Sudoku::ruleCheck(int row, int col, int answerMat[][9]) {
    int temp = answerMat[row][col];
    for (int i = 0; i < 9; ++i) {
        if ((answerMat[row][i] == temp && col != i) || (temp == answerMat[i][col] && row != i)) {
            return false;
        }
    }

    int squareColStartNum = 3 *(col / 3);
    int squareColEndNum = squareColStartNum + 3;

    int squareRowStartNum = 3 * (row / 3);
    int squareRowEndNum = squareRowStartNum + 3;

    for (int i = squareRowStartNum; i < squareRowEndNum; ++i) {
        for (int j = squareColStartNum; j < squareColEndNum; ++j)
            if (answerMat[i][j] == answerMat[row][col] && i != row && j != col) {
                return false;
            }
    }

    return true;
}

void Sudoku::shiftToNextPos(int &i, int &j, bool forward) {
#ifdef DEBUG
    printf("(i, j ) = (%d, %d) go %s to ", i, j, forward ? "forward" : "backward");
#endif
    if (forward) {
        //        i = ((i + 1 < 9) ? i + 1 : -1);
        j = ((j + 1 < 9) ? j + 1 : ((i += 1), 0)); // j is col
    } else {
        // backward
        j = ((j - 1 >= 0) ? j - 1 : ((i -= 1), 8));
    }

#ifdef DEBUG
    printf("(%d, %d)\n", i, j);
#endif
}

bool Sudoku::legal(int i, int j) {
    return ((i >= 0 && j >= 0) && (i < 9 && j < 9));
}

bool Sudoku::legal(int element) {
    return (element <= 9);
}



/**
 *
 * @param i started pos of row
 * @param j started pos of col
 */
int Sudoku::solving(int i0, int j0, int subjectMat[][9]) {
    bool shiftMode = true;
    int answerNum = 0;
    
    int testMat[9][9];
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            testMat[i][j] = subjectMat[i][j];
        }
    }
    
    int i = 0, j = 0;
    do {
        while ((i >= 0 && j >= 0) && (i < 9 && j < 9)) {
            if (!subjectMat[i][j]) {
                do {
                    testMat[i][j] += 1;
                } while (!ruleCheck(i, j, testMat));
                shiftMode = (testMat[i][j] <= 9);

                // shiftToNextPos(i, j, shiftMode);
                if (shiftMode) {
                    //        i = ((i + 1 < 9) ? i + 1 : -1);
                    j = ((j + 1 < 9) ? j + 1 : ((i += 1), 0)); // j is col
                } else {
                    // backward
                    testMat[i][j] = 0;
                    j = ((j - 1 >= 0) ? j - 1 : ((i -= 1), 8));
                }
            } else {

                if (shiftMode) {
                    //        i = ((i + 1 < 9) ? i + 1 : -1);
                    j = ((j + 1 < 9) ? j + 1 : ((i += 1), 0)); // j is col
                } else {
                    // backward
                    j = ((j - 1 >= 0) ? j - 1 : ((i -= 1), 8));
                }
            }
        }
        if(!testMat[i0][j0]) {
            // for infeasible sudoku
            return answerNum;
        } else {
            answerNum += 1;
            i = j = 8;
            shiftMode = false;
            if(answerNum > 1){
                return answerNum;
            }else{
                for(int i = 0; i < 9; ++i){
                    for(int j = 0; j < 9; ++j){
                        answerMat[i][j] = testMat[i][j];
                    }
                }
            }
        }
    } while(testMat[i0][j0] || testMat[i0][j0] == 9);
    return answerNum;
}

void Sudoku::findFirstZeroElementPos(int *ii, int *jj, int subjectMat[][9]) {
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            if(!subjectMat[i][j]) {
                *ii = i;
                *jj = j;
                return;
            }
}

int Sudoku::solve() {
    if (!matNodes.size())
        throw("You haven't inputed a answerMat");
    //    int board[9][9];
    int base[9][9];
    deque<deque<int> > array = matToArray();
    for (int i = 0; i < array.size(); ++i) {
        for (int j = 0; j < array[i].size(); ++j) {
            answerMat[i][j] = base[i][j] = array[i][j];
        }
    }
    int i, j;
    findFirstZeroElementPos(&i,&j,base);
//    float time1 = clock();
    return solving(i,j, base);
//    float time2 = clock();
//    cout << "Time is " << (time2 - time1) / CLOCKS_PER_SEC << "\n";

//    for (int i = 0; i < 9; ++i) {
//        for (int j = 0; j < 9; ++j) {
//            cout << answerMat[i][j] << " ";
//        }
//        cout << endl;
//    }
//    return 0;
}

#endif

// #define __SUDOKU_CPP_TEST__
#ifdef __SUDOKU_CPP_TEST__

int main(int argc, char const *argv[]) {
    Sudoku s;
    s.solve();
    // cout << s << "\n";
}

#endif