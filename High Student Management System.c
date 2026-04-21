#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "students.dat"

struct Student {
    int id;
    char name[30];
};
// ? Add Student
void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "ab");
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student Added!\n");
}
// ? Show Students
void showStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }
    printf("\n--- Student List ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d | Name: %s\n", s.id, s.name);
    }
    fclose(fp);
}
// ? Search Student
void searchStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Found -> ID: %d | Name: %s\n", s.id, s.name);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student not found!\n");
    fclose(fp);
}
// ? Update Student
void updateStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            found = 1;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    if (found)
        printf("Student Updated!\n");
    else
        printf("Student not found!\n");
}
// ? Delete Student
void deleteStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue; // skip writing
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    if (found)
        printf("Student Deleted!\n");
    else
        printf("Student not found!\n");
}
// ? Main Menu
int main() {
    int choice;
    while (1) {
        printf("\n===== STUDENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Show Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
            addStudent();
        else if (choice == 2)
            showStudents();
        else if (choice == 3)
            searchStudent();
        else if (choice == 4)
            updateStudent();
        else if (choice == 5)
            deleteStudent();
        else if (choice == 0)
            exit(0);
        else
            printf("Invalid choice!\n");
    }
}