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


 // check if tree_node is left child or right child
 
int *check_node_position (AVLTreeNode * tree_node)
{
    if (tree_node->parent == NULL)
    { return 0;}
    if (tree_node->parent->left == tree_node)
    {return -1;} // left child of parent
    else return 1; // right child of parent

}
 
 
 
 





AVLTree *BalanceAVLTree(AVLTree * tree, AVLTreeNode *pointer_end_node)
{
    int a,b,c;
    int check;
    AVLTreeNode * z, *y, *x, *current_pointer;
    current_pointer = pointer_end_node;
    check = 1;
    //printf("%d \n", pointer_end_node->key);  //5
    //printf("%d \n", pointer_end_node->parent->key); //4
    //printf("%d \n", pointer_end_node->parent->parent->key); //6
    a = balance_factor(current_pointer->parent->parent); //segmentation fault
    b = balance_factor(current_pointer->parent);
    while (check == 1)
    {  //how do you get out of this loop when while(1), would you use return 0 or return list
        // code is not changing a and b values

        //printf("values of a and b are %d %d \n", a, b);

        if (tree->size <3)
        {   check = 0; // tree is balanced, should I use return 0 ?
        }

        if (tree->size == 3)
        {
            if ((b ==1 || b ==0 || b == -1) && (a ==1  || a ==0 || a == -1)) // tree is balanced
            {
                check = 0; // end
            }
            //Right Straight Line
            else if (a==2 && b ==1 )
            {
                //printf("test before code %d \n" , tree->root->key);
                z = tree->root;
                y = current_pointer->parent;
                z->left = NULL;
                z->right = NULL;
                z-> height = 0;
                z->parent = y;
                y->left = z;
                y->parent = NULL;
                tree->root = y;
                //printf("The height of the right and left children of y are %d %d \n", y->right->height, y->left->height );
                a = balance_factor(y);
                b = balance_factor(z);
                //printf("values of a and b after balancing are %d %d \n", a, b);
                //printf("test after code %d \n" , tree->root->key);

            }
            //left straight line
            else if (a== -2 && b == -1 )
            {
                //printf("test before case 2 code is %d \n" , tree->root->key); //6
                z = tree->root;  //z -> 6
                y = current_pointer->parent;  //y --> 5
                z->left = NULL;
                z->right = NULL;
                z->height = 0;
                tree->root = y; //5
               // printf("root is %d \n" , tree->root->key);
                y->right = z;
                z->parent = y;
                y->parent = NULL;
                a = balance_factor(y);
                b = balance_factor(z);

                 //5
                //printf("2nd node is %d \n" , tree->root->left->key); //4
               // printf("3nd node is %d \n" , tree->root->right->key); //6


            }
            // left elbow
            else if (a== -2 && b == 1 )
            {
                //printf("test before case 3 code is %d \n" , tree->root->key); //6
                //.      6                       6
                //.    4      =====>           5
                //.     5    currentpointer  4
                y = current_pointer->parent;  //y = 4
                x = current_pointer; // 5
                tree->root->left = x; //5
                x->height = 1;
                x->left = y; //4
                y->parent = x;
                y->right = NULL;
                y->height = 0;
                current_pointer = y;
                a = balance_factor(tree->root);  //-2
                //printf("currentpointer parent %d \n", current_pointer->parent->key);
                b = balance_factor(current_pointer->parent);  //-1

            }

            // Right Elbow
            else if (a== 2 && b == -1)
            {   //currentpointer = 7
                y = current_pointer->parent;  //y = 9
                x = current_pointer; // 7
                tree->root->right = x; //7
                x->height = 1;
                x->right = y; //9
                y->parent = x;
                y->right = NULL;
                y->height = 0;
                current_pointer = y;  //9
                a = balance_factor(tree->root);  //-2
                //printf("currentpointer parent %d \n", current_pointer->parent->key);
                b = balance_factor(current_pointer->parent);

            }
        }

    }

    return tree;
}

AVLTree *insert_at_root (AVLTree* tree, AVLTreeNode * node)
    {
  // 1. If the tree is empty, creates a tree with the given node
        if (tree->size ==0)
        {
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
        
        
        
        tree_node->height = 1 + max(getHeight(tree_node->right), getHeight(tree_node->left));
       
        // after increasing the height, check the balance again
       
       
        bx = balance_factor(tree_node);
        if (bf_node != 2 && bf_node!= -2)
        {
            return tree_node; // draw
        } 
        else if (bf_node=2)  // right straight or right elbow, so check which case
        {
            left_height = getHeight(tree_node->left);    
            right_height = getHeight(tree_node->right);
            
            // check if tree_node is left child or right child
            
            if ( left_height == -1 && right_height == 1) // right straight line              ) 
            {
                tree_node->right->parent = tree_node->parent;
                tree_node->parent = tree_node->right;
                tree_node->right = tree_node->parent->left;
                tree_node->parent->left = tree_node;
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
                    //printf("tree size is %d \n",  mytree->size);
                   





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

// put your time complexity analysis for PrintAVLTree() here
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

/*

Do we need to free pointers ?










*/