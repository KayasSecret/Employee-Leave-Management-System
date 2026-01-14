# 🏢 Employee Leave Management System (C Language)

## 📌 Project Overview
The **Employee Leave Management System** is a console-based, menu-driven application developed in **C language**.  
It helps manage employee records and their leave details in a simple, structured, and beginner-friendly way.

This project is ideal for **college students**, **mini projects**, and **C programming learners**.

---

## ✨ Features
- ➕ Add New Employee  
- 👀 View All Employees  
- 📝 Apply for Leave  
- 📊 Check Leave Balance  
- ✅ Leave Approval (Demo Mode)  
- ❌ Delete Employee  
- 📋 Easy Menu-Driven Interface  

---

## 🧠 Technologies & Concepts Used
- C Programming Language  
- Structures (`struct`)  
- Functions (Modular Programming)  
- Arrays  
- Loops (`for`, `do-while`)  
- Conditional Statements (`if-else`)  
- Switch Case  
- Macros (`#define`)  

---

## 🏗️ Project Structure
```
Employee Leave Management System
│
├── main()
│   ├── Menu Display
│   ├── User Choice Handling
│   └── Function Calls
│
├── addEmployee()
├── viewEmployee()
├── applyLeave()
├── viewLeaveBalance()
├── approveLeave()
└── deleteEmployee()
```

---

## 🧾 Data Structure Used
```c
struct Employee {
    int id;
    char name[50];
    int totalLeave;
    int usedLeave;
};
```

### Employee Attributes
- 🆔 Employee ID  
- 👤 Employee Name  
- 📅 Total Leave (Default: 30 days)  
- ❌ Used Leave  

---

## ⚙️ How the System Works
1. The program starts by displaying a menu.
2. The user selects an option.
3. The selected function is executed.
4. The system performs validation and updates data.
5. The menu is displayed again until the user exits.

---

## 🧮 Leave Calculation Logic
```
Remaining Leave = Total Leave - Used Leave
```

✔ Leave is granted only if sufficient balance is available.

---

## 🔐 Admin Module (Demo)
- Leave approval is automatic.
- This is a demo feature and can be extended.

---

## 🚀 Future Enhancements
- 💾 File Handling for permanent storage  
- 🔑 Login system (Admin / Employee)  
- 📆 Date-wise leave records  
- 🗂 Leave types (CL, SL, EL)  
- ⏳ Leave status (Pending / Approved / Rejected)  

---

## 🎯 Suitable For
- MCA / BSc Computer Science Students  
- C Programming Beginners  
- Mini Project Submission  
- Viva & Practical Exams  

---

## 🗣️ Viva Explanation (Short)
> This is a menu-driven Employee Leave Management System developed using C language.  
> It uses structures and functions to manage employee leave records efficiently.  
> The system is simple, modular, and easy to extend.

---

## ❤️ Conclusion
This project demonstrates:
- Clean code structure  
- Practical use of C concepts  
- Real-world problem handling  

A perfect project to strengthen **C programming fundamentals** 🚀

---

### 👨‍💻 Developed By
**Kayas Mishra**  
MCA Student | C & DSA Enthusiast  
