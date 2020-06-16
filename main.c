#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAXCHAR 100

int main(int argc, char const *argv[])
{
    char line[MAXCHAR];
    int firstLine = 1; // first line indicator for inserting root node

    // file pointers
    FILE *inputFilePtr;
    FILE *outputFilePtr;
    FILE *bonusInputFilePtr;
    FILE *bonusOutFilePtr;
    // struct node *root;

    // check parameters
    if (argc != 5)
    {
        printf("Wrong number of parameters\n");
        return 1;
    }

    /* ---------------*/
    /* NORMAL HW PART */
    /* ---------------*/

    // open input and output files
    inputFilePtr = fopen(argv[1], "r");
    outputFilePtr = fopen(argv[2], "w");

    if (inputFilePtr == NULL || outputFilePtr == NULL)
    {
        printf("Error opening input or output file!\n");
        return 1;
    }

    // read normal input file
    while (fgets(line, MAXCHAR, inputFilePtr) != NULL)
    {
        char *command = strtok(line, " []\t");

        // INSERT command
        if (strcmp(command, "INSERT") == 0)
        {
            // insert root
            if (firstLine)
            {
                char *nodeType = strtok(NULL, " []");
                firstLine = 0;

                // insert root node
                addNode(nodeType, NULL, 0);
            }

            // insert normal nodes
            else
            {
                char *nodeType = strtok(NULL, " []");
                char *parentType = strtok(NULL, " []");
                char *parentId = strtok(NULL, " []");

                // insert node
                int id = atoi(parentId);
                addNode(nodeType, parentType, id);
            }
        }

        // DELETE command
        else if (strcmp(command, "DELETE") == 0)
        {
            char *nodeType = strtok(NULL, " []");
            char *nodeId = strtok(NULL, " []");

            // find and delete node
            deleteNode(nodeType, atoi(nodeId));
        }

        // PRINT command
        else if (strcmp(command, "PRINT") == 0)
        {
            char *nodeType = strtok(NULL, " []");
            char *nodeId = strtok(NULL, " []");

            // find and print node
            printNetwork(nodeType, atoi(nodeId), outputFilePtr);
        }
    }

    // close normal input and output files
    fclose(inputFilePtr);
    fclose(outputFilePtr);

    /* ---------------*/
    /* BONUS HW PART */
    /* ---------------*/

    // open and check bonus part input and output files
    bonusInputFilePtr = fopen(argv[3], "r");
    bonusOutFilePtr = fopen(argv[4], "w");
    if (bonusInputFilePtr == NULL || bonusOutFilePtr == NULL)
    {
        printf("Error opening bonus input or output file!\n");
        return 1;
    }

    // read bonus input file
    while (fgets(line, MAXCHAR, bonusInputFilePtr) != NULL)
    {
        char *command = strtok(line, " []\t");

        // MOVE command
        if (strcmp(command, "MOVE") == 0)
        {
            char *nodeType = strtok(NULL, " []");
            char *nodeId = strtok(NULL, " []");

            char *destinationType = strtok(NULL, " []");
            char *destinationId = strtok(NULL, " []");

            // move the given subtree to the given destination as child node
            moveTree(nodeType, atoi(nodeId), destinationType, atoi(destinationId));
        }

        // COUNT command
        else if (strcmp(command, "COUNT") == 0)
        {
            char *nodeType = strtok(NULL, " []");
            char *parentType = strtok(NULL, " []");
            char *parentId = strtok(NULL, " []");

            // count the given nodes occurences
            int count = countNodes(nodeType, parentType, atoi(parentId));

            fprintf(bonusOutFilePtr, "%d\n", count);
        }

        // PRINT_LEVEL command
        else if (strcmp(command, "PRINT_LEVEL") == 0)
        {
            char *nodeType = strtok(NULL, " []");
            char *nodeId = strtok(NULL, " []");

            // print the given node in level order format
            printLevelOrder(nodeType, atoi(nodeId), bonusOutFilePtr);
        }
    }

    // close the bonus input and output files
    fclose(bonusInputFilePtr);
    fclose(bonusOutFilePtr);

    // clean and free memory of leftovers of the tree, if it still exists.
    freeMemory();

    return 0;
}