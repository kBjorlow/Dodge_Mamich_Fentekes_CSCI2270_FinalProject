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
    string filename;
    filename = argv[1];
    MovieTree myTree = MovieTree(filename);
    int choice;
    bool notExit = true;
    while(notExit == true)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Return a movie" << endl;
        cout << "4. Print movies alphabetically" << endl;
        cout << "5. Delete a movie" << endl;
        cout << "6. Count the movies" << endl;
        cout << "7. Rate a movie" << endl;
        cout << "8. Print movies by user rankings" << endl;
        cout << "9. Print movies by IMBD rankings" << endl;
        cout << "10. Quit" << endl;
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
                cin.ignore();
                cout << "Enter movie name: " <<endl;
                string name;
                getline(cin,name);
                cout << "Enter a ranking from 1 to 10: "<<endl;
                string ranking;
                int ranki;
                getline(cin,ranking);
                stringstream st(ranking);
                st>>ranki;
                if (ranki<1 || ranki>10){
                    cout<<"Rank not between 1 and 10"<<endl;
                    break;
                }
                myTree.rankMovie(name,ranki);
                break;
            }
        case 8:
            {
                myTree.printMoviesByUser();
                break;
            }
        case 9:
            {
                myTree.printMoviesByIMDB();
                break;
            }
        case 10:
        {
            cout << "Goodbye!" << endl;
            notExit = false;
            break;
        }
        }
    }

}
