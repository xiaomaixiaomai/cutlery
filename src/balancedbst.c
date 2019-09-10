#include<balancedbst.h>

balancedbst* get_balancedbst(tree_type balanced_tree_type, int (*key_compare)(const void* key0, const void* key1))
{
	balancedbst* balancedbst_p = (balancedbst*) calloc(1, sizeof(balancedbst));
	balancedbst_p->balanced_tree_type = balanced_tree_type;
	balancedbst_p->root = NULL;
	balancedbst_p->key_compare = key_compare;
	return balancedbst_p;
}

node* get_node(const void* key, const void* value)
{
	node* node_p = (node*) calloc(1, sizeof(node));
	node_p->bucket_p = get_bucket(key, value);
	return node_p;
}

/* functions to get node types -- start */

int is_leaf_node(node* node_p)
{
	// if the node does not have a left child and it does not have a right child, it is a leaf node
	return node_p->left_sub_tree == NULL && node_p->right_sub_tree == NULL;
}

int is_root_node(node* node_p)
{
	// if the node does not have a parent node, it is root node of the tree
	return node_p->parent == NULL;
}

int is_internal_node(node* node_p)
{
	// a node which is not leaf node or a root node is an internal node
	return !(is_leaf_node(node_p) || is_root_node(node_p));
}

int has_only_right_sub_tree(node* node_p)
{
	// a node which does not have a left_sub_tree, and has only right_sub_tree
	return node_p->left_sub_tree == NULL && node_p->right_sub_tree != NULL;
}

int has_only_left_sub_tree(node* node_p)
{
	// a node which does not have a right_sub_tree, and has only left_sub_tree
	return node_p->left_sub_tree != NULL && node_p->right_sub_tree == NULL;
}

// used to check if the node is red, in a red black tree
int is_red_node(node* node_p)
{
	return node_p != NULL && node_p->node_property == 0;
}

// used to check if the node is black, in a red black tree
int is_black_node(node* node_p)
{
	return node_p == NULL || node_p->node_property == 1;
}

// returns true if the node_p is the left node of its parent
int is_left_of_its_parent(node* node_p)
{
	return (!(is_root_node(node_p))) && (node_p->parent->left_sub_tree == node_p);
}

// returns true if the node_p is the right node of its parent
int is_right_of_its_parent(node* node_p)
{
	return (!(is_root_node(node_p))) && (node_p->parent->right_sub_tree == node_p);
}

// gets max nodes from itself to any NULL, including itself, in an avl tree
unsigned long long int get_max_height(node* node_p)
{
	if(node_p == NULL)
	{
		return 0;
	}
	if(node_p->node_property > 0)
	{
		return node_p->node_property;
	}
	unsigned long long int left_tree_max_height = get_max_height(node_p->left_sub_tree);
	unsigned long long int right_tree_max_height = get_max_height(node_p->right_sub_tree);
	node_p->node_property = (left_tree_max_height > right_tree_max_height ? left_tree_max_height : right_tree_max_height) + 1;
	return node_p->node_property;
}

// updates max height of the node, in an avl tree
void update_max_height(node* node_p)
{
	node_p->node_property = 0;
	get_max_height(node_p);
}

/* functions to get node types -- end   */

/* utility functions for tree -- start */

int is_balancedbst_empty(balancedbst* blanacedbst_p)
{
	return blanacedbst_p->root == NULL;
}

node* get_smallest_node_from_node(node* node_p)
{
	return node_p->left_sub_tree == NULL ? node_p : node_p->left_sub_tree;
}

node* get_largest_node_from_node(node* node_p)
{
	return node_p->right_sub_tree == NULL ? node_p : node_p->right_sub_tree;
}

//      A                                _B_
//     /  \                             /   \
//    W    B        left rotation      A     C
//        /  \        --------->>     / \   /  \
//       X    C                      W   X Y    Z
//           / \
//          Y   Z
// returns true if rotation was successfull
int left_rotate_tree(balancedbst* balancedbst_p, node* A)
{
	node* parent = A->parent;
	node* B = A->right_sub_tree;
	if( B == NULL )
	{
		return 0;
	}
	else
	{
		node* X = B->left_sub_tree;

		if(parent == NULL)
		{
			balancedbst_p->root = B;
			B->parent = NULL;
		}
		else
		{
			if( is_right_of_its_parent(A) )
			{
				parent->right_sub_tree = B;
				B->parent = parent;
			}
			else if( is_left_of_its_parent(A) )
			{
				parent->left_sub_tree = B;
				B->parent = parent;
			}
		}

		A->right_sub_tree = X;
		X->parent = A;

		B->left_sub_tree = A;
		A->parent = B;
		return 1;
	}
}

//           A                                 _B_
//         /   \                              /   \
//       B      W      right rotation        C     A
//     /   \             --------->>        / \   /  \
//   C      X                              Z   Y  X   W
//  / \
// Z   Y
// returns true if rotation was successfull
int right_rotate_tree(balancedbst* balancedbst_p, node* A)
{
	node* parent = A->parent;
	node* B = A->left_sub_tree;
	if( B == NULL )
	{
		return 0;
	}
	else
	{
		node* X = B->right_sub_tree;

		if(parent == NULL)
		{
			balancedbst_p->root = B;
			B->parent = NULL;
		}
		else
		{
			if( is_right_of_its_parent(A) )
			{
				parent->right_sub_tree = B;
				B->parent = parent;
			}
			else if( is_left_of_its_parent(A) )
			{
				parent->left_sub_tree = B;
				B->parent = parent;
			}
		}

		A->left_sub_tree = X;
		X->parent = A;

		B->right_sub_tree = A;
		A->parent = B;
		return 1;
	}
}

/* utility functions for tree -- end   */

node* find_node_recursively(balancedbst* balancedbst_p, node* root, const void* key_p)
{
	if(balancedbst_p->key_compare(key_p, root->bucket_p->key) == 0)
	{
		return root;
	}
	else if(root->left_sub_tree != NULL && balancedbst_p->key_compare(key_p, root->bucket_p->key) < 0)
	{
		return find_node_recursively(balancedbst_p, root->left_sub_tree, key_p);
	}
	else if(root->right_sub_tree != NULL && balancedbst_p->key_compare(key_p, root->bucket_p->key) > 0)
	{
		return find_node_recursively(balancedbst_p, root->right_sub_tree, key_p);
	}
	else
	{
		return NULL;
	}
}

node* find_node(balancedbst* balancedbst_p, const void* key_p)
{
	// if the tree is empty, just return NULL
	if( is_balancedbst_empty(balancedbst_p) )
	{
		return NULL;
	}
	else
	{
		return find_node_recursively(balancedbst_p, balancedbst_p->root, key_p);
	}
}

// neither root nor node_p params are suppossed to be NULL in the function below
void insert_node_in_non_self_balancing_tree(balancedbst* balancedbst_p, node* root, node* node_p)
{
	if( balancedbst_p->key_compare(node_p->bucket_p->key, root->bucket_p->key) <= 0 )
	{
		if( root->left_sub_tree == NULL )
		{
			root->left_sub_tree = node_p;
			node_p->parent = root;
		}
		else
		{
			insert_node_in_non_self_balancing_tree(balancedbst_p, root->left_sub_tree, node_p);
		}
	}
	else if( balancedbst_p->key_compare(node_p->bucket_p->key, root->bucket_p->key) > 0 )
	{
		if( root->right_sub_tree == NULL )
		{
			root->right_sub_tree = node_p;
			node_p->parent = root;
		}
		else
		{
			insert_node_in_non_self_balancing_tree(balancedbst_p, root->right_sub_tree, node_p);
		}
	}
}

// handle imbalance occuring in red black tree
// only a red node can be imbalanced in a red black tree
// i.e. the parameter node_p->node_property == 0, we dont check that in the function
void handle_imbalance_in_red_black_tree(balancedbst* balancedbst_p, node* node_p)
{
	if(is_root_node(node_p))
	{
		node_p->node_property = 1; //root node is always black
	}
	else
	{
		if( is_red_node(node_p->parent) ) // the parent of the node is red
		{
			// get references to its parent and grand parent nodes
			node* parent_node = node_p->parent;
			node* grand_parent_node = parent_node->parent;

			// node_p's uncle is red
			if ( (is_right_of_its_parent(parent_node) && is_red_node(grand_parent_node->left_sub_tree)) ||
			(is_left_of_its_parent(parent_node) && is_red_node(grand_parent_node->right_sub_tree)) )
			{
				grand_parent_node->node_property = 0;
				grand_parent_node->left_sub_tree->node_property = 1;
				grand_parent_node->right_sub_tree->node_property = 1;
				handle_imbalance_in_red_black_tree(balancedbst_p, grand_parent_node);
			}
			// when node_p's uncle is black
			else
			{
				// i.e. if this is a right right case
				if( is_right_of_its_parent(node_p) && is_right_of_its_parent(parent_node) )
				{
					left_rotate_tree(balancedbst_p, grand_parent_node);
					grand_parent_node->node_property = 0;
					parent_node->node_property = 1;
				}
				// i.e. if this is a left left case
				else if( is_left_of_its_parent(node_p) && is_left_of_its_parent(parent_node) )
				{
					right_rotate_tree(balancedbst_p, grand_parent_node);
					grand_parent_node->node_property = 0;
					parent_node->node_property = 1;
				}
				// i.e. if this is right left case
				else if( is_right_of_its_parent(node_p) && is_left_of_its_parent(parent_node) )
				{
					left_rotate_tree(balancedbst_p, parent_node);
					handle_imbalance_in_red_black_tree(balancedbst_p, parent_node);
				}
				// i.e. if this is left right case
				else if( is_left_of_its_parent(node_p) && is_right_of_its_parent(parent_node) )
				{
					right_rotate_tree(balancedbst_p, parent_node);
					handle_imbalance_in_red_black_tree(balancedbst_p, parent_node);
				}
			}
		}
	}
}

// neither root nor node_p params are suppossed to be NULL in the function below
void insert_node_in_red_black_tree(balancedbst* balancedbst_p, node* root, node* node_p)
{
	// this is a red node
	node_p->node_property = 0;

	// insert this node as if it is getting inserted in a non self balancing tree
	insert_node_in_non_self_balancing_tree(balancedbst_p, root, node_p);

	// handle the imbalance in the red balck tree introduced by inserting the node
	handle_imbalance_in_red_black_tree(balancedbst_p, node_p);
}

// handle imbalance occuring in avl tree
void handle_imbalance_in_avl_tree(balancedbst* balancedbst_p, node* node_p)
{
	while(node_p != NULL)
	{
		update_max_height(node_p);
		unsigned long long int left_tree_max_height = get_max_height(node_p->left_sub_tree);
		unsigned long long int right_tree_max_height = get_max_height(node_p->right_sub_tree);

		// if left tree height is more, do right rotate
		if(left_tree_max_height >= 2 + right_tree_max_height)
		{
			right_rotate_tree(balancedbst_p, node_p);

			// after rotation the height of the node_p or
			// any of its new current parent can not be trusted
			node_p->node_property = 0;
		}
		// if right tree height is more, do left rotate
		else if(right_tree_max_height >= 2 + left_tree_max_height)
		{
			left_rotate_tree(balancedbst_p, node_p);

			// after rotation the height of the node_p or
			// any of its new current parent can not be trusted
			node_p->node_property = 0;
		}
		node_p = node_p->parent;
	}
}

// neither root nor node_p params are suppossed to be NULL in the function below
void insert_node_in_avl_tree(balancedbst* balancedbst_p, node* root, node* node_p)
{
	// the new node is suppossed to be inserted at the leaf initially
	// so right_sub_tree == left_sub_tree == NULL hence difference = 0
	node_p->node_property = 0;

	// insert this node as if it is getting inserted in a non self balancing tree
	insert_node_in_non_self_balancing_tree(balancedbst_p, root, node_p);

	// update max heights of all the parent nodes of node_p
	node* any_parent = node_p;
	do
	{
		update_max_height(any_parent);
		any_parent = any_parent->parent;
	}
	while(any_parent != NULL);

	// handle the imbalance in the red balck tree introduced by inserting the node
	handle_imbalance_in_avl_tree(balancedbst_p, node_p);
}

// node_p param is not suppossed to be NULL in the function below
void insert_node_in_tree(balancedbst* balancedbst_p, node* node_p)
{
	// if the root of the tree is NULL, i.e. the tree is empty, add a new root to the tree
	if( is_balancedbst_empty(balancedbst_p) )
	{
		balancedbst_p->root = node_p;
		node_p->parent = NULL;
		return;
	}

	// else insert node as per the balancing that this tree uses
	switch( balancedbst_p->balanced_tree_type )
	{
		case NON_SELF_BALANCING:
		{
			insert_node_in_non_self_balancing_tree(balancedbst_p, balancedbst_p->root, node_p);
			break;
		}
		case RED_BLACK_TREE :
		{
			insert_node_in_red_black_tree(balancedbst_p, balancedbst_p->root, node_p);
			break;
		}
		case AVL_TREE :
		{
			insert_node_in_avl_tree(balancedbst_p, balancedbst_p->root, node_p);
			break;
		}
	}
}

void put_entry(balancedbst* balancedbst_p, const void* key_p, const void* value_p)
{
	// find a node in the tree that has key_p as its key (we do not want duplicate keys)
	node* node_p = find_node(balancedbst_p, key_p);

	// if we can not find such a node, create a new node and insert it in tree
	if(node_p == NULL)
	{
		node_p = get_node(key_p, value_p);
		insert_node_in_tree(balancedbst_p, node_p);
	}
	// else update the value for the node found
	else
	{
		bucket* bucket_p = ((bucket*)node_p->bucket_p);
		bucket_p->value = value_p;
	}
}

const void* find_value(balancedbst* blancedbst_p, const void* key_p)
{
	node* node_p = find_node(blancedbst_p, key_p);
	return node_p != NULL ? node_p->bucket_p->value : NULL;
}

// the below function only detaches the node thatr has to be deleted
// returns pointer of the node that has to be deleted
// node_p can not be null in the parameters of the function
node* remove_node_from_non_self_balancing_tree(balancedbst* balancedbst_p, node* node_p)
{
	// if atleast one of its children are NULL, the node itself can be removed easily
	if(node_p->left_sub_tree == NULL || node_p->right_sub_tree == NULL)
	{
		// find the parent reference of the node
		node* parent_node = node_p->parent;

		// the child will have one or no child nodes
		// find any one existing node else if it has no child nodes, either left or right are fine
		node* child_sub_tree = has_only_right_sub_tree(node_p) ? node_p->right_sub_tree : node_p->left_sub_tree;

		// since we are removing node_p we update the child references kept by parents 
		// parents = (parent_node if node_p is internal or leaf node, root pointer if node_p is root node)
		// of node_p to the one and only (or none) child of node_p
		if(is_left_of_its_parent(node_p))
		{
			parent_node->left_sub_tree = child_sub_tree;
		}
		else if(is_right_of_its_parent(node_p))
		{
			parent_node->right_sub_tree = child_sub_tree;
		}
		// if a node is neither left or right of its parent, it does not have a parent, hence is a root node 
		else
		{
			balancedbst_p->root = child_sub_tree;
		}

		// since the node_p is removed, and that is has any children
		// the new parent of child of node_p is the parent node of node_p
		if(!is_leaf_node(node_p)) // just to ensure that child_sub_tree is not NULL
		{
			child_sub_tree->parent = parent_node;
		}

		// this new node can not be safely deleted
		return node_p;
	}
	else
	{
		// find a smallest node that is grester than node_p
		node* smallest_node_greater_than_node_p = get_smallest_node_from_node(node_p->right_sub_tree);

		// interchange their data, to bring the removal to any of previously seen easy cases
		const bucket* bucket_p = node_p->bucket_p;
		node_p->bucket_p = smallest_node_greater_than_node_p->bucket_p;
		smallest_node_greater_than_node_p->bucket_p = bucket_p;

		// since we did not remove any node, and now we have duplicate nodes
		// we ask to recursively remove, the duplicate node
		return remove_node_from_non_self_balancing_tree(balancedbst_p, smallest_node_greater_than_node_p);
	}
}

// the below function only detaches the node thatr has to be deleted
// returns pointer of the node that has to be deleted
// node_p can not be null in the parameters of the function
node* remove_node_from_red_black_tree(balancedbst* balancedbst_p, node* node_p)
{
	return NULL;
}

// the below function only detaches the node thatr has to be deleted
// returns pointer of the node that has to be deleted
// node_p can not be null in the parameters of the function
node* remove_node_from_avl_tree(balancedbst* balancedbst_p, node* node_p)
{
	// remove the node as if it is a normal tree, reacquire the pointer to the node that needs to be deleted
	node_p = remove_node_from_non_self_balancing_tree(balancedbst_p, node_p);

	// the imbalance is always in the parent node of the node currently going to be deleted
	node* imbalance_node_p = node_p->parent;

	// remove the imbalance and remove it
	handle_imbalance_in_avl_tree(balancedbst_p, imbalance_node_p);

	// return the node that needs to be deleted
	return node_p;
}

void delete_node(node* node_p)
{
	delete_bucket(((bucket*)node_p->bucket_p));
	free(node_p);
}

int remove_value(balancedbst* balancedbst_p, const void* key_p)
{
	int deleted_nodes_count = 0;
	node* node_p = find_node(balancedbst_p, key_p);
	if(node_p != NULL)
	{
		switch(balancedbst_p->balanced_tree_type)
		{
			case NON_SELF_BALANCING:
			{
				node_p = remove_node_from_non_self_balancing_tree(balancedbst_p, node_p);
				break;
			}
			case RED_BLACK_TREE :
			{
				node_p = remove_node_from_red_black_tree(balancedbst_p, node_p);
				break;
			}
			case AVL_TREE :
			{
				node_p = remove_node_from_avl_tree(balancedbst_p, node_p);
				break;
			}
		}
		if(node_p != NULL)
		{
			delete_node(node_p);
			deleted_nodes_count++;
		}
	}
	return deleted_nodes_count;
}

void print_node(node* node_p, void (*print_key)(const void* key), void (*print_value)(const void* value))
{
	if(node_p != NULL)
	{
		if( is_leaf_node(node_p) )
		{
			printf("\tLEAF NODE     :");
		}
		else if( is_root_node(node_p) )
		{
			printf("\tROOT NODE     :");
		}
		else if( is_internal_node(node_p) )
		{
			printf("\tINTERNAL NODE :");
		}

		printf("\taddress => %d", ((int)node_p));
		printf("\tdata => ");
		print_bucket(node_p->bucket_p, print_key, print_value);
		printf("\t\twith property = %llu\n", node_p->node_property);

		if( !is_root_node(node_p) )
		{
			if(is_left_of_its_parent(node_p))
			{
				printf("\t\tis LEFT of  : \n");
			}
			else if(is_right_of_its_parent(node_p))
			{
				printf("\t\tis RIGHT of : \n");
			}
			printf("\t\t\taddress => %d", ((int)node_p->parent));
			printf("\tdata => ");
			print_bucket(node_p->parent->bucket_p, print_key, print_value);
		}

		if( (!is_leaf_node(node_p)) )
		{
			if(node_p->left_sub_tree != NULL)
			{
				printf("\t\thas a LEFT\n\t\t\tchild  => %d", ((int)node_p->left_sub_tree));
				printf("\tdata => ");
				print_bucket(node_p->left_sub_tree->bucket_p, print_key, print_value);
			}
			if(node_p->right_sub_tree != NULL)
			{
				printf("\t\thas a RIGHT\n\t\t\tchild => %d", ((int)node_p->right_sub_tree)); 
				printf("\tdata => ");
				print_bucket(node_p->right_sub_tree->bucket_p, print_key, print_value);
			}
		}
		printf("\n");
	}
}

void print_tree(node* node_p, void (*print_key)(const void* key), void (*print_value)(const void* value))
{
	if(node_p != NULL)
	{
		print_tree(node_p->left_sub_tree, print_key, print_value);
	}
	print_node(node_p, print_key, print_value);
	printf("\n");
	if(node_p != NULL)
	{
		print_tree(node_p->right_sub_tree, print_key, print_value);
	}
}

void print_balancedbst(const balancedbst* balancedbst_p, void (*print_key)(const void* key), void (*print_value)(const void* value))
{
	printf("TREE : ");
	switch(balancedbst_p->balanced_tree_type)
	{
		case NON_SELF_BALANCING :
		{
			printf("NON_SELF_BALANCING\n");
			break;
		}
		case AVL_TREE :
		{
			printf("AVL_TREE\n");
			break;
		}
		case RED_BLACK_TREE :
		{
			printf("RED_BLACK_TREE\n");
			break;
		}
	}
	print_tree(balancedbst_p->root, print_key, print_value);
	printf("--\n\n");
}

void delete_nodes_from(node* node_p)
{
	if(node_p->left_sub_tree != NULL)
	{
		delete_nodes_from(node_p->left_sub_tree);
	}
	if(node_p->right_sub_tree != NULL)
	{
		delete_nodes_from(node_p->right_sub_tree);
	}
	delete_node(node_p);
}

void delete_balancedbst(balancedbst* balancedbst_p)
{
	delete_nodes_from(balancedbst_p->root);
	free(balancedbst_p);
}