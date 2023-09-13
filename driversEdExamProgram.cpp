//11/30/2022
// This program grades the written portion of the driver's license exam. The correct answers are stored in an array and the student's score is tracked throughout their attempt.

#include <iostream>
#include <cctype>

using namespace std;

//Function Prototypes
void input(char[], int);
void checkAnswers(char[], char[], int &, int &, int);

int main()
{
    const int SIZE = 20;
    char userAnswers[SIZE];
    char correctAnswers[SIZE]
         = {'A', 'D', 'B', 'B', 'C', 'B', 'A', 'B', 'C', 'D',
            'A', 'C', 'D', 'B', 'D', 'C', 'C', 'A', 'D', 'B'};

    int correct = 0, incorrect = 0;

    cout << "Please enter the student's answers for each of the questions.\n";
    cout << "Press Enter after typing each answer.\n";
    cout << "Please enter only an A, B, C, D"
         << " or a, b, c, d for each question." << endl;

    // Loops to ask 20 questions and populate input array
    for(int i = 0; i < SIZE; i++)
    {
        input(userAnswers, i + 1);
    }

    checkAnswers(userAnswers, correctAnswers, correct, incorrect, SIZE);

    // Student passes if they score 15 or higher
    if(correct >= 15)
    {
        cout << "\nThe student passed the exam.\n" << endl;
    }
    else
    {
        cout << "\nThe student failed the exam.\n" << endl;
    }

    cout << "Correct Answers: " << correct << endl;
    cout << "Incorrect Answers: " << incorrect << endl;

    return 0;
}

void input(char list[], int questionNumber)
{
    cout << "Question " << questionNumber << ": ";

    cin >> list[questionNumber - 1];

    while(toupper(list[questionNumber - 1]) > 'D')
    {
        cout << "Use only an A, B, C, D or a, b, c, d!" << endl
             << "Please try again.\n";
        cin >> list[questionNumber - 1];
    }

}

void checkAnswers(char input[], char correct[],
                  int& numCorrect, int& numIncorrect, int size)
{
    numCorrect = 0;
    numIncorrect = 0;

    cout << "\nQuestions that were answered incorrectly:\n";

    for(int i = 0; i < size; i++)
    {
        if(correct[i] == toupper(input[i]))
        {
            numCorrect++;
        }
        else
        {
            numIncorrect++;
            cout << i + 1 << endl;
        }
    }

    if(numIncorrect == 0)
    {
        cout << "None... Perfect Score!" << endl;
    }

}