#include <iostream>
using namespace std;

class Node{
public:
    int value;
    Node *Left;
    Node *Right;
    Node *nil = NULL;
    Node *p;
    string color = "BLACK";
    Node(int value) {
        this->value = value;
        this->Left = this->nil;
        this->Right = this->nil;
        this->p = this->nil;
        this->color = "RED";
    }
};
Node *nil = NULL;

void leftRotate(Node *root, Node* x) {
    Node* y = x->Right;
    x->Right = y->Left;

    if (y->Left != NULL) {
        y->Left->p = x;
    }

    y->p = x->p;

    if (x->p == NULL) {
        root = y;
    } else if (x == x->p->Left) {
        x->p->Left = y;
    } else {
        x->p->Right = y;
    }

    y->Left = x;
    x->p = y;
}
void rightRotate(Node *root, Node* y) {
    Node* x = y->Left;
    y->Left = x->Right;

    if (x->Right != NULL) {
        x->Right->p = y;
    }

    x->p = y->p;

    if (y->p == NULL) {
        root = x;
    } else if (y == y->p->Left) {
        y->p->Left = x;
    } else {
        y->p->Right = x;
    }

    x->Right = y;
    y->p = x;
}

void insertFix(Node *root, Node *nNode){
    Node *uncle;
    while (nNode->p != NULL && nNode->p->color == "RED"){
        if(nNode->p == nNode->p->p->Left){
            uncle = nNode->p->p->Right;
            if (uncle->color == "RED"){
                nNode->p->color = "BLACK";
                uncle->color = "BLACK";
                nNode->p->p->color = "RED";
                nNode = nNode->p->p;
            }
            else{
                if(nNode==nNode->p->Right){
                    nNode = nNode->p;
                    leftRotate(root, nNode);
                }
                nNode->p->color = "BLACK";
                nNode->p->p->color ="RED";
                rightRotate(root, nNode->p->p);
            }
        }
        else{
            uncle = nNode->p->p->Left;
            if (uncle->color == "RED"){
                nNode->p->color = "BLACK";
                uncle->color = "BLACK";
                nNode->p->p->color = "RED";
                nNode = nNode->p->p;
            }
            else{
                if(nNode==nNode->p->Left){
                    nNode = nNode->p;
                    rightRotate(root, nNode);
                }
                nNode->p->color = "BLACK";
                nNode->p->p->color ="RED";
                leftRotate(root, nNode->p->p);
            }
        }
    }
    root->color = "BLACK";
}


bool exist(Node *n){
    return n !=nil;
}
void Insert(Node *root, Node *curr, int val){
    Node *parent = nil;
    while (exist(curr)){
        parent = curr;
        if(val < curr->value)
            curr=curr->Left;
        else
            curr = curr->Right;
    }
    Node *new_node=new Node(val);
    new_node->p=parent;
    if(parent == nil)
        curr=new_node;
    else if (val < parent->value )
        parent->Left = new_node;
    else parent->Right = new_node ;
    insertFix(root, new_node);
}
Node* search1(Node *n ,int val){
    if (n==NULL)
        return NULL;
    if (n->value==val)
        return n;
    return (val< n->value)? search1(n->Left, val): search1(n->Right, val);
}

Node* getMin1(Node *n){
    if (n==NULL)
        return NULL;
    if (n->Left==NULL)
        return n;
    return getMin1(n->Left);
}

Node* getMax1(Node *n){
    if (n==NULL)
        return NULL;
    if (n->Right==NULL)
        return n;
    return getMax1(n->Right);
}



void Print(Node *curr){

    if(curr==NULL){

        return;
    }
    cout<< "(";
    cout << curr->value << " (" << curr->color << ")";
    Print(curr->Left);
    Print(curr->Right);
    cout<< ")";

}

int getChildNum (Node *node){
    int count =0;
    if (exist(node->Left))
        count++;
    if(exist(node->Right))
        count++;
    return count;
}

Node* getChildOrMock(Node* node){
    return exist(node->Left)?node->Left : node->Right;
}

void transplant(Node* root, Node *toN, Node* fromN){
    if(toN==root)
        root=fromN;
    else if(toN == toN->p->Left)
        toN->p->Left=fromN;
    else
        toN->p->Right=fromN;
    fromN->p=toN->p;
}

void deleteFix(Node* root, Node *n){
    while(n != root && n->color == "BLACK"){
        Node *temp;
        if(n==n->p->Left){
            temp = n->p->Right;
            if(temp->color =="RED"){
                temp->color = "BLACK";
                n->p->color="RED";
                leftRotate(root, n->p);
                temp=n->p->Right;
            }
            if(temp->Left->color == "BLACK" && temp->Right->color=="BLACK"){
                temp->color = "RED";
                n = n->p;
            }
            else{
                if(temp->Right->color == "BLACK"){
                    temp->Left->color = "BLACK";
                    temp->color = "RED";
                    rightRotate(root, temp);
                    temp = n->p->Right;
                }
                temp->color = n->p->color;
                n->p->color = "BLACK";
                temp->Right->color = "BLACK";
                leftRotate(root, n->p) ;
                n = root;
            }
        }
        else{
            temp = n->p->Left;
            if(temp->color =="RED"){
                temp->color = "BLACK";
                n->p->color="RED";
                rightRotate(root, n->p);
                temp = n->p->Left;
            }
            if(temp->Left->color == "BLACK" && temp->Right->color=="BLACK"){
                rightRotate(root, n->p);
                temp = n->p->Left;
            }
            else{
                if(temp->Left->color == "BLACK"){
                    temp->Right->color = "BLACK";
                    temp->color = "RED";
                    leftRotate(root, temp);
                    temp = n->p->Left;
                }
                temp->color = n->p->color;
                n->p->color = "BLACK";
                temp->Left->color = "BLACK";
                rightRotate(root, n->p) ;
                n = root;
            }
        }
    }
    n->color="BLACK";
}

void remove(Node* root, int x) {
    Node *delVal = search1(root, x);
    string delColor = delVal->color;
    Node *child;
    if(getChildNum(delVal)<2){
        child = getChildOrMock(delVal);
        transplant(root, delVal, child);
    }
    else{
        Node *min= getMin1(delVal->Right);
        delVal->value = min->value;
        delColor=min->color;
        child= getChildOrMock(min);
        transplant(root, min, child);
    }
    if(delColor == "Black")
        deleteFix(root, child);
}

class RedBlackTree{
private:
    Node *root;
    Node nil = NULL;
public:

    RedBlackTree() {
        this->root=NULL;

    }

    void insert(int val){
        if(this->root == NULL){
            this->root = new Node(val);
            root->color = "BLACK";
        }else{
            Insert(this->root, this->root, val);
        }

    }
    bool search(int val){
        return search1(this->root, val);
    }
    void printTree(){
        Print(this->root);
        cout<<endl;
    }
    void deleteNode(int x){
        remove(root, x);
    }



};

