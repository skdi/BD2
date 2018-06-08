// C++ program for B-Tree insertion
#include<iostream>
#include <queue>
using namespace std;
int ComparisonCount = 0;

class BTreeNode
{
    int *keys;  
    int t;      
    BTreeNode **C; 
    int n;     
    bool leaf; 
public:
    BTreeNode(int _t, bool _leaf);   
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode *search(int k); 
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; 
    int t;  
public:

    BTree(int _t)
    {
        root = NULL;  t = _t;
    }
    void traverse()
    {
        if (root != NULL) root->traverse();
    }
    BTreeNode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

BTreeNode *BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (keys[i] == k)
    {
        ComparisonCount++;
        return this;
    }
    if (leaf == true)
    {
        ComparisonCount++;
        return NULL;
    }

    return C[i]->search(k);
}


void BTree::insert(int k)
{
    if (root == NULL)
    {
        ComparisonCount++;
        root = new BTreeNode(t, true);
        root->keys[0] = k; 
        root->n = 1;  
    }
    else 
    {
        if (root->n == 2 * t - 1)
        {
            ComparisonCount++;
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
            {
                ComparisonCount++;
                i++;
            }s->C[i]->insertNonFull(k);

            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf == true)
    {
        ComparisonCount++;
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i + 1]->n == 2 * t - 1)
        {
            ComparisonCount++;
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}


void BTreeNode::splitChild(int i, BTreeNode *y){

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        ComparisonCount++;
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];

    n = n + 1;
}
void BTreeNode::traverse()
{
    std::queue<BTreeNode*> queue;
    queue.push(this);
    while (!queue.empty())
    {
        BTreeNode* current = queue.front();
        queue.pop();
        int i;
        for (i = 0; i < current->n; i++)  //*
        {
            if (current->leaf == false)  //*
            {
                ComparisonCount++;
                queue.push(current->C[i]);
            }cout << " " << current->keys[i] << endl;
        }
        if (current->leaf == false)  //*
        {
            ComparisonCount++;
            queue.push(current->C[i]);
        }
    }
}

int main()
{
    BTree t(4);
    srand(29324);
    for (int i = 0; i<10; i++)
    {
        int p = rand() % 10000;
        t.insert(p);
    }

    cout << "Traversal of the constucted tree is "<<endl;
    t.traverse();

    int k = 6;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present" << endl;

    k = 28;
    (t.search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present" << endl;

    cout << "There are " << ComparisonCount << " comparisons." << endl;
    system("pause");
    return 0;
}
