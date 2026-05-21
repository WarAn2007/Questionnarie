# Questionnaire

A lightweight, pure C++ menu-driven console application designed to create, manage, and take custom tests and flashcards. Built using standard file handling streams to keep data structured and organized.

## 🚀 Features

### 🛠️ Test Management & Execution
* **Option 1: Create Test**
  * Supports 4 question types: **Single Choice**, **Multiple Choice**, **True/False**, and **Open Questions**.
  * Custom file naming for output.
  * Saved as binary `.dat` files to prevent modification and hide test content from ordinary users.
* **Option 2: Take a Test**
  * Import any existing `.dat` test file.
  * Allows custom naming/directory selection for saving results.
  * Outputs results in clear, readable `.txt` files.
* **Option 3: View Results**
  * Displays a summary directly in the console: who took the test, their score, and the source test file used.

### 📇 Flashcards (In Progress)
* **Option 4: Create Flashcards** *(Coming Soon)* * **Option 5: Take Flashcards** *(Coming Soon)*
* **Option 6: View Flashcard Results** *(Coming Soon)*
* **Option 7: Exit**

---

## 🛠️ Tech Stack & Requirements

* **Language:** Pure C++ (Standard C++17 or higher recommended)
* **IDE/Build System:** Visual Studio (Solution managed via `.slnx`)
* **OS Compatibility:** Windows (Console mode)

---

## 📦 File Structures

To ensure data integrity and simple reporting, the application splits data into two distinct formats:

| File Type | Purpose | Security Level | Format |
| :--- | :--- | :--- | :--- |
| **`.dat`** | Test questions, choices, and answer keys. | **Encoded** (Binary serialization to prevent cheating). | Binary |
| **`.txt`** | User performance reports and scoring. | **Open Text** (Easy for instructors/creators to review). | Plain Text |

---

## 🚦 Getting Started

### Prerequisites
* Visual Studio 2022 (with **Desktop development with C++** workload installed).

### Setup and Running
1. Clone or download this repository.
2. Open the `Questionnaire.slnx` solution file in Visual Studio.
3. Build the solution (`Ctrl + Shift + B`).
4. Run the application (`F5` or `Ctrl + F5`) to launch the console interactive menu.

---

## 🗺️ Roadmap
- [x] Core Questionnaire engine (Single, Multiple, T/F).
- [x] Binary file encryption/serialization for `.dat` protection.
- [ ] Implement multi-type Flashcard generation.
- [ ] Implement Flashcard study session mode and tracking.
- [ ] Open question type for tests
