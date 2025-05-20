#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep()

// Define the structure for a bus stop node
typedef struct BusStop {
    char name[100];
    struct BusStop* prev;
    struct BusStop* next;
} BusStop;

// Head and tail pointers for the list
BusStop* head = NULL;
BusStop* tail = NULL;

// Function to add a bus stop at the end
void addBusStop(const char* name) {
    BusStop* newStop = (BusStop*)malloc(sizeof(BusStop));
    strcpy(newStop->name, name);
    newStop->prev = tail;
    newStop->next = NULL;

    if (head == NULL) {
        head = newStop;
        tail = newStop;
    } else {
        tail->next = newStop;
        tail = newStop;
    }
}

// Move forward from head to tail
void moveForward() {
    BusStop* current = head;
    printf("\nMoving Forward:\n");
    while (current != NULL) {
        printf("Bus Stop: %s\n", current->name);
        sleep(3); // 3 second delay
        current = current->next;
    }
}

// Move backward from tail to head
void moveBackward() {
    BusStop* current = tail;
    printf("\nMoving Backward:\n");
    while (current != NULL) {
        printf("Bus Stop: %s\n", current->name);
        sleep(3); // 3 second delay
        current = current->prev;
    }
}

// Free the list
void freeList() {
    BusStop* current = head;
    while (current != NULL) {
        BusStop* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // Add sample bus stops
    addBusStop("Home");
    addBusStop("Stop 1");
    addBusStop("Stop 2");
    addBusStop("Stop 3");
    addBusStop("Campus");

    int choice;
    printf("1. Move Forward\n2. Move Backward\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        moveForward();
    else if (choice == 2)
        moveBackward();
    else
        printf("Invalid choice.\n");

    freeList();
    return 0;
}