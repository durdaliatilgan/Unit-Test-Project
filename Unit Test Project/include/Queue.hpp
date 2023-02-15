#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"
template<class T>
class Queue{
	List<T> l;
	public:
		T front()const;
		void enqueue(const T& data);
		void dequeue();
		bool isEmpty()const;
};

template<class T>
T Queue<T>::front()const{	
	if(isEmpty())
		throw "Hata : Queue::front() methodunda olustu (queue suanda bos)";
	return l.begin()->data;
}

template<class T>
void Queue<T>::enqueue(const T& data){
	l.push_back(data);
}
		
template<class T>
void Queue<T>::dequeue(){
	if(isEmpty())
		throw "Hata : Queue::dequeue() methodunda olustu (queue suanda bos)";
	l.pop_front();
}
		
template<class T>
bool Queue<T>::isEmpty()const{
	return l.isEmpty();
}

#endif
