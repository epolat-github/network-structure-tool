
struct node
{
    int id;
    int childCount;
    char type[10];
    struct node **childrenList;
    struct node *parentNode;
};

int counter;
struct node root;

// struct node *createNode(int, char *, struct node *);
struct node createNode(int, char *, struct node *);
struct node addNode(char *, char *, int);
void deleteNode(char *, int);
void deleteNodeRecursively(struct node *);
void deleteSelf(struct node *);
int findChildIndex(struct node *, struct node *);
void printNetwork(char *, int);
void printNetworkRecursive(struct node *);
int placeNode(struct node);
struct node *findNode(char *, int, struct node *);