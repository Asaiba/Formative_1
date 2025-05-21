#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Queue for level-order tree construction
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Queue operations
void enqueue(Queue* q, Node* treeNode) {
    QueueNode* newQNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQNode->treeNode = treeNode;
    newQNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newQNode;
    } else {
        q->rear->next = newQNode;
        q->rear = newQNode;
    }
}

Node* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Tree Node creation
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Build binary tree from array (level order)
Node* buildTree(int arr[], int size) {
    if (size == 0) return NULL;

    Node* root = createNode(arr[0]);
    Queue q = {NULL, NULL};
    enqueue(&q, root);

    int i = 1;
    while (i < size) {
        Node* current = dequeue(&q);

        if (i < size) {
            current->left = createNode(arr[i++]);
            enqueue(&q, current->left);
        }
        if (i < size) {
            current->right = createNode(arr[i++]);
            enqueue(&q, current->right);
        }
    }
    return root;
}

// Print leaf nodes
void printLeafNodes(Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Find parent of a given node
Node* findParent(Node* root, int childVal) {
    if (root == NULL) return NULL;
    if ((root->left && root->left->data == childVal) ||
        (root->right && root->right->data == childVal)) {
        return root;
    }

    Node* left = findParent(root->left, childVal);
    if (left) return left;
    return findParent(root->right, childVal);
}

// Find and print siblings of a given node
void findSiblings(Node* root, int target) {
    Node* parent = findParent(root, target);
    if (parent == NULL) {
        printf("No siblings (or node not found).\n");
        return;
    }

    if (parent->left && parent->left->data == target && parent->right)
        printf("Sibling: %d\n", parent->right->data);
    else if (parent->right && parent->right->data == target && parent->left)
        printf("Sibling: %d\n", parent->left->data);
    else
        printf("No siblings.\n");
}

// Print grandchildren of a given node
void printGrandchildren(Node* root, int target) {
    if (root == NULL) return;

    if (root->data == target) {
        if (root->left) {
            if (root->left->left) printf("Grandchild: %d\n", root->left->left->data);
            if (root->left->right) printf("Grandchild: %d\n", root->left->right->data);
        }
        if (root->right) {
            if (root->right->left) printf("Grandchild: %d\n", root->right->left->data);
            if (root->right->right) printf("Grandchild: %d\n", root->right->right->data);
        }
        return;
    }

    printGrandchildren(root->left, target);
    printGrandchildren(root->right, target);
}

// Menu interface
void menu(Node* root) {
    int choice, val;
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Show root node\n");
        printf("2. Show leaf nodes\n");
        printf("3. Show siblings of a node\n");
        printf("4. Show parent of a node\n");
        printf("5. Show grandchildren of a node\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Root: %d\n", root->data);
                break;
            case 2:
                printf("Leaf nodes: ");
                printLeafNodes(root);
                printf("\n");
                break;
            case 3:
                printf("Enter node value: ");
                scanf("%d", &val);
                findSiblings(root, val);
                break;
            case 4:
                printf("Enter node value: ");
                scanf("%d", &val);
                {
                    Node* p = findParent(root, val);
                    if (p) printf("Parent: %d\n", p->data);
                    else printf("Parent not found or it's the root.\n");
                }
                break;
            case 5:
                printf("Enter node value: ");
                scanf("%d", &val);
                printGrandchildren(root, val);
                break;
            case 6:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

int main() {
    int arr[SIZE] = {23, 17, 45, 12, 9, 30, 56, 8, 1, 15, 22, 18, 31, 60, 77, 35, 42, 68, 70, 90};

    Node* root = buildTree(arr, SIZE);
    menu(root);

    return 0;
}
