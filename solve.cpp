#include "./sudoku.cpp"

int main()
{
    // finish your solve code...

    Sudoku s;
    int solveStatus = s.solve();
    cout<<solveStatus<<endl;
    s.outPutPattern(true);


    return 0;
}
