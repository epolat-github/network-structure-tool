#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Summary:         Creates new node with the given data.    
 * Parameters:      id, type and parent node of the new node.
 * Precondition:    id and type can't be NULL. Parent can be NULL, to indicate root.
 * Postcondition:   if inputs are valid, new node is returned.
 */
struct node createNode(int id, char *type, struct node *parentNode)
{
    struct node newNode;
    newNode.id = id;
    newNode.childCount = 0;
    strcpy(newNode.type, type);
    newNode.parentNode = parentNode;

    // init children list.
    for (int i = 0; i < 10; i++)
    {
        newNode.childrenList[i] = (struct node *)NULL;
    }

    return newNode;
}

/* 
 * Summary:         Calls createNode to create new node with the given information.
 *                  Then calls the placeNode to put the created node to the proper location.
 *                  New node id is automatically assigned by the counter variable.
 * Parameters:      Type of the new node and its wanted parent node with the parents id.
 * Precondition:    Given parent node should be valid. If it's the first node (counter == 0), parent can be NULL (root node has no parent).
 * Postcondition:   if inputs are valid && given parent node is found && parent node has less then 10 children, 
 *                  new node is created, added and returned.
 */
struct node addNode(char *type, char *parentType, int parentId)
{

    // counter value starts with 0 but ids start with 1
    int currentID = counter + 1;

    struct node newNode;

    // assign root node
    if (counter == 0)
    {
        newNode = createNode(currentID, type, NULL);
        root = (struct node *)malloc(sizeof(struct node));
        memcpy(root, &newNode, sizeof(struct node));
    }

    // assign normal node
    else
    {
        struct node *parent = findNode(parentType, parentId, root);

        if (parent == NULL)
        {
            printf("%s[%d] parent is not found!\n", parentType, parentId);
            return;
        }

        newNode = createNode(currentID, type, parent);

        int situation = placeNode(newNode);
    }

    counter++;

    return newNode;
}

/* 
 * Summary:         Finds the node with the given information and calls deleteNodeRecursively to delete it and its descendants.
 * Parameters:      Type of the node and its id.
 * Precondition:    Given parent node should be a valid node.
 * Postcondition:   if the given node is found, it and its all descendants are removed from both the tree and memory. 
 */
void deleteNode(char *nodeType, int nodeId)
{
    struct node *deletedNode = findNode(nodeType, nodeId, root);

    deleteNodeRecursively(deletedNode);
}

/* 
 * Summary:         Deletes the given node and its descendant nodes in a recursive manner.
 * Parameters:      Address of the node that is wanted to be deleted.
 * Precondition:    If the given node pointer is NULL, that indicates it's the end of that branch and returns NULL.
 * Postcondition:   Given node and its descendants are removed from the node and memory. Memory is freed. 
 */
void deleteNodeRecursively(struct node *node)
{
    if (node == NULL)
    {
        return;
    }

    // root node of that subtree
    if (node->childCount == 0)
    {
        deleteSelf(node);
        free(node);
        return;
    }
    else
    {
        // delete all the children
        for (int i = 0; i < 10; i++)
        {
            deleteNodeRecursively(node->childrenList[i]);
        }
    }

    // itself
    deleteNodeRecursively(node);
}

/* 
 * Summary:         It's used to set the corresponding index of the deleted node's parent's children list to NULL.
 * Parameters:      Node pointer.
 * Precondition:    Given node must valid.
 * Postcondition:   If the given node is valid and it's the root node, the root variable in the header file is set to NULL.
 *                  If the given node is not the root node, the correct index of its parent's childrenList is set to NULL to free up space. 
 */
void deleteSelf(struct node *node)
{
    struct node *parent = node->parentNode;

    int index = findChildIndex(parent, node);

    if (index != -1)
    {
        parent->childrenList[index] = NULL;
        (parent->childCount)--;
    }

    // root deletion
    else
    {
        root = NULL;
    }
}

/* 
 * Summary:         Frees the memory of the whole tree.
 * Parameters:      -
 * Precondition:    -
 * Postcondition:   If root node is still valid, it and its descendants are deleted from memory.
 *                  Otherwise, tree is already deleted, nothing is done.
 */
void freeMemory()
{
    deleteNodeRecursively(root);
}

/* 
 * Summary:         Finds a given node's index in the given parent node's children list.
 * Parameters:      Parent node pointer and child node pointer.
 * Precondition:    Given parent node should have the given child node as its child.
 *                  Given nodes shouldn't be NULL.
 * Postcondition:   If the nodes are valid and parent has the given child, its index is returned.
 *                  If the parent node hasn't got the given child node, -1 returned.
 *                  If the given parent is NULL, it indicates that the child is the root node; -1 returned (root has no parent).
 */
int findChildIndex(struct node *parent, struct node *child)
{
    if (parent == NULL)
    {
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        // compare of memory locations
        if (parent->childrenList[i] == child)
        {
            return i;
        }
    }
    return -1;
}

/* 
 * Summary:         Prints below of the given node in preorder traversal format. It finds the wanted node and calls printNetworkRecursive.
 * Parameters:      Type and id of the wanted root node. File pointer of the output file to print the tree.
 * Precondition:    Given information must be valid and found as a node in the tree.
 * Postcondition:   Tree is printed in the preorder traversal format. 
 */
void printNetwork(char *nodeType, int nodeId, FILE *outputFile)
{
    struct node *rootNode = findNode(nodeType, nodeId, root);

    if (rootNode == NULL)
    {
        printf("Couldn't find the given node while printing\n");
    }
    else
    {
        printNetworkRecursive(rootNode, outputFile);
    }
}

/* 
 * Summary:         Prints the given node and its descendants in preorder traversal format.
 * Parameters:      root node of the wanted subtree and the output file's pointer.
 * Precondition:    File should be valid and opened. Node can be NULL, that indicates the end of the current subtree.
 * Postcondition:   Tree is printed to the given output file.
 */
void printNetworkRecursive(struct node *node, FILE *outputFile)
{
    if (node != NULL)
    {
        fprintf(outputFile, "%s[%d]\n", node->type, node->id);
        for (int i = 0; i < 10; i++)
        {
            printNetworkRecursive(node->childrenList[i], outputFile);
        }
    }
}

/* 
 * Summary:         Places the given node to the first empty index of the children list of its parent node.
 * Parameters:      New node.
 * Precondition:    Given node's parent property can't be NULL. (placement of the root node without parent is handled within addNode func.)
 * Postcondition:   If the given node's parent is valid and it has less than 10 children, it is placed and returned 1. Otherwise, returned 0.
 */
int placeNode(struct node node)
{
    // find parent node of the given node
    struct node *parent = node.parentNode;

    // add the given node to the child
    for (int i = 0; i < 10; i++)
    {
        // proper place
        if (parent->childrenList[i] == NULL)
        {
            parent->childrenList[i] = (struct node *)malloc(sizeof(struct node));
            memcpy(parent->childrenList[i], &node, sizeof(struct node));
            (parent->childCount)++;

            return 1;
        }
    }

    // not found a place to put child node
    return 0;
}

/* 
 * Summary:         Finds the corresponding node under the descendants of the given root node.
 * Parameters:      Type and id of the to be found node. Root node of the subtree/tree that is wanted to be searched.
 * Precondition:    Root and target node should be valid and found.
 * Postcondition:   If the given node is found, it's returned. Otherwise, NULL returned.
 */
struct node *findNode(char *nodeType, int id, struct node *node)
{
    // invalid node type or empty node
    if (nodeType == NULL || node == NULL)
    {
        return NULL;
    }

    // found
    if (strcmp(node->type, nodeType) == 0 && node->id == id)
    {
        return node;
    }

    // traverse
    for (int i = 0; i < 10; i++)
    {
        struct node *foundNode = findNode(nodeType, id, node->childrenList[i]);

        if (foundNode != NULL)
        {
            return foundNode;
        }
    }

    return NULL;
}

/* 
 * Summary:         Moves the given node under the given new parent node.
 * Parameters:      Types and ids of the parent and child nodes.
 * Precondition:    Both nodes should be valid and found within the tree.
 *                  Wanted parent node should has less than 10 children.
 * Postcondition:   Target node is found and moved to the new parent node as its child.
 *                  Index of the target node's in its old parent's children list is set to NULL and child count is decreased.
 */
void moveTree(char *nodeType, int nodeId, char *destinationType, int destinationId)
{
    struct node *node = findNode(nodeType, nodeId, root);
    struct node *destination = findNode(destinationType, destinationId, root);

    if (node == NULL || destination == NULL)
    {
        printf("%s[%d] destination or %s[%d] child node is not found!\n", destinationType, destinationId, nodeType, nodeId);
        return;
    }

    if (destination->childCount >= 10)
    {
        printf("Wanted parent node is full. Can't move.\n");
    }
    else
    {
        int index = findChildIndex(node->parentNode, node);
        node->parentNode->childrenList[index] = NULL;
        node->parentNode->childCount--;
        node->parentNode = destination;

        for (int i = 0; i < 10; i++)
        {
            if (destination->childrenList[i] == NULL)
            {
                destination->childrenList[i] = node;
                destination->childCount++;
                break;
            }
        }
    }
}

/* 
 * Summary:         Returns the count of the given node within the descendants of the given parent. It calls countRecursively.
 * Parameters:      Types of root and target nodes. Id of the root node.
 * Precondition:    Given root node should be valid.
 * Postcondition:   Count is returned. If it's not found, returned 0.
 */
int countNodes(char *nodeType, char *parentType, int parentId)
{
    struct node *parent = findNode(parentType, parentId, root);

    int count = 0;

    countRecursively(nodeType, parent, &count);

    return count;
}

/* 
 * Summary:         Traverses through the tree and changes the given count variable.
 * Parameters:      Target node type, root node to start searching and address of the count variable.
 * Precondition:    -
 * Postcondition:   Searched within the tree and updated the value of the given count variable.
 */
void countRecursively(char *nodeType, struct node *node, int *count)
{
    if (node != NULL)
    {
        // found
        if (strcmp(node->type, nodeType) == 0)
        {
            (*count)++;
        }

        if (node->childCount > 0)
        {
            for (int i = 0; i < 10; i++)
            {
                countRecursively(nodeType, node->childrenList[i], count);
            }
        }
    }
}

/* 
 * Summary:         Prints the given root node and its descendants in a level order format.
 * Parameters:      Type and id of the root node. File pointer of the output file.
 * Precondition:    File should be valid. Given node should be found.
 * Postcondition:   Tree is printed to the given output file.
 */
void printLevelOrder(char *nodeType, int nodeId, FILE *outputFile)
{
    struct node *node = findNode(nodeType, nodeId, root);

    if (node == NULL)
    {
        printf("%s[%d] root node is not found!\n", nodeType, nodeId);
        return;
    }

    int depth = findDepth(node);

    for (int i = 0; i < depth; i++)
    {
        printLevel(node, i, outputFile);
    }
}

/* 
 * Summary:         Prints the given depth and its sub-levels recursively. 
 * Parameters:      Root node pointer, default depth count, output file pointer.
 * Precondition:    Node can be NULL, it indicates the end of the current subtree.
 * Postcondition:   Tree is printed to the given output file.
 */
void printLevel(struct node *node, int depth, FILE *outputFile)
{
    if (node == NULL)
    {
        return;
    }

    if (depth == 0)
        fprintf(outputFile, "%s[%d]\n", node->type, node->id);
    else if (depth > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            printLevel(node->childrenList[i], depth - 1, outputFile);
        }
    }
}

/* 
 * Summary:         Finds the depth of the given root node's subtree/tree.
 * Parameters:      Node pointer.
 * Precondition:    Given node should not be NULL.
 * Postcondition:   If the given node is NULL, returned 0. Otherwise, depth is found and returned.
 */
int findDepth(struct node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    else
    {
        int largest = 0;

        for (int i = 0; i < 10; i++)
        {
            int result = findDepth(node->childrenList[i]);

            if (result > largest)
            {
                largest = result;
            }
        }

        return (largest + 1);
    }
}
