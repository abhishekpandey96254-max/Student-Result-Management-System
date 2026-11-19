#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATA_FILE "students.dat"
#define TEMP_FILE "students_temp.dat"
#define NAME_LENGTH 50
#define SUBJECT_COUNT 5

/* Each student record is stored in students.dat using binary file handling. */
typedef struct {
    int rollNo;
    char name[NAME_LENGTH];
    float marks[SUBJECT_COUNT];
} Student;

static const char *subjectNames[SUBJECT_COUNT] = {
    "English", "Mathematics", "Physics", "Chemistry", "Programming"
};

/* Read a complete line so names containing spaces are accepted. */
void readLine(const char *prompt, char *buffer, size_t size) {
    while (1) {
        size_t length;
        int ch;

        printf("%s", prompt);
        if (fgets(buffer, (int)size, stdin) == NULL) {
            printf("\nInput ended. Please restart the program.\n");
            exit(EXIT_FAILURE);
        }

        length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        } else {
            /* Discard extra characters if the input line was too long. */
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* discard */
            }
        }

        if (buffer[0] != '\0') {
            return;
        }
        printf("Input cannot be empty. Please try again.\n");
    }
}

int readInt(const char *prompt, int minValue, int maxValue) {
    char line[100];
    char *end;
    long value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        errno = 0;
        value = strtol(line, &end, 10);

        if (errno == 0 && end != line && *end == '\0' &&
            value >= minValue && value <= maxValue) {
            return (int)value;
        }
        printf("Please enter a whole number from %d to %d.\n", minValue, maxValue);
    }
}

float readMark(const char *subject) {
    char line[100];
    char *end;
    double value;

    while (1) {
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Enter marks in %s (0-100): ", subject);
        readLine(prompt, line, sizeof(line));
        errno = 0;
        value = strtod(line, &end);

        if (errno == 0 && end != line && *end == '\0' && value >= 0.0 && value <= 100.0) {
            return (float)value;
        }
        printf("Invalid marks. Enter a value between 0 and 100.\n");
    }
}

float calculateTotal(const Student *student) {
    float total = 0.0f;
    int i;
    for (i = 0; i < SUBJECT_COUNT; i++) {
        total += student->marks[i];
    }
    return total;
}

float calculatePercentage(const Student *student) {
    return calculateTotal(student) / SUBJECT_COUNT;
}

int hasPassed(const Student *student) {
    int i;
    for (i = 0; i < SUBJECT_COUNT; i++) {
        if (student->marks[i] < 33.0f) {
            return 0;
        }
    }
    return 1;
}

const char *calculateGrade(const Student *student) {
    float percentage = calculatePercentage(student);

    if (!hasPassed(student)) return "F (Fail)";
    if (percentage >= 90.0f) return "A+";
    if (percentage >= 80.0f) return "A";
    if (percentage >= 70.0f) return "B";
    if (percentage >= 60.0f) return "C";
    if (percentage >= 50.0f) return "D";
    return "E";
}

int rollNumberExists(int rollNo) {
    FILE *file = fopen(DATA_FILE, "rb");
    Student student;

    if (file == NULL) return 0;

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNo == rollNo) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void inputMarks(Student *student) {
    int i;
    for (i = 0; i < SUBJECT_COUNT; i++) {
        student->marks[i] = readMark(subjectNames[i]);
    }
}

void addStudent(void) {
    Student student;
    FILE *file;

    printf("\n--- Add Student ---\n");
    student.rollNo = readInt("Enter roll number: ", 1, 1000000000);

    if (rollNumberExists(student.rollNo)) {
        printf("A student with this roll number already exists.\n");
        return;
    }

    readLine("Enter student name: ", student.name, sizeof(student.name));
    inputMarks(&student);

    file = fopen(DATA_FILE, "ab");
    if (file == NULL) {
        perror("Unable to open student data file");
        return;
    }

    if (fwrite(&student, sizeof(Student), 1, file) != 1) {
        printf("Could not save the student record.\n");
    } else {
        printf("Student record added successfully.\n");
    }
    fclose(file);
}

void printStudent(const Student *student) {
    int i;
    printf("\n---------------------------------------------\n");
    printf("Roll number : %d\n", student->rollNo);
    printf("Name        : %s\n", student->name);
    for (i = 0; i < SUBJECT_COUNT; i++) {
        printf("%-12s: %6.2f\n", subjectNames[i], student->marks[i]);
    }
    printf("Total       : %.2f / %.2f\n", calculateTotal(student), SUBJECT_COUNT * 100.0f);
    printf("Percentage  : %.2f%%\n", calculatePercentage(student));
    printf("Result      : %s\n", hasPassed(student) ? "PASS" : "FAIL");
    printf("Grade       : %s\n", calculateGrade(student));
    printf("---------------------------------------------\n");
}

void displayAllStudents(void) {
    FILE *file = fopen(DATA_FILE, "rb");
    Student student;
    int found = 0;

    printf("\n--- All Student Records ---\n");
    if (file == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        printStudent(&student);
        found = 1;
    }

    if (!found) printf("No records found.\n");
    fclose(file);
}

void searchStudent(void) {
    FILE *file = fopen(DATA_FILE, "rb");
    Student student;
    int rollNo;
    int found = 0;

    printf("\n--- Search Student ---\n");
    rollNo = readInt("Enter roll number to search: ", 1, 1000000000);

    if (file == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNo == rollNo) {
            printStudent(&student);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with roll number %d was not found.\n", rollNo);
    fclose(file);
}

void updateStudentMarks(void) {
    FILE *file = fopen(DATA_FILE, "rb+");
    Student student;
    int rollNo;
    int found = 0;

    printf("\n--- Update Student Marks ---\n");
    rollNo = readInt("Enter roll number to update: ", 1, 1000000000);

    if (file == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.rollNo == rollNo) {
            int i;
            printf("Updating marks for %s (Roll No: %d)\n", student.name, student.rollNo);
            for (i = 0; i < SUBJECT_COUNT; i++) {
                student.marks[i] = readMark(subjectNames[i]);
            }

            if (fseek(file, -(long)sizeof(Student), SEEK_CUR) != 0 ||
                fwrite(&student, sizeof(Student), 1, file) != 1) {
                printf("Could not update the record.\n");
            } else {
                printf("Student marks updated successfully.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with roll number %d was not found.\n", rollNo);
    fclose(file);
}

void deleteStudent(void) {
    FILE *source = fopen(DATA_FILE, "rb");
    FILE *temporary;
    Student student;
    int rollNo;
    int found = 0;

    printf("\n--- Delete Student ---\n");
    rollNo = readInt("Enter roll number to delete: ", 1, 1000000000);

    if (source == NULL) {
        printf("No records found. Add a student first.\n");
        return;
    }

    temporary = fopen(TEMP_FILE, "wb");
    if (temporary == NULL) {
        perror("Unable to create temporary file");
        fclose(source);
        return;
    }

    while (fread(&student, sizeof(Student), 1, source) == 1) {
        if (student.rollNo == rollNo) {
            found = 1;
        } else if (fwrite(&student, sizeof(Student), 1, temporary) != 1) {
            printf("Error writing temporary data file.\n");
            fclose(source);
            fclose(temporary);
            remove(TEMP_FILE);
            return;
        }
    }

    fclose(source);
    fclose(temporary);

    if (!found) {
        remove(TEMP_FILE);
        printf("Student with roll number %d was not found.\n", rollNo);
        return;
    }

    if (remove(DATA_FILE) != 0) {
        perror("Could not replace the old data file");
        remove(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, DATA_FILE) != 0) {
        perror("Could not rename the temporary data file");
        printf("The remaining records are in %s.\n", TEMP_FILE);
        return;
    }

    printf("Student record deleted successfully.\n");
}

void showMenu(void) {
    printf("\n=============================================\n");
    printf("       STUDENT RESULT MANAGEMENT SYSTEM      \n");
    printf("=============================================\n");
    printf("1. Add student record\n");
    printf("2. Display all student records\n");
    printf("3. Search student by roll number\n");
    printf("4. Update student marks\n");
    printf("5. Delete student record\n");
    printf("0. Exit\n");
    printf("=============================================\n");
}

int main(void) {
    int choice;

    do {
        showMenu();
        choice = readInt("Enter your choice: ", 0, 5);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudentMarks();
                break;
            case 5:
                deleteStudent();
                break;
            case 0:
                printf("Thank you for using the Student Result Management System.\n");
                break;
            default:
                /* readInt prevents values outside 0-5; this is a safe fallback. */
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
