#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
#include "./sudoku.cpp"


int randomInt(int Max, int min=0){
    return min ? (rand() % min + Max - min) : (rand() % Max) + (min ? Max - min : min);
}

int main()
{
    // finish your generate code...

    srand(time(NULL));


    vector<vector<int> > ar = {
            {3 ,0 ,2 ,0 ,0 ,5 ,6 ,9 ,0},
            {0 ,4 ,0 ,0 ,9 ,6 ,0 ,3 ,0},
            {0 ,5 ,0 ,0 ,0 ,8 ,0 ,0 ,0},
{1 ,9 ,0 ,0 ,8 ,0 ,7 ,0 ,3},
{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{5 ,0 ,7 ,0 ,3 ,0 ,0 ,6 ,1},
{0 ,0 ,0 ,8 ,0 ,0 ,0 ,2 ,0},
{0 ,8 ,0 ,9 ,6 ,0 ,0 ,7 ,0},
{0 ,6 ,5 ,7 ,0 ,0 ,3 ,0 ,9}
    };
    Sudoku s(ar);
    int times = randomInt(10, 5);
    int code;
    int x,y;
    for(int i = 0; i < times; i++){
        code = randomInt(5);
        cout<<"Code = "<<code<<endl;
        if(code)
            switch (code)
            {
                case 1:
                    /* code */
                    x = randomInt(9,1);
                    y = randomInt(9,1);
                    printf("swapNum(%d, %d)\n",x,y);
                    s.swapNum(x,y);
                    break;
                case 2:
                    x = randomInt(3);
                    y = randomInt(3);
                    printf("swapRow(%d, %d)\n",x,y);
                    s.swapRow(x,y);
                    break;
                case 3:
                    x = randomInt(3);
                    y = randomInt(3);
                    printf("swapCol(%d, %d)\n",x,y);
                    s.swapCol(x,y);
                    break;
                case 4:
                    x = randomInt(100);
                    printf("rotate %d\n",x);
                    s.rotate(x);
                    break;
                case 5:
                    x = randomInt(2);
                    cout<<"flip "<<x<<endl;
                    s.flip(x);
                    break;
                default:
                    break;
            }
        else
            break;

    }

    s.outPutPattern(false);

    return 0;
}
