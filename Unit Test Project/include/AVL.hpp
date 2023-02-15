#ifndef AVL_HPP
#define AVL_HPP
#include "Util.hpp"
#include <iostream>
using namespace std;

template<class T>
class AVLNode {
public:
	T data;
	AVLNode<T>* left;
	AVLNode<T>* right;
	AVLNode(const T& = T(), AVLNode<T>* = NULL, AVLNode<T>* = NULL);
};

template<class T>
AVLNode<T>::AVLNode(const T& data, AVLNode<T>* left, AVLNode<T>* right)
	: data(data), left(left), right(right)
{	}

template<class T,class Compare = Less<T>>
class AVL {

	public:
	AVLNode<T>* root;
	Compare compare;

	AVLNode<T>* ll_rotate(AVLNode<T>* node);
	AVLNode<T>* rr_rotate(AVLNode<T>* node);
	AVLNode<T>* lr_rotate(AVLNode<T>* node);
	AVLNode<T>* rl_rotate(AVLNode<T>* node);

	int different(AVLNode<T>* node);
	AVLNode<T>* balance(AVLNode<T>* node) ;
	AVLNode<T>* insert(AVLNode<T>* start, const T& value);
	AVLNode<T>* find(AVLNode<T>* start, const T& value);
	int height(AVLNode<T>* node);
	void inorder(AVLNode<T>* start);

	AVL();
	void insert(const T& value);
	AVLNode<T>* find(const T& value);
	void inorder();
};

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::ll_rotate(AVLNode<T>* node) {
	AVLNode<T>* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::rr_rotate(AVLNode<T>* node) {
	AVLNode<T>* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::lr_rotate(AVLNode<T>* node) {
	node->left = rr_rotate(node->left);
	return ll_rotate(node);
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::rl_rotate(AVLNode<T>* node) {
	node->right = ll_rotate(node->right);
	return rr_rotate(node);
}

template<class T,class Compare>
int AVL<T,Compare>::different(AVLNode<T>* node) {
	return height(node->left) - height(node->right);
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::balance(AVLNode<T>* node) {
	if (node) {
		int diff = different(node);
		if (diff > 1) {
			if (different(node->left) < 0)
				node = lr_rotate(node);
			else
				node = ll_rotate(node);
		}
		else if (diff < -1) {
			if (different(node->right) > 0)
				node = rl_rotate(node);
			else
				node = rr_rotate(node);
		}
	}
	return node;
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::insert(AVLNode<T>* start, const T& value) {
	if (start) {
		if (compare(value, start->data))
			start->left = insert(start->left, value);
		else
			start->right = insert(start->right, value);
	}
	else
		return new AVLNode<T>(value);
	return balance(start);
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::find(AVLNode<T>* start, const T& value) {
	if (start) {
		if (compare(value,start->data))
			return find(start->left, value);
		else if (compare(start->data,value))
			return find(start->right, value);
	}
	return start;
}

template<class T,class Compare>
int AVL<T,Compare>::height(AVLNode<T>* node) {
	if (!node)
		return 0;
	int lHeight = height(node->left);
	int rHeight = height(node->right);
	return 	(lHeight < rHeight ? rHeight : lHeight) + 1;
}

template<class T,class Compare>
void AVL<T,Compare>::inorder(AVLNode<T>* start) {
	if (start) {
		inorder(start->left);
		cout << start->data << endl;
		inorder(start->right);
	}
}
	
template<class T,class Compare>
AVL<T,Compare>::AVL() : root(NULL) {	}

template<class T,class Compare>
void AVL<T,Compare>::insert(const T& value) {
	root = insert(root, value);
}

template<class T,class Compare>
AVLNode<T>* AVL<T,Compare>::find(const T& value) {
	return find(root, value);
}

template<class T,class Compare>
void AVL<T,Compare>::inorder() {
	inorder(root);
}
#endif
