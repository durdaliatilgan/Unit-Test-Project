#ifndef NODE_HPP
#define NODE_HPP
#include <memory>
template<class T>
class Node{
public:
	T data;
	Node<T>* next;
	Node(const T& = T(),Node<T>* = NULL);
};

template<class T>
Node<T>::Node(
	const T& data,
	Node<T>* next
) : 
	data(data),
	next(next)
{	}
#endif
