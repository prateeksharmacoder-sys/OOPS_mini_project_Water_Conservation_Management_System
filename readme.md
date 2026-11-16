# MINI PROJECT
# Water Conservation Management System

## Student Details

| Particulars | Details |
|---|---|
| **Group Number** | 3I5 |
| **Student Name(s)** | Rohan Bhatt, Vedant Kodinya, Prateek Sharma |
| **Enrollment Number(s)** | 08314803125, 08914803125, 09014803125 |
| **Course / Semester** | BTECH / 3rd Semester |
| **Subject** | Object-Oriented Programming Using C++ |

---

## Project Overview

The **Water Conservation Management System** is a console-based C++ application developed to record, monitor, and manage indoor and outdoor water consumption. It helps users track water usage, calculate consumption summaries, and promote water-saving habits.

## Features

- Add indoor and outdoor water usage records.
- View all recorded water consumption.
- Calculate total water consumption.
- Display separate indoor and outdoor usage.
- Display water-saving tips.
- Save records permanently using file handling.
- Automatically load previously saved records when the program starts.

## Object-Oriented Programming Concepts Used

1. **Classes and Objects:** Used to structure the water management system.
2. **Inheritance:** IndoorUsage and OutdoorUsage inherit from the WaterUsage base class.
3. **Abstraction:** WaterUsage is an abstract class containing pure virtual functions.
4. **Polymorphism:** Virtual functions provide different implementations for indoor and outdoor usage.
5. **Encapsulation:** Data members and member functions are organized within classes.
6. **File Handling:** ifstream and ofstream are used to load and save records.
7. **Dynamic Memory Management:** unique_ptr manages objects dynamically.
8. **STL:** Vector stores multiple water usage records.

## Technologies Used

- Programming Language: C++
- Concepts: Object-Oriented Programming
- Compiler: GCC / MinGW
- IDE: Visual Studio Code
- Libraries: iostream, fstream, iomanip, memory, limits, sstream, string, vector

## Project Menu

1. Add Water Usage Record
2. View All Records
3. View Consumption Summary
4. Save and Exit

## How to Compile and Run

### Step 1: Compile

```bash
g++ Water_Conservation_Management.cpp -o WaterTracker
```

### Step 2: Execute

**Windows:**
```bash
WaterTracker.exe
```

**Linux / macOS:**
```bash
./WaterTracker
```

## File Storage

The application uses `water_records.txt` to store water consumption records. Previously saved records are automatically loaded when the application starts.

## Project Objective

The main objective of this project is to demonstrate the practical implementation of Object-Oriented Programming concepts in C++ while encouraging efficient water management and conservation.

---

**Project:** Water Conservation Management System  
**Group Number:** 3I5  
**Subject:** Object-Oriented Programming Using C++  
**Course:** B.Tech, 3rd Semester