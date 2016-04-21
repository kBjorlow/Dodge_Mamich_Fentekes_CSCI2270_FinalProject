#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::string;
using std::endl;
MovieTree::MovieTree()
{
    //ctor
}

MovieTree::~MovieTree()
{
    DeleteAll(root);
}
void MovieTree::printMovieInventory()
{
    printMovieInventory(root);
    return;
}
void MovieTree::printMovieInventory(MovieNode* temp)
{
    if(temp == NULL)
    {
        temp = root;
    }
    MovieNode *node = temp;
    if(node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild);
    }
    cout<< "Movie: " << node->title << " " << node->quantity << endl;
    if(node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild);
    }
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    MovieNode *temp = new MovieNode;
    MovieNode *Parent = new MovieNode;
    MovieNode *node = new MovieNode;
    node->ranking = ranking;
    node->title = title;
    node->year = releaseYear;
    node->quantity = quantity;
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;
    if(root == NULL)
    {
        root = node;
    }
    else
    {
        temp = root;
        Parent = root;
        while(temp != NULL)
        {
            Parent = temp;
            if(node->title.compare(temp->title) < 0)//goes left
            {
                temp = temp->leftChild;
            }
            else
            {
                temp = temp->rightChild;
            }
        }
        if(node->title.compare(Parent->title) < 0)
        {
            Parent->leftChild = node;
            node->parent = Parent;
        }
        else
        {
            Parent->rightChild = node;
            node->parent = Parent;
        }
    }
}


void MovieTree::findMovie(string title)
{
    MovieNode *node;
    node = root;
    while(node != NULL)
    {
        if(node->title.compare(title) > 0)
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)
        {
            node = node->rightChild;
        }
        else
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << node->ranking << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year:" << node->year << endl;
            cout << "Quantity:" << node->quantity << endl;
            break;
        }
    }
    if(node == NULL)
    {
        cout << "Movie not found." << endl;

    }
}


void MovieTree::rentMovie(string title)
{
    MovieNode *node;
    node = root;
    while(node != NULL)
    {
        if(node->title.compare(title) > 0)
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)
        {
            node = node->rightChild;
        }
        else
        {
            //node->quantity = node->quantity -1;
            if(node->quantity == 0)
            {
                cout << "Movie out of stock." << endl;
                return;
            }
            if(node->quantity > 0)
            {
                node->quantity = node->quantity- 1;
                cout << "Movie has been rented." << endl;
                cout << "Movie Info:" << endl;
                cout << "===========" << endl;
                cout << "Ranking:" << node->ranking << endl;
                cout << "Title:" << node->title << endl;
                cout << "Year:" << node->year << endl;
                cout << "Quantity:" << node->quantity << endl;
                if(node->quantity == 0)
                {
                    deleteMovieNode(node->title);
                    return;
                }
            }
            break;
        }
    }
    if(node == NULL)
    {
        cout << "Movie not found." << endl;

    }


}

int MovieTree::countMovieNodes()
{
    int *cPtr = new int;
    *cPtr = 0;
    countMovieNodes(root, cPtr);
    return *cPtr;
}

void MovieTree::countMovieNodes(MovieNode *temp, int *cPtr)
{
    if(temp == NULL)
    {
        temp = root;
    }
    MovieNode *node = temp;
    if(node->leftChild != NULL)
    {
        countMovieNodes(node->leftChild, cPtr);
    }
    *cPtr = *cPtr +1;
    if(node->rightChild != NULL)
    {
        countMovieNodes(node->rightChild, cPtr);
    }
}

void MovieTree::DeleteAll(MovieNode * node)
{
    indexCount = indexCount +1;
    deletedNodeArray[indexCount] = node;
    if(node->leftChild != NULL)
    {
        DeleteAll(node->leftChild);
    }
    if(node->rightChild != NULL)
    {
        DeleteAll(node->rightChild);
    }
    cout << "Deleting: " << node->title <<endl;
    delete node;
}

void MovieTree::deleteMovieNode(string title)
{
    MovieNode *node;
    node = root;
    while(node != NULL)
    {
        if(node->title.compare(title) > 0)
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)
        {
            node = node->rightChild;
        }
        else
        {
            break;
        }
    }
    if(node == NULL)
    {
        cout << "Movie not found." << endl;
        return;
    }
    if(node->leftChild == NULL && node->rightChild == NULL)
    {
        if(node->parent->leftChild == node)
        {
            node->parent->leftChild = NULL;
            delete node;
            return;
        }
        else
        {
            node->parent->rightChild = NULL;
            delete node;
            return;
        }
    }
    else if(node->leftChild != NULL && node->rightChild == NULL)
    {
        MovieNode *x = new MovieNode;
        x = node->leftChild;
        if(node->parent->leftChild == node)
        {
            node->parent->leftChild = x;
            x->parent = node->parent;
        }
        else
        {
            node->parent->rightChild = x;
            x->parent = node->parent;
        }
        delete node;
        return;
    }
    else if(node->rightChild != NULL && node->leftChild == NULL)
    {
        MovieNode *x = new MovieNode;
        x = node->rightChild;
        if(node->parent->leftChild == node)
        {
            node->parent->leftChild = x;
            x->parent = node->parent;
        }
        else
        {
            node->parent->rightChild = x;
            x->parent = node->parent;
        }
        delete node;
        return;
    }
    else if(node->rightChild != NULL && node->leftChild != NULL)
    {
        MovieNode *newMovie = new MovieNode;
        MovieNode *Right = new MovieNode;
        Right = node->rightChild;
        newMovie = treeMinimum(node->rightChild);
        if(newMovie == Right)
        {
            if(node->parent->leftChild == node)
            {
                node->parent->leftChild = newMovie;
            }
            else
            {
                node->parent->rightChild = newMovie;
            }
            newMovie->parent = node->parent;
            newMovie->leftChild = node->leftChild;
            delete node;
            return;
        }
        if(newMovie == NULL)
        {
            Right->parent = node->parent;
            node->leftChild->parent = Right;
            if(node->parent->leftChild == node){
                node->parent->leftChild = Right;
            }
            else{
                node->parent->rightChild = Right;
            }
            delete node;
        }
        else
        {
            if(newMovie->rightChild != NULL)
            {
                newMovie->rightChild->parent = newMovie->parent;
                newMovie->parent->leftChild = newMovie->rightChild;
            }
            node->leftChild->parent = newMovie;
            if(node->parent == NULL)
            {
                newMovie->leftChild = root->leftChild;
                newMovie->rightChild = root->rightChild;
                newMovie->parent = NULL;
                delete node;
                root = newMovie;
                return;
            }
            if(node->parent->leftChild == node){
                node->parent->leftChild = newMovie;
                newMovie->parent = node->parent;
            }
            if(node->parent->rightChild == node){
                node->parent->rightChild = newMovie;
                newMovie->parent = node->parent;
            }

        }


    }


}

MovieNode* MovieTree::treeMinimum(MovieNode *node)
{
    //passing in right child of node being deleted
    if(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;
}

void MovieTree::returnMovie(string title, int year)
{
    MovieNode *node;
    node = root;
    while(node != NULL)
    {
        if(node->title.compare(title) > 0)
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)
        {
            node = node->rightChild;
        }
        else//node found
        {
            node->quantity = node->quantity + 1;
        }
    }
    if(node == NULL)
    {
        bool deletedPrev = false;
        MovieNode *newMovie = new MovieNode;
        for(int i = 0; i <= indexCount; i++)
        {
            if(deletedNodeArray[i].title.compare(title) == 0)
            {
                deletedPrev = true;
                addMovieNode(deletedNodeArray[i].ranking, deletedNodeArray[i].title, deletedNodeArray[i].year, 1);
            }
        }
        if(deletedPrev == false)
        {
            addMovieNode(-1, title, year, 1);
        }
    }
}
