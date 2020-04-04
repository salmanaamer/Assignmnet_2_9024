
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

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

int balance_factor(AVLTreeNode * node)
{
    int balance_factor;
    int left_height;
    int right_height;
    if (node->height ==0)
    {
        balance_factor = 0;
    }
    else 
    {
        if (node->left ==NULL)
        {
            left_height = -1;
            balance_factor = node->right->height - left_height;
        }
        else if (node->right ==NULL)
        {
            right_height = -1;
            balance_factor = right_height - node->left->height;
        }
        else
        {
            balance_factor = node->right->height - node->left->height;
        }
    }
    return balance_factor;
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
        
        printf("values of a and b are %d %d \n", a, b);

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
                printf("test before case 2 code is %d \n" , tree->root->key); //6
                z = tree->root;  //z -> 6
                y = current_pointer->parent;  //y --> 5
                z->left = NULL;
                z->right = NULL;
                z->height = 0;
                tree->root = y; //5
                printf("root is %d \n" , tree->root->key);
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
               // printf("values of a and b are %d %d \n", a, b);
                //return tree;  //after the 1st rotation
                //printf("root is %d \n" , tree->root->key); //6
                //printf("2nd node is %d \n" , tree->root->left->key); //5
                //printf("3nd node is %d \n" , tree->root->left->left->key); //4

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
            {
                node = newAVLTreeNode(x,y); 
                if (mytree->size ==0)  // case when empty tree
                {
                  //List is empty, the added node will be a root
                  mytree->root = node; // the first node will by default be parent
                  mytree->size++;  // no space in this case, it doesn't matter where the ++ occur  
                  //Tests
                  //printf("mytree first node key  is %d \n", mytree->root->key);
                  //printf("mytree size after first node  is %d \n", mytree->size);
                } 
                // cases when inserted into a balanced tree of 1 node
                else if (mytree->size ==1)    
                {   
                    if ((mytree->root->key < node->key)  || (mytree->root->key == node->key && mytree->root->value < node->value))
                    // adding to right side, with only a parent node before
                    {   mytree->root->right = node;
                        node->parent = mytree->root;
                        
                        
                    }  
                    else
                    {
                        mytree->root->left = node;  // adding to left side, with only a parent node before
                        node->parent = mytree->root; 
                    }
                    mytree->root->height++;
                    mytree->size++;
                    // Tests
                    //printf("mytree size after second node inserted  is %d \n", mytree->size);
                    // printf("mytree key for second node inserted  is %d \n", mytree->root->right->key);
                } 
                // cases when inserted into a balanced tree of 2 nodes
                else if (mytree->size == 2)  
                {   
                    if ((mytree->root->key < node->key) || (mytree->root->key == node->key && mytree->root->value < node->value)) // adding to right side 
                    {
                        if (mytree->root->right == NULL) // adding to right with no node to right side, and one node on left side of parent
                        {
                            mytree->root->right = node;
                            node->parent = mytree->root;
                            mytree->root->height++;
                            mytree->size++;
                        }                        
                        else if ((mytree->root->right->key < node->key) || (mytree->root->right->key == node->key && mytree->root->right->value < node->value))
                        // adding to right side, with one node on right side, with inserted node greater than current right side node
                        {   
                            mytree->root->right->right = node;
                            node->parent = mytree->root->right;
                            mytree->root->right->height++;
                            mytree->root->height++;
                            mytree->size++;   
                        }
                        else 
                        // adding to right side, with one node on right side, with inserted node less than current right side node
                        {   
                            mytree->root->right->left = node;
                            node->parent = mytree->root->right;
                            mytree->root->right->height++;
                            mytree->root->height++;
                            mytree->size++;
                            
                        }}

                    else if (mytree->root->left == NULL)  // adding to left side - No Node on left, one on right
                    {
                            mytree->root->left = node;
                            node->parent = mytree->root;
                            mytree->root->height++;
                            mytree->size++;
                    }
                    else if ((mytree->root->left->key < node->key) || (mytree->root->left->key == node->key && mytree->root->left->value < node->value))
                    {   
                      
                         // adding to left side, with one node on left side, with inserted node greater than current left side node

                            mytree->root->left->right = node;
                            node->parent = mytree->root->left;
                            mytree->root->left->height++;
                            mytree->root->height++;
                            mytree->size++;
                    }
                    else 
                    {
                        // adding to left side, with one node on left side, with inserted node less than current left side node
                            mytree->root->left->left = node;
                            node->parent = mytree->root->left;
                            mytree->root->left->height++;
                            mytree->root->height++;
                            mytree->size++;
                    }
                // Tests
                //printf("mytree size after third node inserted  is %d \n", mytree->size);
                //printf("mytree height for third node inserted  is %d \n", mytree->root->height);    
                }
             



            }
    
        }
    /* Test Cases for First Case in Whiteboard 
    
    printf("mytree root key before balancing is %d \n", mytree->root->key);
    printf("mytree second node key before balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key before balancing is %d \n", mytree->root->right->right->key);
    printf("mytree size before balancing is %d \n \n \n", mytree->size);
    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root before balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node before balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->right->right);
    printf("The balance factor for third node before balancing is %d \n \n \n", balance_factor_node); 
    

    mytree = BalanceAVLTree(mytree, node);
    printf("mytree root key after balancing is %d \n", mytree->root->key);
    /*printf("mytree second node key after balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key after balancing is %d \n", mytree->root->left->key);
    printf("mytree size after balancing is %d \n \n \n", mytree->size);
    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root after balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node after balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->left);
    printf("The balance factor for third node after balancing is %d \n", balance_factor_node); */

    /* /Test Cases for Left Elbow 
    
    printf("mytree root key before balancing is %d \n", mytree->root->key);
    printf("mytree second node key before balancing is %d \n", mytree->root->left->key);
    printf("mytree third node key before balancing is %d \n", mytree->root->left->right->key);
    printf("mytree size before balancing is %d \n \n \n", mytree->size);


    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root before balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->left);
    printf("The balance factor for second node before balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->left->right);
    printf("The balance factor for third node before balancing is %d \n \n \n", balance_factor_node); 
    

    mytree = BalanceAVLTree(mytree, node);
    printf("mytree root key after balancing is %d \n", mytree->root->key);

    printf("mytree second node key after balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key after balancing is %d \n", mytree->root->left->key); //5
    printf("mytree size after balancing is %d \n \n \n", mytree->size);

    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root after balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node after balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->left);
    printf("The balance factor for third node after balancing is %d \n", balance_factor_node); */

  /* Test Cases for First Case in Whiteboard 
    
    printf("mytree root key before balancing is %d \n", mytree->root->key);
    printf("mytree second node key before balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key before balancing is %d \n", mytree->root->right->right->key);
    printf("mytree size before balancing is %d \n \n \n", mytree->size);
    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root before balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node before balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->right->right);
    printf("The balance factor for third node before balancing is %d \n \n \n", balance_factor_node); 
    

    mytree = BalanceAVLTree(mytree, node);
    printf("mytree root key after balancing is %d \n", mytree->root->key);
    /*printf("mytree second node key after balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key after balancing is %d \n", mytree->root->left->key);
    printf("mytree size after balancing is %d \n \n \n", mytree->size);
    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root after balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node after balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->left);
    printf("The balance factor for third node after balancing is %d \n", balance_factor_node); */

    //Test Cases for Right Elbow 
    
    printf("mytree root key before balancing is %d \n", mytree->root->key);
    printf("mytree second node key before balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key before balancing is %d \n", mytree->root->right->left->key);
    printf("mytree size before balancing is %d \n \n \n", mytree->size);


    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root before balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node before balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->right->left);
    printf("The balance factor for third node before balancing is %d \n \n \n", balance_factor_node); 
    

    mytree = BalanceAVLTree(mytree, node);
    printf("mytree root key after balancing is %d \n", mytree->root->key);

    printf("mytree second node key after balancing is %d \n", mytree->root->right->key);
    printf("mytree third node key after balancing is %d \n", mytree->root->left->key); //5
    printf("mytree size after balancing is %d \n \n \n", mytree->size);

    balance_factor_grandparent = balance_factor(mytree->root);
    printf("The balance factor for root after balancing is %d \n", balance_factor_grandparent);
    balance_factor_parent = balance_factor(mytree->root->right);
    printf("The balance factor for second node after balancing is %d \n", balance_factor_parent);
    balance_factor_node = balance_factor(mytree->root->left);
    printf("The balance factor for third node after balancing is %d \n", balance_factor_node); 












    fclose ( fp ) ; // Closing the file
    //printf("mytree size in create avl tree function is is %d \n", mytree->size);
    return mytree;
}







int main(){ 
AVLTree *mytree;
mytree = CreateAVLTree ("File1.txt");
free (mytree);
}


// Given that you have list of key - values
// Build up an unbalanced tree from the list
// Balance tree 
// Balance an AVL given that the subtree is balanced


// Other approach
// Build and balance the tree as you read in the key - value
// elbow vs straight

// Read in (key-value) one at a time
// Create an AVLTreeNode out of this key-value
// Add this node to the AVLTree (tree is empty and when tree has some nodes)
// Make sure the tree is balanced: from the newly added node upto the root, following the path
// If the node has a balance factor > 1 or < -1 -> fix the tree based on 1 out of 4 configuration 
// Balance the tree if out of balance 
// 

// Create the AVLTree with the 1st node 
// From the 2nd node onwards, we check the balance after every newly added node 
// Fix the balance if out of balance 