# Project Report: Student Result Management System

## 1. Introduction

The Student Result Management System is a menu-driven application developed using the C programming language. It helps a user store and manage student marks and view calculated results through a simple text-based menu.

## 2. Objectives

- To practise basic C programming concepts in one project.
- To store student details and marks using a structure.
- To add, display, search, update, and delete student records.
- To calculate total marks, percentage, pass/fail status, and grade automatically.
- To preserve records using file handling.

## 3. Software and Concepts Used

**Language:** C  
**Compiler:** GCC  
**Editor:** VS Code (optional)

The project uses variables, arrays, structures, functions, loops, conditional statements, switch-case, input validation, and binary file handling.

## 4. Project Modules

1. **Add Student:** Accepts a unique roll number, student name, and marks in five subjects.
2. **Display Students:** Reads and displays all saved student records.
3. **Search Student:** Finds a record using the roll number.
4. **Update Marks:** Changes the marks of an existing student.
5. **Delete Student:** Removes a selected student record while keeping the other records.
6. **Result Calculation:** Calculates total, percentage, pass/fail status, and grade.

## 5. Algorithm

1. Start the program.
2. Display the main menu.
3. Read the user's menu choice.
4. If the choice is 1, accept student details and save the record.
5. If the choice is 2, display all saved records.
6. If the choice is 3, search for a student using the roll number.
7. If the choice is 4, find a student and update the marks.
8. If the choice is 5, find and delete a student record.
9. If the choice is 0, display the exit message and stop.
10. For choices 1–5, return to the menu.

## 6. Result Calculation

- Total = sum of marks in all five subjects.
- Percentage = total / 5, because each subject is marked out of 100.
- The student passes only when marks are at least 33 in every subject.
- Grade is assigned according to the percentage bands documented in `README.md`.

## 7. Conclusion

This project demonstrates how the basic concepts of C can be combined to build a useful console application. It also provides practice with structures, functions, arrays, validation, and persistent file storage.

## 8. Future Scope

The project can be extended with a graphical interface, separate login roles, subject selection, report-card export, and database integration.
