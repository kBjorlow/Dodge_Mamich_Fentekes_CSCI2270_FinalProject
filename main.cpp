/*
Adam Dodge, Rachel Mamich, and Nick Fentekes
Final Project
Main Function
*/

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
    string filename;//initialization
    filename = argv[1];//gets filename from input
    MovieTree myTree = MovieTree(filename);
    int choice;
    bool notExit = true;
    while(notExit == true)//menu
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Return a movie" << endl;
        cout << "4. Print movies alphabetically" << endl;
        cout << "5. Print movies ranked by user" << endl;
        cout << "6. Print movies by IMDb rankings" << endl;
        cout << "7. Delete a movie" << endl;
        cout << "8. Count the movies" << endl;
        cout << "9. Rate a movie" << endl;
        cout << "10. Rent a random movie" << endl;
        cout << "11. Recommend a movie" << endl;
        cout << "12. Rent most recently recommended movie" << endl;
        cout << "13. Find movies by year" << endl;
        cout << "14. Find oldest movie" << endl;
        cout << "15. Find newest movie" << endl;
        cout << "16. Quit" << endl;
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
                myTree.printMoviesByUser();
                break;
            }
        case 6:
            {
                myTree.printMoviesByIMDB();
                break;
            }
        case 7:
            {
            cin.ignore(1000, '\n');
            string title;
            cout << "Enter title:" << endl;
            getline(cin, title);
            cin.clear();
            myTree.deleteMovieNode(title);
            break;
            }
        case 8:
            {
                cout << "Tree contains " << myTree.countMovieNodes() << " movies." << endl;
                break;
            }
        case 9:
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
        case 10:
            {
                myTree.rentRandomMovie();
                break;
            }
        case 11:
            {
                string title;
                cin.ignore();
                cout<<"Enter movie title: "<<endl;
                getline(cin,title);
                myTree.recommendMovie(title);
                break;
            }
        case 12:
            {
                myTree.rentRecommended();
                break;
            }
        case 13:
        {
            string y;
            cin.ignore();
            cout<<"Enter movie year: "<<endl;
            getline(cin,y);
            myTree.printMoviesByYear(atoi(y.c_str()));
            break;
        }
        case 14:
        {
            myTree.findOldestMovie();
            break;
        }
        case 15:
        {
            myTree.findNewestMovie();
            break;
        }
        case 16:
        {
            cout << "Goodbye!" << endl;
            notExit = false;
            break;
        }
        default:
            {
                cout<<"Not a valid entry, try again"<<endl;
                break;
            }
        }
    }
}
