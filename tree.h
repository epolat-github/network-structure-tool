#include <stdio.h>

/* tree.h
 * abstract data type tree
 * 
 * This data type holds nodes to represent a network structure, with an implementation of N-ary tree
 * 
 * Type node has these components:
 *      id, childCount, type, childrenList, parentNode
 */

#define NODE_MAX_TYPE_SIZE 10
#define NODE_MAX_CHILD_COUNT 10

struct node
{
    int id;
    int childCount;
    char type[NODE_MAX_TYPE_SIZE];
    struct node *childrenList[NODE_MAX_CHILD_COUNT];
    struct node *parentNode;
    // int init;
};

/* variable declarations 
 *      counter => to hold the least attended id
 *      root => the root node of the tree
 */
int counter;
struct node *root;


/* 
 * Summary:         Creates new node with the given data.    
 * Parameters:      id, type and parent node of the new node.
 * Precondition:    id and type can't be NULL. Parent can be NULL, to indicate root.
 * Postcondition:   if inputs are valid, new node is returned.
 */
extern struct node createNode(int, char *, struct node *);

/* 
 * Summary:         Calls createNode to create new node with the given information.
 *                  Then calls the placeNode to put the created node to the proper location.
 *                  New node id is automatically assigned by the counter variable.
 * Parameters:      Type of the new node and its wanted parent node with the parents id.
 * Precondition:    Given parent node should be valid. If it's the first node (counter == 0), parent can be NULL (root node has no parent).
 * Postcondition:   if inputs are valid && given parent node is found && parent node has less then 10 children, 
 *                  new node is created, added and returned.
 */
extern struct node addNode(char *, char *, int);

/* 
 * Summary:         Finds the node with the given information and calls deleteNodeRecursively to delete it and its descendants.
 * Parameters:      Type of the node and its id.
 * Precondition:    Given parent node should be a valid node.
 * Postcondition:   if the given node is found, it and its all descendants are removed from both the tree and memory. 
 */
extern void deleteNode(char *, int);

/* 
 * Summary:         Deletes the given node and its descendant nodes in a recursive manner.
 * Parameters:      Address of the node that is wanted to be deleted.
 * Precondition:    If the given node pointer is NULL, that indicates it's the end of that branch and returns NULL.
 * Postcondition:   Given node and its descendants are removed from the node and memory. Memory is freed. 
 */
extern void deleteNodeRecursively(struct node *);

/* 
 * Summary:         It's used to set the corresponding index of the deleted node's parent's children list to NULL.
 * Parameters:      Node pointer.
 * Precondition:    Given node must valid.
 * Postcondition:   If the given node is valid and it's the root node, the root variable in the header file is set to NULL.
 *                  If the given node is not the root node, the correct index of its parent's childrenList is set to NULL to free up space. 
 */
extern void deleteSelf(struct node *);

/* 
 * Summary:         Finds a given node's index in the given parent node's children list.
 * Parameters:      Parent node pointer and child node pointer.
 * Precondition:    Given parent node should have the given child node as its child.
 *                  Given nodes shouldn't be NULL.
 * Postcondition:   If the nodes are valid and parent has the given child, its index is returned.
 *                  If the parent node hasn't got the given child node, -1 returned.
 *                  If the given parent is NULL, it indicates that the child is the root node; -1 returned (root has no parent).
 */
extern int findChildIndex(struct node *, struct node *);

/* 
 * Summary:         Prints below of the given node in preorder traversal format. It finds the wanted node and calls printNetworkRecursive.
 * Parameters:      Type and id of the wanted root node. File pointer of the output file to print the tree.
 * Precondition:    Given information must be valid and found as a node in the tree.
 * Postcondition:   Tree is printed in the preorder traversal format. 
 */
extern void printNetwork(char *, int, FILE *);

/* 
 * Summary:         Prints the given node and its descendants in preorder traversal format.
 * Parameters:      root node of the wanted subtree and the output file's pointer.
 * Precondition:    File should be valid and opened. Node can be NULL, that indicates the end of the current subtree.
 * Postcondition:   Tree is printed to the given output file.
 */
extern void printNetworkRecursive(struct node *, FILE *);

/* 
 * Summary:         Places the given node to the first empty index of the children list of its parent node.
 * Parameters:      New node.
 * Precondition:    Given node's parent property can't be NULL. (placement of the root node without parent is handled within addNode func.)
 * Postcondition:   If the given node's parent is valid and it has less than 10 children, it is placed and returned 1. Otherwise, returned 0.
 */
extern int placeNode(struct node);

/* 
 * Summary:         Finds the corresponding node under the descendants of the given root node.
 * Parameters:      Type and id of the to be found node. Root node of the subtree/tree that is wanted to be searched.
 * Precondition:    Root and target node should be valid and found.
 * Postcondition:   If the given node is found, it's returned. Otherwise, NULL returned.
 */
extern struct node *findNode(char *, int, struct node *);
// extern void copyNode(struct node *, struct node *);

/* 
 * Summary:         Frees the memory of the whole tree.
 * Parameters:      -
 * Precondition:    -
 * Postcondition:   If root node is still valid, it and its descendants are deleted from memory.
 *                  Otherwise, tree is already deleted, nothing is done.
 */
extern void freeMemory();

/* 
 * Summary:         Moves the given node under the given new parent node.
 * Parameters:      Types and ids of the parent and child nodes.
 * Precondition:    Both nodes should be valid and found within the tree.
 *                  Wanted parent node should has less than 10 children.
 * Postcondition:   Target node is found and moved to the new parent node as its child.
 *                  Index of the target node's in its old parent's children list is set to NULL and child count is decreased.
 */
extern void moveTree(char *, int, char *, int);

/* 
 * Summary:         Returns the count of the given node within the descendants of the given parent. It calls countRecursively.
 * Parameters:      Types of root and target nodes. Id of the root node.
 * Precondition:    Given root node should be valid.
 * Postcondition:   Count is returned. If it's not found, returned 0.
 */
extern int countNodes(char *, char *, int);

/* 
 * Summary:         Traverses through the tree and changes the given count variable.
 * Parameters:      Target node type, root node to start searching and address of the count variable.
 * Precondition:    -
 * Postcondition:   Searched within the tree and updated the value of the given count variable.
 */
extern void countRecursively(char *, struct node *, int *);

/* 
 * Summary:         Prints the given root node and its descendants in a level order format.
 * Parameters:      Type and id of the root node. File pointer of the output file.
 * Precondition:    File should be valid. Given node should be found.
 * Postcondition:   Tree is printed to the given output file.
 */
extern void printLevelOrder(char *, int, FILE *);

/* 
 * Summary:         Prints the given level and its sub-levels recursively. 
 * Parameters:      Root node pointer, default level count, output file pointer.
 * Precondition:    Node can be NULL, it indicates the end of the current subtree.
 * Postcondition:   Tree is printed to the given output file.
 */
extern void printLevel(struct node *, int, FILE *);

/* 
 * Summary:         Finds the depth of the given root node's subtree/tree.
 * Parameters:      Node pointer.
 * Precondition:    Given node should not be NULL.
 * Postcondition:   If the given node is NULL, returned 0. Otherwise, depth is found and returned.
 */
extern int findDepth(struct node *);