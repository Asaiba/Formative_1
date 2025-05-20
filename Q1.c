#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define LINE_LEN 200

typedef struct {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int grade;
} Student;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Student arr[], int low, int high) {
    int pivot = arr[high].grade;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].grade <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int readStudents(const char *filename, Student students[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    char line[LINE_LEN];

    while (fgets(line, sizeof(line), file) && count < MAX_STUDENTS) {
        char *token = strtok(line, ",");
        if (token) strcpy(students[count].firstName, token);

        token = strtok(NULL, ",");
        if (token) strcpy(students[count].lastName, token);

        token = strtok(NULL, ",");
        if (token) students[count].grade = atoi(token);

        count++;
    }

    fclose(file);
    return count;
}

void writeStudents(const char *filename, Student students[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error writing to file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%d\n", students[i].firstName, students[i].lastName, students[i].grade);
    }

    fclose(file);
}

int main() {
    Student students[MAX_STUDENTS];
    int count = readStudents("students.txt", students);

    if (count == 0) {
        printf("No students to sort.\n");
        return 1;
    }

    quickSort(students, 0, count - 1);
    writeStudents("sorted_students.txt", students, count);

    printf("Sorting complete. Sorted data saved to 'sorted_students.txt'.\n");
    return 0;
}
