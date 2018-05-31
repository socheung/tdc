#pragma once

#ifndef TDC_LIST_H
#define TDC_LIST_H

#include <initializer_list>
#include <utility>

// tdc namespace
namespace tdc {

// single linked list
template <class T>
class List {
public:
	class const_iterator;
	class iterator;
	class ListNode;

	// constructors
	List() : head(nullptr), tail(nullptr), count(0) { initialize(); }
	List(std::initializer_list<T> other);	// for initializer list constructor
	List(const List& other);				// for copy
	List(List&& other) 						// for move
	: head(std::move(other.head)) , tail(std::move(other.tail))
	, count(std::move(other.count))
	{
		other.initialize();					// reinitialize other after its members moved
	}
	List& operator= (const List& rhs);		// for assignment
	List& operator= (List&& rhs);			// for move
	~List();

	// access
	T& front() { return (*begin()); }
	const T& front() const { return (*begin()); }
	T& back() { return (*(--end())); }
	const T& back() const { return (*(--end())); }

	// iterators
	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();

	// capacity
	bool empty() const { return (count == 0); }
	unsigned int size() const { return count; }

	// modifiers
	void clear();
	iterator insert(const iterator& pos, const T& value);
	iterator erase(const iterator& pos);
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	void swap(List& rhs);

	// test
	bool equal(const List& other) const;
	bool operator==(const List& other) const { return equal(other); }
	bool operator!=(const List& other) const { return !equal(other); }

	// double linked node
	class ListNode {
	public:
		explicit ListNode(const T& data = T{}) : data(data), prev(nullptr), next(nullptr) {}
	private:
		T 				data;
		ListNode*		prev;
		ListNode*		next;
		friend class List<T>;
	};

	class const_iterator {
	public:
		explicit const_iterator() : curr(nullptr) {}

		const T& operator* ()
		{
			return retrieve();
		}

		const_iterator& operator++ ()		// pre-increment
		{
			if (!curr) throw std::out_of_range("forward out of range");
			curr = curr->next;
			return *this;
		}

		const_iterator& operator++ (int)	// post-increment
		{
			auto old = *this;
			operator++();					// use pre-increment implementation
			return old;						// return old self
		}

		const_iterator& operator-- ()		// pre-decrement
		{
			if (!curr) throw std::out_of_range("backward out of range");
			curr = curr->prev;
			return *this;
		}

		const_iterator& operator-- (int)	// post-decrement
		{
			auto old = *this;
			operator--();					// use pre-decrement implementation
			return old;						// return old self
		}

		const_iterator& operator+ (int n)
		{
			if (n < 0) return operator-(-n);
			while (n--)
				operator++();
			return *this;
		}

		const_iterator& operator- (int n)
		{
			if (n < 0) return operator+(-n);
			while (n--)
				operator--();
			return *this;
		}

		bool operator== (const const_iterator& rhs) const
		{
			return (curr == rhs.curr);
		}

		bool operator!= (const const_iterator& rhs) const
		{
			return (curr != rhs.curr);
		}

	protected:
		ListNode* curr;
		explicit const_iterator(ListNode* p) : curr(p) {}
		T& retrieve()
		{
			if (!curr) throw std::out_of_range("out of range");
			return curr->data;
		}

		friend class List<T>;
	};
	
	class iterator : public const_iterator {
	public:
		T& operator* ()
		{
			return const_iterator::retrieve();
		}

		iterator& operator++ ()		// pre-increment
		{
			const_iterator::operator++();
			return *this;
		}

		iterator& operator++ (int)	// post-increment
		{
			auto old = *this;
			++(*this);
			return old;				// return old self
		}

		iterator& operator-- ()		// pre-decrement
		{
			const_iterator::operator--();
			return *this;
		}

		iterator& operator-- (int)	// post-decrement
		{
			auto old = *this;
			--(*this);
			return old;				// return old self
		}

		iterator& operator+ (int n)
		{
			const_iterator::operator+(n);
			return *this;
		}

		iterator& operator- (int n)
		{
			const_iterator::operator-(n);
			return *this;
		}

		bool operator== (const iterator& rhs) const
		{
			return (this.curr == rhs.curr);
		}

		bool operator!= (const iterator& rhs) const
		{
			return (this.curr != rhs.curr);
		}

	protected:
		explicit iterator(ListNode* p) : const_iterator(p) {}

		friend class List<T>;
	};

private:
	void initialize();

	ListNode*		head;
	ListNode*		tail;
	unsigned int	count;
};

template <class T>
void List<T>::initialize()
{
	head = new ListNode();		// dummy head node
	tail = new ListNode();		// dummy tail node
	head->next = tail;
	tail->prev = head;
	count = 0;					// initialize count
}

template <class T>
List<T>::List(std::initializer_list<T> other)
: List()	// call default constructor to init first
{
	for (auto value : other)
		push_back(value);
}

// copy constructor
template <class T>
List<T>::List(const List<T>& other)
: List()	// call default constructor to init first
{
	for (auto value : other)
		push_back(value);
}

// assignment operator
template <class T>
List<T>& List<T>::operator= (const List<T>& rhs)
{
	// make a copy by copy constructor and swap members
	List<T> copy = rhs;
	std::swap(head, copy.head);
	std::swap(tail, copy.tail);
	std::swap(count, copy.count);
	return *this;
}

// move assignment operator
template <class T>
List<T>& List<T>::operator= (List<T>&& rhs)
{
	// move by swapping internal members to make both valid
	swap(rhs);
	return *this;
}

template <class T>
List<T>::~List()
{
	clear();
	delete head;
	delete tail;
}

// iterators
template <class T>
typename List<T>::const_iterator List<T>::begin() const
{
	if (!head->next) throw std::out_of_range("out of range");
	return const_iterator(head->next);
}

template <class T>
typename List<T>::iterator List<T>::begin()
{
	if (!head->next) throw std::out_of_range("out of range");
	return iterator(head->next);
}

template <class T>
typename List<T>::const_iterator List<T>::end() const
{
	return const_iterator(tail);
}

template <class T>
typename List<T>::iterator List<T>::end()
{
	return iterator(tail);
}

// modifiers
template <class T>
void List<T>::clear()
{
	ListNode* prev = head;
	ListNode* node = head->next;
	while (node != tail)
	{
		prev = node;
		node = node->next;
		delete prev;
	}
	head->next = tail;
	tail->prev = head;
	count = 0;
}

template <class T>
typename List<T>::iterator List<T>::insert(const iterator& pos, const T& value)
{
	ListNode* node = pos.curr;
	if (node == head)
		throw std::out_of_range("out of range");
	ListNode* newNode = new ListNode(value);

	// insert new value node to pos node front, pos node become new node next
	newNode->next = node;
	newNode->prev = node->prev;
	node->prev->next = newNode;
	node->prev = newNode;
	++count;

	return iterator(newNode);
}

template <class T>
typename List<T>::iterator List<T>::erase(const iterator& pos)
{
	ListNode* node = pos.curr;
	if (count == 0 || node == tail)
		throw std::out_of_range("out of range");
	ListNode* next = node->next;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
	--count;

	return iterator(next);
}

template <class T>
void List<T>::push_back(const T& value)
{
	ListNode* node = new ListNode(value);
	node->prev = tail->prev;
	node->next = tail;
	tail->prev->next = node;
	tail->prev = node;
	++count;
}

template <class T>
void List<T>::push_front(const T& value)
{
	ListNode* node = new ListNode(value);
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
	++count;
}

template <class T>
void List<T>::pop_back()
{
	ListNode* node = tail->prev;
	node->prev->next = tail;
	tail->prev = node->prev;
	delete node;
	--count;
}

template <class T>
void List<T>::pop_front()
{
	ListNode* node = head->next;
	node->next->prev = head;
	head->next = node->next;
	delete node;
	--count;
}

template <class T>
void List<T>::swap(List& rhs)
{
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	std::swap(count, rhs.count);
}

template <class T>
bool List<T>::equal(const List<T>& other) const
{
	if (count != other.size())		// fast check for size
		return false;

	// compare values between two list by iterators
	// return false immediately when one of value are not equal at same position
	for (auto it1 = begin(), it2 = other.begin();
		it1 != end() && it2 != other.end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
			return false;
	}

	return true;
}

}; // end of tdc namespace

#endif // TDC_LIST_H