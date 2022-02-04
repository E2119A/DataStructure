#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <windows.h>
#include <random>
#include <math.h>
using namespace std;



class AVLT
{
    struct node
    {
        int data;
        node* left;
        node* right;
        int height;
    };

    node* root;

    node* Empty(node* t)
    {
        if(t != nullptr)
        {
            Empty(t->left);
            Empty(t->right);
            delete t;
        }
        return nullptr;
    }

    node* _find(node* tree, int el)
    {
        if(tree == nullptr)//if tree is empty or no element found
            return nullptr;
        else if(el < tree->data)
            return _find(tree->left, el);
        else if(el > tree->data)
            return _find(tree->right, el);
        else//if el equals to root data in current tree
            return tree;
    }

    int getHeight(node* tree)
    {
        return (tree == nullptr ? -1 : tree->height);
    }

    node* leftRotateOnce(node* &tree)
    {
        node* newroot = tree->right;
        tree->right = newroot->left;
        newroot->left = tree;

        tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
        newroot->height = max(getHeight(newroot->right), tree->height) + 1;
        return newroot;
    }

    node* rightRotateOnce(node* &tree)
    {
        node* newroot = tree->left;
        tree->left = newroot->right;
        newroot->right = tree;

        tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
        newroot->height = max(getHeight(newroot->left), tree->height) + 1;
        return newroot;
    }

    node* leftRotateTwice(node* &tree)
    {
        tree->right = rightRotateOnce(tree->right);
        return leftRotateOnce(tree);
    }

    node* rightRotateTwice(node* &tree)
    {
        tree->left = leftRotateOnce(tree->left);
        return rightRotateOnce(tree);
    }

    node* _insert(node* tree, int el)
    {
        if(tree == nullptr)//assuming tree is root
        {
            tree = new node;
            tree->data = el;
            tree->left = nullptr;
            tree->right = nullptr;
            tree->height = 0;
        }
        else if(el < tree->data)
        {
            tree->left = _insert(tree->left, el);
            if(getHeight(tree->left) - getHeight(tree->right) == 2)
            {
                if(el < tree->left->data)
                    tree = rightRotateOnce(tree);
                else
                    tree = rightRotateTwice(tree);
            }
        }
        else if(el > tree->data)
        {
            tree->right = _insert(tree->right, el);
            if(getHeight(tree->right) - getHeight(tree->left) == 2)
            {
                if(el > tree->right->data)
                    tree = leftRotateOnce(tree);
                else
                    tree = leftRotateTwice(tree);
            }
        }

        tree->height = max(getHeight(tree->left), getHeight(tree->right))+1;
        return tree;
    }


    void displInOrder(node* tree)
    {
        if(tree == nullptr)
            return;
        displInOrder(tree->left);
        cout << "(" << tree->data << ", " << tree->height << ") ";
        displInOrder(tree->right);
    }

public:

    AVLT()
    {
        root = nullptr;
    }

    ~AVLT()
    {
        root = Empty(root);
    }

    void insertAVLT(int el)
    {
        root = _insert(root, el);
    }

    void searchAVLT(int el)
    {
        auto found = _find(root, el);
        /*
        if(found  != nullptr)
        {
            cout<<"exists, height "<< found->height <<endl;
        }
        else
            cout<<"not exists"<<endl;
            */
    }

    void displayAVLT()
    {
        displInOrder(root);
        cout<<endl;
    }


};

class BST
{
    struct node
    {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* Empty(node* t)
    {
        if(t != NULL)
        {
            Empty(t->left);
            Empty(t->right);
            delete t;
        }
        return NULL;
    }

    node* _find(node* tree, int el)
    {
        if(tree == NULL)//if tree is empty or no element found
            return NULL;
        else if(el < tree->data)
            return _find(tree->left, el);
        else if(el > tree->data)
            return _find(tree->right, el);
        else//if el equals to root data in current tree
            return tree;
    }

    node* _insert(node* tree, int el)
    {
        if(tree == NULL)//if found place to insert
        {
            tree = new node;
            tree->data = el;
            tree->left = NULL;
            tree->right = NULL;
        }
        else if(el < tree->data)
            tree->left = _insert(tree->left, el);
        else if(el > tree->data)
            tree->right = _insert(tree->right, el);

        return tree;
    }

    void displInOrder(node* tree)
    {
        if(tree == NULL)
            return;
        displInOrder(tree->left);
        cout << tree->data << " ";
        displInOrder(tree->right);
    }

public:

    BST()
    {
        root = NULL;
    }

    ~BST()
    {
        root = Empty(root);
    }

    void insertBST(int el)
    {
        root = _insert(root, el);
    }

    void searchBST(int el)
    {
        auto found = _find(root, el);
        /*
        if(found != NULL)
            cout<<"exists"<<endl;
        else
            cout<<"not exists"<<endl;
            */
    }

    void displayBST()
    {
        displInOrder(root);
        cout<<endl;
    }
};



int main()
{
    int type_of_tree;
    //adequate sizes are from 5 to 100000
    int n;
    int m;

    //number of program iterations
    int k = 20;

    double interval_gomothety = 0.5;


    int times = 1000;
    int64_t start_t;
    int64_t end_t;
    int64_t taken;


    BST bsTree;
    AVLT avlTree;

    vector<int> elements;
    vector<int> elements_to_search;

    vector<double> BSTreeTimes(k,0);
    vector<double> AVLTreeTimes(k,0);
    vector<double> BSTreeInsTimes(k,0);
    vector<double> AVLTreeInsTimes(k,0);

    //both tree initialization

    while(type_of_tree != 1)
    {
        cout<<"Press 1 to start, else to exit program): "<<endl;
        cin>>type_of_tree;
        if(type_of_tree == 1)
        {
            cout<<"Enter the size of the tree: "<<endl;
            cin>>n;
            //number of searches
            //min value is 2 and max value is bounded by sqrt(n)
            //if n == 100000 then m = 79 + 2
            //2 grands us hope that we will search at least once for existing element and for non-existing
            m = 2 + floor(n/4); //here we chose elements what we will find
            elements.resize(n);
            elements_to_search.resize(m);
        }

        else
        {
            cout<<"Thank you."<<endl;
            return 0;
        }



        //search part

        double freq = 0.0;
        LARGE_INTEGER x,y;
        QueryPerformanceFrequency(&x);
        freq = x.QuadPart/1.0;
        LARGE_INTEGER seed;
        QueryPerformanceCounter(&seed);
        mt19937 gen(seed.QuadPart);

        //interval = (-0.5*n, 0.5*n) grants very hight chance that when choosing random numbers to search we will get existing numbers from array.
        //interval = (-1*n, 1*n) grant lesser chance so array of elements to search will have less elements from our elements array
        //and so on
        uniform_int_distribution<> dis(-floor(interval_gomothety * n), floor(interval_gomothety * n));

        for (int j = 0; j < k; j++)
        {
            cout<<"Iteration "<< j<<" started"<<endl;
            cout<<m<<endl;

            //generate tree
            if(type_of_tree == 1)
            {

                for(int i = 0; i<n; i++)
                {
                    int current = dis(gen);
                    elements[i] = current;
                }
                QueryPerformanceCounter(&x);
                for(int i = 0; i<n; i++)
                {
                    bsTree.insertBST(elements[i]);
                }
                QueryPerformanceCounter(&y);
                start_t = x.QuadPart;
                end_t = y.QuadPart;

                taken = end_t - start_t;
                BSTreeInsTimes[j] = taken;
                BSTreeInsTimes[j] = BSTreeInsTimes[j] / freq / times;


                QueryPerformanceCounter(&x);
                for(int i = 0; i<n; i++)
                {
                    avlTree.insertAVLT(elements[i]);
                }
                QueryPerformanceCounter(&y);
                start_t = x.QuadPart;
                end_t = y.QuadPart;

                taken = end_t - start_t;
                AVLTreeInsTimes[j] = taken;
                AVLTreeInsTimes[j] = AVLTreeInsTimes[j] / freq / times;
                cout<<"Trees generated"<<endl;
            }
            //choosing elements to search
            for(int i = 0; i < m; i++)
            {
                if(i == 0)//chose at least one existing
                {
                    elements_to_search[i] = elements[0];
                    // cout<<i<<endl;
                }
                else if(i == 1)//chose at least one non-existing
                {
                    elements_to_search[i] = interval_gomothety * n + 1;
                    // cout<<i<<endl;
                }
                else//chose randomly existing or randomly non-existing element from elements
                {
                    elements_to_search[i] = dis(gen);
                    // cout<<i<<endl;
                }

            }


            cout<<"Search in BST started in iteration "<<j<<endl;
            QueryPerformanceCounter(&x);
            //searching for elements in BS tree
            for(int i = 0; i < m; i++)
            {
                bsTree.searchBST(elements_to_search[i]);
            }
            QueryPerformanceCounter(&y);
            start_t = x.QuadPart;
            end_t = y.QuadPart;

            taken = end_t - start_t;
            BSTreeTimes[j] = taken;
            BSTreeTimes[j] = BSTreeTimes[j] / freq / times;
            cout<<"Search in BST finished in iteration "<< j<<endl;


            cout<<"Search in AVLT started in iteration "<< j<<endl;
            QueryPerformanceCounter(&x);
            //searching for elements in AVL tree
            for(int i = 0; i < m; i++)
            {
                avlTree.searchAVLT(elements_to_search[i]);
            }
            QueryPerformanceCounter(&y);
            start_t = x.QuadPart;
            end_t = y.QuadPart;

            taken = end_t - start_t;
            AVLTreeTimes[j] = taken;
            AVLTreeTimes[j] = AVLTreeTimes[j] / freq / times;
            cout<<"Search in AVLT finished in iteration "<< j<<endl;


            cout<<"Iteration "<< j<<" finished"<<endl;


        }
        cout<< m <<" elements to search chosen."<<endl;

        //result of this program is
        //n - size of tree
        //t1 = sum(time_to_search_BST_k)/k
        //t2 = sum(time_to_search_AVLT_k)/k
        double t1 = 0;
        for (auto& el : BSTreeTimes)
            t1 += el;
        cout<<"BS Tree: size = "<< n <<", average duration of search time = "<< t1 <<endl;

        double t2 = 0;
        for (auto& el : AVLTreeTimes)
            t2 += el;
        cout<<"AVL Tree: size = "<< n <<", average duration of search time = "<< t2 <<endl;

        double t3 = 0;
        for (auto& e3 : BSTreeInsTimes)
            t3 += e3;
        cout<<"BS Tree: size = "<< n <<", average duration of insertion time = "<< t3 <<endl;

        double t4 = 0;
        for (auto& e4 :AVLTreeInsTimes)
            t4 += e4;
        cout<<"AVL Tree: size = "<< n <<", average duration of insertion time = "<< t4 <<endl;

    }





    return 0;
}
