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

    protected:
    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void countMovieNodes(MovieNode *node, int *c);
        void printMovieInventory(MovieNode * node);
        MovieNode* search(std::string title);
        MovieNode* treeMinimum(MovieNode *node);
        MovieNode *root = NULL;
        MovieNode deletedNodeArray[50];
        int indexCount = 0;

};

#endif // MOVIETREE_H

