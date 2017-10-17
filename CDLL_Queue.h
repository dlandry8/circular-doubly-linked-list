//----------------------------------------------------------------------------
//	File:			CDLL_Queue.h
//
//	Class:			Queue Class
//
//	Title:			Queue, Inherited from a Circular Doubly-Linked List
//
//	Description:	This file contains the class definitions for the
//						Queue Template Class.
//
//	Programmer:		David Landry
//
//	Date:			5/14/2016
//
//	Version:		0.9
//
//	Environment:	Hardware:	PC with Intel Core i7
//					Software:	Windows 10 64-bit edition
//								Compiled using Microsoft Visual Studio 2013
//									Community
//
//	Class Queue:
//		Description:
//			A queue, built around a circular doubly-linked list.  Data gets
//				pushed in to the back and popped out from the front	(FIFO).
//
//		Properties:
//			listelem head-	This is the node at the front of the queue.
//							It is a listelem struct consisting of the
//							data and pointers to the next and previous data
//							node.  Its previous node is tail.
//			listelem tail-	This is the node at the back of the queue.  
//							It is a listelem struct consisting of the
//							data and pointers to the next and previous data
//							node.  Its next node is head.
//			unsigned m_size-The number of data nodes in the queue.
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
//				Queue<DataType>()
//					Description:	The default constructor
//					Parameters:		None
//					Returns:		None
//					Calls:			List default constructor
//					Called by:		None
//					Input:			None
//					Output:			None
//				Queue<DataType>(size_t n_elements, DataType datum)
//					Description:	Constructor that fills the queue with a
//										quantity of n_elements DataTypes.
//					Parameters:		size_t n_elements- The quantity of items
//										to fill the queue with.
//									DataType datum- The default item to fill
//										the queue with.
//					Returns:		None
//					Calls:			List fill constructor
//					Called by:		None
//					Input:			None
//					Output:			None
//				Queue<DataType>(iterator b, iterator e)
//					Description:	Constructor that copies elements from
//										the indicated beginning and end
//										points.
//					Parameters:		iterator b- the beginning point.
//									iterator e- the end point.
//					Returns:		None
//					Calls:			List iterator constructor
//					Called by:		None
//					Input:			None
//					Output:			None
//				Queue<DataType>(const Queue& x)
//					Description:	The copy constructor
//					Parameters:		const Queue& x
//					Returns:		None
//					Calls:			List copy constructor
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
//					Calls:			List's getSize method
//					Called by:		None
//					Input:			None
//					Output:			None
//				virtual iterator begin() const
//					Description:	Returns an iterator that points to the
//										List's head.
//					Parameters:		None
//					Returns:		head
//					Calls:			List's begin method
//					Called by:		operator<<
//					Input:			None
//					Output:			None
//				virtual iterator end() const
//					Description:	Returns an iterator that points to the
//										List's tail.
//					Parameters:		None
//					Returns:		tail
//					Calls:			List's end method
//					Called by:		operator<<
//					Input:			None
//					Output:			None
//				virtual bool empty()const
//					Description:	Tests whether the List is empty.
//					Parameters:		None
//					Returns:		True if either head or tail points to a
//										nullptr.  Otherwise false.
//					Calls:			List's empty method.
//					Called by:		push_front(); push_back();
//									pop_front(); pop_back()
//					Input:			None
//					Output:			None
//				void release()
//					Description:	empties the list
//					Parameters:		None
//					Returns:		None
//					Calls:			List's release method
//					Called by:		None
//					Input:			None
//					Output:			None
//				void push(DataType element)
//					Description:	insert element at end of list
//					Parameters:		DataType datum- the item to insert
//					Returns:		None
//					Calls:			List's push_back method
//					Called by:		None
//					Input:			None
//					Output:			None
//				DataType pop()
//					Description:	removes front element and returns the data 
//										from that element
//					Parameters:		None
//					Returns:		A DataType equal to the item being popped.
//					Calls:			List's pop_front method
//					Called by:		None
//					Input:			None
//					Output:			None
//				virtual ~Queue<DataType>()
//					Description:	The default constructor
//					Parameters:		None
//					Returns:		None
//					Calls:			None
//					Called by:		None
//					Input:			None
//					Output:			None
//
//	Functions:
//		ostream& operator<<(ostream& sout, const List<DataType>& x)- Outputs 
//			the list to the indicated output stream.
//----------------------------------------------------------------------------
#ifndef DL_CDLL_QUEUE_H
#define DL_CDLL_QUEUE_H

#include "CircDoubLinkList.h"

namespace DL_CDLL
{
	template<class DataType>
	class Queue: virtual protected List<DataType>
	{
		// Declarations will be here; definitions will be down below (except
		//	for very simple one-line inline functions).
	public:
		Queue<DataType>():List<DataType>(){}
		Queue<DataType>(size_t n_elements, DataType datum) :
			List<DataType>(n_elements, datum){}
		Queue<DataType>(iterator b, iterator e):
			List<DataType>(b, e){}
		Queue<DataType>(const List& x) :
			List<DataType>(x){}	
		virtual ~Queue<DataType>() { release(); }
		unsigned getSize() const { return List<DataType>::getSize(); }
		iterator begin() const { return List<DataType>::begin(); }
		iterator end() const { return List<DataType>::end(); }
		bool empty() const { return List<DataType>::empty(); }
		void release() { List<DataType>::release(); }
		void push(DataType element){ List<DataType>::push_back(element); }
		DataType pop(){ return List<DataType>::pop_front(); }
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p){}
			// Prefix increment
			iterator operator++()
			{
				if (ptr == nullptr)
					throw runtime_error("nullptr pointer");
				ptr = ptr->next;
				return *this;
			}
			// Prefix decrement
			iterator operator--()
			{
				if (ptr == nullptr)
					throw runtime_error("nullptr pointer");
				ptr = ptr->prev;
				return *this;
			}
			// Postfix increment
			iterator operator++(int)
			{
				if (ptr == nullptr)
					throw runtime_error("nullptr pointer");
				iterator temp = *this;
				ptr = ptr->next;
				return temp;
			}
			// Postfix decrement
			iterator operator--(int)
			{
				if (ptr == nullptr)
					throw runtime_error("nullptr pointer");
				iterator temp = nullptr;
				ptr = ptr->prev;
				return temp;
			}
			listelem* operator->() const { return ptr; }
			DataType& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};
	};
	template <class DataType>
	ostream& operator<<(ostream& sout, const Queue<DataType>& x);

	//------------------------------------------------------------------------
	//	Function:		ostream& operator<<
	//						(ostream& sout, const Queue<DataType>& x)
	//	Version			1.0
	//	Date			5/13/2016
	//	Description:	prints out a list
	//	Parameters:		ostream& sout- A reference to the output stream.
	//					const Queue<DataType>& x- A reference to the item to 
	//						be printed.
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
	ostream& operator<<(ostream& sout, const Queue<DataType>& x)
	{
		Queue<DataType>::iterator p = x.begin(); // gets x.h
		Queue<DataType>::iterator q = x.begin();	// gets x.h too.
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