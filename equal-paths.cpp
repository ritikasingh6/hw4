#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node *node);


bool equalPaths(Node * root)
{
    // Add your code below
    // empty tree, so paths are equal
    if (root == nullptr){
        return true;
    }
    if (root -> left == nullptr && root -> right == nullptr){
        return true;
    }
    // check if left and right subtrees are equal lengths
		/*
    bool equalLeft = equalPaths(root -> left);
    bool equalRight = equalPaths(root -> right);

    // if either subtree has unequal length path
    if (equalLeft == false || equalRight == false){
        return false;
    }
		*/

    int leftDepth = depth(root -> left);
    int rightDepth = depth(root -> right);
    if(leftDepth == rightDepth){
			return true;
		}
		else if (leftDepth == 1 && rightDepth == 0){
			return true;
		}
		else if (leftDepth == 0 && rightDepth == 1){
			return true;
		}
		return false;


}

int depth(Node *node){
    if (node == nullptr){
        return 0;
    }
    int ldepth = depth(node -> left);
    int rdepth = depth(node -> right);
    int max = rdepth;

    if (ldepth > rdepth){
        max = ldepth;
    }
    return max + 1;
}

