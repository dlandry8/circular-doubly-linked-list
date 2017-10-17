//----------------------------------------------------------------------------
//	File:		CDLLTester.cpp
//
//	Functions:	main()
//				testCDLL()
//				testExceptCDLL()
//				testQueue()
//----------------------------------------------------------------------------
#include "CircDoubLinkList.h"
#include "CDLL_Queue.h"
using namespace DL_CDLL;

void testCDLL();
void testQueue();
void testExceptCDLL();

//----------------------------------------------------------------------------
//	Function:		main
//
//	Description:	Main menu for testing List and Queue class.
//
//	Programmer:		David Landry
//	
//	Version:		1.0
//
//	Date:			5/19/2016
//
//	Environment:	Hardware:
//						Intel Core i7 processor
//					Software:
//						PC powered by Windows 10
//						Compiled using Microsoft Visual Studio Community 2013.
//
//	Parameters:		None
//
//	Returns:		EXIT_SUCCESS or EXIT_FAILURE
//
//	Calls:			testCDLL(), testExceptCDLL(), testQueue()
//
//	Called by:		None
//
//	Input:			Menu prompt.
//
//	Output:			Menu options.
//----------------------------------------------------------------------------
int main()
{
	//using DL_CDLL::List; // not the same as std::list<class T>
	unsigned short menuSelection;
	do
	{
		system("CLS");
		cout << "Select a test." << endl << endl;
		cout << "\t1. CDLL standard tests.\n";
		cout << "\t2. CDLL exception tests.\n";
		cout << "\t3. Queue tests.\n";
		cout << "\t0. Quit\n";
		(cin >> menuSelection).get();
		system("CLS");
		switch (menuSelection)
		{
		case 1:
			testCDLL();
			break;
		case 2:
			testExceptCDLL();
			break;
		case 3:
			testQueue();
			break;
		default:
			break;
		}
	} while (menuSelection > 0);
	return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------
//	Function:		testCDLL
//
//	Description:	Test driver for a circular doubly-linked list.
//
//	Programmer:		David Landry
//	
//	Version:		1.0
//
//	Date:			5/19/2016
//
//	Environment:	Hardware:
//						Intel Core i7 processor
//					Software:
//						PC powered by Windows 10
//						Compiled using Microsoft Visual Studio Community 2013.
//
//	Parameters:		None
//
//	Returns:		None
//
//	Calls:			Various methods of the List class
//
//	Called by:		main
//
//	Input:			Prompts to continue.
//
//	Output:			Data from the List class
//----------------------------------------------------------------------------
void testCDLL()
{
	try
	{
		cout << "Constructor Tests" << endl;
		cout << "=================" << endl;
		List<char> emptyList;
		List<int> filledList(4, 5);
		List<string> stringList(3, "Test string");
		List<string> strList2(stringList);
		cout << "emptyList: " << emptyList << "Size: " << emptyList.getSize() 
			<< endl << endl;
		cout << "filledList (4 ints, each with value 5): " << filledList << 
			"Size: " << filledList.getSize() << endl << endl;
		cout << "stringList (3 strings, each with a test message): " << 
			stringList << "Size: " << stringList.getSize() << endl << endl;
		cout << "strList2 (copy of stringList): " << strList2 << "Size: " << 
			strList2.getSize() << endl << endl;
		cout << "Press \"Enter\" to continue."; cin.get();
		system("CLS");
		cout << "Various tests on fillList and itList" << endl;
		cout << "====================================" << endl;
		cout << "emptyList: " << emptyList;
		for (char fillList = 'A'; fillList <= 'H'; fillList++)
		{
			cout << "Pushing " << fillList << " to the front." << endl;
			emptyList.push_front(fillList);
		}
		cout << "emptyList now filled with letters: " << emptyList << "Size: " 
			<< emptyList.getSize() << endl << endl;
		List<char>::iterator itStart = emptyList.begin();
		for (unsigned short i = 0; i < 4; i++)
			itStart++;
		List<char>::iterator itEnd = emptyList.end();
		List<char> itList(itStart, itEnd);
		cout << "itList (using iterators copying from emptyList): " << itList 
			<< "Size: " << itList.getSize() << endl << endl;
		cout << "First character in itList is " << *itList.begin() << endl;
		cout << "Last character in itList is " << *itList.end() << endl;
		cout << "Popping the " << emptyList.pop_front() << " from emptyList." 
			<< endl;
		cout << "Popping the " << emptyList.pop_front() << " from emptyList." 
			<< endl;
		cout << "Popping the " << emptyList.pop_front() << " from emptyList." 
			<< endl;
		cout << "emptyList: " << emptyList << "Size: " << emptyList.getSize() 
			<< endl;
		cout << "\tFront: " << emptyList.front() << "\tBack: " << 
			emptyList.back() << endl;
		cout << "Press \"Enter\" to continue."; cin.get();
		system("CLS");
		cout << "Remaining List Tests" << endl;
		cout << "====================" << endl;
		for (unsigned short i = 6; i <= 8; i++)
		{
			cout << "Pushing " << i << " to the end of filledList." << endl;
			filledList.push_back(i);
		}
		cout << "filledList: " << filledList << "Size: " << 
			filledList.getSize() << endl << endl;
		for (unsigned short i = 0; i < 4; i++)
			cout << "Popping " << filledList.pop_back() << ":\n";
		cout << "filledList: " << filledList << endl;
		if (stringList.empty())
			cout << "stringList is empty.";
		else
			cout << "stringList is NOT empty!";
		cout << endl << "Using release() on stringList:" << endl;
		stringList.release();
		cout << "stringList: " << stringList << "Size: " << 
			stringList.getSize();
		if (stringList.empty())
			cout << " stringList is now empty." << endl;
		else
			cout << " stringList is NOT empty!" << endl;
		List<string> SL2;
		SL2.push_back("this");
		SL2.push_back("IS");
		SL2.push_back("a");
		SL2.push_back("TEST");
		cout << "New created string list, SL2:" << endl << SL2;
		cout << "Setting stringList equal to SL2.";
		stringList = SL2;
		cout << "stringList:\n" << stringList << "Size: " << 
			stringList.getSize() << "  Empty? ";
		if (stringList.empty())
			cout << "Yes." << endl;
		else
			cout << "No." << endl;
		cout << "stringList[0] should equal \"this\":  " << stringList[0] << 
			endl;
		cout << "stringList[-1] should equal \"TEST\":  " << stringList[-1] <<
			endl;
		cout << "Changing stringList[1]..." << endl;
		stringList[1] = "BE";
		cout << "stringList:" << stringList;
		cout << "Press \"Enter\" to continue."; cin.get();
		system("CLS");
		cout << "Iteration and Circularity Testing" << endl;
		cout << "=================================" << endl;
		cout << "Using itList for testing: " << itList;
		List<char>::iterator it2 = itList.begin();
		cout << "How many iterator hops would you like to test? ";
		int trials = 0;
		(cin >> trials).get();
		
		for (int i = 0; i < trials; i++)
		{
			cout << "Iterator: " << it2 << "\tValue: " << *it2;
			if (it2 == itList.begin())
				cout << "\tHead.";
			if (it2 == itList.end())
				cout << "\tTail.";
			cin.get();
			it2++;
		}
		it2 = itList.begin();
		cout << "How many iterator hops would you like to test? ";
		(cin >> trials).get();

		for (int i = 0; i < trials; i++)
		{
			cout << "Iterator: " << it2 << "\tValue: " << *it2;
			if (it2 == itList.begin())
				cout << "\tHead.";
			if (it2 == itList.end())
				cout << "\tTail.";
			cin.get();
			++it2;
		}
		it2 = itList.end();
		cout << "How many iterator hops would you like to test? ";
		(cin >> trials).get();

		for (int i = 0; i < trials; i++)
		{
			cout << "Iterator: " << it2 << "\tValue: " << *it2;
			if (it2 == itList.begin())
				cout << "\tHead.";
			if (it2 == itList.end())
				cout << "\tTail.";
			cin.get();
			it2--;
		}
		it2 = itList.end();
		cout << "How many iterator hops would you like to test? ";
		(cin >> trials).get();

		for (int i = 0; i < trials; i++)
		{
			cout << "Iterator: " << it2 << "\tValue: " << *it2;
			if (it2 == itList.begin())
				cout << "\tHead.";
			if (it2 == itList.end())
				cout << "\tTail.";
			cin.get();
			--it2;
		}
	}
	catch (exception e)
	{
		cerr << "program terminated: " << e.what() << endl;
		cin.get();
	}

}

//----------------------------------------------------------------------------
//	Function:		testExceptCDLL
//
//	Description:	Test driver for exceptions thrown by the circular 
//						doubly-linked list.
//
//	Programmer:		David Landry
//	
//	Version:		1.0
//
//	Date:			5/19/2016
//
//	Environment:	Hardware:
//						Intel Core i7 processor
//					Software:
//						PC powered by Windows 10
//						Compiled using Microsoft Visual Studio Community 2013.
//
//	Parameters:		None
//
//	Returns:		None
//
//	Calls:			Various methods of the List class
//
//	Called by:		main
//
//	Input:			Prompts to continue.
//
//	Output:			Data from the List class
//----------------------------------------------------------------------------
void testExceptCDLL()
{
	List<int> tempEmpty;
	cout << "Created a list of size " << tempEmpty.getSize() << "." << endl;
	List<int>::iterator testIt;
	testIt = tempEmpty.begin();
	cout << "testIt: " << testIt << endl;
	if (tempEmpty.empty())
		cout << "tempEmpty is empty, as it should be." << endl;
	else
		cout << "tempEmpty is not empty.  Something's wrong." << endl;
	try
	{
		//cout << tempEmpty.front();
		//cout << tempEmpty.back();
		//cout << tempEmpty.pop_back();
		//cout << tempEmpty.pop_front();
		testIt = tempEmpty.begin();
		//cout << *testIt;
		testIt = tempEmpty.end();
		//cout << *testIt;
		//cout << "Value at index 0 is " << tempEmpty[0];
		//cout << "Value at index 5 is " << tempEmpty[5];
		//testIt++;
		//++testIt;
		testIt--;
		--testIt;
	}
	catch (runtime_error e)
	{
		cout << "Function failed:  " << e.what();
	}
	catch (out_of_range e)
	{
		cout << "Invalid index:  " << e.what();
	}
	cin.get();
}

//----------------------------------------------------------------------------
//	Function:		testQueue
//
//	Description:	Test driver for a Queue inherited from a circular
//						doubly-linked list.
//
//	Programmer:		David Landry
//	
//	Version:		1.0
//
//	Date:			5/19/2016
//
//	Environment:	Hardware:
//						Intel Core i7 processor
//					Software:
//						PC powered by Windows 10
//						Compiled using Microsoft Visual Studio Community 2013.
//
//	Parameters:		None
//
//	Returns:		None
//
//	Calls:			Various methods of the Queue class
//
//	Called by:		main
//
//	Input:			Prompts to continue.
//
//	Output:			Data from the Queue class
//----------------------------------------------------------------------------
void testQueue()
{
	try
	{
		cout << "Constructor Tests" << endl;
		cout << "=================" << endl;
		Queue<char> emptyQueue;
		Queue<int> filledQueue(4, 5);
		Queue<string> stringQueue(3, "Test string");
		Queue<string> strQueue2(stringQueue);
		cout << "emptyQueue: " << emptyQueue << "Size: " << 
			emptyQueue.getSize() << endl << endl;
		cout << "filledQueue (4 ints, each with value 5): " << filledQueue << 
			"Size: " << filledQueue.getSize() << endl << endl;
		cout << "stringQueue (3 strings, each with a test message): " << 
			stringQueue << "Size: " << stringQueue.getSize() << endl << endl;
		cout << "strQueue2 (copy of stringQueue): " << strQueue2 << "Size: " 
			<< strQueue2.getSize() << endl << endl;
		cout << "Press \"Enter\" to continue."; cin.get();
		system("CLS");
		cout << "Test other methods" << endl;
		cout << "==================" << endl;
		for (char pushStuff = 'A'; pushStuff <= 'E'; pushStuff++)
		{
			cout << "Adding " << pushStuff << " to the queue." << endl;
			emptyQueue.push(pushStuff);
		}
		cout << "Filled emptyQueue: " << emptyQueue;
		cout << "Creating a new queue, itQueue." << endl;
		Queue<char> itQueue(emptyQueue.begin(), emptyQueue.end());
		cout << "itQueue: " << itQueue;
		cout << "First character: " << *itQueue.begin() << 
			".  Last character: " << *itQueue.end() << endl;
		cout << "Is stringQueue empty?  ";
		if (stringQueue.empty())
			cout << "Yes!" << endl;
		else
			cout << "No!" << endl;
		cout << "Using release() on stringQueue to empty it:" << endl;
		stringQueue.release();
		cout << "Is stringQueue empty?  ";
		if (stringQueue.empty())
			cout << "Yes!" << endl;
		else
			cout << "No!" << endl;
		cout << "Emptying itQueue one item at a time:" << endl;
		unsigned size = itQueue.getSize();
		for (short i = 0; i < size; i++)
		{
			cout << "Removing the " << itQueue.pop() << endl;
		}
		cout << "itQueue: " << itQueue << "Size: " << itQueue.getSize() << 
			endl;
		cout << "Press \"Enter\" to continue."; cin.get();
	}
	catch (exception e)
	{
		cout << e.what();
	}

}