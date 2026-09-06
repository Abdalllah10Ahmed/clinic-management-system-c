# Clinic Management System

A command-line Clinic Management System written in C. The project manages patient records and doctor appointments using a linked-list data structure and an in-memory scheduling system.

> This is a learning project designed to demonstrate fundamental C programming, dynamic memory allocation, linked lists, modular code organization, and terminal-based user interaction.

## Features

### Admin Mode

- Password-protected admin access
- Add a new patient record
- Edit an existing patient record
- Reserve an appointment slot
- Cancel an appointment reservation
- Prevent duplicate patient IDs during registration

### User Mode

- View a patient record using the patient ID
- View today's reserved appointment slots

## Technical Highlights

- Written in **C**
- Modular structure using header and source files
- Patient records stored in a singly linked list
- Dynamic memory allocation with `malloc`
- Fixed daily appointment schedule with five available time slots
- Colored terminal interface using ANSI escape sequences

## Project Structure

```text
.
├── main.c       # Application entry point and main menu flow
├── funcs.c      # Clinic, patient, and appointment functions
├── header.h     # Data structures, constants, and function declarations
├── README.md
└── .gitignore
```

## How to Run

### Visual Studio

1. Open the project source files in Visual Studio.
2. Build and run the project.

### GCC

```bash
gcc -std=c11 -Wall -Wextra main.c funcs.c -o clinic_management_system
./clinic_management_system
```

On Windows:

```powershell
.\clinic_management_system.exe
```

## Limitations

- All patient and reservation data is stored in memory and is lost when the application closes.
- The admin password is hardcoded for demonstration purposes only and is not intended as real security.
- The system uses a fixed set of daily appointment slots.

## Future Improvements

- Save patient records and reservations to a file or database
- Add stronger input validation
- Add patient deletion
- Add search by patient name
- Replace the demonstration password with secure authentication

## Usage and Permissions

Copyright © 2026 Abdallah Ahmed. All rights reserved.

This repository is shared for portfolio and reference purposes only. No permission is granted to copy, modify, redistribute, or commercially use any part of this project without prior written permission.

## Author

**Abdallah Ahmed**  
Engineering Student, Zagazig University  
[GitHub](https://github.com/Abdalllah10Ahmed)
