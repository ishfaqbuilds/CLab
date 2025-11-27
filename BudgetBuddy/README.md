### Budget Buddy (C Terminal)
A beginner-friendly **personal finance tracker** built in C.  

Budget Buddy helps you manage income, expenses, and net worth — all directly from your terminal. Track your finances in seconds — no spreadsheets required.

---

#### Features
##### **User Management:**
  1. Registration and login

##### **Finance Tracking:**
  1. Balance tracking  
  2. Add income deposits  
  3. Record expenses  
  4. Net worth calculation

##### **System:**
  1. Credits display  
  2. Exit system  

---

#### Getting Started

##### Prerequisites:
- GCC (tested with version 11+)  
- Linux/macOS terminal  

##### Installation:
###### **1. Clone The Repository**
```
git clone https://github.com/ishfaqbuilds/CLab.git
cd CLab/BudgetBuddy
```
###### **2. Compile The Source Code**
```
gcc src/main.c -o budget_buddy
```
###### **3. Run The Program**
```
./budget_buddy
```
---
#### Project Structure
```
BudgetBuddy/
│── src/
     └── main.c
     ├── User_Info.txt
     ├── Balance_Sheet.txt
     ├── Income_Sheet.txt
     └── Expense_Sheet.txt
README.md
```
---
#### Learning Highlights
- Structs for user data  
- Arrays  
- File handling  
- Functions  
- Loops  
- Conditional statements  
- Terminal input/output  
---
#### Contributing
**Contributions are welcome:**
- Fork the repo
- Create a feature branch
- Follow coding style (clang-format)
- Submit a pull request

#### For bugs or feature requests, please open an issue.
---
#### License
This project is licensed under the **MIT License**. See the `LICENSE` file for details.
