#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rightRotate(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    void leftRotate(AVLNode<Key, Value>* n1, AVLNode<Key,Value>* n2);
		void insertFix(AVLNode<Key,Value>* curr, AVLNode<Key,Value>* parent, AVLNode<Key,Value>* grandp);
    void removeFix(AVLNode<Key,Value>* n, int diff);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
	Key key_ = new_item.first;
	Value value_ = new_item.second;
	AVLNode<Key, Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
	AVLNode<Key, Value>* parent = nullptr;
	bool left_ = false;

	if (this -> root_ == NULL){
		this->root_ = new AVLNode<Key,Value>(key_,value_,nullptr);
    return;
	}
	else{
		while (curr != NULL){
			Key currKey = curr -> getKey();
			parent = curr;
			
			if (key_ < currKey){
				curr = curr->getLeft();
				left_ = true;
			}
			else if (key_ > currKey){
				curr = curr->getRight();
				left_ = false;
			}
			else if (key_ == currKey){
				curr->setValue(value_);
				return;
			}
		}

		curr = new AVLNode<Key,Value>(key_,value_,parent);
		if (left_ == true){
			parent -> setLeft(curr);
		}
		else if (left_ == false){
			parent -> setRight(curr);
		}
	}

	if (parent -> getLeft() != curr){
		parent->updateBalance(1);
	}
	else if (parent -> getLeft()==curr){
		parent->updateBalance(-1);
	}

	AVLNode<Key, Value>* grandp = parent->getParent();

	while(grandp != nullptr){
		if (parent -> getBalance() == 0){
			return;
		}
		if (grandp -> getLeft() == parent){
			grandp -> updateBalance(-1);
		}
		else{
			grandp -> updateBalance(1);
		}

		if (grandp->getBalance()== 2){
			insertFix(curr,parent,grandp);
			return;
		}
		else if (grandp -> getBalance() == -2){
			insertFix(curr,parent,grandp);
			return;
		}
		else{
			curr = parent;
			parent = grandp;
			grandp = grandp -> getParent();
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* curr, AVLNode<Key,Value>* parent, AVLNode<Key,Value>* grandp){
    if(parent == NULL || parent->getParent() == NULL || grandp->getBalance() == 0){
        return;
    }

    if(grandp->getBalance() == 2){
        if(parent->getRight() == curr){
            leftRotate(parent, grandp);
            parent->setBalance(0);
            grandp->setBalance(0);
        }
        else{
            rightRotate(curr, parent);
            leftRotate(curr, grandp);

            if(curr->getBalance() == 1){
                curr->setBalance(0);
                parent->setBalance(0);
                grandp->setBalance(-1);
            }
            else if(curr->getBalance() == -1){
                curr->setBalance(0);
                parent->setBalance(1);
                grandp->setBalance(0);
            }
            else if(curr->getBalance() == 0){
                curr->setBalance(0);
                parent->setBalance(0);
                grandp->setBalance(0);
            }
        }
    }
    else if(grandp->getBalance() == -2){
        if(parent->getLeft() == curr){
            rightRotate(parent, grandp);
            parent->setBalance(0);
            grandp->setBalance(0);
        }
        else{
            leftRotate(curr, parent);
            rightRotate(curr, grandp);

            if(curr->getBalance() == -1){
                curr->setBalance(0);
                parent->setBalance(0);
                grandp->setBalance(1);
            }
            else if(curr->getBalance() == 1){
                curr->setBalance(0);
                parent->setBalance(-1);
                grandp->setBalance(0);
            }
            else if(curr->getBalance() == 0){
                curr->setBalance(0);
                parent->setBalance(0);
                grandp->setBalance(0);
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
	AVLNode<Key,Value>* curr = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
	if (curr == nullptr){
		return;
	}

	AVLNode<Key,Value>* parent = curr -> getParent();
	AVLNode<Key,Value>* child = nullptr;

	int diff = 0;

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
			parent -> setLeft(nullptr);
			diff = 1;
		}
		else if (rtrue){
			parent -> setRight(nullptr);
			diff = -1;
		}
		else if (isRoot){
			this -> root_ = nullptr;
		}
		delete curr;
	}
	else if (curr->getLeft()==nullptr || curr->getRight()==nullptr){
		if (curr->getLeft()==nullptr){
			child = curr -> getRight();
		}
		else{
			child = curr -> getLeft();
		}


		if (isRoot){
			this -> root_ = child;
		}
		else if (ltrue){
			parent -> setLeft(child);
			diff = 1;
		}
		else if (rtrue){
			parent -> setRight(child);
			diff = -1;
		}
		
		child -> setParent(parent);
		delete curr;
	}
	else{
		AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(curr));
		child = pred -> getLeft();
		//pred->getParent()->setRight(child);
		nodeSwap(curr, pred);
		parent = curr -> getParent();
		if (parent -> getLeft() != curr){
			parent -> setRight(child);
			diff = -1;
		}
		if (parent -> getLeft() == curr){
			parent -> setLeft(child);
			diff = 1;
		}
		

		if (child != nullptr){
			child -> setParent(parent);
		}
		delete curr;
	}
	removeFix(parent, diff);

}

template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* node,int diff){
	if (diff == 0){
		return;
	}
	
	int parentDifference = 0;
	AVLNode<Key,Value>* parent = node -> getParent();

	if (parent != nullptr){
		if (parent -> getLeft() == node){
			parentDifference =  1;
		}
		else{
			parentDifference = -1;
		}
	}

	int ba = node -> getBalance();
	int bas = ba + diff;
	if (bas == 0){
		node -> setBalance(0);
		removeFix(parent, parentDifference);
	}
	else if (bas == 1 || bas == -1){
		node -> setBalance(diff);
		return;
	}
	else if (bas == -2){
		AVLNode<Key,Value>* child = node -> getLeft();
		AVLNode<Key,Value>* grandChild = nullptr;

		int bChild = child -> getBalance();
		if (bChild == 0){
			rightRotate(child, node);
			node -> setBalance(-1);
			child -> setBalance(1);
			return;
		}
		else if (bChild == -1){
			rightRotate(child, node);
			node -> setBalance(0);
			child -> setBalance(0);
			removeFix(parent, parentDifference);
		}
		else if (bChild == 1){
			grandChild = child -> getRight();
			leftRotate(grandChild, child);
			rightRotate(grandChild, node);
			int bgrandChild = grandChild -> getBalance();

			if (bgrandChild == -1){
				node -> setBalance(1);
				child -> setBalance(0);
				grandChild -> setBalance(0);
			}
			else if (bgrandChild == 0){
				node -> setBalance(0);
				child -> setBalance(0);
				grandChild -> setBalance(0);
			}
			else if (bgrandChild == 1){
				node -> setBalance(0);
				child ->setBalance(-1);
				grandChild -> setBalance(0);
			}
			removeFix(parent, parentDifference);
		}
	}
		else if(bas == 2){
			AVLNode<Key,Value>* child = node -> getRight();
			AVLNode<Key,Value>* grandChild = nullptr;

			int bChild = child -> getBalance();
			if (bChild == 0){
				leftRotate(child, node);
				node -> setBalance(1);
				child -> setBalance(-1);
				return;
			}
			else if (bChild == 1){
				leftRotate(child, node);
				node -> setBalance(0);
				child -> setBalance(0);
				removeFix(parent, parentDifference);
			}
			else if (bChild == -1){
				grandChild = child -> getLeft();
				rightRotate(grandChild, child);
				leftRotate(grandChild, node);
				int bgrandChild = grandChild -> getBalance();

				if (bgrandChild == -1){
					node -> setBalance(0);
					child -> setBalance(1);
					grandChild -> setBalance(0);
				}
				else if (bgrandChild == 0){
					node -> setBalance(0);
					child -> setBalance(0);
					grandChild -> setBalance(0);
				}
				else if (bgrandChild == 1){
					node -> setBalance(-1);
					child ->setBalance(0);
					grandChild -> setBalance(0);
				}
				removeFix(parent, parentDifference);
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2) 
{
  AVLNode<Key, Value>* parent_n2 = n2->getParent();
  n2->setLeft(n1->getRight());
  if (n1->getRight() != nullptr) {
    n1->getRight()->setParent(n2);
  }
  n1->setRight(n2);
  n2->setParent(n1);
  n1->setParent(parent_n2);
  if (parent_n2 != nullptr) {
    if (parent_n2->getLeft() == n2) {
      parent_n2->setLeft(n1);
    } else {
      parent_n2->setRight(n1);
    }
  } else {
    this->root_ = n1;
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2) 
{
  AVLNode<Key, Value>* parent_n2 = n2->getParent();
  n2->setRight(n1->getLeft());
  if (n1->getLeft() != nullptr) {
    n1->getLeft()->setParent(n2);
  }
  n1->setLeft(n2);
  n2->setParent(n1);
  n1->setParent(parent_n2);
  if (parent_n2 != nullptr) {
    if (parent_n2->getLeft() == n2) {
      parent_n2->setLeft(n1);
    } else {
      parent_n2->setRight(n1);
    }
  } else {
    this->root_ = n1;
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
	BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
	int8_t temp = n1 -> getBalance();
	n1 -> setBalance(n2 -> getBalance());
	n2 -> setBalance(temp);
}




#endif
