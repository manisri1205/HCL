#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[50];
    float salary;
    char work[50];
    char email[50];
    char phone[15];
    char dateOfJoining[15];
};

struct Employee employees[MAX_EMPLOYEES];
int numEmployees = 0;

// Function prototypes
void login();
void displayMenu();
void addEmployee();
void displayAllEmployees();
void deleteEmployee();
void updateEmployee();
void searchEmployee();
void displayEmployee(int index);
void sortEmployees();
void filterEmployees();
void clearBuffer();
void showError(char* message);
int isDateValid(char* date); 

int main() {
    login();
    return 0;
}

void login() {
    char username[20];
    char password[20];
    int i = 0;

    printf("Welcome to Employee Management System\n");
    printf("Please enter your credentials:\n");

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    while (i < 20) {
        password[i] = _getch();
        if (password[i] == '\r') {
            break;
        } else if (password[i] == '\b' && i > 0) {
            i--;
            printf("\b \b");  // Erase the character from the console
        } else {
            printf("*");
            i++;
        }
    }
    password[i] = '\0';

    printf("\n");  // Add this line to print a newline

    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) { 
        system("cls");
        displayMenu();
    } else {
        showError("Invalid username or password. Please try again.");
    }
}


void displayMenu() {
    int choice;

    do {
        printf("+--------------------------------------+\n");
        printf("|             Menu Options             |\n");
        printf("+--------------------------------------+\n");
        printf("| 1. Add Employee                      |\n");
        printf("| 2. Display All Employees             |\n");
        printf("| 3. Delete Employee                   |\n");
        printf("| 4. Update Employee Profiles          |\n");
        printf("| 5. Search Employee Record            |\n");
        printf("| 6. Sort Employees                    |\n");
        printf("| 7. Filter Employees                  |\n");
        printf("| 8. Exit                              |\n");
        printf("+--------------------------------------+\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            showError("Invalid input. Please enter a number.");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                updateEmployee();
                break;
            case 5:
                searchEmployee();
                break;
            case 6:
                sortEmployees();
                break;
            case 7:
                filterEmployees();
                break;
            case 8:
                printf("Exiting... Thank you!\n");
                break;
            default:
                showError("Invalid choice. Please try again.");
        }
    } while (choice != 8);
}

void addEmployee() {
    if (numEmployees < MAX_EMPLOYEES) {
        struct Employee newEmployee;

        printf("\nEnter employee ID: ");
        if (scanf("%d", &newEmployee.id) != 1) {
            showError("Invalid input for ID. Please enter a number.");
            clearBuffer();
            return;
        }

        printf("Enter employee name: ");
        if (scanf("%s", newEmployee.name) != 1) {
            showError("Invalid input for name. Please enter a string.");
            clearBuffer();
            return;
        }

        printf("Enter employee salary: ");
        if (scanf("%f", &newEmployee.salary) != 1) {
            showError("Invalid input for salary. Please enter a number.");
            clearBuffer();
            return;
        }

        clearBuffer(); // Clear buffer after reading float

        printf("Enter employee work: ");
        if (scanf("%s", newEmployee.work) != 1) {
            showError("Invalid input for work. Please enter a string.");
            clearBuffer();
            return;
        }

        printf("Enter employee email: ");
        if (scanf("%s", newEmployee.email) != 1) {
            showError("Invalid input for email. Please enter a string.");
            clearBuffer();
            return;
        }

        printf("Enter employee phone number: ");
        if (scanf("%s", newEmployee.phone) != 1) {
            showError("Invalid input for phone number. Please enter a string.");
            clearBuffer();
            return;
        }

        printf("Enter date of joining (YYYY-MM-DD): ");
        if (scanf("%s", newEmployee.dateOfJoining) != 1 || !isDateValid(newEmployee.dateOfJoining)) {
            showError("Invalid input for date of joining. Please enter a valid date (YYYY-MM-DD).");
            clearBuffer();
            return;
        }

        employees[numEmployees++] = newEmployee;

        printf("\nEmployee added successfully!\n");
    } else {
        printf("\nMaximum number of employees reached!\n");
    }
}

void displayAllEmployees() {
    if (numEmployees > 0) {
        printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
        printf("| ID | Name                 | Salary     | Work                 | Email                       | Phone             | Date of Joining  |\n");
        printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");

        for (int i = 0; i < numEmployees; i++) {
            printf("| %-2d | %-20s | %-10.2f | %-20s | %-30s | %-15s | %-15s |\n", employees[i].id, employees[i].name, employees[i].salary, employees[i].work, employees[i].email, employees[i].phone, employees[i].dateOfJoining);
            printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
        }
    } else {
        printf("\nNo employees to display.\n");
    }
}

void deleteEmployee() {
    int empId;
    int found = 0;

    if (numEmployees > 0) {
        printf("\nEnter the ID of the employee to delete: ");
        if (scanf("%d", &empId) != 1) {
            showError("Invalid input for ID. Please enter a number.");
            clearBuffer();
            return;
        }

        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == empId) {
                found = 1;
                for (int j = i; j < numEmployees - 1; j++) {
                    employees[j] = employees[j+1];
                }
                numEmployees--;
                printf("\nEmployee with ID %d deleted successfully.\n", empId);
                break;
            }
        }

        if (!found) {
            printf("\nEmployee with ID %d not found.\n", empId);
        }
    } else {
        printf("\nNo employees to delete.\n");
    }
}

void updateEmployee() {
    int empId;
    int found = 0;

    if (numEmployees > 0) {
        printf("\nEnter the ID of the employee to update: ");
        if (scanf("%d", &empId) != 1) {
            showError("Invalid input for ID. Please enter a number.");
            clearBuffer();
            return;
        }

        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == empId) {
                found = 1;

                printf("\nEnter new ID: ");
                if (scanf("%d", &employees[i].id) != 1) {
                    showError("Invalid input for ID. Please enter a number.");
                    clearBuffer();
                    return;
                }

                printf("Enter new name: ");
                if (scanf("%s", employees[i].name) != 1) {
                    showError("Invalid input for name. Please enter a string.");
                    clearBuffer();
                    return;
                }

                printf("Enter new salary: ");
                if (scanf("%f", &employees[i].salary) != 1) {
                    showError("Invalid input for salary. Please enter a number.");
                    clearBuffer();
                    return;
                }

                clearBuffer(); // Clear buffer after reading float

                printf("Enter new work: ");
                if (scanf("%s", employees[i].work) != 1) {
                    showError("Invalid input for work. Please enter a string.");
                    clearBuffer();
                    return;
                }

                printf("Enter new email: ");
                if (scanf("%s", employees[i].email) != 1) {
                    showError("Invalid input for email. Please enter a string.");
                    clearBuffer();
                    return;
                }

                printf("Enter new phone number: ");
                if (scanf("%s", employees[i].phone) != 1) {
                    showError("Invalid input for phone number. Please enter a string.");
                    clearBuffer();
                    return;
                }

                printf("Enter new date of joining (YYYY-MM-DD): ");
                if (scanf("%s", employees[i].dateOfJoining) != 1 || !isDateValid(employees[i].dateOfJoining)) {
                    showError("Invalid input for date of joining. Please enter a valid date (YYYY-MM-DD).");
                    clearBuffer();
                    return;
                }

                printf("\nEmployee details updated successfully.\n");
                break;
            }
        }

        if (!found) {
            printf("\nEmployee with ID %d not found.\n", empId);
        }
    } else {
        printf("\nNo employees to update.\n");
    }
}

void searchEmployee() {
    int choice;
    printf("\nSearch employees by:\n");
    printf("1. Employee ID\n");
    printf("2. Employee Name\n");
    printf("3. Mobile Number\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        showError("Invalid input. Please enter a number.");
        clearBuffer();
        return;
    }

    int found = 0;
    switch (choice) {
        case 1:
            {
                int empId;
                printf("\nEnter the ID of the employee to search: ");
                if (scanf("%d", &empId) != 1) {
                    showError("Invalid input for ID. Please enter a number.");
                    clearBuffer();
                    return;
                }

                for (int i = 0; i < numEmployees; i++) {
                    if (employees[i].id == empId) {
                        found = 1;
                        displayEmployee(i);
                        break;
                    }
                }

                if (!found) {
                    printf("\nEmployee with ID %d not found.\n", empId);
                }
            }
            break;
        case 2:
            {
                char empName[50];
                printf("\nEnter the name of the employee to search: ");
                scanf("%s", empName);

                for (int i = 0; i < numEmployees; i++) {
                    if (strcmp(employees[i].name, empName) == 0) {
                        found = 1;
                        displayEmployee(i);
                        break;
                    }
                }

                if (!found) {
                    printf("\nEmployee with name '%s' not found.\n", empName);
                }
            }
            break;
        case 3:
            {
                char empMobile[15];
                printf("\nEnter the mobile number of the employee to search: ");
                scanf("%s", empMobile);

                for (int i = 0; i < numEmployees; i++) {
                    if (strcmp(employees[i].phone, empMobile) == 0) {
                        found = 1;
                        displayEmployee(i);
                        break;
                    }
                }

                if (!found) {
                    printf("\nEmployee with mobile number '%s' not found.\n", empMobile);
                }
            }
            break;
        default:
            showError("Invalid choice.");
    }
}

void displayEmployee(int index) {
    printf("\nEmployee Details:\n");
    printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
    printf("| ID | Name                 | Salary     | Work                 | Email                       | Phone             | Date of Joining  |\n");
    printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
    printf("| %-2d | %-20s | %-10.2f | %-20s | %-30s | %-15s | %-15s |\n", employees[index].id, employees[index].name, employees[index].salary, employees[index].work, employees[index].email, employees[index].phone, employees[index].dateOfJoining);
    printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
}


int isDateValid(char* date) {
    if (strlen(date) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else if (date[i] < '0' || date[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void sortEmployees() {
    int choice;

    if (numEmployees < 2) {
        printf("\nInsufficient employees to sort.\n");
        return;
    }

    printf("\nSort employees by:\n");
    printf("1. Name\n");
    printf("2. ID\n");
    printf("3. Salary\n");

    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        showError("Invalid input. Please enter a number.");
        clearBuffer();
        return;
    }

    switch (choice) {
        case 1:
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - i - 1; j++) {
                    if (strcmp(employees[j].name, employees[j+1].name) > 0) {
                        struct Employee temp = employees[j];
                        employees[j] = employees[j+1];
                        employees[j+1] = temp;
                    }
                }
            }
            printf("\nEmployees sorted by name.\n");
            break;
        case 2:
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - i - 1; j++) {
                    if (employees[j].id > employees[j+1].id) {
                        struct Employee temp = employees[j];
                        employees[j] = employees[j+1];
                        employees[j+1] = temp;
                    }
                }
            }
            printf("\nEmployees sorted by ID.\n");
            break;
        case 3:
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - i - 1; j++) {
                    if (employees[j].salary > employees[j+1].salary) {
                        struct Employee temp = employees[j];
                        employees[j] = employees[j+1];
                        employees[j+1] = temp;
                    }
                }
            }
            printf("\nEmployees sorted by salary.\n");
            break;
        default:
            showError("Invalid choice.");
    }
}

void filterEmployees() {
    int choice;

    if (numEmployees == 0) {
        printf("\nNo employees to filter.\n");
        return;
    }

    printf("\nFilter employees by:\n");
    printf("1. Salary Range\n");
    printf("2. Work\n");

    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        showError("Invalid input. Please enter a number.");
        clearBuffer();
        return;
    }

    switch (choice) {
        case 1:
            float minSalary, maxSalary;
            printf("\nEnter minimum salary: ");
            if (scanf("%f", &minSalary) != 1) {
                showError("Invalid input for salary. Please enter a number.");
                clearBuffer();
                return;
            }
            printf("Enter maximum salary: ");
            if (scanf("%f", &maxSalary) != 1) {
                showError("Invalid input for salary. Please enter a number.");
                clearBuffer();
                return;
            }
            printf("\nEmployees within the salary range %.2f - %.2f:\n", minSalary, maxSalary);
            printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
            printf("| ID | Name                 | Salary     | Work                 | Email                       | Phone             | Date of Joining  |\n");
            printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
            for (int i = 0; i < numEmployees; i++) {
                if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary) {
                    printf("| %-2d | %-20s | %-10.2f | %-20s | %-30s | %-15s | %-15s |\n", employees[i].id, employees[i].name, employees[i].salary, employees[i].work, employees[i].email, employees[i].phone, employees[i].dateOfJoining);
                    printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
                }
            }
            break;
        case 2:
            char work[50];
            printf("\nEnter work to filter by: ");
            if (scanf("%s", work) != 1) {
                showError("Invalid input for work. Please enter a string.");
                clearBuffer();
                return;
            }
            printf("\nEmployees with work '%s':\n", work);
            printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
            printf("| ID | Name                 | Salary     | Work                 | Email                       | Phone             | Date of Joining  |\n");
            printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
            for (int i = 0; i < numEmployees; i++) {
                if (strcmp(employees[i].work, work) == 0) {
                    printf("| %-2d | %-20s | %-10.2f | %-20s | %-30s | %-15s | %-15s |\n", employees[i].id, employees[i].name, employees[i].salary, employees[i].work, employees[i].email, employees[i].phone, employees[i].dateOfJoining);
                    printf("+----+----------------------+------------+----------------------+-----------------------------+-------------------+------------------+\n");
                }
            }
            break;
        default:
            showError("Invalid choice.");
    }
}


void clearBuffer() {
    while (getchar() != '\n');
}


void showError(char* message) {
    printf("\nError: %s\n", message);
}
