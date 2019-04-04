#ifndef __MATRIX_CPP__
#define __MATRIX_CPP__

#include "./matrix.hpp"

Node::Node(int r,int c, int val) {
    row = r,col = c, value = val;
    Next = Down = Right = NULL;
}

Node::Node() {
    row = col = value = -1;
    Next = Down = Right = NULL;
}

int Node::Row() {
    return row;
}

int Node::Col() {
    return col;
}

int Node::Value() {
    return value;
}

int Node::Row(int r){
    row = r;
    return row;
}

int Node::Col(int c){
    col = c;
    return col;
}

int Node::Value(int v){
    value = v;
    return value;
}

NodePointer Node::ItSelf(){
    return this;
}

ostream &operator<<(ostream & out, Node & node){
    String s;
    s = "( " + to_String(node.Col()) + ", " + to_String(node.Row()) + " ) " + "value = " + to_String(node.Value());
    return out<<s;
}

ostream &operator<<(ostream &out, NodePointer & nodep){
    String s;
    s = "( " + to_String(nodep->Col()) + ", " + to_String(nodep->Row()) + " ) " + "value = " + to_String(nodep->Value());
    return out<<s;
}

__sparse_mat::__sparse_mat(int rows, int cols, int num){
    FIRST_NODE = NULL;
    __sparse_mat::rows = rows;
    __sparse_mat::cols = cols;
    mread(rows,cols, num);
}

template<class T>
__sparse_mat::__sparse_mat(int rows, int cols, T matArray) {
    FIRST_NODE = NULL;
    __sparse_mat::rows = rows;
    __sparse_mat::cols = cols;
    mread(matArray);
}



int __sparse_mat::mread_initialize(int rows,int cols, int num,NodePointer * &current_row,NodePointer * &current_col) {
    if(FIRST_NODE) delete FIRST_NODE; // avoid dangling memory as user need to re-construct answerMat again.
    FIRST_NODE = new Node(rows,cols,num); // new the first node
    const int HEADER_NODE_AMOUNT = (rows >= cols ? rows : cols); // decide header node's amount which is MAX{rows, cols}

    // point to the current position col/row
    current_col = new NodePointer[HEADER_NODE_AMOUNT];
    current_row = new NodePointer[HEADER_NODE_AMOUNT];

    if(!hdnode)
        hdnode = new Node[HEADER_NODE_AMOUNT];

    // initially,each element of current_col and current_row point to header node;
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++) {
        current_col[i] = &hdnode[i];
        current_row[i] = &hdnode[i];
    }

    // FIRST_NODE->RIGHT point to the first hdnode;
    FIRST_NODE->Right = &hdnode[0];

    //to get the chain formed by all of hdnodes
    for(int i = 0; i < HEADER_NODE_AMOUNT - 1; i++) hdnode[i].Next = &hdnode[i + 1];
    hdnode[HEADER_NODE_AMOUNT - 1].Next = FIRST_NODE;// point back to FIRSTNODE

    return HEADER_NODE_AMOUNT; // return the hdnode's amount;
}

void __sparse_mat::mread_addNode(NodePointer item, NodePointer * &current_row,NodePointer * & current_col) {
    // link answerMat with new node;
    current_row[item->Row()]->Right = item;
    current_col[item->Col()]->Down = item;

    // update the current position switch to next position
    current_row[item->Row()] = item;
    current_col[item->Col()] = item;
}

void __sparse_mat::mread_final(NodePointer * &current_row,NodePointer * &current_col, const int HEADER_NODE_AMOUNT) {

    // for each chain, the tail of chain point back to the head
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++) {
        current_col[i]->Down = &hdnode[i];
        current_row[i]->Right = &hdnode[i];
    }
}

template<class T>
void __sparse_mat::mread(T matArray) {
    NodePointer temp;

    for(int i = 0; i < matArray.size(); ++i){
        for(int j = 0; j < matArray[i].size(); ++j){
            if(matArray[i][j]){
                temp = new Node(i, j, matArray[i][j]);
                matNodes.push_back(temp);
            }
        }
    }
}


void __sparse_mat::mread(int rows, int cols, int num) {

    int value;
//    NodePointer * current_element_row, * current_element_col;
    NodePointer  temp;

    // first step, initialize this matrix.create the format of sparse matrix(FIRSTNODE and hdnode), also set the current col/row position
//    const int HEADER_NODE_AMOUNT = mread_initialize(rows,cols,num,current_element_row,current_element_col);

    // Add "num" nodes;
    // for(int i = 0; i < num; i++){
    //     cin>>row>>col>>value;
    //     temp = new Node(row,col,value);
    //     mread_addNode(temp,current_element_row,current_element_col);
    // }

    /*Store the answerMat node*/
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            cin>>value;
            if(value) {
                temp = new Node(i, j, value);
                matNodes.push_back(temp);
//                mread_addNode(temp, current_element_row, current_element_col);
            }
        }
    }

//    // close the matrix
//    mread_final(current_element_row,current_element_col,HEADER_NODE_AMOUNT);
//
//    delete[] current_element_col;
//    delete[] current_element_row;

}


bool nodeComp(NodePointer n1, NodePointer n2){
    if(n1->Col() < n2->Col()) return true;
    else if(n1->Col() == n2->Col()) return (n2->Row() < n2->Row());
    return false;
}

NodePointer __sparse_mat::ConstructMat() {
    if(!matNodes.size()){
        overflow_error e("Number of Matrix Nodes is 0.\nPlease use mread function before using ConstructMat");
    }

    std::sort(matNodes.begin(), matNodes.end(), nodeComp);

    NodePointer * current_element_row, * current_element_col;
    NodePointer  temp;
    const int HEADER_NODE_AMOUNT = mread_initialize(rows,cols,matNodes.size(),current_element_row, current_element_col);

    int num = matNodes.size();

    for(int i = 0; i < num; i++){
//        cout<<matNodes[i]<<endl;
        mread_addNode(matNodes[i],current_element_row,current_element_col);
    }

    // close the matrix
    mread_final(current_element_row,current_element_col,HEADER_NODE_AMOUNT);

    delete[] current_element_col;
    delete[] current_element_row;

    return FIRST_NODE;

}

deque<deque<int> > __sparse_mat::matToArray() {
    // NodePointer first = FIRST_NODE;
    ConstructMat();
    deque<deque<int> > matAry;
    NodePointer O;
    NodePointer current_hd = FIRST_NODE->Right;
    int row = 0;
    int col = 0;

    while(row < FIRST_NODE->Row()) {
        O = current_hd->Right;
        col = 0;
        deque<int> rows;
        while(col < FIRST_NODE->Col()) {
            if(O->Row() == row && O->Col() == col) {
//                printf("%d ",O->Value());
                rows.push_back(O->Value());
                O = O->Right;
            } else {
//                printf("0 ");
                rows.push_back(0);
            }

            ++col;
        }
//        printf("\n");
        ++row;
        matAry.push_back(rows);
        current_hd = O->Next;
    }
    return matAry;
}

__sparse_mat __sparse_mat::Transpose(__sparse_mat newMat) {
    NodePointer * current_row, * current_col;
    NodePointer  temp;
    const int HEADER_NODE_AMOUNT = newMat.mread_initialize(FIRST_NODE->Col(),FIRST_NODE->Row(),FIRST_NODE->Value(),current_row,current_col);

    NodePointer hdpointer = FIRST_NODE->Right; // Initially, hdpointer points to the first headernode;
    NodePointer elementptr;
    while(hdpointer != FIRST_NODE) {
        elementptr = hdpointer->Down;
        while(elementptr != hdpointer) {
            temp = new Node(elementptr->Col(),elementptr->Row(),elementptr->Value());
            newMat.mread_addNode(temp,current_row,current_col);
            elementptr = elementptr->Down;
        }
        hdpointer = hdpointer->Next;
    }
    newMat.mread_final(current_row,current_col,HEADER_NODE_AMOUNT);
    return newMat;
}


__sparse_mat __sparse_mat::Transpose() {
    int temprow;

    for(int i = 0; i < matNodes.size(); i++){
        temprow = matNodes[i]->Row();
        matNodes[i]->Row(matNodes[i]->Col());
        matNodes[i]->Col(temprow);
    }
//    ConstructMat();

    // traversal
//    NodePointer current_hd = FIRST_NODE->Right;
//    NodePointer current_col;

//    while(current_hd != FIRST_NODE){
//        current_col = current_hd->Down;
//        while (current_col != current_hd){
//            cout<<current_col<<endl;
//            current_col = current_col->Down;
//        }
//        current_hd = current_hd->Next;
//    }
//    cout<<"Transpose Finish"<<endl;
    return *this;
}

__sparse_mat __sparse_mat::operator*(__sparse_mat mat2) {
    if(FIRST_NODE->Col() != mat2.FIRST_NODE->Row()) throw ("Matrix Should be the same size");
    __sparse_mat resultMat;
    vector<NodePointer> nodes;
    NodePointer mat1_element_ptr,mat2_element_ptr;
    NodePointer hdptr1 = FIRST_NODE->Right;
    NodePointer hdptr2 = mat2.FIRST_NODE->Right;
    NodePointer temp;
    NodePointer * current_element_row, * current_element_col;
    int sum,row,col;

    if(hdptr1->Next == FIRST_NODE) {
        throw ("Link error");
    }
    while(hdptr1 != FIRST_NODE) {
        for(hdptr2 = mat2.FIRST_NODE->Right; hdptr2 != mat2.FIRST_NODE; hdptr2 = hdptr2->Next) {
            sum = 0;
            mat1_element_ptr = hdptr1->Right;
            mat2_element_ptr = hdptr2->Down;
            row = mat1_element_ptr->Row();
            col = mat2_element_ptr->Col();
            while(mat1_element_ptr != hdptr1 && mat2_element_ptr != hdptr2) {
                // cout<<mat1_element_ptr->Value()<<"   "<<mat2_element_ptr->Value()<<endl;
                if(mat1_element_ptr->Col() == mat2_element_ptr->Row()) {
                    sum += mat1_element_ptr->Value() * mat2_element_ptr->Value();
                    mat1_element_ptr = mat1_element_ptr->Right;
                    mat2_element_ptr = mat2_element_ptr->Down;
                } else if(mat1_element_ptr->Col() < mat2_element_ptr->Row()) mat1_element_ptr = mat1_element_ptr->Right;
                else  mat2_element_ptr = mat2_element_ptr->Down;
            }
            if(sum) {
                temp = new Node(row,col,sum);
                nodes.push_back(temp);
            }
        }
        hdptr1 = hdptr1->Next;
    }
    const int HEADER_NODE_AMOUNT = resultMat.mread_initialize(FIRST_NODE->Row(),mat2.FIRST_NODE->Col(),nodes.size(),current_element_row,current_element_col);
    for(int i = 0; i < nodes.size(); i++) resultMat.mread_addNode(nodes[i],current_element_row,current_element_col);
    resultMat.mread_final(current_element_row,current_element_col,HEADER_NODE_AMOUNT);
    delete[] current_element_col;
    delete[] current_element_row;
    return resultMat;
}


//void __sparse_mat::resetHeaderNode(){
//    NodePointer nIter = FIRST_NODE->Right;
//    NodePointer next;
//    while(nIter != FIRST_NODE){
//        next = nIter->Right;
//    }
//}

//__sparse_mat::~__sparse_mat() {
//    cout<<"Destructor"<<endl;
//    for(int i = 0 ; i < matNodes.size(); i++) {
//        cout<<matNodes[i]<<endl;
//    }
//
//}


#endif


//#define __matrix_unitTest__
#ifdef __matrix_unitTest__

int main() {
    int nrow,ncol,nterm;
    deque<deque<int> > twoArray;
//     SudokuSparseMat ssmat(9,9);
//
//     cout<<"Input First Matrix"<<endl;
//     cin>>nrow>>ncol>>nterm;
//    __sparse_mat answerMat(9,9,0);
//    answerMat.ConstructMat();
//    twoArray = answerMat.matToArray();
//    for(int i = 0; i < twoArray.size(); i++){
//        for(int j = 0; j < twoArray[i].size(); j++){
//            cout<<twoArray[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<"==============================="<<endl;
//    answerMat.Transpose();
//    twoArray = answerMat.matToArray();
//    for(int i = 0; i < twoArray.size(); i++){
//        for(int j = 0; j < twoArray[i].size(); j++){
//            cout<<twoArray[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<"=========================\n"<<endl;
//    answerMat.Transpose();
//    cout<<"==============================================\n\n\n\n";
//    answerMat.matToArray();
//    answerMat.Transpose();
//
//     cout<<"Input Second Matrix"<<endl;
//     cin>>nrow>>ncol>>nterm;
//     __sparse_mat mat2(nrow,ncol,nterm);
//     cout<<"mat2 Transpose"<<endl;
//     mat2.Transpose().matToArray();
//     cout<<"====================\n";
//     cout<<"mat1 * mat2transpose"<<endl;
//     (answerMat*mat2.Transpose()).matToArray();
}

#endif