#include <stdio.h>
#include <stdio.h>
//QUESTION1
int main() {
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(file, "This is some initial text.");
    fclose(file);

    file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error opening file in append mode");
        return 1;
    }

    fprintf(file, "\nThis is additional text added in append mode.");
    fclose(file);
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    printf("File Contents:\n");

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}

//QUESTION2
#include <stdio.h>
#include <stdlib.h>

int countWords(FILE *file) {
    int count = 0;
    char word[100];

    // Read words and count them
    while (fscanf(file, "%s", word) == 1) {
        count++;
    }

    return count;
}

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    int wordCount = countWords(file);

    printf("Total number of words in the file: %d\n", wordCount);

    fclose(file);

    return 0;
}


//QUESTION3
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

void addStudent(FILE *file) {
    struct Student newStudent;

    printf("Enter Roll Number: ");
    scanf("%d", &newStudent.rollNumber);

    printf("Enter Name: ");
    scanf("%s", newStudent.name);

    printf("Enter Marks: ");
    scanf("%f", &newStudent.marks);

     Write the new student record to the file
    fwrite(&newStudent, sizeof(struct Student), 1, file);

    printf("Student added successfully.\n");
}

void displayStudents(FILE *file) {
    struct Student student;

     Read and display all student records from the file
    rewind(file);

    printf("\nStudent Records:\n");

    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", student.rollNumber, student.name, student.marks);
    }
}

int main() {
    FILE *file = fopen("students.dat", "ab+"); // Open in binary append/update mode
    if (file == NULL) {
        perror("Error opening student database file");
        return 1;
    }

    int choice;

    do {
        printf("\nStudent Database System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                displayStudents(file);
                break;
            case 3:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

     Close the file
    fclose(file);

    return 0;
}
