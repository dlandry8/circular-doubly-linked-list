//----------------------------------------------------------------------------
//	File:			CircDoubLinkList.h
//
//	Class:			List
//
//	Title:			Circular Doubly-Linked List
//
//	Description:	This file contains the class definitions for the
//						CDLL Template Class.
//
//	Programmer:		David Landry
//					Using starting code provided by Paul Bladek
//
//	Date:			5/19/2016
//
//	Version:		1.1
//
//	Environment:	Hardware:	PC with Intel Core i7
//					Software:	Windows 10 64-bit edition
//								Compiled using Microsoft Visual Studio 2013
//									Community
//
//	Class List:
//		Allows the use, pushing to, and popping from a circular doubly-linked
//			list.
//
//		Properties:
//			listelem head-	This is the node inserted to or popped from the 
//							front.  It is a listelem struct consisting of the
//							data and pointers to the next and previous data
//							node.  Its previous node is tail.
//			listelem tail-	This is the node inserted to or popped from the
//							back.  It is a listelem struct consisting of the
//							data and pointers to the next and previous data
//							node.  Its next node is head.
//			unsigned m_size-The number of data nodes in the list.
//
//		Classes and structs contained within:
//			listelem-		Each is one data node, containing a DataType, a
//							pointer to previous, and a pointer to next.
//				Properties:
//						DataType data- The data contained within a node in the
//							list.
//						listelem *next- A pointer to the next linked node in
//							the list (or the 1st if the current node is the
//							tail).
//						listelem *prev- A pointer to the previous linked node
//							in the list (or to the last if the current node is
//							the first).
//				Method:		
//						listelem(DataType datum, listelem* p, listelem* n)-
//							The constructor for the listelem struct.
//			iterator-		The iterator class.  This is a wrapper around a
//							pointer associated with this list class.
//				Properties:
//						listelem* ptr- A pointer to the listelem that the
//							iterator points to.
//				Methods:
//						iterator(listelem* p = nullptr)- Default constructor
//						iterator operator++()- Prefix incrementer.
//						iterator operator--()- Prefix decrementer.
//						iterator operator++(int)- Postfix incrementer.
//						iterator operator--(int)- Prefix decrementer.
//						listelem* operator->() const- Target operator.
//							Accesses listelem's members using the iterator.
//						DataType& operator*() const- Dereferencing operator.
//							Accesses the reference of the DataType.
//						operator listelem*() const- Dereferencing operator.
//							Accesses the value of the listelem.
//
//		Methods:
//			Inline:
//				List<DataType>()
//					Description:	The default constructor
//					Parameters:		None
//					Returns:		None
//					Calls:			None
//					Called by:		None
//					Input:			None
//					Output:			None
//				List<DataType>(size_t n_elements, DataType datum)
//					Description:	Constructor taking in a quantity of
//										n_element DataTypes.
//					Parameters:		size_t n_elements- The number of elements
//										to construct the object with.
//									DataType datum- The data to fill the List
//										with.
//					Returns:		None
//					Calls:			None
//					Called by:		None
//					Input:			None
//					Output:			None
//				~List<DataType>()
//					Description:	The destructor.
//					Parameters:		None
//					Returns:		None
//					Calls:			release()
//					Called by:		None
//					Input:			None
//					Output:			None
//				virtual unsigned getSize() const
//					Description:	Returns the number of data nodes in the
//										List.
//					Parameters:		None
//					Returns:		m_size
//					Calls:			None
//					Called by:		operator[]
//									operator[] const
//					Input:			None
//					Output:			None
//				virtual iterator begin() const
//					Description:	Returns an iterator that points to the
//										List's head.
//					Parameters:		None
//					Returns:		head
//					Calls:			None
//					Called by:		Copy constructor
//									operator=
//									pop_front()
//									operator[]
//									operator<<
//					Input:			None
//					Output:			None
//				virtual iterator end() const
//					Description:	Returns an iterator that points to the
//										List's tail.
//					Parameters:		None
//					Returns:		tail
//					Calls:			None
//					Called by:		Copy constructor
//									operator=
//									pop_back()
//									operator[]
//									operator<<
//					Input:			None
//					Output:			None
//				virtual bool empty()const
//					Description:	Tests whether the List is empty.
//					Parameters:		None
//					Returns:		True if either head or tail points to a
//										nullptr.  Otherwise false.
//					Calls:			None
//					Called by:		push_front(); push_back();
//									pop_front(); pop_back()
//					Input:			None
//					Output:			None
//
//			Non-inline:
//				List<DataType>(const List& x)- Copy constructor.
//				List<DataType>(iterator b, iterator e)- Constructor that uses
//					iterators to construct a list.
//				void push_front(DataType datum)- Adds a data node to the front 
//					of the list, also adding 1 to the size of the list.
//				DataType pop_front()- Removes a data node from the front of
//					the list, reducing its size by 1, and returning the value
//					stored in that data node.
//				push_back(DataType datum)- Adds a data node to the back of the
//					list, also adding 1 to the size of the list.
//				DataType pop_back()- Removes a data node from the back of the
//					list, reducing its size by 1, and returning the value
//					stored in that data node.
//				DataType& front() const- Returns the data value in the head
//					data node.
//				DataType& back() const- Returns the data value in the tail
//					data node.
//				void release()- Empties the list, resetting its size to 0,
//					freeing the memory of each data node, and setting each
//					pointer to nullptr.
//				List<DataType>operator=- Sets the contents of one List to that 
//					of another.
//				DataType operator[](int index)- Accesses the data in the data
//					node at the index within the brackets for editing.
//				DataType operator[](int index) const- Accesses the data in the
//					data node at the index within the brackets for read access
//
//	Functions:
//		ostream& operator<<(ostream& sout, const List<DataType>& x)- Outputs 
//			the list to the indicated output stream.
//----------------------------------------------------------------------------
#ifndef DL_CIRCULAR_DOUBLY_LINKED_LIST_H
#define DL_CIRCULAR_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
#include <string>

using namespace std;

namespace DL_CDLL
{
	template<class DataType>
	class List
	{
	public:
		// forward declarations:
		struct listelem;
		class iterator;

		// constructors
		List<DataType>() : head(nullptr), tail(nullptr), m_size(0) {}
		List<DataType>(size_t n_elements, DataType datum);
		List<DataType>(const List& x);
		List<DataType>(iterator b, iterator e);

		// Destructor
		virtual ~List<DataType>() { release(); }

		// Public methods:
		virtual unsigned getSize() const { return m_size; }
		virtual iterator begin() const { return head; }
		virtual iterator end() const { return tail; }
		void push_front(DataType datum);
		DataType pop_front();
		void push_back(DataType datum);
		DataType pop_back();
		DataType& front() const;
		DataType& back() const;
		virtual bool empty()const 
			{ return head == nullptr || tail == nullptr; }
		void release();
		List<DataType> operator=(const List<DataType> & rlist);
		DataType& operator[](int index);
		const DataType& operator[](int index) const;
	private:
		// Properties:
		listelem *head;
		listelem *tail;
		unsigned m_size; // number of elements in the list
	public:
		// The struct for each node and the List-scoped iterator class are
		//	configured here.
		struct listelem // list cell
		{
			DataType data;
			listelem *next;
			listelem *prev;
			// Struct constructor:
			listelem(DataType datum, listelem* p, listelem* n)
				: data(datum), prev(p), next(n) {}
		};
		// Iterator class is scoped within List class!
		// Here's its setup:
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p){}
			// Prefix increment
			iterator operator++()
			{
				if (ptr == nullptr)
					throw runtime_error
					("Could not increment the iterator: nullptr pointer");
				ptr = ptr->next;
				return *this;
			}
			// Prefix decrement
			iterator operator--()
			{
				if (ptr == nullptr)
					throw runtime_error
					("Could not decrement the iterator: nullptr pointer");
				ptr = ptr->prev;
				return *this;
			}
			// Postfix increment
			iterator operator++(int)
			{
				if (ptr == nullptr)
					throw runtime_error
					("Could not increment the iterator: nullptr pointer");
				iterator temp = *this;
				ptr = ptr->next;
				return temp;
			}
			// Postfix decrement
			iterator operator--(int)
			{
				if (ptr == nullptr)
					throw runtime_error
					("Could not decrement the iterator: nullptr pointer");
				iterator temp = nullptr;
				ptr = ptr->prev;
				return temp;
			}
			listelem* operator->() const { return ptr; }
			DataType& operator*() const
			{ 
				if (ptr == nullptr) 
					throw runtime_error
					("Could not retrieve data from an empty list.");
				else return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};	// End List::iterator class declarations.
	}; // End List class declarations.

	// Here is the declaration for the overloaded output operator used by the 
	//	List class:
	template <class DataType>
	ostream& operator<<(ostream& sout, const List<DataType>& x);

	// Definitions for the List class now follow.

	//------------------------------------------------------------------------
	//	Method:			List<DataType>::List(size_t n_elements,DataType datum)
	//	Version			1.1
	//	Date			5/19/2016
	//	Description:	Constructor that fills the list with a quantity of
	//						n_elements DataTypes.
	//	Parameters:		size_t n_elements- the quantity of items to fill the
	//						List with.
	//					DataType datum- the data to fill the List with.
	//	Returns:		None
	//	Calls:			push_front()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Throws:			out_of_range
	//	Changelog		4/15/2011	PB	completed version 0.7
	//					4/29/2016	DL	completed version 0.8, adapting the 
	//										code to the template class
	//										List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//					5/19/2016	DL	completed version 1.1, writing a
	//										more specific exception throw
	//										message.
	//------------------------------------------------------------------------
	template <class DataType>
	List<DataType>::List(size_t n_elements, DataType datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Could not create List object: Empty list");
		for (size_t i = 0; i < n_elements; ++i)
		{
			push_front(datum);
		}
	}

	//------------------------------------------------------------------------
	//	Method:			List<DataType>::List(const List& source)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	Copy constructor
	//	Parameters:		const List& source- the List to copy from.
	//	Returns:		None
	//	Calls:			begin()
	///					end()
	//					push_back()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB	completed version 0.4
	//					4/29/2016	DL	completed version 0.5, adapting the 
	//										code to the List<DataType>
	//										template class.
	//					5/13/2016	DL	completed version 1.0, fixing memory-
	//										related bugs.
	//------------------------------------------------------------------------
	template <class DataType>
	List<DataType>::List(const List& source)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		m_size = source.m_size;
		//listelem* toCopy = new listelem[m_size];
		List<DataType>::iterator r_it = source.begin();
		while (r_it != source.end())
			push_back(*r_it++);
		push_back(*r_it);
		m_size = source.m_size;
	}

	//------------------------------------------------------------------------
	//	Method:			List<DataType>::List(iterator b, iterator e)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	constructor using iterators, copies from b to one 
	//						before e
	//	Parameters:		iterator b- the begin iterator.
	//					iterator e- the end iterator.
	//	Returns:		None
	//	Calls:			push_back()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB	completed version 0.7
	//					4/29/2016	DL	completed version 0.8, adapting it to 
	//										the template class List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	List<DataType>::List(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (b != e)
			push_back(*b++);
		push_back(*b);
	}

	//------------------------------------------------------------------------
	//	Method:			void List<DataType>::release()
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	empties the list
	//	Parameters:		None
	//	Returns:		None
	//	Calls:			pop_front()
	//	Called by:		~List() (the destructor)
	//					operator=
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB	completed version 0.8
	//					4/29/2016	DL	completed version 0.9, adapting it to 
	//										the template class List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	void List<DataType>::release()
	{
		while (head != tail)
			List::pop_front();
		if (head == tail && tail != nullptr)
			List::pop_front();
		head = tail = nullptr;
	}

	//------------------------------------------------------------------------
	//	Method:			void List<DataType>::push_front(DataType datum)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	insert element at front of list
	//	Parameters:		DataType datum- the data to insert
	//	Returns:		None
	//	Calls:			listelem struct constructor
	//					empty()
	//	Called by:		Fill constructor
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB	completed version 0.8
	//					4/29/2016	DL	copied from PB's list push_front
	//										method and changed it to 
	//										List<DataType> push_front.
	//					5/4/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template<class DataType>
	void List<DataType>::push_front(DataType datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())
		{ // was a nonempty list
			head->prev = temp;
			head = temp;
			//head->prev = tail;
			tail->next = head;
		}
		else
		{
			temp->prev = temp;
			temp->next = temp;
			head = tail = temp;
		}
	}

	//------------------------------------------------------------------------
	//	Method:			void List<DataType>::push_back(DataType datum)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	insert element at end of list
	//	Parameters:		DataType datum- the item to insert
	//	Returns:		None
	//	Calls:			listelem struct constructor
	//					empty()
	//	Called by:		Copy Constructor
	//					Iterator constructor
	//					operator=
	//	Input:			None
	//	Output:			None
	//	Changelog		5/2/2016	DL	completed version 0.5, but seems to 
	//										have gotten the pointers in the 
	//										incorrect order.
	//					5/4/2016	DL	completed version 0.9.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template<class DataType>
	void List<DataType>::push_back(DataType datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())
		{ // was a nonempty list
			tail->next = temp;
			tail = temp;
			//tail->next = head;
			head->prev = tail;
		}
		else
		{
			head = tail = temp;
			head->prev = tail;
			head->next = tail;
			tail->prev = head;
			tail->next = tail;
		}
	}

	//------------------------------------------------------------------------
	//	Method:			List<DataType> List<DataType>::operator=
	//						(const List<DataType>& rlist)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	returns a copy of rlist
	//	Parameters:		const List<DataType>& rlist- the List to copy from.
	//	Returns:		A List<DataType> that is a copy of rlist.
	//	Calls:			begin()
	//					end()
	//					release()
	//					push_back()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB completed version 0.5
	//					4/29/2016	DL	completed version 0.6, adapting the 
	//										code to fit the mold of the 
	//										template class List<DataType>.
	//					5/4/2016	DL	completed version 0.8, correcting the
	//										order of list elements copied to
	//										the new list.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	List<DataType> List<DataType>::operator=(const List<DataType>& rlist)
	{
		if (&rlist != this)
		{
			List<DataType>::iterator r_it = rlist.begin();
			release();
			while (r_it != rlist.end())
				push_back(*r_it++);
			push_back(*r_it);
		}
		return *this;
	}

	//------------------------------------------------------------------------
	//	Method:			DataType List<DataType>::pop_front()
	//	Version			1.1
	//	Date			5/19/2016
	//	Description:	removes front element and returns the data from that 
	//						element
	//	Parameters:		None
	//	Returns:		A DataType equal to the item being popped.
	//	Calls:			begin()
	//					empty()
	//	Called by:		release()
	//	Input:			None
	//	Output:			None
	//	Throws:			runtime_error
	//	Changelog		4/15/2011	PB	completed version 0.7
	//					4/30/2016	DL	completed version 0.8, adapting the 
	//										code to the template class 
	//										List<DataType>.
	//					5/13/2016	DL	completed version 1.0, fixing memory-
	//										related bugs.
	//					5/19/2016	DL	completed version 1.1, adding clearer
	//										exception throw message.
	//------------------------------------------------------------------------
	template <class DataType>
	DataType List<DataType>::pop_front()
	{
		if (head == nullptr)
			throw runtime_error("Could not remove front item: Empty list");
		m_size--;
		DataType data = head->data;
		iterator temp = begin();
		temp++;
		if (m_size >= 0)
			delete head;
		if (m_size == 0)
			head = nullptr;
		if (!empty())
		{
			head = temp;
			head->prev = tail;
			tail->next = head;
		}
		else
			head = tail = nullptr; // empty at both ends
		return data;
	}

	//------------------------------------------------------------------------
	//	Method:			DataType List<DataType>::pop_back()
	//	Version			1.1
	//	Date			5/19/2016
	//	Description:	removes back element and returns the data from that 
	//						element
	//	Parameters:		None
	//	Returns:		A DataType that equals the item being popped.
	//	Calls:			iterator::end()
	//					empty()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Throws:			runtime_error
	//	Changelog		5/5/2016	DL	completed version 0.4
	//					5/5/2016	DL	completed version 0.8, fixing the
	//										iterator.
	//					5/13/2016	DL	completed version 1.0, fixing memory-
	//										related bugs.
	//					5/19/2016	DL	completed version 1.1, writing a
	//										more specific exception throw
	//										message.
	//------------------------------------------------------------------------
	template <class DataType>
	DataType List<DataType>::pop_back()
	{
		if (tail == nullptr)
			throw runtime_error
			("Could not remove item from the back: Empty list");
		m_size--;
		DataType data = tail->data;
		iterator temp = end();
		temp--;
		if (m_size >= 0)
			delete tail;
		if (m_size == 0)
			tail = nullptr;
		if (!empty())
		{
			tail = temp;
			tail->next = head;
			head->prev = tail;
		}
		else
			head = tail = nullptr; // empty at both ends
		return data;
	}

	//------------------------------------------------------------------------
	//	Method:			DataType& front() const
	//	Version:		1.1
	//	Date:			5/19/2016
	//	Description:	Returns the data value within the head.
	//	Parameters:		None
	//	Returns:		head->data
	//	Calls:			None
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Throws:			runtime_error
	//	Changelog:		5/13/2016	DL	completed version 1.0
	//					5/19/2016	DL	completed version 1.1, correcting a
	//										program-breaking bug when
	//										attempting to access the head of
	//										an empty list.
	//------------------------------------------------------------------------
	template<class DataType>
	DataType& List<DataType>::front() const 
	{ 
		if (empty())
			throw runtime_error
			("Could not access the front value of an empty list.");
		else
			return head->data;
	}

	//------------------------------------------------------------------------
	//	Method:			DataType& back() const
	//	Version:		1.1
	//	Date:			5/19/2016
	//	Description:	Returns the data value within the tail.
	//	Parameters:		None
	//	Returns:		tail->data
	//	Calls:			None
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Throws:			runtime_error
	//	Changelog:		5/13/2016	DL	completed version 1.0
	//					5/19/2016	DL	completed version 1.1, correcting a
	//										program-breaking bug when
	//										attempting to access the tail of
	//										an empty list.
	//------------------------------------------------------------------------
	template<class DataType>
	DataType& List<DataType>::back() const
	{ 
		if (empty()) 
			throw runtime_error
			("Could not access the back value of an empty list."); 
		else 
			return tail->data; 
	}

	//------------------------------------------------------------------------
	//	Method:			DataType& List<DataType>::operator[](int index)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	[] operator -- Modifiable l-value
	//	Parameters:		int index- An integer used to get the index of the
	//						desired item.
	//	Returns:		DataType&, a reference to the data contained at the
	//						index.
	//	Calls:			getSize()
	//					end()
	//					begin()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/1011	PB	completed version 0.6
	//					4/30/2016	DL	completed version 0.7, adapting the 
	//										code to the template class 
	//										List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	DataType& List<DataType>::operator[](int index)
	{
		iterator it;
		int testSize = getSize();
		int midpoint = getSize() / 2;
		List<DataType>* midPointer = this + midpoint;
		if (index < 0)
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			index = getSize() + index;
		}
		else
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
		}
		if (index >= midpoint)
		{
			it = end();
			for (int i = getSize() - 1; i > index; i--)
				it--;
		}
		else
		{
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		return *it;
	}

	//------------------------------------------------------------------------
	//	Method:			const DataType& List<DataType>::operator[](int index)
	//						const
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	[] operator -- Non-modifiable r-value
	//	Parameters:		int index- An integer used to get the index of the
	//						desired item.
	//	Returns:		A const DataType&; a reference to the item.
	//	Calls:			getSize()
	//					end()
	//					begin()
	//	Called by:		None
	//	Input:			None
	//	Output:			None
	//	Changelog		4/15/2011	PB	completed version 0.6
	//					4/30/2016	DL	completed version 0.7, adapting the 
	//										code to the template class 
	//										List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	const DataType& List<DataType>::operator[](int index)const
	{
		iterator it;
		int midpoint = getSize() / 2;
		List<DataType>* midPointer = this + midpoint;
		if (index < 0)
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			index = getSize() - index;
		}
		else
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
		}
		if (index > midpoint)
		{
			it = end();
			for (int i = getSize() - 1; i > index; i--)
				it--;
		}
		else
		{
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		return *it;
	}

	//------------------------------------------------------------------------
	//	Function:		ostream& operator<<
	//						(ostream& sout, const List<DataType>& x)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	prints out a list
	//	Parameters:		ostream& sout- A reference to the output stream.
	//					const List<DataType>& x- A reference to the item to be
	//						printed.
	//	Returns:		The ostream&
	//	Calls:			begin()
	//					end()
	//	Called by:		None
	//	Input:			None
	//	Output:			The data contents of the List.
	//	Changelog		4/15/2011	PB	completed version 0.8
	//					4/29/2016	DL	completed version 0.9, adapting it to
	//										the template class List<DataType>.
	//					5/13/2016	DL	completed version 1.0.
	//------------------------------------------------------------------------
	template <class DataType>
	ostream& operator<<(ostream& sout, const List<DataType>& x)
	{
		List<DataType>::iterator p = x.begin(); // gets x.h
		List<DataType>::iterator q = x.begin();	// gets x.h too.
		sout << "(";
		if (p != nullptr)
		{
			do
			{
				sout << *q;
				if (q != x.end())
					sout << ",";
				++q; // advances iterator using next
			} while (p != q);
		}
		sout << ")\n";
		return sout;
	}


} // End DL_CDLL namespace.

#endif