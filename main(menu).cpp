#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include "stdlib.h"

using namespace std;

int main(int argc, char *argv[])
{
    MovieTree myTree = MovieTree();
    string filename;
    filename = argv[1];
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
                myTree.addMovieNode(atoi(Ranking.c_str()), movieTitle, atoi(Year.c_str()), atoi(Quant.c_str()));
                break;
            }
            }
        }
    }
    int choice;
    bool notExit = true;
    while(notExit == true)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Return a movie" << endl;
        cout << "4. Print the inventory" << endl;
        cout << "5. Delete a movie" << endl;
        cout << "6. Count the movies" << endl;
        cout << "7. Quit" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            {
            cin.ignore(1000, '\n');
            string Title;
            cout << "Enter title:" << endl;
            getline(cin, Title);
            cin.clear();
            myTree.findMovie(Title);
            break;
        }
        case 2:
        {
            cin.ignore(1000, '\n');
            string title;
            cout << "Enter title:" << endl;
            getline(cin, title);
            cin.clear();
            myTree.rentMovie(title);
            break;
        }
        case 3:
            {
                cin.ignore(1000, '\n');
                string title;
                string Yearr;
                cout<< "Enter title:" << endl;
                getline(cin, title);
                cin.clear();
                cout << "Enter the year the movie was made:" << endl;
                getline(cin, Yearr);
                cin.clear();
                myTree.returnMovie(title, atoi(Yearr.c_str()));
            }
        case 4:
        {
             myTree.printMovieInventory();
            break;
        }
        case 5:
            {
            cin.ignore(1000, '\n');
            string title;
            cout << "Enter title:" << endl;
            getline(cin, title);
            cin.clear();
            myTree.deleteMovieNode(title);
            break;
            }
        case 6:
            {
                cout << "Tree contains: " << myTree.countMovieNodes() << " movies." << endl;
                break;
            }
        case 7:
        {
            cout << "Goodbye!" << endl;
            notExit = false;
            break;
        }
        }
    }

}
