#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

MovieTree::MovieTree(std::string filename)
{
    int index = 0;
    head=NULL;
    root=NULL;
    recommend="";
    ifstream inFile(filename);
    int counter = 0;
    while(inFile)
    {
        string data;
        string Ranking;
        string movieTitle;
        string Year;
        string Quant;
        if(!getline(inFile,data))
        {
            break;
        }

        istringstream ss(data);
        while(ss)
        {
            if(!getline(ss,data,','))
            {
                break;
            }
            counter++;
            stringstream ss(data);
            switch(counter%4)
            {
            case 1:
            {
                Ranking = data;
                break;
            }
            case 2:
            {
                movieTitle = data;
                break;
            }
            case 3:
            {
                Year = data;
                break;
            }
            case 0:
            {
                Quant = data;
                MovieTree::addMovieNode(atoi(Ranking.c_str()), movieTitle, atoi(Year.c_str()), atoi(Quant.c_str()), index);
                index = index +1;
                break;
            }
            }
        }
    }
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

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity, int counter)
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
    node->userRank=-1;
    IMDBnodeOrder[counter] = *node;
    allNodes[numberOfMovies]=node;
    numberOfMovies++;
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
    deletedNodeArray[indexCount] = *node;
    indexCount = indexCount +1;
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
    deletedNodeArray[indexCount] = *node;
    indexCount = indexCount +1;
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
            if(node->parent->leftChild == node)
            {
                node->parent->leftChild = Right;
            }
            else
            {
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
            if(node->parent->leftChild == node)
            {
                node->parent->leftChild = newMovie;
                newMovie->parent = node->parent;
            }
            if(node->parent->rightChild == node)
            {
                node->parent->rightChild = newMovie;
                newMovie->parent = node->parent;
            }
        }
    }
    numberOfMovies--;
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
            return;
        }
    }
    if(node == NULL)
    {
        bool deletedPrev = false;
        for(int i = 0; i <= indexCount; i++)
        {
            if(deletedNodeArray[i].title.compare(title) == 0)
            {
                deletedPrev = true;
                addMovieNode(deletedNodeArray[i].ranking, deletedNodeArray[i].title, deletedNodeArray[i].year, 1, deletedNodeArray[i].ranking);
            }
        }
        if(deletedPrev == false)
        {
            addMovieNode(-1, title, year, 1, endofArray);
            endofArray = endofArray +1;
        }
    }
}

void MovieTree::rankMovie(std::string title,int rank)
{
    MovieNode *node=search(title,root);
    if (node!=NULL)
    {
        if(node->ranks +1 > 1)
        {
            linkedList *temp = hashTable[node->userRank - 1];
            while(temp->node->title.compare(title) != 0)
            {
                temp = temp->next;
            }
            if(temp->next != NULL && temp->prev != NULL)
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
            }
            if(temp->next == NULL && temp->prev == NULL)
            {
                hashTable[temp->node->userRank - 1] = NULL;
            }
            if(temp->next == NULL && temp->prev != NULL)
            {
                temp->prev->next = NULL;
            }
            if(temp->next != NULL && temp->prev == NULL)
            {
                temp->next->prev = NULL;
                hashTable[temp->node->userRank - 1] = temp->next;
            }
            delete temp;
        }
        int ranka=((node->ranks*node->userRank)+rank)/(node->ranks+1);
        node->ranks++;
        node->userRank=ranka;
        linkedList *newNode = new linkedList;
        newNode->node = node;
        newNode->prev = NULL;
        newNode->next = NULL;
        if(hashTable[ranka - 1] == NULL)
        {
            hashTable[ranka - 1] = newNode;
        }
        else
        {
            linkedList *temp = hashTable[ranka - 1];
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    else
    {
        cout<<"Movie not found."<<endl;
    }
}

MovieNode *MovieTree::search(std::string title,MovieNode *node)
{
    if (node!=NULL)
    {
        if (node->title==title)
        {
            return node;
        }
        if (title.compare(node->title)<0)
        {
            return search(title,node->leftChild);
        }
        else
        {
            return search(title,node->rightChild);
        }
    }
    else
    {
        return NULL;
    }
}

void MovieTree::printMoviesByUser()
{
    linkedList *temp = new linkedList;
    bool noElements = true;
    for(int i = 9; i >= 0; i--)
    {
        if(hashTable[i] != NULL)
        {
            noElements = false;
            temp = hashTable[i];
            while(temp != NULL)
            {
                cout << "Rank: "<<temp->node->userRank<<" Title: "<<temp->node->title << endl;
                temp = temp->next;
            }
        }
    }
    if(noElements)
    {
        cout << "empty" << endl;
    }
}

void MovieTree::printMoviesByIMDB()
{
    for(int i = 0; i < endofArray; i++)
    {
        cout <<IMDBnodeOrder[i].ranking<<": "<< IMDBnodeOrder[i].title <<endl;
    }
}

void MovieTree::rentRandomMovie()
{
    int a=rand() % numberOfMovies;
    cout<<a<<endl;
    MovieNode *node=allNodes[a];
    rentMovie(node->title);
}

void MovieTree::recommendMovie(std::string title)
{
    recommend=title;
}

void MovieTree::rentRecommended()
{
    if (recommend!=""){
        rentMovie(recommend);
    }
    else{
        cout<<"No Movie Recommended."<<endl;
    }
}
void MovieTree::printMoviesByYear(int yr){
    printMoviesByYear(yr,root);

}
void MovieTree::printMoviesByYear(int yr, MovieNode *temp){
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)
  {
      printMoviesByYear(yr,node->leftChild);
  }
  if(node->year==yr){
      cout<< "Movie: " << node->title << " " << node->year << endl;
  }

  if(node->rightChild != NULL)
  {
      printMoviesByYear(yr,node->rightChild);
  }
}
void MovieTree::findOldestMovie(){
  findOldestMovie(root);
  cout<<"Oldest Movie: "<<oldest->title<<" "<<oldest->year<<endl;
}
void MovieTree::findOldestMovie(MovieNode *temp){
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)
  {
      findOldestMovie(node->leftChild);
  }
  if(oldest==NULL){
      oldest = node;
  }
  if(node->year < oldest->year && oldest!=NULL){
      oldest=node;
  }

  if(node->rightChild != NULL)
  {
      findOldestMovie(node->rightChild);
  }
}
void MovieTree::findNewestMovie(){
  findNewestMovie(root);
  cout<<"Newest Movie: "<<newest->title<<" "<<newest->year<<endl;
}
void MovieTree::findNewestMovie(MovieNode *temp){
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)
  {
      findNewestMovie(node->leftChild);
  }
  if(newest==NULL){
      newest=node;
  }
  if(node->year > newest->year && newest!=NULL){
      newest=node;
  }

  if(node->rightChild != NULL)
  {
      findNewestMovie(node->rightChild);
  }
}
