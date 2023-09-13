// Megan Luu
// This program creates a hash table by reading from a file with employee information. The program calculates collisions and analyzes the best hashing method for this set of data.

#include <cstdlib>
#include <iostream>
#include <array>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

#define TABLE_SIZE 400

template <typename T>
class Node
{
public:
	T data;
	Node<T>* previous, * next;
	Node<T>() { previous = NULL; next = NULL; data = 0; }
	Node<T>(T t) { previous = NULL; next = NULL;  data = t; }
};

template <typename T>
class List
{
public:
	Node<T>* tail, * head;
	List() { tail = NULL; head = NULL; }  // default constructor
	// appends to tail of list
	void Append(T data)
	{
		Node<T>* pdata = new Node<T>(data);
		if (IsEmpty())
		{
			tail = pdata;
			head = pdata;
		}
		else
		{
			tail->next = pdata;
			pdata->previous = tail;
			tail = pdata;
		}
	}
	// prepends to head of list
	void Prepend(T data)
	{
		Node<T>* pdata = new Node<T>(data);
		if (IsEmpty())
		{
			head = pdata;
			tail = pdata;
		}
		else
		{
			head->previous = pdata;
			pdata->next = head;
			head = pdata;
		}
	}
	// inserts data after found data
	void InsertAfter(T find, T data)
	{
		Node<T>* pdata = new Node<T>(data);
		Node<T>* itr = head;
		while (itr != nullptr)
		{
			if (itr->data == find)
			{
				pdata->previous = itr;
				pdata->next = itr->next;

				if (itr == tail)
				{
					tail = pdata;
				}
				else
				{
					itr->next->previous = pdata;
				}
				itr->next = pdata;
				return;
			}
			itr = itr->next;
		}
	}
	// inserts data before found data
	void InsertBefore(T find, T data)
	{
		Node<T>* pdata = new Node<T>(data);
		Node<T>* itr = head;
		while (itr != nullptr)
		{
			if (itr->data == find)
			{
				pdata->next = itr;
				pdata->previous = itr->previous;

				if (itr == head)
				{
					head = pdata;
				}
				else
				{
					itr->previous->next = pdata;
				}

				itr->previous = pdata;
				return;
			}
			itr = itr->next;
		}
	}

	// finds data node and returns it
	Node<T>* Search(T data)
	{
		Node<T>* itr = head;
		while (itr != nullptr && itr->data != data)
		{
			itr = itr->next;
		}

		return itr;
	}
	// deletes a node from the list
	void Delete(T data)
	{
		Node<T>* itr = head;

		while (itr != nullptr) {
			if (itr->data == data) {

				if (itr != head)
					itr->previous->next = itr->next;
				else
					head = itr->next;

				if (itr != tail)
					itr->next->previous = itr->previous;
				else
					tail = itr->previous;

				delete itr;
				return;
			}
			itr = itr->next;
		}
	}
	// returns number of nodes in list
	int Count()
	{
		Node<T>* itr = tail;
		int count = 0;

		while (itr != nullptr)
		{
			count++;
			itr = itr->previous;
		}
		return count;
	}
	// returns true if list is empty
	bool IsEmpty()
	{
		return(!head);
	}
	// prints list from tail of list
	void Output()
	{
		Node<T>* rover = tail;
		int c = -1;
		while (rover != NULL)
		{
			rover = rover->previous;
			c++;
		}
		if (c > 0) {
			cout << endl << c << " collision(s) occured: " << endl;
			rover = head;
			while (rover != NULL)
			{
				cout << rover->data;
				rover = rover->next;
			}
			cout << endl;
		}
	}
};

// HASHFUNCTIONS
int divHashFunc(string key)
{
	int sum = stoi(key);
	return sum % TABLE_SIZE;
}

int sqrHashFunc(string key)
{
	int sum = stoi(key);

	int sqr = sum * sum;
	sqr = sqr / pow(10, (log10(sqr) + 1) / 4);

	return (sqr % 400);
}

int digHashFunc(string key)
{
	int sum = 0;
	int i;
	for (i = 0; i <= key.length() / 2; i += 2) {
		sum += 10 * key[i] + key[i + 1];
	}
	if (i < key.length())
	{
		sum += key[i];
	}
	return (sum - 48) % TABLE_SIZE;
}

int mulHashFunc(string key)
{
	float sum = 0;
	float A = 0.83;
	for (int i = 0; i < key.length(); i++) {
		sum += key[i];
	}
	sum *= A;

	while (sum >= 1)
	{
		sum--;
	}

	return floor(sum * TABLE_SIZE);
}

class Customer
{
private:
	string lastName = "";
	string firstName = "";
	string id = "";
	int key = 0;
public:
	int used = 0;
	Customer(string l = "", string f = "", string i = "", int k = 0, int u = 0)
	{
		lastName = l;
		firstName = f;
		id = i;
		used = u;
		key = k;
	}
	void setFirstName(string s) { firstName = s; }
	void setLastName(string s) { lastName = s; }
	void setID(string s) { id = s; }
	void setKey(int k) { key = k; }

	int getKey() { return key; }
	string getFirstName() { return firstName; }
	string getLastName() { return lastName; }
	string getID() { return id; }
	operator int() { return getKey(); }

	friend ostream& operator << (ostream& out, const Customer& data)
	{
		out << data.key << ": " << data.lastName << ", "
			<< data.firstName << ", " << data.id << endl;

		return out;
	}
};

class HashTable
{
private:
	List<Customer> table[TABLE_SIZE];
	int collisions = 0;
public:
	HashTable() {};
	int getcollisions() { return collisions; }
	string getFirstName(string key)
	{
		int hash = divHashFunc(key);
		return table[hash].head->data.getFirstName();
	}
	string getLastName(string key)
	{
		int hash = divHashFunc(key);
		return table[hash].head->data.getLastName();
	}
	string getID(string key)
	{
		int hash = divHashFunc(key);
		return table[hash].head->data.getID();
	}
	Customer get(int index)
	{
		return table[index].head->data;
	}
	void set(string l, string f, string i, int key)
	{
		int hash = key;
		Customer temp(l, f, i);
		
		if (table[hash].IsEmpty())
		{
			temp.setKey(hash);
			table[hash].Append(temp);
		}
		else
		{
			if (table[hash - 1].IsEmpty())
			{
				temp.setKey(hash - 1);
				table[hash - 1].Append(temp);
			}
			else
			{
				temp.setKey(hash);
				table[hash].Append(temp);
				collisions++;
			}
		}
	}
	Customer operator [] (int index)
	{
		return get(index);
	}
	void tableOutput() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			table[i].Output();
		}
	}
};

int main() {
	HashTable divTable;
	HashTable sqrTable;
	HashTable digitTable;
	HashTable mulTable;

	ifstream inFile;
	inFile.open("Customer.csv");
	string last, first, id;
	
	while (!inFile.eof()) {
		getline(inFile, last, ',');
		getline(inFile, first, ',');
		getline(inFile, id);

		// In order to showcase all 4 hash functions in 1 run,
		// the key is calculated in main and passed.
		divTable.set(last, first, id, divHashFunc(id));
		sqrTable.set(last, first, id, sqrHashFunc(id));
		digitTable.set(last, first, id, digHashFunc(id));
		mulTable.set(last, first, id, mulHashFunc(id));
	}
	inFile.close();

	cout << "Division Hash Function: " << endl;
	divTable.tableOutput();

	cout << "Mid Square Hash Function: " << endl;
	sqrTable.tableOutput();

	cout << "Digit Fold Hash Function: " << endl;
	digitTable.tableOutput();

	cout << "Multiplication Hash Function: " << endl;
	mulTable.tableOutput();

	cout << endl;
	cout << "Division Total Collisions: " << divTable.getcollisions() << endl;
	cout << "Mid Square Total Collisions: " << sqrTable.getcollisions() << endl;
	cout << "Digit Folding Total Collisions: " << digitTable.getcollisions() << endl;
	cout << "Multiplication Total Collisions: " << mulTable.getcollisions() << endl;

	return 0;
}

