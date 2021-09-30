//MERT KALENDER - 26351

#ifndef BST_cpp

#define BST_cpp


#include "BST.h"

Item::Item(){}

Item::Item(string title, string info) {
	this->title = title;
	this->info = info;
}


bool Item::operator< (const Item& rhs) const {
	if (this->title > rhs.title) {
		return true;
	}
	return false;
}

bool Item::operator> (const Item& rhs) const{
	if (this->title < rhs.title) {
		return true;
	}
	return false;
}

string Item::getTitle()const {
	return this->title;
}

string Item::getInfo() const{
	return this->info;
}

void Item::setInfo(string info) {
	this->info = info;
}

// ----------- Binary Node ----------

template <class T>
BinaryNode<T>::BinaryNode(const T elem, BinaryNode* lt, BinaryNode* rt) {

	this->element = elem;
	this->left = lt;
	this->right = rt;
}

template <class T>
BinaryNode<T>::BinaryNode(){}


// -------------------------- BST ----------------------------

template <class T>
BinarySearchTree<T>::BinarySearchTree(){}

template <class T>
BinarySearchTree<T>::BinarySearchTree(T notFound): ITEM_NOT_FOUND(notFound) {
	this->root = NULL;
}

template <class T>
T& BinarySearchTree<T>::elementAt(BinaryNode<T>* t) {
	if (t == NULL) {
		return ITEM_NOT_FOUND;
	}
	else {
		return t->element;
	}
}

template <class T>
T& BinarySearchTree<T>::findMin(){

	return elementAt(findMin(root));
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMin(BinaryNode<T>* t) const {
	
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}

template <class T>
bool BinarySearchTree<T>::elementFinder(BinaryNode<T>* t) const {
	if (t == NULL) {
		return false;
	}
	else {
		return true;
	}
}


template <class T>
bool BinarySearchTree<T>::found(T& obj) const {
	return elementFinder(find(obj, root));
}

template <class T>
T& BinarySearchTree<T>::find(T& obj){
	return elementAt(find(obj, root));
}


template <class T>
BinaryNode<T>* BinarySearchTree<T>::find(T& obj, BinaryNode<T>* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (obj < t->element) {
		return find(obj, t->left);
	}
	else if (obj > t->element) {
		return find(obj, t->right);
	}
	else {
		return t;
	}
}

template <class T>
void BinarySearchTree<T>::insert(const T& obj)
{
	insert(obj, root);
}

template <class T>
void BinarySearchTree<T>::insert(const T& obj, BinaryNode<T>*& t) const{
	if (t == nullptr) 
		t = new BinaryNode<T>(obj, NULL, NULL);
	else if (obj < t->element)
		insert(obj, t->left);  
	else if (obj > t->element)
		insert(obj, t->right);
}

template <class T>
void BinarySearchTree<T>::remove(const T& obj)
{
	remove(obj, root);
}



template <class T>
void BinarySearchTree<T>::remove(const T& x, BinaryNode<T>*& t)
const
{
	if (t == NULL)
		return;   
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) 
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else 
	{
		BinaryNode<T>* oldNode = t;
		if (t->left != NULL) {
			t = t->left;
		}
		else {
			t = t->right;
		}
		delete oldNode;
	}
}

template <class T>
void BinarySearchTree<T>::makeEmpty()
{
	makeEmpty(root);
}

template <class T>
void BinarySearchTree<T>::makeEmpty(BinaryNode<T>*& t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

template <class T>
bool BinarySearchTree<T>::isEmpty() const {
	if (root == NULL) {
		return true;
	}
	return false;
}


template <class T>
void BinarySearchTree<T>::printTree() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		cout << endl << "*****" << endl;
		printTree(root);
		cout << "*****" << endl;
	}
}


template <class T>
void BinarySearchTree<T>::printTree(BinaryNode<T>* t) const {
	if (t != NULL)
	{
		printTree(t->right); 
		cout << t->element << endl;
		printTree(t->left);
	}
}



template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	makeEmpty();
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& rhs) : root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND) {
	*this = rhs;
}

template <class T>
const BinarySearchTree<T>& BinarySearchTree<T>::operator =(const BinarySearchTree<T>& rhs) {

	if (this != &rhs){

		this->~BinarySearchTree();
		this->root = NULL;




	}
}

// ------------------------ AVL NODE ------------------------
template <class T>
AvlNode<T>::AvlNode(const T& theElement, AvlNode* lt, AvlNode* rt, int h){
	this->element = theElement;
	this->height = h;
	this->left = lt;
	this->right = rt;
}

template <class T>
AvlNode<T>::AvlNode(){}


// ------------------------ AVL Tree -------------------------

template <class T>
AVLTree<T>::AVLTree(){}

template <class T>
AVLTree<T>::AVLTree(T notFound): ITEM_NOT_FOUND(notFound) {
	this->root = NULL;
}



template <class T>
T& AVLTree<T>::elementAt(AvlNode<T>* t){
	if (t == NULL) {
		return ITEM_NOT_FOUND;
	}
	else {
		return t->element;
	}
}

template <class T>
T& AVLTree<T>::findMin(){

	return elementAt(findMin(root));
}

template <class T>
AvlNode<T>* AVLTree<T>::findMin(AvlNode<T>* t){

	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}


template <class T>
bool AVLTree<T>::elementFinder(AvlNode<T>* t) const {
	if (t == NULL) {
		return false;
	}
	else {
		return true;
	}
}


template <class T>
bool AVLTree<T>::found(T& obj) const {
	return elementFinder(find(obj, root));
}

template <class T>
T& AVLTree<T>::find(T& obj){
	return elementAt(find(obj, root));
}


template <class T>
AvlNode<T>* AVLTree<T>::find(T& obj, AvlNode<T>* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (obj < t->element) {
		return find(obj, t->left);
	}
	else if (obj > t->element) {
		return find(obj, t->right);
	}
	else {
		return t;
	}
}

template <class T>
void AVLTree<T>::insert(T& obj)
{
	insert(obj, root);
}

template <class T>
void AVLTree<T>::insert(T& x, AvlNode<T>*& t){

	if (t == NULL) {
		t = new AvlNode<T>(x, NULL, NULL, 0);
	}
	else if (x < t->element) {

		insert(x, t->left);

		if (height(t->left) - height(t->right) == 2) {
			if (x < t->left->element) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
	}
	else if (t->element < x){

		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2) {

			if (t->right->element < x) {

				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}
	}
	else
		;  

  // update the height of the node
	t->height = max(height(t->left), height(t->right)) + 1;
}





template <class T>
void AVLTree<T>::remove(T& obj)
{
	remove(obj, root);
}



template <class T>
void AVLTree<T>::remove(T& x, AvlNode<T>*& t){
	if (t == NULL)
		return;   // Item not found; do nothing
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else // one or no children
	{
		AvlNode<T>* oldNode = t;
		if (t->left != NULL) {
			t = t->left;
		}
		else {
			t = t->right;
		}
		delete oldNode;
	}
}

template <class T>
void AVLTree<T>::makeEmpty()
{
	makeEmpty(root);
}

template <class T>
void AVLTree<T>::makeEmpty(AvlNode<T>*& t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

template <class T>
bool AVLTree<T>::isEmpty() const {
	if (root == NULL) {
		return true;
	}
	return false;
}


template <class T>
void AVLTree<T>::printTree() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		cout << endl << "*****" << endl;
		printTree(root);
		cout << "*****" << endl;
	}
}


template <class T>
void AVLTree<T>::printTree(AvlNode<T>* t) const {
	if (t != NULL)
	{
		printTree(t->right);
		cout << t->element << endl;
		printTree(t->left);
	}
}



template <class T>
AVLTree<T>::~AVLTree() {
	makeEmpty();
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& rhs) : root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND) {
	*this = rhs;
}

template <class T>
const AVLTree<T>& AVLTree<T>::operator =(const AVLTree<T>& rhs) {
	if (this != &rhs)
	{
		this->~BinarySearchTree();

	}
}


template <class T>
int AVLTree<T>::height(AvlNode<T>* t) const{

	if (t == NULL)
		return -1;

	return t->height;
}

template <class T>
int AVLTree<T>::max(int lhs, int rhs) const{

	if (lhs > rhs)
		return lhs;

	return rhs;
}

template <class T>
void AVLTree<T>::rotateWithLeftChild(AvlNode<T>*& k2) const{

	AvlNode<T>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

template <class T>
void AVLTree<T>::rotateWithRightChild(AvlNode<T>*& k1) const{

	AvlNode<T>* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

template <class T>
void AVLTree<T>::doubleWithLeftChild(AvlNode<T>*& k3) const {

	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template <class T>
void AVLTree<T>::doubleWithRightChild(AvlNode<T>*& k1) const{

	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}




// ------------------------ Section --------------------------



Section::Section() {
	this->sectionBST = NULL;
	this->sectionAVL = NULL;
}

Section::Section(string title, BinarySearchTree<Item>* BSTptr, AVLTree<Item>* AVLptr) {
	this->title = title;
	this->sectionBST = BSTptr;
	this->sectionAVL = AVLptr;
}


bool Section::operator< (const Section& rhs) const{
	if (this->title > rhs.title) {
		return true;
	}
	return false;
}

bool Section::operator> (const Section& rhs) const{
	if (this->title < rhs.title) {
		return true;
	}
	return false;
}

const Section& Section::operator =(const Section & rhs) { 
	this->title = rhs.title;
	this->sectionBST = rhs.sectionBST;
	this->sectionAVL = rhs.sectionAVL;
	return *this;
};

const string Section::getTitle() const {
	return this->title;
}

void Section::setTitle(string title) {
	this->title = title;
}

BinarySearchTree<Item>* Section::getSectionBST() {
	return this->sectionBST;
};

AVLTree<Item>* Section::getSectionAVL() {
	return this->sectionAVL;
};
#endif