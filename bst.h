#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		bool isBalanced(Node<Key, Value>* root) const;
    void deleteTree(Node<Key,Value>* root);
		Node<Key, Value> *getSmallestNode(Node<Key, Value>* root) const;
		int treeHeight(Node<Key, Value>* root) const; 
		static Node<Key, Value>* successor(Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
		//virtual Node<Key, Value>* successor(Node<Key, Value>* current);
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    //TODO
		current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return (current_ != rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
	Node<Key,Value>* curr = current_;
	current_ = successor(curr);
	return *this;

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
	if (current == nullptr) {
    return nullptr;
	}
	if (current->getRight() != nullptr) {
		Node<Key, Value>* node = current->getRight();
		while (node->getLeft() != nullptr) {
				node = node->getLeft();
		}
		return node;
	}
	else {
		Node<Key, Value>* node = current->getParent();
		while (node != nullptr && current == node->getRight()) {
			current = node;
			node = node->getParent();
		}
		return node;
	}

}



/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree():root_(nullptr) 
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Node<Key,Value>* curr = root_;
		Node<Key,Value>* parent = nullptr;

		Key key_ = keyValuePair.first;
		Value value_ = keyValuePair.second;

		if(empty() == true){
			root_ = new Node<Key,Value>(key_,value_,nullptr);
		}
		else{
			bool loc;
			while (curr != nullptr){
				Key curr_ = curr -> getKey();
				parent = curr;
				if (key_ < curr_){
					curr = curr -> getLeft();
					loc = true;
				}
				else if (key_ > curr_){
					curr = curr -> getRight();
					loc = false;
				}
				else if (key_ == curr_){
					curr -> setValue(value_);
					return;
				}
			}

			curr = new Node<Key, Value>(key_, value_, parent);
			if (loc == true){
				parent -> setLeft(curr);
			}
			else{
				parent -> setRight(curr);
			}
		}
		return;

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* curr = internalFind(key);
    if (curr==nullptr){
      return;
    }
    Node<Key, Value>* parent = curr->getParent();
    Node<Key, Value>* child = nullptr;

    bool ltrue = false;
		bool rtrue = false;
		bool isRoot = false;

		if (parent == nullptr){
			isRoot = true;
		}
		else if (parent -> getLeft() == curr){
			ltrue = true;
		}
		else if (parent -> getRight() == curr){
			rtrue = true;
		}

    if (curr->getLeft()==nullptr && curr->getRight()==nullptr){
      if (ltrue){
				parent->setLeft(nullptr);
			}
      else if (rtrue){
				parent->setRight(nullptr);
			}
      else if (isRoot) {
				root_=nullptr;
			}
      delete curr;
    }
		else if(curr->getLeft()==nullptr){
      child = curr->getRight();
      if (ltrue) {
        parent->setLeft(child);
      }
			else if (rtrue) {
        parent->setRight(child);
      }
			else if (isRoot) {
        root_ = child;
      }
      child->setParent(parent);
      delete curr;
    }	
		else if(curr->getRight()==nullptr){
  		child = curr->getLeft();
      if (ltrue) {
        parent->setLeft(child);
      }
			else if (rtrue) {
        parent->setRight(child);
      }
			else if (isRoot) {
        root_ = child;
      }
      child->setParent(parent);
      delete curr;
    }
		else{
      Node<Key, Value>* pred = predecessor(curr);
      child = pred->getLeft();
      nodeSwap(curr, pred);
      parent = curr->getParent();
      if (parent->getLeft()==curr){ 
        parent->setLeft(child);
      }
			else{
        parent->setRight(child);
      }
      if (child != nullptr){
        child->setParent(parent);
      }
      delete curr;
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    Node<Key, Value>* curr = current;
		if (curr == nullptr || curr -> getLeft() == nullptr){
			return nullptr;
		}
		else{
			curr = curr -> getLeft();
			while (curr -> getRight() != nullptr){ // change?
				curr = curr -> getRight();
			}
			return curr;
		}
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    deleteTree(root_);
		root_ = NULL;
		return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteTree(Node<Key,Value>* root){
	if(root == nullptr){ // base case
        return;
    }
    
	// recursively delete left and right subtrees
	deleteTree(root->getLeft());
	deleteTree(root->getRight());
	
	// delete current node
	delete root;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
  return getSmallestNode(root_);
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode(Node<Key, Value>* root) const{
	if (root == nullptr){
		return nullptr;
	}
	Node<Key, Value>* curr = root;
	while (curr != nullptr && (curr -> getLeft()) != nullptr){
		curr = curr -> getLeft();
	}
	return curr;

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    Node<Key, Value>* curr = root_;
		if (curr == nullptr){
			return nullptr;
		}
		while(curr != nullptr && curr -> getKey() != key){
			if (key < (curr -> getKey())){
				curr = curr -> getLeft();
			}
			else if (key > curr -> getKey()){
				curr = curr -> getRight();
			}
			else if (key == curr -> getKey()){
				return nullptr;
			}
		}
		return curr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return isBalanced(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced(Node<Key, Value>* root) const {
    if (root == nullptr) {
        // An empty tree is always balanced
        return true;
    }

    int leftHeight = treeHeight(root->getLeft());
    int rightHeight = treeHeight(root->getRight());

    // Check if the height difference between the left and right subtrees
    // is within the allowed range (-1, 0, or 1)
    int heightDiff = abs(leftHeight - rightHeight);
    if (heightDiff <= 1 && isBalanced(root->getLeft()) && isBalanced(root->getRight())) {
        return true;
    } else {
        return false;
    }
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::treeHeight(Node<Key, Value> * root) const{
	if (root == nullptr){
		return 0;
	}

	int leftHeight = treeHeight(root -> getLeft());
	int rightHeight = treeHeight(root -> getRight());

	int max = leftHeight;
	if (rightHeight > leftHeight){
		max = rightHeight;
	}

	return 1 + max;

}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    // If the nodes are the same or either of them is NULL, return
    if (n1 == n2 || n1 == nullptr || n2 == nullptr) {
        return;
    }

    // Store the parent, right and left children, and the positional relationship of the first node
    Node<Key, Value>* n1_parent = n1->getParent();
    Node<Key, Value>* n1_right = n1->getRight();
    Node<Key, Value>* n1_left = n1->getLeft();
    bool n1_is_left_child = (n1_parent != nullptr) && (n1_parent->getLeft() == n1);

    // Store the parent, right and left children, and the positional relationship of the second node
    Node<Key, Value>* n2_parent = n2->getParent();
    Node<Key, Value>* n2_right = n2->getRight();
    Node<Key, Value>* n2_left = n2->getLeft();
    bool n2_is_left_child = (n2_parent != nullptr) && (n2_parent->getLeft() == n2);

    // Swap the parent of the two nodes
		Node<Key, Value>* temp;

		temp = n1 -> getParent();
    n1->setParent(n2 -> getParent());
    n2->setParent(temp);

    // Swap the right child of the two nodes
		temp = n1 -> getRight();
    n1->setRight(n2 -> getRight());
    n2->setRight(temp);

    // Swap the left child of the two nodes
		temp = n1 -> getLeft();
    n1->setLeft(n2 -> getLeft());
		n2 ->setLeft(temp);

		if (n1_right != nullptr && n1_right == n2){
			n2 -> setRight(n1);
			n1 -> setParent(n2);
		}
		else if (n1_left != nullptr && n1_left == n2){
			n2 -> setLeft(n1);
			n1 ->setParent(n2);
		}
		else if (n2_right != nullptr && n2_right == n1){
			n1 -> setRight(n2);
			n2 -> setParent(n1);
		}
		else if (n2_left != nullptr && n2_left == n1){
			n1 -> setLeft(n2);
			n2 -> setParent(n1);
		}

    // Swap the child pointers between the two nodes
    if (n1_parent != nullptr && n1_parent != n2) {
        if (n1_is_left_child) {
            n1_parent->setLeft(n2);
        } else {
            n1_parent->setRight(n2);
        }
    }
    if (n2_parent != nullptr && n2_parent != n1) {
        if (n2_is_left_child) {
            n2_parent->setLeft(n1);
        } else {
            n2_parent->setRight(n1);
        }
    }
    if (n1_left != nullptr && n1_left != n2) {
        n1_left->setParent(n2);
    }
    if (n1_right != nullptr && n1_right != n2) {
        n1_right->setParent(n2);
    }
    if (n2_left != nullptr && n2_left != n1) {
        n2_left->setParent(n1);
    }
    if (n2_right != nullptr && n2_right != n1) {
        n2_right->setParent(n1);
    }


		if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
