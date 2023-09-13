/*
Date: 2/16/2023
This program creates a snack vending machine and sells items to a user
while keeping track of the stock and data of the sold items using a class.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>

#pragma warning (disable:4996)

using namespace std;

class Snack {
private: 
	string snackName;
	double snackPrice;
	int stockQty;
	int sold;
	string* times;

	// 1. Receives nothing.
	// 2. Returns a string containing the current time
	// 3. Gets current time
	string getCurrentTime() {
		time_t t = time(0);
		struct tm ts;
		char buff[10];
		ts = *localtime(&t);
		strftime(buff, sizeof(buff), "%X", &ts);
		return buff;
	}

public:
	string getName() const {
		return snackName;
	}

	void setName(string name) {
		snackName = name;
	}

	double getPrice() const {
		return snackPrice;
	}

	void setPrice(double price) {
		snackPrice = price;
	}

	int getQty() const {
		return stockQty;
	}

	void setQty(int stock) {
		stockQty = stock;
		times = new string[stockQty];

	}

	int getSold() const {
		return sold;
	}

	void setSold(int numSold) {
		sold = numSold;
	}

	string getTime(int i) const {
		return times[i];
	}

	Snack() {
		snackName = " ";
		snackPrice = 0;
		stockQty = 0;
		sold = 0;
	}

	Snack(string name, double price, int qty) { //Overloaded constructor
		snackName = name;
		snackPrice = price;
		stockQty = qty;
		sold = 0;

		times = new string[stockQty];

	}

	~Snack() {
		cout << endl << "Closing info for " << snackName << endl;
		cout << "\t" << stockQty << " in stock" << endl;
		cout << "\t" << sold << " sold for a profit of $"
			 << fixed << setprecision(2) << snackPrice * sold;
		cout << endl;

		if(sold != 0)
		{
			cout << endl << "Transactions occured at:" << endl;
			for (int i = 0; i < sold; i++)
			{
				cout << "\t" << times[i] << endl;
			}
		}

		delete[] times;
		times = NULL;
	}

	// 1. Receives a double passed by reference containing the user's money
	// 2. Returns a boolean value
	// 3. Sells the item depending of stock and amount the user has
	bool buyItem(double& moneyEntered) {
		if (stockQty == 0)
		{
			cout << "This item is sold out.\n" << endl;
			return false;
		}

		if (moneyEntered >= snackPrice)
		{
			moneyEntered -= snackPrice;
			stockQty -= 1;

			cout << "Item has been dispensed below.\n" << endl;

			times[sold] = getCurrentTime();
			sold += 1;

			return true;
		}
		else
		{
			cout << "Insufficient funds.\n" << endl;
			return false;
		}
	}
};

//FUNCTION PROTOTYPES
void displayVendingMachine(const Snack[], int);
int getQuarters();
void userBuyItem(Snack[], int);
bool promptToContinue();

int main()
{
	const int SIZE = 3;
	Snack machine[SIZE] = { Snack(), 
							Snack("Candy", 1.25, 5), 
							Snack("Soda", 1, 2)};

	machine[0].setName("Chips");
	machine[0].setPrice(1.75);
	machine[0].setQty(3);

	cout << "Welcome to the vending machine!\n" << endl;

	do {
		userBuyItem(machine, SIZE);
	} while (promptToContinue());
	
	return 0;
}

// 1. Receives const array of class snack and the element size of the array
// 2. Returns nothing
// 3. Displays the attributes for each snack in a table
void displayVendingMachine(const Snack snacks[], int size)
{
	cout << "Item # \t " << "Item Name\t" << "Price\t" << "# in-stock\t";
	cout << endl << "------------------------------------------"<< endl;

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "\t "
			 << left << setw(12) << snacks[i].getName()
			 << "\t" << fixed << setprecision(2) << snacks[i].getPrice()
			 << "\t" << setprecision(0) << snacks[i].getQty();
		cout << endl;
	}
}

// 1. Receives nothing
// 2. Returns integer of amount of quarters user entered
// 3. Prompt the user to enter an amount of quarters and save it
int getQuarters() {
	int numQuarters;

	cout << "Enter a number of quarters: ";
	cin >> numQuarters;
	cin.ignore();

	while (numQuarters <= 0)
	{
		cout << "Please enter a number greater than 0: ";
		cin >> numQuarters;
		cin.ignore();
	}

	return numQuarters;
}

// 1. Receives array of class snack and the array's element size
// 2. Returns nothing
// 3. Call other functions to successfully make transactions
void userBuyItem(Snack snacks[], int size) {
	int quarters, itemChoice;
	double totalMoney;

	displayVendingMachine(snacks, size);
	quarters = getQuarters();

	totalMoney = quarters / 4.0;
	cout << "Amount Entered: $" << fixed << setprecision(2) 
		 << totalMoney << endl;

	cout << endl << "Enter an item number between 1 and 3: ";
	cin >> itemChoice;

	while (itemChoice < 1 || itemChoice > 3)
	{
		cout << "Invalid input. Please enter a number between 1 and 3: ";
		cin >> itemChoice;
	}

	int snackIndex = itemChoice - 1;

	snacks[snackIndex].buyItem(totalMoney);

	if (totalMoney > 0)
	{
		cout << "$" << totalMoney << " dispensed below.\n" << endl;
	}
}

// 1. Receives nothing
// 2. Returns a boolean value
// 3. Asks the user if they would like to continue and
//    terminates the program if not
bool promptToContinue() {
	char exit;

	cout << "Would you like to continue? (Y/N): ";
	cin >> exit;

	while (toupper(exit) != 'Y' && toupper(exit) != 'N')
	{
		cout << "Please enter either Y/N: ";
		cin >> exit;
	}
	cout << endl;

	return (toupper(exit) == 'Y');
}

/*
SAMPLE RUN:

Welcome to the vending machine!

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    3
2        Candy          1.25    5
3        Soda           1.00    2
Enter a number of quarters: -1
Please enter a number greater than 0: 8
Amount Entered: $2.00

Enter an item number between 1 and 3: 3
Item has been dispensed below.

$1.00 dispensed below.

Would you like to continue? (Y/N): y

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    3
2        Candy          1.25    5
3        Soda           1.00    1
Enter a number of quarters: 4
Amount Entered: $1.00

Enter an item number between 1 and 3: 3
Item has been dispensed below.

Would you like to continue? (Y/N): Y

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    3
2        Candy          1.25    5
3        Soda           1.00    0
Enter a number of quarters: 4
Amount Entered: $1.00

Enter an item number between 1 and 3: 3
This item is sold out.

$1.00 dispensed below.

Would you like to continue? (Y/N): Y

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    3
2        Candy          1.25    5
3        Soda           1.00    0
Enter a number of quarters: 10
Amount Entered: $2.50

Enter an item number between 1 and 3: 1
Item has been dispensed below.

$0.75 dispensed below.

Would you like to continue? (Y/N): y

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    2
2        Candy          1.25    5
3        Soda           1.00    0
Enter a number of quarters: 5
Amount Entered: $1.25

Enter an item number between 1 and 3: 2
Item has been dispensed below.

Would you like to continue? (Y/N): y

Item #   Item Name      Price   # in-stock
------------------------------------------
1        Chips          1.75    2
2        Candy          1.25    4
3        Soda           1.00    0
Enter a number of quarters: 9
Amount Entered: $2.25

Enter an item number between 1 and 3: 1
Item has been dispensed below.

$0.50 dispensed below.

Would you like to continue? (Y/N): n


Closing info for Soda
		0 in stock
		2 sold for a profit of $2.00

Transactions occured at:
		20:29:44
		20:30:04

Closing info for Candy
		4 in stock
		1 sold for a profit of $1.25

Transactions occured at:
		20:30:50

Closing info for Chips
		1 in stock
		2 sold for a profit of $3.50

Transactions occured at:
		20:30:41
		20:31:03

(process 60948) exited with code 0.
*/