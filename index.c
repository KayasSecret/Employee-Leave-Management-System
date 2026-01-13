#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for Employee
struct Employee {
    int id;
    char name[50];
    int totalLeave;
    int usedLeave;
};

struct Employee emp[MAX];
int count = 0;

// Function Declarations
void addEmployee();
void viewEmployee();
void applyLeave();
void viewLeaveBalance();
void approveLeave();
void deleteEmployee();

int main() {
    int choice;

    do {
        printf("\n========== Employee Leave Management System ==========\n");
        printf("1. Add Employee\n");
        printf("2. View All Employees\n");
        printf("3. Apply Leave\n");
        printf("4. View Leave Balance\n");
        printf("5. Approve Leave (Admin)\n");
        printf("6. Delete Employee\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployee(); break;
            case 3: applyLeave(); break;
            case 4: viewLeaveBalance(); break;
            case 5: approveLeave(); break;
            case 6: deleteEmployee(); break;
            case 7: printf("Exiting System... Thank You!\n"); break;
            default: printf("Invalid Choice! Try Again.\n");
        }
    } while(choice != 7);

    return 0;
}

// Add Employee
void addEmployee() {
    printf("\nEnter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Employee Name: ");
    scanf("%s", emp[count].name);

    emp[count].totalLeave = 30;   // default leave
    emp[count].usedLeave = 0;

    count++;
    printf("Employee Added Successfully!\n");
}

// View Employees
void viewEmployee() {
    int i;
    if(count == 0) {
        printf("No Employee Record Found!\n");
        return;
    }

    printf("\nID\tName\tTotal\tUsed\n");
    for(i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%d\n",
               emp[i].id, emp[i].name,
               emp[i].totalLeave, emp[i].usedLeave);
    }
}

// Apply Leave
void applyLeave() {
    int id, days, i, found = 0;

    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            found = 1;
            printf("Enter Leave Days: ");
            scanf("%d", &days);

            if(emp[i].usedLeave + days <= emp[i].totalLeave) {
                emp[i].usedLeave += days;
                printf("Leave Applied Successfully!\n");
            } else {
                printf("Not Enough Leave Balance!\n");
            }
            break;
        }
    }

    if(!found)
        printf("Employee Not Found!\n");
}

// View Leave Balance
void viewLeaveBalance() {
    int id, i;

    printf("Enter Employee ID: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            printf("Employee Name: %s\n", emp[i].name);
            printf("Remaining Leave: %d\n",
                   emp[i].totalLeave - emp[i].usedLeave);
            return;
        }
    }
    printf("Employee Not Found!\n");
}

// Approve Leave (Dummy Admin)
void approveLeave() {
    printf("All Leave Requests are Auto Approved (Demo Mode).\n");
}

// Delete Employee
void deleteEmployee() {
    int id, i, j;

    printf("Enter Employee ID to Delete: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++) {
        if(emp[i].id == id) {
            for(j = i; j < count - 1; j++) {
                emp[j] = emp[j + 1];
            }
            count--;
            printf("Employee Deleted Successfully!\n");
            return;
        }
    }
    printf("Employee Not Found!\n");
}
