#include "./sudoku.cpp"

int main()
{
    // finish your transform code...

    Sudoku s;
    int code;
    int x = 0, y= 0;
    do{
        cin>>code;
        switch (code)
        {
            case 1:
                /* code */
                cin>>x>>y;
                s.swapNum(x,y);
                break;
            case 2:
                cin>>x>>y;
                s.swapRow(x,y);
                break;
            case 3:
                cin>>x>>y;
                s.swapCol(x,y);
                break;
            case 4:
                cin>>x;
                s.rotate(x);
                break;
            case 5:
                cin>>x;
                s.flip(x);
                break;
            default:
                break;
        }
    }while(code);
    s.outPutPattern(false);

    return 0;
}
