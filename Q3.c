#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create new node
Node* createNode(int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Build binary tree (level order insertion using array)
Node* buildTree(int arr[], int i, int n) {
    if (i >= n)
        return NULL;
    Node* root = createNode(arr[i]);
    root->left = buildTree(arr, 2*i + 1, n);
    root->right = buildTree(arr, 2*i + 2, n);
    return root;
}

// Print leaf nodes
void printLeafNodes(Node* root) {
    if (!root) return;
    if (!root->left && !root->right)
        printf("%d ", root->data);
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Find and print siblings
void printSiblings(Node* root, int value) {
    if (!root) return;

    if (root->left && root->right) {
        if (root->left->data == value)
            printf("Sibling: %d\n", root->right->data);
        else if (root->right->data == value)
            printf("Sibling: %d\n", root->left->data);
    }

    printSiblings(root->left, value);
    printSiblings(root->right, value);
}

// Find and return parent of given node
Node* findParent(Node* root, int value, Node* parent) {
    if (!root)
        return NULL;
    if (root->data == value)
        return parent;

    Node* left = findParent(root->left, value, root);
    if (left) return left;

    return findParent(root->right, value, root);
}

// Print grandchildren of given node
void printGrandchildren(Node* node) {
    if (!node) return;

    if (node->left) {
        if (node->left->left) printf("%d ", node->left->left->data);
        if (node->left->right) printf("%d ", node->left->right->data);
    }

    if (node->right) {
        if (node->right->left) printf("%d ", node->right->left->data);
        if (node->right->right) printf("%d ", node->right->right->data);
    }
}

// Search a node by value
Node* findNode(Node* root, int value) {
    if (!root)
        return NULL;
    if (root->data == value)
        return root;
    Node* left = findNode(root->left, value);
    if (left)
        return left;
    return findNode(root->right, value);
}

int main() {
    int arr[20] = {15, 10, 20, 8, 12, 17, 25, 6, 9, 11, 13, 16, 18, 22, 27, 5, 7, 23, 21, 19};
    int n = 20;

    Node* root = buildTree(arr, 0, n);

    printf("Root node: %d\n", root->data);

    printf("Leaf nodes: ");
    printLeafNodes(root);
    printf("\n");

    int query;
    printf("Enter a node to find its siblings: ");
    scanf("%d", &query);
    printSiblings(root, query);

    Node* parent = findParent(root, query, NULL);
    if (parent)
        printf("Parent of %d is: %d\n", query, parent->data);
    else
        printf("No parent (might be root or not found).\n");

    Node* target = findNode(root, query);
    if (target) {
        printf("Grandchildren of %d: ", query);
        printGrandchildren(target);
        printf("\n");
    } else {
        printf("Node not found.\n");
    }

    return 0;
}