#ifndef HEAP_HPP
#define HEAP_HPP
#include "Util.hpp"
using namespace std;
template<class T,class Compare>
class Heap {
	T* elements;
	int size;
	int capacity;
	Compare compare;
	
	int getParentIndex(int index);
	int getLeftChildIndex(int index);
	int getRightChildIndex(int index);
	void resize(int capacity);
	void reset(int capacity);

public:
	Heap();
	Heap(const Heap<T, Compare>& obj);
	~Heap();
	Heap<T, Compare>& operator=(const Heap<T, Compare>& obj);
	
	int getSize()const;
	int getCapacity()const;
	bool isEmpty()const;
	void clear();
	void enqueue(const T& element);
	T dequeue();
};

template<class T,class Compare>
int Heap<T,Compare>::getParentIndex(int index) {
	return index / 2;
}

template<class T,class Compare>
int Heap<T,Compare>::getLeftChildIndex(int index) {
	return 2 * index;
}

template<class T,class Compare>
int Heap<T,Compare>::getRightChildIndex(int index) {
	return 2 * index + 1;
}

template<class T,class Compare>
void Heap<T,Compare>::resize(int capacity) {
	T* temp = elements;
	elements = NULL;
	int bound = min_t(size, capacity);
	reset(capacity);
	size = bound;
	for (int i = 1; i < size; i++) {
		elements[i] = temp[i];
	}
	delete[] temp;
}

template<class T,class Compare>
void Heap<T,Compare>::reset(int capacity) {
	if (elements)
		delete[] elements;
	size = 1;
	this->capacity = capacity;
	elements = new T[capacity];
}

template<class T,class Compare>
Heap<T,Compare>::Heap() : elements(NULL){
	clear();
}

template<class T,class Compare>
Heap<T,Compare>::Heap(const Heap<T, Compare>& obj)
	: elements(NULL)
{
	*this = obj;
}

template<class T,class Compare>
Heap<T,Compare>::~Heap() {
	delete[] elements;
}

template<class T,class Compare>
Heap<T, Compare>& Heap<T,Compare>::operator=(const Heap<T, Compare>& obj) {
	reset(obj.capacity);
	size = obj.size;
	for (int i = 0; i < size; i++) {
		elements[i] = obj.elements[i];
	}
	return *this;
}

template<class T,class Compare>
int Heap<T,Compare>::getSize()const { 
	return size - 1;
}

template<class T,class Compare>
int Heap<T,Compare>::getCapacity()const { 
	return capacity;
}

template<class T,class Compare>
bool Heap<T,Compare>::isEmpty()const { 
	return getSize() == 0;
}

template<class T,class Compare>
void Heap<T,Compare>::clear() {	
	reset(1);
}

template<class T,class Compare>
void Heap<T,Compare>::enqueue(const T& element) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	elements[size] = element;

	int currIndex = size;
	int parent = getParentIndex(currIndex);

	while (parent > 0 && compare(elements[currIndex], elements[parent])){
		swap_t(elements[currIndex],elements[parent]);
		currIndex = parent;
		parent = getParentIndex(currIndex);
	}
	size++;
}

template<class T,class Compare>
T Heap<T,Compare>::dequeue() {
	int parent = 1;
	T element = elements[parent];
	size--;
	swap_t(elements[parent], elements[size]);
	int leftChild = getLeftChildIndex(parent);
	int rightChild = getRightChildIndex(parent);

	while (leftChild < size || rightChild < size) {

		if (rightChild < size) {
			if (compare(elements[rightChild], elements[leftChild])) {
				if (compare(elements[rightChild], elements[parent])) {
					swap_t(elements[rightChild], elements[parent]);
					parent = rightChild;
				}
				else {
					break;
				}
			}
			else {
				if (compare(elements[leftChild], elements[parent])) {
					swap_t(elements[leftChild], elements[parent]);
					parent = leftChild;
				}
				else {
					break;
				}
			}
		}
		else {
			if (compare(elements[leftChild], elements[parent])) {
				swap_t(elements[leftChild], elements[parent]);
				parent = leftChild;
			}
			else {
				break;
			}
		}

		leftChild = getLeftChildIndex(parent);
		rightChild = getRightChildIndex(parent);
	}

	return element;
}

template<class T>
using MaxHeap = Heap<T, Greater<T>>;

template<class T>
using MinHeap = Heap<T, Less<T>>;
#endif
