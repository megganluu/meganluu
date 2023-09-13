// Megan Luu - CIS22C Summer De Anzza
// 7/11/2023
// This program creates and tests the following data structures:
// single linked list, double linked list, stack, and queue

#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T>* previous, * next;
	Node<T>() { previous = NULL; next = NULL; data = 0; }
	Node<T>(T t) { previous = NULL; next = NULL;  data = t; }
};

// PART 1
template <typename T>
class SList
{
public:
	Node<T>* tail;
	SList() { tail = NULL; }  // default constructor
	// appends to tail of list
	void Append(T data)
	{
		Node<T>* pdata = new Node<T>(data);
		if (IsEmpty())
		{
			tail = pdata;
		}
		else
		{
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
			tail = pdata;
		}
		else
		{
			Node<T>* itr = tail;
			while (itr->previous != nullptr) {
				itr = itr->previous;
			}
			itr->previous = pdata;
		}
	}
	// inserts data after found data
	void InsertAfter(T find, T data)
	{
		Node<T>* pdata = new Node<T>(data);
		Node<T>* itr = tail;
		while (itr != nullptr)
		{
			if (itr->data == find)
			{
				pdata->previous = itr->previous;
				itr->previous = pdata;
				return;
			}
			itr = itr->previous;
		}
		cout << "Error: Data Not Found";
	}
	// inserts data before found data
	void InsertBefore(T find, T data)
	{
		Node<T>* pdata = new Node<T>(data);
		Node<T>* itr = tail;
		if (tail->data == find)
		{
			pdata->previous = tail;
			tail = pdata;
		}
		else
		{
			while (itr->previous != nullptr)
			{
				if (itr->previous->data == find)
				{
					pdata->previous = itr->previous;
					itr->previous = pdata;
					return;
				}
				itr = itr->previous;
			}
			cout << "Error: Data Not Found";
		}
	}
	// finds data node and returns it
	Node<T>* Search(T data)
	{
		Node<T>* itr = tail;
		while (itr != nullptr && itr->data != data)
		{
			itr = itr->next;
		}

		return itr;
	}
	// deletes a node from the list
	void Delete(T data)
	{
		Node<T>* itr = tail, * itrAfter = tail;
		if (tail->data == data)
		{
			tail = tail->previous;
			delete itr;
		}
		else
		{
			while (itr != nullptr) {
				if (itr->data == data)
				{
					itrAfter->previous = itr->previous;
					delete itr;
					return;
				}
				itrAfter = itr;
				itr = itr->previous;
			}
			cout << "Error: Data Not Found";
		}
	}
	// returns number of nodes in list
	int Count()
	{
		Node<T>* itr;
		int count = 0;
		itr = tail;
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
		return(!tail);
	}
	// prints list from tail of list
	void Output()
	{
		Node<T>* rover = tail;
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->previous;
		}
		cout << endl;
	}
};

// PART 2
template <typename T>
class DList
{
public:
	Node<T>* tail, * head;
	DList() { tail = NULL; head = NULL; }  // default constructor
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
		cout << "Error: Data Not Found";
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
		cout << "Error: Data Not Found";
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
		cout << "Error: Data Not Found";
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
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->previous;
		}
		cout << endl;
	}
};

// PART 3
template <typename T>
class Stack
{
public:
	Node<T>* top;
	Stack() { top = NULL; }  // default constructor
	// Adds new node to top of stack
	void push(T data) 
	{
		Node<T>* pdata = new Node<T>(data);
		if (IsEmpty()) {
			top = pdata;
		}
		else {
			top->next = pdata;
			pdata->previous = top;
			top = pdata;
		}
	}
	//Removes top node in stack
	void Pop()
	{
		if (IsEmpty()) {
			return;
		}
		Node<T>* temp = top;
		top = top->previous;
		if (top)
			top->next = NULL;
		delete temp;
	}
	//Returns the top node
	Node<T>* Peek()
	{
		return top;
	}

	// returns true if stack is empty
	bool IsEmpty()
	{
		return(!top);
	}
	// returns number of nodes in stack
	int GetLength()
	{
		Node<T>* itr = top;
		int count = 0;

		while (itr != nullptr)
		{
			count++;
			itr = itr->previous;
		}
		return count;
	}
	// prints stack from top of stack
	void Output()
	{
		Node<T>* rover = top;
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->previous;
		}
		cout << endl;
	}
};

// PART 4
template<typename T>
class Queue
{
public:
	Node<T>* head, *tail;
	Queue() { head = NULL; tail = NULL; }  // default constructor
	// Adds new node to end of the queue
	void push(T data)
	{
		Node<T>* pdata = new Node<T>(data);
		if (IsEmpty()) {
			head = pdata;
			tail = pdata;
		}
		else {
			tail->next = pdata;
			pdata->previous = tail;
			tail = pdata;
		}
	}
	// Removes first node in the queue
	void Pop()
	{
		if (IsEmpty()) {
			return;
		}
		Node<T>* temp = head;
		head = head->next;
		if(head)
			head->previous = NULL;
		delete temp;
	}
	//Returns the front node
	Node<T>* Peek()
	{
		return head;
	}

	// returns true if queue is empty
	bool IsEmpty()
	{
		return(!head);
	}
	// returns number of nodes in queue
	int GetLength()
	{
		Node<T>* itr = head;
		int count = 0;

		while (itr != nullptr)
		{
			count++;
			itr = itr->next;
		}
		return count;
	}
	// prints queue from front to rear
	void Output()
	{
		Node<T>* rover = head;
		while (rover != NULL)
		{
			cout << rover->data << '\t';
			rover = rover->next;
		}
		cout << endl;
	}
};

void main()
{
	int count = 10;
	Stack<int> stackList;
	Queue<int> queueList;

	cout << "Pushing the following 10 random numbers onto a stack and queue..." << endl;

	for (int x = 0; x < count; x++)
	{
		int rnumber = rand() % 100 + 1;
		stackList.push(rnumber);
		queueList.push(rnumber);
		cout << rnumber << "\t";
	}
	cout << endl << endl;

	cout << "Stack: ";
	stackList.Output();
	cout << "Queue: ";
	queueList.Output();

	cout << endl << "Top of stack: " << stackList.Peek()->data;
	cout << endl << "Front of queue: " << queueList.Peek()->data << endl;

	cout << endl << "Popping one item off of the stack and queue..." << endl << endl;

	stackList.Pop();
	queueList.Pop();

	cout << "Stack: ";
	stackList.Output();
	cout << "Queue: ";
	queueList.Output();

	cout << endl << "Stack Length: " << stackList.GetLength();
	cout << endl << "Queue Length: " << queueList.GetLength();
}