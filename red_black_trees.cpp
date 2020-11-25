#include<bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK}; 
  
struct Node 
{ 
    int data; 
    bool color; 
    Node *left, *right, *parent; 
  
    // Constructor 
    Node(int data) 
    { 
       this->data = data; 
       left = right = parent = NULL; 
       this->color = RED; 
    } 
}; 

class RBTree 
{ 
private: 
    Node *root; 
protected: 
    void rotateLeft(Node *&, Node *&); 
    void rotateRight(Node *&, Node *&); 
    void fixViolation(Node *&, Node *&); 
public: 
    // Constructor 
    RBTree() { root = NULL; } 
    void insert(const int &n); 
    void inorder(); 
    void levelorder();
}; 

// A recursive function to do inorder traversal 
void inorderHelper(Node *root) 
{ 
    if (root == NULL) 
        return; 
  
    inorderHelper(root->left); 
    cout << root->data << "  "; 
    inorderHelper(root->right); 
} 

void levelorderHelper(Node *root) 
{ 
    if (root == NULL) 
        return; 
  
    std::queue<pair<Node *,int>> q; 
    q.push({root,0});
    int pl=0; 
    int l;
    while (!q.empty()) 
    { 
        Node *temp = q.front().first;
        l=q.front().second;
        if(l!=pl)cout<<endl;
        cout << temp->data << " ";
        if(temp->color==RED)cout<<"RED   ";
        else cout<<"BCK   "; 
        q.pop(); 
  
        if (temp->left != NULL) 
            q.push({temp->left,l+1}); 
  
        if (temp->right != NULL) 
            q.push({temp->right,l+1});
        pl=l; 
    } 

    cout<<endl;
} 

Node* BSTInsert(Node* root, Node *pt) 
{ 
    if (root == NULL) 
       return pt; 
  
    if (pt->data < root->data) 
    { 
        root->left  = BSTInsert(root->left, pt); 
        root->left->parent = root; 
    } 
    else if (pt->data > root->data) 
    { 
        root->right = BSTInsert(root->right, pt); 
        root->right->parent = root; 
    } 
  
    return root; 
} 

void RBTree::rotateLeft(Node *&root, Node *&pt) 
{ 
    Node *pt_right = pt->right; 
  
    pt->right = pt_right->left; 
  
    if (pt->right != NULL) 
        pt->right->parent = pt; 
  
    pt_right->parent = pt->parent; 
  
    if (pt->parent == NULL) 
        root = pt_right; 
  
    else if (pt == pt->parent->left) 
        pt->parent->left = pt_right; 
  
    else
        pt->parent->right = pt_right; 
  
    pt_right->left = pt; 
    pt->parent = pt_right; 
} 

void RBTree::rotateRight(Node *&root, Node *&pt) 
{ 
    Node *pt_left = pt->left; 
  
    pt->left = pt_left->right; 
  
    if (pt->left != NULL) 
        pt->left->parent = pt; 
  
    pt_left->parent = pt->parent; 
  
    if (pt->parent == NULL) 
        root = pt_left; 
  
    else if (pt == pt->parent->left) 
        pt->parent->left = pt_left; 
  
    else
        pt->parent->right = pt_left; 
  
    pt_left->right = pt; 
    pt->parent = pt_left; 
} 




void RBTree::fixViolation(Node *&root, Node *&pt) 
{ 
    Node *parent_pt = NULL; 
    Node *grand_parent_pt = NULL; 
  
    while ((pt != root) && (pt->color != BLACK) && 
           (pt->parent->color == RED)) 
    { 
  
        parent_pt = pt->parent; 
        grand_parent_pt = pt->parent->parent; 
  
        //Left cases
        if (parent_pt == grand_parent_pt->left) 
        { 
  
            Node *uncle_pt = grand_parent_pt->right; 
  
            //case 1
            //RED uncle 
            //only recoloring
            if (uncle_pt != NULL && uncle_pt->color ==  
                                                   RED) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
  
            //BLACK uncle
            else
            { 
                //case 2
                //left right case
                //2 rotations 1 recoloring
                //left rotaion to get to left left case
                //right rotation to solve left left case
                if (pt == parent_pt->right) 
                { 
                    rotateLeft(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
                //case 3
                //left left case
                //1 rotation 1 recoloring
                //left rotation 
                rotateRight(root, grand_parent_pt); 
                swap(parent_pt->color,  
                           grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 

        //RIGHT cases
        else
        { 
            Node *uncle_pt = grand_parent_pt->left; 
  
            //case 1
            //RED uncle
            //only recoloring
            if ((uncle_pt != NULL) && (uncle_pt->color ==  
                                                    RED)) 
            { 
                grand_parent_pt->color = RED; 
                parent_pt->color = BLACK; 
                uncle_pt->color = BLACK; 
                pt = grand_parent_pt; 
            } 
            else
            { 
               //case 2
               //Right -left case
               //2 rotations 1 recoloring
               //right rotate to get right-right case
               //then left rotate to solve right-right case 
                if (pt == parent_pt->left) 
                { 
                    rotateRight(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
                //case 3
                //Right- Right case
                //1 rotation 1 recoloring
                rotateLeft(root, grand_parent_pt); 
                swap(parent_pt->color,  
                         grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
    } 
  
    root->color = BLACK; 
} 

void RBTree::inorder()     {  inorderHelper(root);} 
void RBTree::levelorder()     {  levelorderHelper(root);} 

void RBTree::insert(const int &data) 
{ 
    Node *pt = new Node(data); 
    root = BSTInsert(root, pt); 
    fixViolation(root, pt); 
} 
  
  
// Driver Code 
int main() 
{ 
    RBTree tree; 
    int x;
    while(true){
        cout<<" Enter element to be inserted or -1 to stop : ";
        cin>>x;
        if(x==-1)break;
        else {
            tree.insert(x);
            tree.levelorder();
        }
    }
  
    cout << "Inoder Traversal of Created Tree\n"; 
    tree.inorder(); 
  
    
  
    return 0; 
} 
  
 

  