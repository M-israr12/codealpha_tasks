#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bank.dat"
  // Structure
struct Account {
    long long accNo;  
    char name[50];
    float balance;
};
       // Function Prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
        // Main Function
int main() {
    int choice;
    while (1) {
        printf("\n===== BANK SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: printf("Thank you!\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
    // Create Account
void createAccount() {
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "ab");
    printf("Enter Account Number: ");
    scanf("%lld", &acc.accNo);   // FIX
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}
  // Deposit Money
void depositMoney() {
    long long accNo;   
    int found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Account Number: ");
    scanf("%lld", &accNo);   // FIX
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Amount deposited successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
    fclose(fp);
}
  // Withdraw Money
void withdrawMoney() {
    long long accNo;   
    int found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Account Number: ");
    scanf("%lld", &accNo);   
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("Amount withdrawn successfully!\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
    fclose(fp);
}
    // Check Balance
void checkBalance() {
    long long accNo;   
    int found = 0;
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Account Number: ");
    scanf("%lld", &accNo);   // FIX
    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("\nAccount No: %lld\n", acc.accNo);   // FIX
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
    fclose(fp);
}