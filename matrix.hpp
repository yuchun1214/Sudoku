#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <exception>
#include <algorithm>
#include "./DS.cpp"

using namespace DS;
using namespace std;


class Node;
typedef Node * NodePointer;
class Node {
  private:
    int row,col,value;
  public:
    Node(int r,int c, int val);
    Node();

    int Row();
    int Col();
    int Value();

    int Row(int r);
    int Col(int c);
    int Value(int v);

    NodePointer Down;
    NodePointer Right;
    NodePointer Next;
    NodePointer ItSelf();
};

// multi-key sorting
bool nodeComp(NodePointer, NodePointer);

ostream &operator<<(ostream & out, Node & node);
ostream &operator<<(ostream & out, NodePointer & nodep);

class __sparse_mat {
  private:

    int mread_initialize(int rows,int cols, int num,NodePointer * &current_row,NodePointer * &current_col);
    void mread_addNode(NodePointer item,NodePointer * &current_row, NodePointer * &current_col);
    void mread_final(NodePointer * &current_row,NodePointer * &current_col,const int HEADER_NODE_AMOUNT);

    int rows,cols;
  public:
    deque<NodePointer> matNodes;
    NodePointer hdnode;
    NodePointer FIRST_NODE;
//    void resetHeaderNode();
  public:

  // constructor
    __sparse_mat(int rows,int cols,int num) ;
    __sparse_mat() {hdnode = FIRST_NODE = NULL; rows = cols = 0;}
    template<class T>
    __sparse_mat(int rows, int cols, T matArray);

  // basic IO
  void mread(int rows, int cols, int num);
    template<class T>
    void mread(T matArray);
    deque<deque<int> > matToArray();

    // basic matrix arithmetic
    __sparse_mat operator * (__sparse_mat);
    __sparse_mat Transpose(); // transpose itself
    __sparse_mat Transpose(__sparse_mat smt);// return the transpose answerMat. of itself but not transpose itself

    
    // clear instruction(free memory)
    void virtual virtualFunction() {}

    // construct answerMat
    NodePointer ConstructMat();

//    ~__sparse_mat();
};


#endif