#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- MAX EMPLOYEE LIMIT -------- */
#define MAX 100

/* -------- TERMINAL COLORS -------- */
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"

/* -------- EMPLOYEE STRUCTURE -------- */
struct Employee {
    int id;
    char name[50];
    int totalLeave;
    int usedLeave;
};

/* -------- GLOBAL DATA -------- */
struct Employee emp[MAX];
int count = 0;
FILE *fp;

/* -------- COMMON LINE -------- */
void line() {
    printf(YELLOW "============================================\n" RESET);
}

/* -------- FUNCTION DECLARATIONS -------- */
void loadData();
void saveData();

void adminLogin();
void employeeLogin();

void adminMenu();
void employeeMenu(int index);

void addEmployee();
void viewEmployees();
void deleteEmployee();

void applyLeave(int index);
void viewLeave(int index);

/* ================= MAIN ================= */
int main() {
    int choice;
    loadData();

    while(1) {
        line();
        printf(CYAN "   EMPLOYEE LEAVE MANAGEMENT SYSTEM\n" RESET);
        line();
        printf("1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Exit\n");
        line();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
            adminLogin();
        else if(choice == 2)
            employeeLogin();
        else if(choice == 3) {
            saveData();
            printf(CYAN "Data saved. Program closed.\n" RESET);
            break;
        }
        else
            printf("Invalid choice!\n");
    }
    return 0;
}

/* ================= FILE HANDLING ================= */
void loadData() {
    fp = fopen("employee.dat", "rb");
    if(fp == NULL)
        return;

    fread(&count, sizeof(int), 1, fp);
    fread(emp, sizeof(struct Employee), count, fp);
    fclose(fp);
}

void saveData() {
    fp = fopen("employee.dat", "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(emp, sizeof(struct Employee), count, fp);
    fclose(fp);
}

/* ================= ADMIN LOGIN ================= */
void adminLogin() {
    char user[20], pass[20];

    line();
    printf("ADMIN LOGIN\n");
    line();
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if(strcmp(user, "Arvind") == 0 && strcmp(pass, "mca25") == 0)
        adminMenu();
    else
        printf("Wrong username or password!\n");
}

/* ================= EMPLOYEE LOGIN ================= */
void employeeLogin() {
    int id, i;

    line();
    printf("EMPLOYEE LOGIN\n");
    line();
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            employeeMenu(i);
            return;
        }
    }
    printf("Employee not found!\n");
}

/* ================= ADMIN MENU ================= */
void adminMenu() {
    int choice;

    do {
        line();
        printf("ADMIN MENU\n");
        line();
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Delete Employee\n");
        printf("4. Logout\n");
        line();
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1) addEmployee();
        else if(choice == 2) viewEmployees();
        else if(choice == 3) deleteEmployee();
        else if(choice == 4) {
            saveData();
            printf("Admin logged out.\n");
        }
        else printf("Invalid choice!\n");

    } while(choice != 4);
}

/* ================= EMPLOYEE MENU ================= */
void employeeMenu(int index) {
    int choice;

    do {
        line();
        printf("EMPLOYEE MENU\n");
        line();
        printf("1. Apply Leave\n");
        printf("2. View Leave Balance\n");
        printf("3. Logout\n");
        line();
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1) applyLeave(index);
        else if(choice == 2) viewLeave(index);
        else if(choice == 3) {
            saveData();
            printf("Employee logged out.\n");
        }
        else printf("Invalid choice!\n");

    } while(choice != 3);
}

/* ================= ADD EMPLOYEE ================= */
void addEmployee() {
    if(count >= MAX) {
        printf("Employee limit reached!\n");
        return;
    }

    line();
    printf("ADD EMPLOYEE\n");
    line();

    printf("Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Employee Name: ");
    getchar();
    fgets(emp[count].name, 50, stdin);
    emp[count].name[strcspn(emp[count].name, "\n")] = '\0';

    emp[count].totalLeave = 30;
    emp[count].usedLeave = 0;

    count++;
    saveData();

    printf("Employee added successfully!\n");
}

/* ================= VIEW EMPLOYEES ================= */
void viewEmployees() {
    int i;

    if(count == 0) {
        printf(CYAN "No Employee Record Found!\n" RESET);
        return;
    }

    line();
    printf(CYAN "              EMPLOYEE LIST\n" RESET);
    line();

    printf(CYAN "+------+----------------------+--------+--------+-----------+\n" RESET);
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
    printf("Enter leave days: ");
    scanf("%d", &days);

    if(emp[index].usedLeave + days <= emp[index].totalLeave) {
        emp[index].usedLeave += days;
        saveData();
        printf("Leave approved!\n");
    } else {
        printf("Insufficient leave balance!\n");
    }
}

/* ================= VIEW LEAVE ================= */
void viewLeave(int index) {
    line();
    printf("LEAVE DETAILS\n");
    line();
    printf("Name      : %s\n", emp[index].name);
    printf("Total     : %d\n", emp[index].totalLeave);
    printf("Used      : %d\n", emp[index].usedLeave);
    printf("Remaining : %d\n",
           emp[index].totalLeave - emp[index].usedLeave);
}

/* ================= DELETE EMPLOYEE ================= */
void deleteEmployee() {
    int id, i, j;
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            for(j = i; j < count - 1; j++)
                emp[j] = emp[j + 1];

            count--;
            saveData();
            printf("Employee deleted.\n");
            return;
        }
    }
    printf("Employee not found!\n");
}
