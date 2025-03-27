// Bank Management System

#include <stdio.h>  // printf(), scanf(), fgets()
#include <stdlib.h> // exit(), system()
#include <string.h> // strcspn()
#include <time.h>   // time(), ctime()

#ifdef _WIN32
#include <conio.h> // getch() for Windows
#else
#define getch() getchar()
#endif

char name[50];
int dip_amt, amt = 10000, acc_no, ac, count = 0; // Global variables
int trans_amt;
int with_amt;

void deposit_money();
void withdraw_money();
void transfer_money();
void checkDetail();
void LastDetail();
void transaction_details();
void menu();

void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf("\n");
}

int main()
{
    FILE *ptr = fopen("Account.txt", "w");
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int ch;
    printf("Enter your name : \n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    fprintf(ptr, "\nName : %s\n", name);

    printf("Enter your account no. : ");
    scanf("%d", &acc_no);
    fprintf(ptr, "Account no. : %d\n", acc_no);

    fclose(ptr);

    while (1)
    {
        menu();
        printf("\nEnter your choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            system("cls");
            deposit_money();
            break;
        case 2:
            system("cls");
            withdraw_money();
            break;
        case 3:
            system("cls");
            transfer_money();
            break;
        case 4:
            system("cls");
            checkDetail();
            break;
        case 5:
            transaction_details();
            break;
        case 6:
            system("cls");
            LastDetail();
            exit(0);
        default:
            printf("Invalid choice\n");
            printf("Press any key...\n");
            getch();
        }
    }

    return 0;
}

void menu()
{
    system("cls");
    divider();
    printf("\tMENU\n");
    divider();
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account details\n");
    printf("5. Transaction details\n");
    printf("6. Exit\n");
    divider();
}

void deposit_money()
{
    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("DEPOSITING MONEY\n");
    divider();

    printf("Enter the amount you want to deposit: ");
    scanf("%d", &dip_amt);
    amt += dip_amt;
    printf("Money Deposited\n");
    printf("Current balance: %d\n", amt);
    fprintf(ptr, "\nRs%d has been deposited to your account\n", dip_amt);
    fprintf(ptr, "Date/Time of transaction: %s\n", ctime(&tm));
    count++;

    fclose(ptr);
    printf("Press any key...\n");
    getch();
}

void withdraw_money()
{
    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("WITHDRAWING MONEY\n");
    divider();

    printf("Enter the amount you want to withdraw: ");
    scanf("%d", &with_amt);

    if (amt < with_amt)
    {
        printf("Insufficient balance\n");
    }
    else
    {
        amt -= with_amt;
        printf("Money Withdrawn\n");
        printf("Current balance: %d\n", amt);
        fprintf(ptr, "\nRs%d has been withdrawn from your account\n", with_amt);
        fprintf(ptr, "Date/Time of transaction: %s\n", ctime(&tm));
        count++;
    }
    fclose(ptr);
    printf("Press any key...\n");
    getch();
}

void transfer_money()
{
    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("TRANSFERRING MONEY\n");
    divider();

    printf("Enter the account no. to transfer money: ");
    scanf("%d", &ac);
    printf("Enter the amount you want to transfer: ");
    scanf("%d", &trans_amt);

    if (amt < trans_amt)
    {
        printf("Insufficient balance\n");
    }
    else
    {
        amt -= trans_amt;
        printf("Money Transferred\n");
        printf("Current balance: %d\n", amt);
        fprintf(ptr, "\nRs%d has been transferred to account %d\n", trans_amt, ac);
        fprintf(ptr, "Date/Time of transaction: %s\n", ctime(&tm));
        count++;
    }
    fclose(ptr);
    printf("Press any key...\n");
    getch();
}

void checkDetail()
{
    printf("ACCOUNT DETAILS\n");
    divider();

    printf("Name: %s\n", name);
    printf("Account No.: %d\n", acc_no);
    printf("Total balance: %d\n", amt);
    printf("Total transactions: %d\n", count);
    printf("Press any key...\n");
    getch();
}

void transaction_details()
{
    system("cls");
    FILE *ptr = fopen("Account.txt", "r");
    if (ptr == NULL)
    {
        printf("Unable to open file\n");
        printf("Press any key...\n");
        getch();
        return;
    }

    char c = fgetc(ptr);
    printf("TRANSACTION DETAILS\n");
    divider();

    if (c == EOF)
    {
        printf("** NO RECENT TRANSACTION **\n");
    }
    else
    {
        printf("Total transactions: %d\n", count);
        rewind(ptr); // Reset file pointer to beginning
        while ((c = fgetc(ptr)) != EOF)
        {
            putchar(c);
        }
    }
    fclose(ptr);
    printf("\nPress any key...\n");
    getch();
}

void LastDetail()
{
    printf("ACCOUNT DETAILS\n");
    divider();
    printf("Name: %s\n", name);
    printf("Account No.: %d\n", acc_no);
    printf("Total balance: %d\n", amt);
    printf("\nPress any key to exit...\n");
    getch();
}
