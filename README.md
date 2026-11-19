# Student Result Management System (C)

A menu-driven, beginner-friendly **C programming mini project** for managing student marks and results. It uses structures, functions, loops, conditional statements, and binary file handling.

## Features

1. Add a student with a unique roll number and name.
2. Enter marks for five subjects: English, Mathematics, Physics, Chemistry, and Programming.
3. Display all saved student records.
4. Search for a student by roll number.
5. Update a student's marks.
6. Delete a student record.
7. Automatically calculate total marks, percentage, pass/fail status, and grade.
8. Save records in `students.dat`, so records remain available after the program closes.

## Requirements

- Windows, Linux, or macOS
- GCC C compiler (MinGW-w64 on Windows is fine)
- VS Code or any text editor (optional)

## Compile and run on Windows (PowerShell)

Open the project folder in VS Code. Open Terminal and run:

```powershell
gcc main.c -o student_manager.exe
.\student_manager.exe
```

## Compile and run on Linux/macOS

```bash
gcc main.c -o student_manager
./student_manager
```

## How to use

1. Choose `1` to add a student.
2. Enter a roll number, name, and marks between 0 and 100 for each subject.
3. Choose `2` to display all records, or `3` to search using a roll number.
4. Choose `4` to update marks, or `5` to delete a student.
5. Choose `0` to exit.

The program creates `students.dat` in the folder from which it is run. This file contains the saved student records. It is intentionally excluded from GitHub by `.gitignore`, because it may contain personal student data.

## Grade rules used in this project

A student must score at least 33 marks in **every** subject to pass.

| Percentage | Grade |
|---|---|
| 90–100 | A+ |
| 80–89.99 | A |
| 70–79.99 | B |
| 60–69.99 | C |
| 50–59.99 | D |
| Below 50 (and passed each subject) | E |
| Failed in any subject | F (Fail) |

These grading bands are example rules for this mini project. Change them to match your college's grading policy if required.

## Concepts demonstrated

- Variables and data types
- Structures (`struct`)
- Arrays
- Functions
- `if`, `switch`, `while`, and `for`
- Input validation
- File handling (`fopen`, `fread`, `fwrite`, `fseek`, `remove`, and `rename`)

## Project files

- `main.c` — complete C source code
- `PROJECT_REPORT.md` — short college-style project report
- `sample_output.txt` — example menu and sample interaction
- `.gitignore` — excludes generated executable and local student data

## Note

This is an educational console application, not an official college examination or student information system. Use sample data for demonstrations and do not publish real student personal information.
