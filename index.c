#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- MCRS FUNCTION ------*/
#define MAX 100

/* ---------- COLORS ---------- */
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"

/* ---------- Structure ---------- */
struct Employee {
    int id;
    char name[50];
    int totalLeave;
    int usedLeave;
};

struct Employee emp[MAX];
int count = 0;
FILE *fp;

/* ---------- Utility ---------- */
void line() {
    printf(YELLOW "============================================\n" RESET);
}

/* ---------- Function Declarations ---------- */
void loadFromFile();
void saveToFile();

void adminLogin();
void employeeLogin();

void adminMenu();
void employeeMenu(int index);

void addEmployee();
void viewEmployee();
void deleteEmployee();

void applyLeave(int index);
void viewLeaveBalance(int index);

/* ================= MAIN ================= */
int main() {
    int choice;
    loadFromFile();

    do {
        line();
        printf(CYAN "   EMPLOYEE LEAVE MANAGEMENT SYSTEM\n" RESET);
        line();
        printf(CYAN "1. Admin Login\n" RESET);
        printf(CYAN "2. Employee Login\n" RESET);
        printf(CYAN "3. Exit\n" RESET);
        line();
        printf(CYAN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch(choice) {
            case 1: adminLogin(); break;
            case 2: employeeLogin(); break;
            case 3:
                saveToFile();
                printf(CYAN "Data Saved. Exiting...\n" RESET);
                break;
            default:
                printf(CYAN "Invalid Choice!\n" RESET);
        }
    } while(choice != 3);

    return 0;
}

/* ================= FILE HANDLING ================= */
void loadFromFile() {
    fp = fopen("employee.dat", "rb");
    if(fp == NULL) {
        count = 0;
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(emp, sizeof(struct Employee), count, fp);
    fclose(fp);
}

void saveToFile() {
    fp = fopen("employee.dat", "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(emp, sizeof(struct Employee), count, fp);
    fclose(fp);
}

/* ================= ADMIN LOGIN ================= */
void adminLogin() {
    char user[20], pass[20];

    line();
    printf(CYAN "            ADMIN LOGIN\n" RESET);
    line();
    printf(CYAN "Username: " RESET);
    scanf("%s", user);
    printf(CYAN "Password: " RESET);
    scanf("%s", pass);

    if(strcmp(user, "Arvind") == 0 && strcmp(pass, "mca25") == 0) {
        adminMenu();
    } else {
        printf(CYAN "Invalid Admin Credentials!\n" RESET);
    }
}

/* ================= EMPLOYEE LOGIN ================= */
void employeeLogin() {
    int id, i;

    line();
    printf(CYAN "           EMPLOYEE LOGIN\n" RESET);
    line();
    printf(CYAN "Enter Employee ID: " RESET);
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            employeeMenu(i);
            return;
        }
    }
    printf(CYAN "Employee Not Found!\n" RESET);
}

/* ================= ADMIN MENU ================= */
void adminMenu() {
    int choice;
    do {
        line();
        printf(CYAN "              ADMIN MENU\n" RESET);
        line();
        printf(CYAN "1. Add Employee\n" RESET);
        printf(CYAN "2. View All Employees\n" RESET);
        printf(CYAN "3. Delete Employee\n" RESET);
        printf(CYAN "4. Logout\n" RESET);
        line();
        printf(CYAN "Enter choice: " RESET);
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4:
                saveToFile();
                printf(CYAN "Admin Logged Out!\n" RESET);
                break;
            default:
                printf(CYAN "Invalid Choice!\n" RESET);
        }
    } while(choice != 4);
}

/* ================= EMPLOYEE MENU ================= */
void employeeMenu(int index) {
    int choice;
    do {
        line();
        printf(CYAN "            EMPLOYEE MENU\n" RESET);
        line();
        printf(CYAN "1. Apply Leave\n" RESET);
        printf(CYAN "2. View Leave Balance\n" RESET);
        printf(CYAN "3. Logout\n" RESET);
        line();
        printf(CYAN "Enter choice: " RESET);
        scanf("%d", &choice);

        switch(choice) {
            case 1: applyLeave(index); break;
            case 2: viewLeaveBalance(index); break;
            case 3:
                saveToFile();
                printf(CYAN "Employee Logged Out!\n" RESET);
                break;
            default:
                printf(CYAN "Invalid Choice!\n" RESET);
        }
    } while(choice != 3);
}

/* ================= ADD EMPLOYEE ================= */
void addEmployee() {
    line();
    printf(CYAN "           ADD EMPLOYEE\n" RESET);
    line();

    printf(CYAN "Enter Employee ID: " RESET);
    scanf("%d", &emp[count].id);

    printf(CYAN "Enter Employee Name: " RESET);
    getchar();
    fgets(emp[count].name, sizeof(emp[count].name), stdin);
    emp[count].name[strcspn(emp[count].name, "\n")] = '\0';

    emp[count].totalLeave = 30;
    emp[count].usedLeave = 0;

    count++;
    saveToFile();

    printf(CYAN "Employee Added Successfully!\n" RESET);
}

/* ================= VIEW EMPLOYEE ================= */
void viewEmployee() {
    int i;
    if(count == 0) {
        printf(CYAN "No Employee Record Found!\n" RESET);
        return;
    }

    printf(CYAN "\n+------+----------------------+--------+--------+-----------+\n" RESET);
    printf(CYAN "| ID   | Name                 | Total  | Used   | Remaining |\n" RESET);
    printf(CYAN "+------+----------------------+--------+--------+-----------+\n" RESET);

    for(i = 0; i < count; i++) {
        printf(CYAN "| %-4d | %-20s | %-6d | %-6d | %-9d |\n" RESET,
               emp[i].id,
               emp[i].name,
               emp[i].totalLeave,
               emp[i].usedLeave,
               emp[i].totalLeave - emp[i].usedLeave);
    }

    printf(CYAN "+------+----------------------+--------+--------+-----------+\n" RESET);
}

/* ================= APPLY LEAVE ================= */
void applyLeave(int index) {
    int days;
    printf(CYAN "Enter Leave Days: " RESET);
    scanf("%d", &days);

    if(emp[index].usedLeave + days <= emp[index].totalLeave) {
        emp[index].usedLeave += days;
        saveToFile();
        printf(CYAN "Leave Applied Successfully!\n" RESET);
    } else {
        printf(CYAN "Not Enough Leave Balance!\n" RESET);
    }
}

/* ================= VIEW LEAVE BALANCE ================= */
void viewLeaveBalance(int index) {
    line();
    printf(CYAN "          LEAVE BALANCE\n" RESET);
    line();
    printf(CYAN "Name       : %s\n" RESET, emp[index].name);
    printf(CYAN "Total Leave: %d\n" RESET, emp[index].totalLeave);
    printf(CYAN "Used Leave : %d\n" RESET, emp[index].usedLeave);
    printf(CYAN "Remaining  : %d\n" RESET,
           emp[index].totalLeave - emp[index].usedLeave);
    line();
}

/* ================= DELETE EMPLOYEE ================= */
void deleteEmployee() {
    int id, i, j;
    printf(CYAN "Enter Employee ID to Delete: " RESET);
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            for(j = i; j < count - 1; j++) {
                emp[j] = emp[j + 1];
            }
            count--;
            saveToFile();
            printf(CYAN "Employee Deleted Successfully!\n" RESET);
            return;
        }
    }
    printf(CYAN "Employee Not Found!\n" RESET);
}
