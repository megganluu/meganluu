/*
2/6/2023
This program creates a database of movies and its information. 
Users can search for the information of the movies in the database as well as save their favorites into a text file.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

struct Movie {
	string title;
	double grossTotal;
	string director;
	string releaseDate;
	int runtime;
};

//Function prototypes
int numberOfLines(ifstream&);
void populateMovieFromFile(ifstream&, Movie&);
void displayMovie(const Movie& movie);
Movie* createDatabase(int& numMovies);
bool caseInsensitiveCmp(string userTitle, string databaseTitle);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

int main()
{
	int numMovies;

	Movie* moviePtr = createDatabase(numMovies);

	do
	{
		findMovie(moviePtr, numMovies);

	} while (promptToContinue());

	displayFavorites();

	delete[] moviePtr;
	moviePtr = NULL;
}

/*
1. Receives an input file.
2. Returns the number of lines in the file in an integer.
3. Counts the lines in a file.
*/
int numberOfLines(ifstream& inFile)
{
	string dummy;
	int count = 0;
	while (getline(inFile, dummy))
	{
		count++;
	}

	return count;
}

/*
1. Receives an input file and a movie object.
2. Returns nothing.
3. Reads information from a file and stores it into an object.
*/
void populateMovieFromFile(ifstream& inFile, Movie& movie)
{
	string temp;

	getline(inFile, temp, ',');
	movie.title = temp;
	inFile.ignore();

	getline(inFile, temp, ',');
	movie.grossTotal = stod(temp);
	inFile.ignore();

	getline(inFile, temp, ',');
	movie.director = temp;
	inFile.ignore();

	getline(inFile, temp, ',');
	movie.releaseDate = temp;
	inFile.ignore();

	getline(inFile, temp);
	movie.runtime = stoi(temp);
}

/*
1. Receives an object.
2. Returns nothing.
3. Displays the information of a movie.
*/
void displayMovie(const Movie& movie)
{
	cout << endl;

	cout << setw(14) << "Title: " << movie.title << endl
		 << setw(14) << "Gross Total: " << movie.grossTotal
		 << " billion dollars" << endl
		 << setw(14) << "Director: " << movie.director << endl
		 << "Release date: " << movie.releaseDate << endl
		 << setw(14) << "Runtime: " << movie.runtime << " minutes" << endl;
	
	cout << endl;
}

/*
1. Receives an integer passed by reference.
2. Returns a struct pointer.
3. Asks the user for a file name. By reading from the file, it then uses a 
   struct pointer to create an array on the heap and populate the objects
   in the array.
*/
Movie* createDatabase(int& numMovies)
{
	string fileName;
	ifstream inFile;

	cout << "Enter a file name: ";
	getline(cin, fileName);

	inFile.open(fileName);

	while (!inFile)
	{
		cout << "Error: could not open file." << endl;

		cout << "Re-enter the file name (remember .txt): ";
		getline(cin, fileName);

		inFile.open(fileName);
	}

	numMovies = numberOfLines(inFile);

	Movie* p = new Movie[numMovies];

	inFile.clear();
	inFile.seekg(0);

	for (int i = 0; i < numMovies; i++)
	{
		populateMovieFromFile(inFile, p[i]);
	}

	inFile.close();

	return p;
}

/*
1. Receives a user input string and string from an object.
2. Returns a boolean true or false.
3. Compares two strings.
*/
bool caseInsensitiveCmp(string userTitle, string databaseTitle)
{
	if (userTitle.length() != databaseTitle.length())
	{
		return false;
	}

	for (int i = 0; i < userTitle.length(); i++)
	{
		if (tolower(userTitle[i]) != tolower(databaseTitle[i]))
		{
			return false;
		}
	}

	return true;
}

/*
1. Receives a struct pointer and integer of number of movies in the database.
2. Returns nothing.
3. Asks user to enter a movie title and matches it to one in the database.
   It displays the movie found and asks if the user would like to save it.
*/
void findMovie(Movie* ptr, int numMovies)
{
	string movieSearch;
	bool movieFound = 0;
	char save;

	cout << endl;

	cout << "Enter a movie title to search for: ";
	getline(cin, movieSearch);

	for (int i = 0; i < numMovies; i++)
	{
		if (caseInsensitiveCmp(movieSearch, ptr[i].title))
		{
			displayMovie(ptr[i]);
			movieFound = 1;

			cout << "Would you like to save the above movie? (Y or N): ";
			cin >> save;
			cin.ignore();

			while (toupper(save) != 'Y' && toupper(save) != 'N')
			{
				cout << "Please enter either Y/N: ";
				cin >> save;
				cin.ignore();
			}

			if (toupper(save) == 'Y')
			{
				saveToFile(ptr[i]);
				cout << "Successfully saved to favorites.txt!" << endl;
			}
		}
	}
	
	if (!movieFound)
	{
		cout << "Error: " << movieSearch
		  	 << " not found in database. Please try again" << endl;
	}


}

/*
1. Receives a struct pointer.
2. Returns nothing.
3. Saves object information to file "favorites.txt".
*/
void saveToFile(const Movie& movie)
{
	static bool firstCall = true;
	ofstream outFile;

	if (firstCall)
	{
		outFile.open("favorites.txt");
		firstCall = false;
	}
	else
	{
		outFile.open("favorites.txt", ios::app);
	}

	outFile << movie.title << ", " << movie.grossTotal << ", "
			<< movie.director << ", " << movie.releaseDate << ", "
			<< movie.runtime << endl;

	outFile.close();
}

/*
1. Receives nothing.
2. Returns a boolean variable.
3. Determines whether or not a user would like to continue.
*/
bool promptToContinue()
{
	char exit;

	cout << endl;
	cout << "Would you like to exit? (Y/N): ";
	cin >> exit;
	cin.ignore();

	while (toupper(exit) != 'Y' && toupper(exit) != 'N')
	{
		cout << "Please enter either Y/N: ";
		cin >> exit;
		cin.ignore();
	}

	if (toupper(exit) == 'Y')
	{
		return false;
	}

		return true;
}

/*
1. Receives nothing.
2. Returns nothing.
3. Creates a new database of the user's favorite movies and displays them.
*/
void displayFavorites()
{
	ifstream inFile;
	int numMovies;


	inFile.open("favorites.txt");

	if(!inFile)
	{
		cout << "Error: could not open file.";
	}
	else
	{
		inFile.clear();
		inFile.seekg(0);

		if (inFile.eof())
		{
			cout << "Error: You have no saved movies.";
		}
		else
		{
			numMovies = numberOfLines(inFile);

			cout << endl;

			cout << "Your saved movies are: " << endl;

			inFile.clear();
			inFile.seekg(0);

			Movie* moviePtr = new Movie[numMovies];

			for (int i = 0; i < numMovies; i++)
			{
				populateMovieFromFile(inFile, moviePtr[i]);
			}

			for (int i = 0; i < numMovies; i++)
			{
				displayMovie(moviePtr[i]);
			}

			delete[] moviePtr;
			moviePtr = NULL;

		}

		inFile.close();

	}

}

/*
SAMPLE RUN:

Enter a file name: movies.txt

Enter a movie title to search for: AvaTar

	   Title: Avatar
 Gross Total: 2.788 billion dollars
	Director: James Cameron
Release date: 12/18/09
	 Runtime: 161 minutes

Would you like to save the above movie? (Y or N): y
Successfully saved to favorites.txt!

Would you like to exit? (Y/N): n

Enter a movie title to search for: FINDING dory

	   Title: Finding Dory
 Gross Total: 1.029 billion dollars
	Director: Andrew Stanton
Release date: 6/17/16
	 Runtime: 97 minutes

Would you like to save the above movie? (Y or N): Y
Successfully saved to favorites.txt!

Would you like to exit? (Y/N): N

Enter a movie title to search for: jurassic word
Error: jurassic word not found in database. Please try again

Would you like to exit? (Y/N): y

Your saved movies are:

	   Title: Avatar
 Gross Total: 2.788 billion dollars
	Director: James Cameron
Release date: 12/18/09
	 Runtime: 161 minutes


	   Title: Finding Dory
 Gross Total: 1.029 billion dollars
	Director: Andrew Stanton
Release date: 6/17/16
	 Runtime: 97 minutes


(process 2792) exited with code 0.
*/