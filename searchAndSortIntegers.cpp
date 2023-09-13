// This program utilizes selection sort and binary search to sort an array and find an integer among a list of numbers. The numbers are read from a text file and the result is saved into a separate text file.

#include <iostream>
#include <fstream>

using namespace std;

//Function Prototypes
int binarySearch(const int[], int, int);
void selectionSort(int [], int);
float findMean(const int [], int);

int main()
{
    int count = 0, num, find;

    ofstream output;
    output.open("array.txt");

    ifstream input;
    input.open("nums.txt");

    if(!input)
        cout << "Error: could not find file";
    else
    {

        while(input >> num)
        {
            count++;
        }

        input.clear();
        input.seekg(0);

        //Creating array with the number of data in the file.
        int nums[count];

        for(int i = 0; i < count; i++)
        {
            input >> nums[i];
        }

        //Start of user interaction

        cout << "Enter an integer to search for: ";
        cin >> find;

        cout << "This array has " << count << " items.\n";
        cout << "The array entered by the user is as follows: \n";

        for(int i = 0; i < count; i++)
        {
            cout << nums[i] << " ";
        }

        selectionSort(nums, count);

        cout << "\nThe sorted array is as follows: \n";

        for(int j = 0; j < count; j++)
        {
            cout << nums[j] << " ";
        }


        cout << "\nThe item searched for is " << find << endl;

        if(binarySearch(nums, count, find) != -1)
        {
            cout << "The value " << find << " is in position number "
                 << binarySearch(nums, count, find) << " of the list.\n";
        }
        else
        {
            cout << "This value is not in the array.\n";
        }

        cout << "The mean of all the elements in the array is "
             << findMean(nums, count);

        output.close();
        input.close();

    }
    return 0;
}

void selectionSort(int array[], int size)
{
   int startScan, minIndex, minValue;

   for (startScan = 0; startScan < (size - 1); startScan++)
   {
      minIndex = startScan;
      minValue = array[startScan];
      for(int index = startScan + 1; index < size; index++)
      {
         if (array[index] < minValue)
         {
            minValue = array[index];
            minIndex = index;
         }
      }
      array[minIndex] = array[startScan];
      array[startScan] = minValue;
   }
}

int binarySearch(const int array[], int numElems, int value)
{
	int first = 0, last = numElems - 1, middle;

	while (first <= last)
	{
		middle = (first + last) / 2;
		if (array[middle] == value)
		{
			return middle + 1;
		}
		else if (array[middle] > value)
			last = middle - 1;
		else
			first = middle + 1;
	}
	return -1;
}

float findMean(const int array[], int dataNum)
{
    float sum = 0;

    for(int i = 0; i < dataNum; i++)
    {
        sum += array[i];
    }

    return sum/dataNum;
}

/*

nums.txt:

22

-4

5
100

39

20

88

10

55

3

10
78
*/

/*
SAMPLE RUN:

Enter an integer to search for: 100
This array has 12 items.
The array entered by the user is as follows:
22 -4 5 100 39 20 88 10 55 3 10 78
The sorted array is as follows:
-4 3 5 10 10 20 22 39 55 78 88 100
The item searched for is 100
The value 100 is in position number 12 of the list.
The mean of all the elements in the array is 35.5
Process returned 0 (0x0)   execution time : 3.908 s
Press any key to continue.

*/
