#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAXCHAR 100

int main(int argc, char const *argv[])
{
    char line[MAXCHAR];
    int firstLine = 1;
    FILE *inputFilePtr;
    FILE *outputFilePtr;
    struct node *root;

    // check parameters
    //TODO should be 5
    if (argc != 3)
    {
        printf("Wrong number of parameters\n");
        return 1;
    }

    inputFilePtr = fopen(argv[1], "r");

    if (inputFilePtr == NULL)
    {
        printf("Error opening input file!\n");
        return 1;
    }

    while (fgets(line, MAXCHAR, inputFilePtr) != NULL)
    {
        char *command = strtok(line, " []");

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
                // printf("girdi\n");
                // printf("root=> %s %d\n", root->type, root->id);
            }

            // insert normal node
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
            printNetwork(nodeType, atoi(nodeId));
        }

        // INVALID input
        else
        {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}