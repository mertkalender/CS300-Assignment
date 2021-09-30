//MERT KALENDER - 26351

#ifndef BST_h
#define BST_h


#include <string>
#include <iostream>

using namespace std;


// -------------------- ITEM -------------------

class Item {
private:
	string title;
	string info;

public:
	Item();
	Item(string title, string info);

	string getTitle() const;

	string getInfo() const;
	void setInfo(string info);

	bool operator< (const Item& rhs) const;
	bool operator> (const Item& rhs) const;

	friend ostream& operator<<(ostream& os, const Item& item);
};

ostream& operator<<(ostream& os, const Item& item)
{
	os << item.title;
	return os;
}

// ----------------- BINARY NODE -------------------

template <class T>
class BinaryNode {
	T element;
	BinaryNode* left;
	BinaryNode* right;
	BinaryNode();
	BinaryNode(const T elem, BinaryNode* lt, BinaryNode* rt);

	template <class T2>
	friend class BinarySearchTree;
};

// --------------------- BINARY SEARCH TREE ----------------


template <class T>
class BinarySearchTree {
public:
	BinarySearchTree();
	BinarySearchTree(T notFound);
	BinarySearchTree(const BinarySearchTree<T>& rhs);
	~BinarySearchTree();


	bool found(T& obj) const;
	T& find(T& obj);
	T& findMin();

	bool isEmpty() const;
	void printTree() const;
	void makeEmpty();

	void insert(const T& obj);
	void remove(const T& obj);


private:
	BinaryNode<T>* root;
	T ITEM_NOT_FOUND;

	T& elementAt(BinaryNode<T>* t);
	bool elementFinder(BinaryNode<T>* t) const;

	void insert(const T& x, BinaryNode<T>*& t) const;
	void remove(const T& x, BinaryNode<T>*& t) const;

	BinaryNode<T>* find(T& x, BinaryNode<T>* t) const;
	BinaryNode<T>* findMin(BinaryNode<T>* t) const;


	void makeEmpty(BinaryNode<T>*& t) const;
	void printTree(BinaryNode<T>* t) const;

	const BinarySearchTree<T>& operator =(const BinarySearchTree<T>& rhs);

};


// ------------------------------------- AVL NODE -----------------------------------------------------------------------


template <class T>
class AvlNode
{
	T element;
	AvlNode* left;
	AvlNode* right;
	int height;

	AvlNode();
	AvlNode(const T& theElement, AvlNode* lt, AvlNode* rt, int h);

	template <class T1>
	friend class AVLTree;
};




// -------------------------------------- AVL TREE ------------------------------------------------------------------------


template <class T>
class AVLTree {
public:
	AVLTree();
	AVLTree(T notFound);
	AVLTree(const AVLTree<T>& rhs);
	~AVLTree();

	bool found(T& obj) const;
	T& find(T& obj);
	T& findMin();

	bool isEmpty() const;
	void printTree() const;
	void makeEmpty();

	void insert(T& obj);
	void remove(T& obj);


private:
	AvlNode<T>* root;
	T ITEM_NOT_FOUND;

	T& elementAt(AvlNode<T>* t);
	bool elementFinder(AvlNode<T>* t) const;

	void insert(T& x, AvlNode<T>*& t);
	void remove(T& x, AvlNode<T>*& t);

	AvlNode<T>* find(T& x, AvlNode<T>* t) const;
	AvlNode<T>* findMin(AvlNode<T>* t);


	void makeEmpty(AvlNode<T>*& t) const;
	void printTree(AvlNode<T>* t) const;

	const AVLTree<T>& operator =(const AVLTree<T>& rhs);

	int height(AvlNode<T>* t) const;
	int max(int lhs, int rhs) const;
	void rotateWithLeftChild(AvlNode<T>*& k2) const;
	void rotateWithRightChild(AvlNode<T>*& k1) const;
	void doubleWithLeftChild(AvlNode<T>*& k3) const;
	void doubleWithRightChild(AvlNode<T>*& k1) const;


};


// ------------------------- SECTION ------------------------

class Section {
private:
	string title;
	BinarySearchTree<Item>* sectionBST;
	AVLTree<Item>* sectionAVL;


public:
	Section();
	Section(string title, BinarySearchTree<Item>* BSTptr, AVLTree<Item>* AVLptr);

	const string getTitle() const;
	void setTitle(string title);

	BinarySearchTree<Item>* getSectionBST();
	AVLTree<Item>* getSectionAVL();

	const Section& operator =(const Section & rhs);
	bool operator < (const Section& rhs) const;
	bool operator > (const Section& rhs) const;

	friend ostream& operator<<(ostream& os, const Section& section);
};

ostream& operator<<(ostream& os, const Section& section)
{
	os << section.title;
	return os;
}

#include "BST.cpp"

#endif