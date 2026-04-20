#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

void deposit() {
    int accNo;
    float amount;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAmount Deposited Successfully!\n");
            fclose(fp);
            return;
        }
    }

    printf("\nAccount Not Found!\n");
    fclose(fp);
}

void withdraw() {
    int accNo;
    float amount;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("\nInsufficient Balance!\n");
            } else {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("\nWithdrawal Successful!\n");
            }
            fclose(fp);
            return;
        }
    }

    printf("\nAccount Not Found!\n");
    fclose(fp);
}

void checkBalance() {
    int accNo;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("\nAccount No: %d", acc.accNo);
            printf("\nName: %s", acc.name);
            printf("\nBalance: %.2f\n", acc.balance);
            fclose(fp);
            return;
        }
    }

    printf("\nAccount Not Found!\n");
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n====== BANK MANAGEMENT SYSTEM ======\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }
}