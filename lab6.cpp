#include<iostream>
#include<stdio.h>

using namespace std;

class BTreeNode{

    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

    public:
        BTreeNode(bool _leaf,int _t);
        void traverse();
        BTreeNode *search(int k);
        void insertNonFull(int k);
        void splitChild(int i, BTreeNode *y);
        friend class BTree;
};

class BTree{
    int t;
    BTreeNode *root;
    public:
        BTree(int _t)
        {
            root=NULL;
            t=_t;
        }

        void traverse()
        {
            if(root==NULL)cout<<"Empty!!"<<endl;
            else root->traverse();
        }

        void insert(int k); 
};

void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new BTreeNode(true,t);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(false,t);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

void BTreeNode::traverse()
{

    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (leaf == false)
        C[i]->traverse();
}

BTreeNode::BTreeNode(bool _leaf,int _t)
{
    t=_t;
    keys = new int[2*t -1]; 
    C = new BTreeNode*[2*t];
    leaf=_leaf;
    n=0;
}

void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;
    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i,BTreeNode *y)
{
    //root=present node
    //y= child to be split and roots child

    //create a new node z with t-1 nodes
    BTreeNode *z = new BTreeNode(y->leaf,t);
    z->n = t - 1;


    //transfer ys last t-1 keys to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        //transfer ys last t kids to z it its not leaf
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    //now y is left with t-1 
    y->n = t - 1;

    //shift root's child and keys right from i so that we make space for new node
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    //insert new node
    keys[i] = y->keys[t - 1];
    n = n + 1;
}


int main()
{
    int min_range;
    cout<<"Enter the minimun range of the B Tree:  ";
    cin>>min_range;
    BTree t(min_range); 
    cout << "Enter number of nodes to be inserted: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter node value " << i + 1 << " : ";
        int node;
        cin >> node;
        t.insert(node);
        cout << "inorder of tree is \n";
        t.traverse();
        cout << endl;
    }

    return 0;
}