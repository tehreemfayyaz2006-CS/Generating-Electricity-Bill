
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

// Structure to hold customer details
struct Customer {
    char name[50];
    int customerID;
    float unitsConsumed;
    float billAmount;
};

// Function prototypes
void calculateBill(struct Customer *c);
void saveBillToFile(struct Customer *c);
void displayAllBills();

int main() {
    struct Customer customers[MAX_CUSTOMERS];
    int numCustomers, i;
    FILE *file;

    printf("Enter the number of customers: ");
    scanf("%d", &numCustomers);
    getchar(); // Clear newline from buffer

    // Input customer details
    for (i = 0; i < numCustomers; i++) {
        printf("\nEnter details for customer %d:\n", i + 1);
        printf("Name: ");
        fgets(customers[i].name, sizeof(customers[i].name), stdin);
        customers[i].name[strcspn(customers[i].name, "\n")] = '\0'; // Remove newline

        printf("Customer ID: ");
        scanf("%d", &customers[i].customerID);

        printf("Units Consumed: ");
        scanf("%f", &customers[i].unitsConsumed);

        calculateBill(&customers[i]);
        saveBillToFile(&customers[i]);
        getchar(); // Clear newline from buffer
    }

    // Display all bills
    printf("\nAll Bills:\n");
    displayAllBills();

    return 0;
}

// Function to calculate the bill
void calculateBill(struct Customer *c) {
    float rate;
    if (c->unitsConsumed <= 100) {
        rate = 1.5;
    } else if (c->unitsConsumed <= 300) {
        rate = 2.0;
    } else {
        rate = 3.0;
    }
    c->billAmount = c->unitsConsumed * rate;
}

// Function to save the bill to a file
void saveBillToFile(struct Customer *c) {
    FILE *file = fopen("ElectricityBills.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "Customer ID: %d\n", c->customerID);
    fprintf(file, "Name: %s\n", c->name);
    fprintf(file, "Units Consumed: %.2f\n", c->unitsConsumed);
    fprintf(file, "Bill Amount: $%.2f\n", c->billAmount);
    fprintf(file, "------------------------\n");
    fclose(file);
}

// Function to display all bills from the file
void displayAllBills() {
    FILE *file = fopen("ElectricityBills.txt", "r");
    char line[100];

    if (file == NULL) {
        printf("No bills found!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

