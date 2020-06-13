#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct node createNode(int id, char *type, struct node *parentNode)
{
    struct node newNode;
    newNode.id = id; // change it to assign auto
    newNode.childCount = 0;
    strcpy(newNode.type, type);

    newNode.childrenList = malloc(10 * sizeof(*(newNode.childrenList)));
    if (newNode.childrenList == NULL)
    {
        printf("Memory problem on children list\n");
        exit(1);
    }
    for (int i = 0; i < 10; i++)
    {
        newNode.childrenList[i] = (struct node *)NULL;
    }

    newNode.parentNode = parentNode;

    return newNode;
}

// add new node
struct node addNode(char *type, char *parentType, int parentId)
{
    // counter value starts with 0 but ids start with 1
    int currentID = counter + 1;

    struct node *parent = findNode(parentType, parentId, &root);
    struct node newNode = createNode(currentID, type, parent);

    // assign root node
    if (counter == 0)
    {
        root = newNode;
    }

    // find proper place
    else
    {
        int situation = placeNode(newNode);
    }

    counter++;

    return newNode;
}

// delete given node
void deleteNode(char *nodeType, int nodeId)
{
    // recursively, root node and its subnodes too
    struct node *deletedNode = findNode(nodeType, nodeId, &root);

    deleteNodeRecursively(deletedNode);
}

void deleteNodeRecursively(struct node *node)
{
    if (node->childCount == 0)
    {
        free(node);
    }

    for (int i = 0; i < 10; i++)
    {
        deleteNodeRecursively(node->childrenList[i]);
        node->childrenList[i] = NULL;
    }

    // itself
    deleteSelf(node);
}

void deleteSelf(struct node *node)
{
    struct node *parent = node->parentNode;

    int index = findChildIndex(parent, node);

    parent->childrenList[index] = NULL;

    free(node);
}

int findChildIndex(struct node *parent, struct node *child)
{
    for (int i = 0; i < 10; i++)
    {
        if (parent->childrenList[i] == child)
        {
            return i;
        }
    }
    return -1;
}

// print the tree
void printNetwork(char *nodeType, int nodeId)
{

    // find the given node then print
    struct node *rootNode = findNode(nodeType, nodeId, &root);

    if (rootNode == NULL)
    {
        printf("Couldn't find the given node while printing\n");
    }
    else
    {
        printNetworkRecursive(rootNode);
    }
}

void printNetworkRecursive(struct node *node)
{
    if (node != NULL)
    {
        printf("%s[%d]\n", node->type, node->id);
    }

    else
    {
        for (int i = 0; i < 10; i++)
        {
            printNetworkRecursive(node->childrenList[i]);
        }
    }
}

// place the given node
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
            parent->childrenList[i] = &node;
            (parent->childCount)++;
            return 1;
        }
    }

    // not found a place to put child node
    return 0;
}

// find the given node
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
