/***********************************************************************
* Header:
*    List
* Summary:
*    This will contain List class
* Author
*    Scott Tolman
************************************************************************/
#ifndef LIST
#define List

namespace custom
{
	template <class T>
	class list
	{
	public:
		class Node; //forward declaration p.375
		class iterator; //forward declaration
		class reverse_iterator; //forward declaration
		list() : pHead(NULL), pTail(NULL), numElements(0) {}
		list(const list<T>& rhs) throw (const char *);
		~list();
		list& operator = (const list<T> & rhs);
		int size() const { return numElements; }
		bool empty() const { return (pHead == NULL); }
		void clear();
		void push_back(const T & t) throw (const char *);
		void push_front(const T & t) throw (const char *);
		void pop_back();
		void pop_front();
		T& back() throw (const char *);
		T& front() throw (const char *);
		T back() const throw (const char *);
		T front() const throw (const char *);
		list<T>::iterator find(const T & t);
		void erase(list<T>::iterator it);
		list<T>insert(const T & t, list<T>::iterator it);
		list<T>::iterator begin() { return list<T>::iterator(pHead); }
		list<T>::iterator end() { return list<T>::iterator(NULL); }
		list<T>::reverse_iterator rbegin() { return list<T>::reverse_iterator(pTail); }
		list<T>::reverse_iterator rend() { return list<T>::reverse_iterator(NULL); }
	private:
		Node* pHead;
		Node* pTail;
		int numElements;
	};

	/******************************************************
	* NODE
	* node class members and methods
	******************************************************/
	template <class T>
	class list<T>::Node
	{
	public:
		T data;
		Node pNext;
		Node pPrev;
		Node() : data(NULL), pNext(NULL), pPrev(NULL) {}
		Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
	};

	/******************************************************
	* ITERATOR
	* contains all methods needed for iterator
	******************************************************/
	template <class T>
	class list <T> ::iterator
	{
	private:
		list<T>::Node * p;
	public:
		iterator() : p(NULL) {}
		iterator(list <T> ::Node p) { this->p = p; }
		iterator(const list<T>::iterator& rhs) { *this = rhs; }
		list <T> ::iterator & operator = (const list <T> ::iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}
		bool operator == (list <T> ::iterator rhs) { return rhs.p == this->p; }
		bool operator != (list <T> ::iterator rhs) { return rhs.p != this->p; }
		list <T> ::iterator & operator ++ ();
		list <T> ::iterator & operator ++ (int postfix);
		list <T> ::iterator & operator -- ();
		list <T> ::iterator & operator -- (int postfix);
		T & operator T* () { return p; } //p has no members available, this is broken

	};

	/******************************************************
	* REVERSE_ITERATOR
	* contains all methods needed for iterator
	******************************************************/
	template <class T>
	class list <T> ::reverse_iterator
	{
	private:
		list <T> ::Node * p;
	public:
		reverse_iterator() : p(NULL) {}
		reverse_iterator(list <T> ::Node p) { this->p = p; }
		reverse_iterator(list <T> ::reverse_iterator rhs) { *this = rhs; }
		list <T> ::reverse_iterator & operator = (const list <T> ::reverse_iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}
		bool operator == (list <T> ::reverse_iterator rhs) { return rhs.p == this->p; }
		bool operator != (list <T> ::reverse_iterator rhs) { return rhs.p != this->p; }
		list <T> ::reverse_iterator & operator ++ ();
		list <T> ::reverse_iterator & operator ++ (int postfix);
		list <T> ::reverse_iterator & operator -- ();
		list <T> ::reverse_iterator & operator -- (int postfix);

		T & operator * () { return p->data; }
	};

	/******************************************************
	* COPY CONSTURCTOR
	*
	******************************************************/
	template<class T>
	list<T>::list(list rhs) throw(const char *)
	{
		try
		{
			list <T> newList = new list <T>;
			newList = rhs;

		}
		catch (bad_alloc)
		{
			throw "ERROR: unable to allocate a new node for a list";
		}
	}

	/******************************************************
	* DESTRUCTOR
	*
	******************************************************/
	template<class T>
	list<T>::~list()
	{
		clear();
	}

	/******************************************************
	* ASSIGNMENT OPERATOR
	*
	******************************************************/
	template<class T>
	list<T> & list<T>::operator=(const list<T>& rhs)
	{
		clear();
		Node * tmpLhs = new Node *;
		Node * tmpRhs = new Node *;
		tmpRhs = rhs->pHead;
		tmpLhs = pHead;
		while (tmpRhs)
		{
			tmpLhs = tmpRhs;
			tmpLhs = tmpLhs->pNext;
			tmpRhs = tmpRhs->pPrev;
		}
		pHead = rhs->pHead;
		pTail = rhs->pTail;
		numElements = rhs->numElements;
		return *this;
	}

	/******************************************************
	* CLEAR
	*
	******************************************************/
	template<class T>
	void list<T>::clear()
	{
		Node * tmp = new Node*;
		if (numElements < 2)
		{
			tmp = this->pHead;
			delete tmp;
			tmp = NULL;
		}
		else
			tmp = this->pHead;
		while (tmp)
		{
			tmp = tmp->pNext;
			delete tmp->pPrev;
		}
		delete tmp;
		tmp = NULL;
	}

	/******************************************************
	* PUSH BACK
	*
	******************************************************/
	template<class T>
	void list<T>::push_back(const T & t) throw(const char *)
	{
		pTail->pNext = new Node(t);
		pTail->pNext->pPrev = pTail;
		pTail = pTail->pNext;
		pTail->pNext = NULL;
	}

	/******************************************************
	* PUSH FRONT
	*
	******************************************************/
	template<class T>
	void list<T>::push_front(const T & t) throw(const char *)
	{
		pHead->pPrev = new Node(t);
		pHead->pPrev->pNext = pHead;
		pHead = pHead->pPrev;
		pHead->pPrev = NULL;
	}

	/******************************************************
	* POP BACK
	*
	******************************************************/
	template<class T>
	void list<T>::pop_back()
	{
		pTail = pTail->pPrev;
		delete pTail->pNext;
		pTail->pNext = NULL;
	}

	/******************************************************
	* POP FRONT
	*
	******************************************************/
	template<class T>
	void list<T>::pop_front()
	{
		pHead = pHead->pNext;
		delete pHead->pPrev;
		pHead->pPrev = NULL;
	}

	/******************************************************
	* BACK (by reference)
	*
	******************************************************/
	template<class T>
	T & list<T>::back() throw(const char *)
	{
		if (pHead)
			return pTail->data;
		else
			throw "ERROR: unable to access data from an empty list"
	}

	/******************************************************
	* FRONT (by reference)
	*
	******************************************************/
	template<class T>
	T & list<T>::front() throw(const char *)
	{
		if (pHead)
			return pHead->data;
		else
			throw "ERROR: unable to access data from an empty list"
	}

	/******************************************************
	* BACK
	*
	******************************************************/
	template<class T>
	T list<T>::back() const throw(const char *)
	{
		if (pHead)
			return pTail->data;
		else
			throw "ERROR: unable to access data from an empty list"
	}

	/******************************************************
	* FRONT
	*
	******************************************************/
	template<class T>
	T list<T>::front() const throw(const char *)
	{
		if (pHead)
			return pHead->data;
		else
			throw "ERROR: unable to access data from an empty list"
	}

	/******************************************************
	* FIND
	*
	******************************************************/
	template<class T>
	list<T>::iterator list<T>::find(const T & t)
	{
		return list<T>::iterator();
	}

	/******************************************************
	* ERASE
	*
	******************************************************/
	template<class T>
	void list<T>::erase(list<T>::iterator it)
	{
	}

	/******************************************************
	* INSERT
	*
	******************************************************/
	template<class T>
	list<T> list<T>::insert(const T & t, list<T>::iterator it)
	{
		list <T> ::Node * pNew = new list <T> ::Node(t);
		if (it)
		{
			pNew->pNext = it;
			pNew->pPrev = it->pPrev;
			it->pPrev = pNew;
			if (pNew->pPrev)
				pNew->pPrev->pNext = pNew;
			return pNew;
		}
	}

} // namespace custom

#endif // !LIST
