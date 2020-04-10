#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

// if a greater than b you print out a otherwise, condition is followed by a question mark, if condition is true
// return a, else (:) return b






// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}



int getHeight(AVLTreeNode *node) // doesn't have to use node in funtion
{
	if (node)
	{
		return node->height; // code will stop, get out of tunnel
	}
	return -1;  //empty node has the height of -1
}




int balance_factor(AVLTreeNode * node)
{
    int balance_factor;
    balance_factor = getHeight(node->right) - getHeight(node->left);
    return balance_factor;
}


 /* check if tree_node is left child or right child

 char *check_node_position (AVLTreeNode * tree_node)
{
    if (tree_node->parent == NULL)
    { return "left child";}
    if (tree_node->parent->left == tree_node)
    {return -1;} // left child of parent
    else return 1; // right child of parent

}

 xy = "left child"
 include string library, string.h
 strrcomp (xy, leftchild) */

// Right straight line // why can the input not just be a node, why is it a pointer to a node ?

AVLTreeNode *Rotate_left (AVLTreeNode* current_node)
{
    current_node->right->parent = current_node->parent; // parent of 4 becomes root
    current_node->parent = current_node->right; // 2's parent becomes 4, root points to 4
    current_node->right = current_node->parent->left; // any tree on the left side of 4 (T1) becomes a child of 2
    // but how do you change this trees parent
    if (current_node->right != NULL)
    {
        current_node->right->parent = current_node; // WHY CAN IT NOT WORK WITHOUT THIS
    }
    current_node->parent->left = current_node; // 4's left child becomes 2
    current_node->height = 1 + max(getHeight(current_node->right), getHeight(current_node->left));
    current_node = current_node->parent;
    current_node->height = 1 + max(getHeight(current_node->right), getHeight(current_node->left));
    return current_node;
    
}


// Left straight line // why can the input not just be a node, why is it a pointer to a node ?

AVLTreeNode *Rotate_right (AVLTreeNode* current_node)
{
    current_node->left->parent = current_node->parent; // parent of 3 becomes root
    current_node->parent = current_node->left; // 4's parent becomes 3, root points to 3
    current_node->left = current_node->parent->right; // any tree on the right side of 3 (T1) becomes a child of 4
    if (current_node->left != NULL)
    {
        current_node->left->parent = current_node; // WHY CAN IT NOT WORK WITHOUT THIS
    }
    current_node->parent->right = current_node; // 3's right child becomes 4 and the left child remains unchanged
    current_node->height = 1 + max(getHeight(current_node->right), getHeight(current_node->left));
    current_node = current_node->parent;
    current_node->height = 1 + max(getHeight(current_node->right), getHeight(current_node->left));
    return current_node;
    
}

// need to update height


// This function transforms left elbow into a left straight line which is then rotated

AVLTreeNode *Rotate_right_double(AVLTreeNode * current_node)
{   AVLTreeNode * x;
    AVLTreeNode * y;
    AVLTreeNode * z;
    y = current_node->left;
    x = current_node->left->right;
    current_node->left = x;
    x->parent = current_node;
    y->right = x->left;
    if (y->right != NULL)
    {
        y->right->parent = y;
    }
    x->left = y;
    y->parent = x;
    
    x->height = 1 + max(getHeight(x->right), getHeight(x->left));
    y->height = 1 + max(getHeight(y->right), getHeight(y->left));
    current_node->height = 1 + max(getHeight(current_node->right), getHeight(current_node->left));
    return current_node;
}


AVLTree *insert_at_root (AVLTree* tree, AVLTreeNode * node)
    {
  // 1. If the tree is empty, creates a tree with the given node
        if (tree->size ==0)
        {

            node->parent = tree->root;
            tree->root = node;
            tree->size++;

        }
    return tree;
    }


AVLTreeNode *insert_in_tree  (AVLTreeNode * tree_node, AVLTreeNode * insert_node)
    {   int bf_node, by, bz;
        int left_height, right_height;
        // base case when null is reached
        if (tree_node == NULL)
           // tree_node->parent = parent_newnode_pointer;
            //printf("tree node key is %d \n ",tree_node->key);
        {
            tree_node = insert_node; // the inserted node will always have a balance factor of 0 as it has no children
            //tree_node->parent = parent_newnode_pointer;
            //printf("parent node key is %d \n ",tree_node->parent->key);
            return tree_node; // early exit from entire code -- skips everything after this and goes into the main function that called this entire thing
        }
        // recursion case
        AVLTreeNode * parent_newnode_pointer = tree_node; // why is this causing an issue ?
        if ((tree_node->key < insert_node->key)  || (tree_node->key == insert_node->key && tree_node->value < insert_node->value))
        {

            tree_node->right = insert_in_tree(tree_node->right, insert_node);
            tree_node->right->parent = tree_node;

        }
        else
        {   tree_node->left = insert_in_tree(tree_node->left, insert_node);
            tree_node->left->parent = tree_node;

        }


        // update height before and after balancing
        tree_node->height = 1 + max(getHeight(tree_node->right), getHeight(tree_node->left));

        // after increasing the height, check the balance again

        bf_node = balance_factor(tree_node);
        
        if (bf_node != 2 && bf_node!= -2)  // check if we need to balance
        {
            return tree_node; // return node as balanced, 1 / -1 is already balanced
        }
        else if (bf_node == 2)  // right straight or right elbow, so check which case
        {
            // check if tree_node is left child or right child - there is no need
            // both right straight and right elbow have second node (b) on right side of node
            // with balance factor of 2

            if (balance_factor(tree_node->right) == 1) // right straight line              )
            {   
                // tree_node = 2, tree_node->right = 4, tree_node_right_right = 9

                tree_node = Rotate_left(tree_node);
                bf_node = balance_factor(tree_node);
            }
            
            //if (balance_factor(tree_node->right) == -1) // right elbow
                

            
        }
        
        else if (bf_node == -2)
        {        bf_node = balance_factor(tree_node); 
             if (bf_node == -2 && balance_factor(tree_node->left) == -1) // left straight line              
            {   
                // tree_node = 2, tree_node->right = 4, tree_node_right_right = 9

                tree_node = Rotate_right(tree_node);
                bf_node = balance_factor(tree_node);
            }
            
           if (bf_node == -2 && balance_factor(tree_node->left) == 1) // left elbow
                // left elbow, break it into 2 steps, first transform into a order that can be fixed using a single rotation
                // transformation
            {   tree_node = Rotate_right_double(tree_node);
                tree_node = Rotate_right(tree_node);
                bf_node = balance_factor(tree_node);
            }
            
        }
        
        return tree_node; // draw


    }





AVLTree *CreateAVLTree (const char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    AVLTree *mytree;
    AVLTreeNode *node;
    AVLTreeNode *pointer_end_node;
    AVLTreeNode *temp_pointer;
    mytree = newAVLTree(); // empty tree
    int x , balance_factor_node, balance_factor_parent, balance_factor_grandparent ,  num_pairs,  size,  y , flag ;  // variables used
    int endcode = 1;  //if I use while 1, then I get an error, as my code does not run anything outside of while loop
    int i = 0;
    while (endcode ==1)
        {
            flag =  fscanf(fp, " %*[(] %d %*[,] %d %*[)] ", &x, &y); // obtain a pair of key and value

            //EOF Case
            if (flag == EOF)
            {
                printf("end of file \n");
                endcode = 0 ; // why not return 0 here as we need to end while loop, or return tree ?
            }
            // Invalid Input Case
            else if (flag == 0)
            {
                printf("Invalid input \n");
                endcode = 0 ;
            }
            // All other cases
            else
            {    // case when empty tree
                node = newAVLTreeNode(x,y);
                if (mytree->size ==0)
                {
                  mytree = insert_at_root (mytree, node);


                }

                else
                {
                    mytree->root = insert_in_tree(mytree->root, node);
                    mytree->size ++;
                    printf("tree root is this after balancing %d \n",  mytree->root->key);






                }}}

    fclose ( fp ) ; // Closing the file
    return mytree;
}





// function followed immediately with paranthesis
void printhelper(AVLTreeNode* node){
    if (node != NULL){
        printhelper(node->left);
        printf("key is %d and value is %d \n",  node->key, node->value);
        printhelper(node->right);
    }

// if null, all function is skipped, nothing is performed, all body of if part is skipped



}


void PrintAVLTree(AVLTree *T)  // if original function has input different from what we need to use, make use of helper function
{ printhelper(T->root);
}





int main()
{
    AVLTree *mytree;
    mytree = CreateAVLTree ("File1.txt");
    //PrintAVLTree(mytree);
    free (mytree);
}
