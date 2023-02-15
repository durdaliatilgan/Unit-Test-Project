#ifndef LIST_HPP
#define LIST_HPP
#include "Node.hpp"

template<class T>
class List {

	
public:
	List();
	List(const List<T>& obj);
	~List();

	Node<T>* dummyHead;
	int size;


	List<T>& operator=(const List<T>& obj);

	int getSize()const;
	bool isEmpty()const;
	Node<T>* begin()const;
	Node<T>* begin();

	void insert(Node<T>* pos, const T& value);
	Node<T>* erase(Node<T>* pos);
	void clear();
	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
};

template<class T>
List<T>::List() {
	size = 0;
	dummyHead = new Node<T>();
}

template<class T>
List<T>::List(const List<T>& obj) : List<T>() {
	*this = obj;
}

template<class T>
List<T>::~List() {
	clear();
	delete dummyHead;
}
template<class T>
List<T>& List<T>::operator=(const List<T>& obj) {
	clear();
	Node<T>* objTemp = obj.begin();
	Node<T>* temp = dummyHead;
	while (objTemp) {
		temp->next = new Node<T>(objTemp->data);
		size++;
		temp = temp->next;
		objTemp = objTemp->next;
	}
	return *this;
}

template<class T>
int List<T>::getSize()const { return size; }

template<class T>
bool List<T>::isEmpty()const { return dummyHead->next == NULL; }

template<class T>
Node<T>* List<T>::begin()const { return dummyHead->next; }

template<class T>
Node<T>* List<T>::begin() { return dummyHead->next; }

template<class T>
void List<T>::insert(Node<T>* pos, const T& value) {
	Node<T>* temp = dummyHead;
	while (temp && temp->next != pos)
		temp = temp->next;
	temp->next = new Node<T>(value, temp->next);
	size++;
}

template<class T>
Node<T>* List<T>::erase(Node<T>* pos) {
	if (isEmpty())
		throw "Error : List::erase(pos) for list is empty";

	Node<T>* prev = dummyHead;
	if (pos) {
		while (prev && prev->next != pos) {
			prev = prev->next;
		}

		if (prev && prev->next == pos) {
			prev->next = pos->next;
			delete pos;
			size--;
		}
	}
	else {
		while (prev->next->next)
			prev = prev->next;
		delete prev->next;
		prev->next = NULL;
		size--;
	}

	return prev ? prev->next : NULL;
}

template<class T>
void List<T>::clear() {
	while (!isEmpty()) {
		pop_front();
	}
}

template<class T>
void List<T>::push_front(const T& value) {
	insert(begin(), value);
}

template<class T>
void List<T>::push_back(const T& value) {
	insert(NULL, value);
}

template<class T>
void List<T>::pop_front() {
	erase(dummyHead->next);
}

template<class T>
void List<T>::pop_back() {
	erase(NULL);
}
#endif
