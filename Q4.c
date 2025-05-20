#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define LINE_LEN 100

// Student structure
typedef struct Student {
    char firstName[NAME_LEN];
    char lastName[NAME_LEN];
    int grade;
} Student;

// BST Node structure
typedef struct Node {
    Student data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert student into BST using last name as key
Node* insert(Node* root, Student s) {
    if (root == NULL) return createNode(s);

    if (strcmp(s.lastName, root->data.lastName) < 0)
        root->left = insert(root->left, s);
    else
        root->right = insert(root->right, s);

    return root;
}

// Search student by last name
Student* search(Node* root, const char* lastName) {
    if (root == NULL) return NULL;

    int cmp = strcmp(lastName, root->data.lastName);
    if (cmp == 0)
        return &root->data;
    else if (cmp < 0)
        return search(root->left, lastName);
    else
        return search(root->right, lastName);
}

// Build BST from comma-separated file
Node* buildBSTFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    Node* root = NULL;
    char line[LINE_LEN];

    while (fgets(line, sizeof(line), file)) {
        Student temp;
        char* token = strtok(line, ",");
        if (token) strcpy(temp.firstName, token);

        token = strtok(NULL, ",");
        if (token) strcpy(temp.lastName, token);

        token = strtok(NULL, ",\n");
        if (token) temp.grade = atoi(token);

        root = insert(root, temp);
    }

    fclose(file);
    return root;
}

// Search menu
void menu(Node* root) {
    char searchLastName[NAME_LEN];
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Search for a student by last name\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            printf("Enter last name: ");
            fgets(searchLastName, NAME_LEN, stdin);
            searchLastName[strcspn(searchLastName, "\n")] = '\0'; // Remove newline

            Student* s = search(root, searchLastName);
            if (s)
                printf("Found: %s %s, Grade: %d\n", s->firstName, s->lastName, s->grade);
            else
                printf("Student with last name '%s' not found.\n", searchLastName);
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
}

// Main function
int main() {
    Node* root = buildBSTFromFile("students.txt");
    menu(root);
    return 0;
}
