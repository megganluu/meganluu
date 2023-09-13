/* 1/16/2023
This program generates a card matching memory game
and saves the results to a file. A board is pseudo-randomly generated and shown using a 2D array. Using coordinates, players choose 2 coordinates to match and complete the game when all of the cards are matched. The program keeps track of how many turns the player takes to finish or how many beofre they quit. 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>


using namespace std;

const int LENGTH = 4;

//Function Prototypes

void initializeCards(int cards[][LENGTH]);
void showCards(int cards[][LENGTH], bool faceup[][LENGTH]);
bool checkFinished(bool faceup[][LENGTH]);
bool validateInput(int val);

int main()
{
    string name;
    int x1, y1, x2, y2, turns = 0;
    char exit;

    srand(time(NULL));

    // initializing list of card values
    int cards[LENGTH][LENGTH] = { {1, 1, 2, 2},
                                  {3, 3, 4, 4},
                                  {5, 5, 6, 6},
                                  {7, 7, 8, 8} };

    // initializing list of false bools
    bool faceup[LENGTH][LENGTH] = { 0 };

    initializeCards(cards);

    cout << "Welcome to the memory game!\n";
    cout << "Please enter your full name: ";
    getline(cin, name);
    cout << "\nFind all matching pairs on the board!\n";

    do
    {
        showCards(cards, faceup);

        cout << "Enter x and y position of the first card: ";
        cin >> x1 >> y1;

        while (!validateInput(x1))
        {
            cout << "Re-enter x-value: ";
            cin >> x1;
        }

        while(!validateInput(y1))
        {
            cout << "Re-enter y-value: ";
            cin >> y1;
        }

        cout << "Enter x and y position of the second card: ";
        cin >> x2 >> y2;

        while (!validateInput(x2))
        {
            cout << "Re-enter x-value: ";
            cin >> x2;
        }

        while (!validateInput(y2))
        {
            cout << "Re-enter y-value: ";
            cin >> y2;
        }

        // Setting bools to true to temporarily display coordinate number
        faceup[x1][y1] = 1;
        faceup[x2][y2] = 1;

        showCards(cards, faceup);

        if (cards[x1][y1] == cards[x2][y2])
        {
            cout << endl << "Match Found!" << endl;
        }
        else
        {
            faceup[x1][y1] = 0;
            faceup[x2][y2] = 0;
            
            cout << "No match.\n"
                 << "Flipping cards over again. \n";
        }

        // counts number of turns player is taking
        turns++;

        if (checkFinished(faceup))
        {
            exit = 'q';
        }
        else
        {
            cout << endl << "Enter 'q' to quit or press any key to continue\n";
            cin.ignore();
            cin.get(exit);
        }
    } while (tolower(exit) != 'q');

    ofstream outFile;
    outFile.open("gameResults.txt");


    if (checkFinished(faceup))
    {
        cout << "Good job " << name << "! You completed the game in "
             << turns << " turns!";

        outFile << "Memory Game Results" << endl;
        outFile << "Name: " << name << endl;
        outFile << "Game completed in " << turns << " turns.";
    }
    else
    {
        cout << "You failed after " << turns << " turns." << endl;

        outFile << "Don't give up!";
    }

    outFile.close();

    cout << "Results saved. Goodbye!";

    return 0;
}

// This function randomizes the order of the cards.
// Receives a 2D array (the array of card numbers) without returning anything.
void initializeCards(int cards[][LENGTH])
{
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            int widthIndex = rand() % LENGTH;
            int lengthIndex = rand() % LENGTH;
            int temp;

            temp = cards[i][j];
            cards[i][j] = cards[widthIndex][lengthIndex];
            cards[widthIndex][lengthIndex] = temp;
        }
    }
}

// This function displays the game board and
// adjusts it to match the status of the matched cards.
// Receives two 2D arrays (the cards array and bool array).
// Does not return anything.
void showCards(int cards[][LENGTH], bool faceup[][LENGTH])
{
    cout << endl << "   0 1 2 3\n";
    cout << "============\n";

    for (int i = 0; i < LENGTH; i++)
    {
        cout << i << "| ";

        for (int j = 0; j < LENGTH; j++)
        {
            if (faceup[i][j])
            {
                cout << cards[i][j] << " ";
            }
            else
            {
                cout << "*" << " ";
            }
        }

        cout << "|" << endl;
    }
    cout << "============\n" << endl;
}

// This function checks if all cards are matched.
// Receives the bool faceup array.
// Returns false if at least one item is 0 and returns true otherwise.
bool checkFinished(bool faceup[][LENGTH])
{
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            if (faceup[i][j] == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

// This function validates input to prevent a violation of array bounds.
// Receives the inputted coordinates (x and y values).
// Returns a bool to indicate it's validity.
bool validateInput(int val)
{
    if (val < 0 || val > 3)
    {
        return false;
    }

    return true;
}

/*
SAMPLE RUN PORTION 1:

Welcome to the memory game!
Please enter your full name: Bob Jones

Find all matching pairs on the board!

   0 1 2 3
============
0| * * * * |
1| * * * * |
2| * * * * |
3| * * * * |
============

Enter x and y position of the first card: -1 9
Re-enter x-value: 8
Re-enter x-value: 2
Re-enter y-value: 3
Enter x and y position of the second card: 0 1

   0 1 2 3
============
0| * 7 * * |
1| * * * * |
2| * * * 3 |
3| * * * * |
============

No match.
Flipping cards over again.

Enter 'q' to quit or press any key to continue
q
You failed after 1 turns.
Results saved. Goodbye!
C:\CIS22B Code\AssignmentOne\x64\Debug\AssignmentOne.exe (process 26264)
exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options
->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

************************************************

SAMPLE RUN PORTION 2:

Welcome to the memory game!
Please enter your full name: Bob Jones

Find all matching pairs on the board!

   0 1 2 3
============
0| * * * * |
1| * * * * |
2| * * * * |
3| * * * * |
============

Enter x and y position of the first card: 0 0
Enter x and y position of the second card: 2 0

   0 1 2 3
============
0| 8 * * * |
1| * * * * |
2| 8 * * * |
3| * * * * |
============


Match Found!

Enter 'q' to quit or press any key to continue

*5 iterations have been removed*


   0 1 2 3
============
0| 8 1 4 2 |
1| 5 1 5 6 |
2| 8 * * 2 |
3| * 4 * 6 |
============

Enter x and y position of the first card: 2 1
Enter x and y position of the second card: 2 2

   0 1 2 3
============
0| 8 1 4 2 |
1| 5 1 5 6 |
2| 8 3 3 2 |
3| * 4 * 6 |
============


Match Found!

Enter 'q' to quit or press any key to continue


   0 1 2 3
============
0| 8 1 4 2 |
1| 5 1 5 6 |
2| 8 3 3 2 |
3| * 4 * 6 |
============

Enter x and y position of the first card: 3 0
Enter x and y position of the second card: 3 2

   0 1 2 3
============
0| 8 1 4 2 |
1| 5 1 5 6 |
2| 8 3 3 2 |
3| 7 4 7 6 |
============


Match Found!
Good job Bob Jones! You completed the game in 8 turns!Results saved. Goodbye!
C:\CIS22B Code\AssignmentOne\x64\Debug\AssignmentOne.exe (process 11124)
exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options
->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
