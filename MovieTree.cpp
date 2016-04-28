/*
Adam Dodge, Rachel Mamich, and Nick Fentekes
Final Project
Driver Function
*/

#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

MovieTree::MovieTree(std::string filename)//constructor to create tree
{
    int index = 0;
    head=NULL;
    root=NULL;
    recommend="";//intitialization
    ifstream inFile(filename);//opens file
    int counter = 0;
    while(inFile)
    {
        string data;//strings for creating node
        string Ranking;
        string movieTitle;
        string Year;
        string Quant;
        if(!getline(inFile,data))//if no data
        {
            break;
        }
        istringstream ss(data);//creates stringstream to split data
        while(ss)
        {
            if(!getline(ss,data,','))//if no data
            {
                break;//exit while loop
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
                MovieTree::addMovieNode(atoi(Ranking.c_str()), movieTitle, atoi(Year.c_str()), atoi(Quant.c_str()), index);//adds node
                index = index +1;
                break;
            }
            }
        }
    }
}

MovieTree::~MovieTree()//destructor deletes all nodes in tree
{
    DeleteAll(root);
}

void MovieTree::printMovieInventory()//calls private function with root
{
    printMovieInventory(root);
    return;
}

void MovieTree::printMovieInventory(MovieNode* temp)//private function to print all nodes alphabetically
{
    if(temp == NULL)
    {
        temp = root;
    }
    MovieNode *node = temp;
    if(node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild);//calls function for left child
    }
    cout<< "Movie: " << node->title << " " << node->quantity << endl;//prints
    if(node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild);//calls function for right child
    }
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity, int counter)//adds movie node to tree
{
    MovieNode *temp = new MovieNode;
    MovieNode *Parent = new MovieNode;
    MovieNode *node = new MovieNode;//initialization of node
    node->ranking = ranking;//initialization of node properties
    node->title = title;
    node->year = releaseYear;
    node->quantity = quantity;
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->userRank=-1;
    IMDBnodeOrder[counter] = *node;//for printing by IMDb
    allNodes[numberOfMovies]=node;//for random movies function
    numberOfMovies++;
    if(root == NULL)
    {
        root = node;
    }
    else//finds place for node
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

void MovieTree::findMovie(string title)//finds movie in tree
{
    MovieNode *node;//initialization
    node = root;
    while(node != NULL)
    {
        if(node->title.compare(title) > 0)//go left
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)//go right
        {
            node = node->rightChild;
        }
        else
        {
            cout << "Movie Info:" << endl;//print statements
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

void MovieTree::rentMovie(string title)//rents movie from tree
{
    MovieNode *node;
    node = root;
    while(node != NULL)//finds node
    {
        if(node->title.compare(title) > 0)//go left
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)//go right
        {
            node = node->rightChild;
        }
        else
        {
            if(node->quantity == 0)//if no more movies left
            {
                cout << "Movie out of stock." << endl;
                return;
            }
            if(node->quantity > 0)//rent movie
            {
                node->quantity = node->quantity- 1;//stock decreases
                cout << "Movie has been rented." << endl;//print info
                cout << "Movie Info:" << endl;
                cout << "===========" << endl;
                cout << "Ranking:" << node->ranking << endl;
                cout << "Title:" << node->title << endl;
                cout << "Year:" << node->year << endl;
                cout << "Quantity:" << node->quantity << endl;
                if(node->quantity == 0)//if there is only one, delete the node from the tree
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

int MovieTree::countMovieNodes()//counts the number of movies in the tree- calls private function
{
    int *cPtr = new int;
    *cPtr = 0;
    countMovieNodes(root, cPtr);
    return *cPtr;
}

void MovieTree::countMovieNodes(MovieNode *temp, int *cPtr)//private function for counting nodes in a tree
{
    if(temp == NULL)
    {
        temp = root;
    }
    MovieNode *node = temp;
    if(node->leftChild != NULL)//go left
    {
        countMovieNodes(node->leftChild, cPtr);
    }
    *cPtr = *cPtr +1;
    if(node->rightChild != NULL)//go right
    {
        countMovieNodes(node->rightChild, cPtr);
    }
}

void MovieTree::DeleteAll(MovieNode * node)//deletes all movies in the tree
{
    deletedNodeArray[indexCount] = *node;
    indexCount = indexCount +1;
    if(node->leftChild != NULL)//all nodes to left
    {
        DeleteAll(node->leftChild);
    }
    if(node->rightChild != NULL)//all nodes to right
    {
        DeleteAll(node->rightChild);
    }
    cout << "Deleting: " << node->title <<endl;
    delete node;//delete
}

void MovieTree::deleteMovieNode(string title)//delete one node in the tree
{
    MovieNode *node;
    node = root;
    while(node != NULL)//finds node
    {
        if(node->title.compare(title) > 0)//go left
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)//go right
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
    deletedNodeArray[indexCount] = *node;//the deleted node array is so that if a movie is returned and it has been deleted, it can be re-added with all of its previous information
    indexCount = indexCount +1;
    if(node->leftChild == NULL && node->rightChild == NULL)//no children
    {
        if(node->parent->leftChild == node)//if it is left child
        {
            node->parent->leftChild = NULL;
            delete node;
            return;
        }
        else//right child
        {
            node->parent->rightChild = NULL;
            delete node;
            return;
        }
    }
    else if(node->leftChild != NULL && node->rightChild == NULL)//only left child
    {
        MovieNode *x = new MovieNode;
        x = node->leftChild;
        if(node->parent->leftChild == node)//if leftchild
        {
            node->parent->leftChild = x;
            x->parent = node->parent;
        }
        else//if rightchild
        {
            node->parent->rightChild = x;
            x->parent = node->parent;
        }
        delete node;
        return;
    }
    else if(node->rightChild != NULL && node->leftChild == NULL)//only rightchild
    {
        MovieNode *x = new MovieNode;
        x = node->rightChild;
        if(node->parent->leftChild == node)//if leftchild
        {
            node->parent->leftChild = x;
            x->parent = node->parent;
        }
        else//if rightchild
        {
            node->parent->rightChild = x;
            x->parent = node->parent;
        }
        delete node;
        return;
    }
    else if(node->rightChild != NULL && node->leftChild != NULL)//two children
    {
        MovieNode *newMovie = new MovieNode;
        MovieNode *Right = new MovieNode;
        Right = node->rightChild;
        newMovie = treeMinimum(node->rightChild);//finds minimum value in tree
        if(newMovie == Right)//if movie is the one to the right
        {
            if(node->parent->leftChild == node)//if leftchild
            {
                node->parent->leftChild = newMovie;
            }
            else//if rightchild
            {
                node->parent->rightChild = newMovie;
            }
            newMovie->parent = node->parent;
            newMovie->leftChild = node->leftChild;
            delete node;
            return;
        }
        if(newMovie == NULL)//no right child
        {
            Right->parent = node->parent;
            node->leftChild->parent = Right;
            if(node->parent->leftChild == node)//if leftchild
            {
                node->parent->leftChild = Right;
            }
            else//if rightchild
            {
                node->parent->rightChild = Right;
            }
            delete node;
        }
        else
        {
            if(newMovie->rightChild != NULL)//if there is a right child
            {
                newMovie->rightChild->parent = newMovie->parent;
                newMovie->parent->leftChild = newMovie->rightChild;
            }
            node->leftChild->parent = newMovie;
            if(node->parent == NULL)//if no parent
            {
                newMovie->leftChild = root->leftChild;
                newMovie->rightChild = root->rightChild;
                newMovie->parent = NULL;
                delete node;
                root = newMovie;
                return;
            }
            if(node->parent->leftChild == node)//if leftchild
            {
                node->parent->leftChild = newMovie;
                newMovie->parent = node->parent;
            }
            if(node->parent->rightChild == node)//if rightchild
            {
                node->parent->rightChild = newMovie;
                newMovie->parent = node->parent;
            }
        }
    }
    numberOfMovies--;
}

MovieNode* MovieTree::treeMinimum(MovieNode *node)//finds node with minimum value for title in the tree
{
    //passing in right child of node being deleted
    if(node->leftChild != NULL)
    {
        node = node->leftChild//go all the way left
    }
    return node;
}

void MovieTree::returnMovie(string title, int year)//returns a movie and adds it to the inventory
{
    MovieNode *node;
    node = root;
    while(node != NULL)//finds node
    {
        if(node->title.compare(title) > 0)//go left
        {
            node = node->leftChild;
        }
        else if(node->title.compare(title) <0)//go right
        {
            node = node->rightChild;
        }
        else//node found
        {
            node->quantity = node->quantity + 1;
            return;
        }
    }
    if(node == NULL)//if movie not in inventory
    {
        bool deletedPrev = false;
        for(int i = 0; i <= indexCount; i++)
        {
            if(deletedNodeArray[i].title.compare(title) == 0)//looks to see if it is in the deleted node array
            {
                deletedPrev = true;
                addMovieNode(deletedNodeArray[i].ranking, deletedNodeArray[i].title, deletedNodeArray[i].year, 1, deletedNodeArray[i].ranking);
            }
        }
        if(deletedPrev == false)//if not, adds new node
        {
            addMovieNode(-1, title, year, 1, endofArray);
            endofArray = endofArray +1;
        }
    }
}

void MovieTree::rankMovie(std::string title,int rank)//lets the user rank a function
{
    MovieNode *node=search(title,root);//finds node
    if (node!=NULL)//if node exists
    {
        if(node->ranks +1 > 1)//if it has been ranked before
        {
            linkedList *temp = hashTable[node->userRank - 1];
            while(temp->node->title.compare(title) != 0)//while it is not the correct node
            {
                temp = temp->next;
            }
            if(temp->next != NULL && temp->prev != NULL)//if there is next and previous
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
            }
            if(temp->next == NULL && temp->prev == NULL)//if no next nor previous
            {
                hashTable[temp->node->userRank - 1] = NULL;
            }
            if(temp->next == NULL && temp->prev != NULL)//only previous
            {
                temp->prev->next = NULL;
            }
            if(temp->next != NULL && temp->prev == NULL)//only next
            {
                temp->next->prev = NULL;
                hashTable[temp->node->userRank - 1] = temp->next;
            }
            delete temp;
        }
        int ranka=((node->ranks*node->userRank)+rank)/(node->ranks+1);//finds average of all rankings
        node->ranks++;
        node->userRank=ranka;
        linkedList *newNode = new linkedList;//initializes for linked list
        newNode->node = node;
        newNode->prev = NULL;
        newNode->next = NULL;
        if(hashTable[ranka - 1] == NULL)
        {
            hashTable[ranka - 1] = newNode;//add to hashTable if no node is there
        }
        else//otherwise add to linked list on hashTable
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
    else//no movie
    {
        cout<<"Movie not found."<<endl;
    }
}

MovieNode *MovieTree::search(std::string title,MovieNode *node)//searches for a node
{
    if (node!=NULL)//if no node
    {
        if (node->title==title)//correct node
        {
            return node;
        }
        if (title.compare(node->title)<0)//go left
        {
            return search(title,node->leftChild);
        }
        else//go right
        {
            return search(title,node->rightChild);
        }
    }
    else
    {
        return NULL;
    }
}

void MovieTree::printMoviesByUser()//prints movies ranked by user
{
    linkedList *temp = new linkedList;//initialization
    bool noElements = true;
    for(int i = 9; i >= 0; i--)
    {
        if(hashTable[i] != NULL)//if element in hash table
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

void MovieTree::printMoviesByIMDB()//print movies based on IMDb rankings
{
    for(int i = 0; i < endofArray; i++)
    {
        cout <<IMDBnodeOrder[i].ranking<<": "<< IMDBnodeOrder[i].title <<endl;
    }
}

void MovieTree::rentRandomMovie()//rents a random movie from the tree
{
    int a=rand() % numberOfMovies;//finds random number from 1 to number of movies
    //cout<<a<<endl;
    MovieNode *node=allNodes[a];
    rentMovie(node->title);//rents movie
}

void MovieTree::recommendMovie(std::string title)//function to reccomend movie
{
    recommend=title;
}

void MovieTree::rentRecommended()//rents most recently recommended movie
{
    if (recommend!=""){
        rentMovie(recommend);
    }
    else{
        cout<<"No Movie Recommended."<<endl;
    }
}
void MovieTree::printMoviesByYear(int yr){//calls private function
    printMoviesByYear(yr,root);

}
void MovieTree::printMoviesByYear(int yr, MovieNode *temp){//prints movies made in a inputed year
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)//go left
  {
      printMoviesByYear(yr,node->leftChild);
  }
  if(node->year==yr){//print node
      cout<< "Movie: " << node->title << " " << node->year << endl;
  }

  if(node->rightChild != NULL)//print node
  {
      printMoviesByYear(yr,node->rightChild);
  }
}
void MovieTree::findOldestMovie(){//calls private function to find oldest movie in tree
  findOldestMovie(root);
  cout<<"Oldest Movie: "<<oldest->title<<" "<<oldest->year<<endl;
}
void MovieTree::findOldestMovie(MovieNode *temp){//finds oldest movie in tree
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)//go left
  {
      findOldestMovie(node->leftChild);
  }
  if(oldest==NULL){
      oldest = node;
  }
  if(node->year < oldest->year && oldest!=NULL){//if oldest
      oldest=node;
  }

  if(node->rightChild != NULL)//go right
  {
      findOldestMovie(node->rightChild);
  }
}
void MovieTree::findNewestMovie(){//calls private function to fund newest movie
  findNewestMovie(root);
  cout<<"Newest Movie: "<<newest->title<<" "<<newest->year<<endl;
}
void MovieTree::findNewestMovie(MovieNode *temp){//finds newest movie
  if(temp == NULL)
  {
      temp = root;
  }
  MovieNode *node = temp;
  if(node->leftChild != NULL)//go left
  {
      findNewestMovie(node->leftChild);
  }
  if(newest==NULL){
      newest=node;
  }
  if(node->year > newest->year && newest!=NULL){//if newest
      newest=node;
  }

  if(node->rightChild != NULL)//go right
  {
      findNewestMovie(node->rightChild);
  }
}
