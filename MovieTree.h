#ifndef MOVIETREE_H
#define MOVIETREE_H
#include <iostream>
struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;
    int userRank;
    int ranks;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        userRank = -1;
    }
};
struct linkedList{
    MovieNode *node;
    MovieNode *next;
    MovieNode *prev;
};
class MovieTree
{
    public:
        MovieTree(std::string filename);
        ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        void returnMovie(std::string title, int year);
        void rankMovie(std::string title,int rank);
        void printMoviesByUser();
        void printMoviesByIMBD();
    protected:
    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void countMovieNodes(MovieNode *node, int *c);
        void printMovieInventory(MovieNode * node);
        MovieNode* search(std::string title,MovieNode *node);
        MovieNode* treeMinimum(MovieNode *node);
        void printMoviesByUser(MovieNode *temp);
        void printMoviesByIMBD(MovieNode *temp);
        MovieNode *root;
        MovieNode deletedNodeArray[50];
        int indexCount = 0;
        linkedList *head;

};

#endif // MOVIETREE_H

