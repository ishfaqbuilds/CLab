#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_user 100
#define bank_vault 100

typedef struct
{
    char username[max_user];
    char password[max_user];
    double balance;
    double income[bank_vault];
    double expense[bank_vault];
} USER;

USER user[max_user];
USER new_user;
int total_user = 0;
int option, i, j, number;

FILE *file1;
FILE *file2;
FILE *file3;
FILE *file4;

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void save_user()
{
    file4 = fopen("User_Info.txt", "a");
    fprintf(file4, "%s\n", new_user.username);
    fprintf(file4, "%s\n", new_user.password);
    fclose(file4);
}

void read_balance()
{
    file3 = fopen("Balance_Sheet.txt", "r");

    char stored_username[max_user];
    double current_balance;
    int found = 0;

    while (fscanf(file3, "%s %lf", stored_username, &current_balance) == 2)
    {
        if (strcmp(stored_username, new_user.username) == 0)
        {
            new_user.balance = current_balance;
            found = 1;
            break;
        }
    }

    if (!found)
    {
        new_user.balance = 0.0;
    }

    fclose(file3);
}

void write_balance()
{
    FILE *tempfile3 = fopen("Temp_Balance_Sheet.txt", "w");
    file3 = fopen("Balance_Sheet.txt", "r");

    char stored_username[max_user];
    double current_balance;
    int found = 0;

    while (fscanf(file3, "%s %lf", stored_username, &current_balance) == 2)
    {
        if (strcmp(stored_username, new_user.username) == 0)
        {
            fprintf(tempfile3, "%s %.2lf\n", new_user.username, new_user.balance);
            found = 1;
        }
        else
        {
            fprintf(tempfile3, "%s %.2lf\n", stored_username, current_balance);
        }
    }

    if (!found)
    {
        fprintf(tempfile3, "%s %.2lf\n", new_user.username, new_user.balance);
    }

    fclose(file3);
    fclose(tempfile3);

    remove("Balance_Sheet.txt");
    rename("Temp_Balance_Sheet.txt", "Balance_Sheet.txt");
}

void add_income()
{
    read_balance();
    double total_income = 0;

    for (i = 1; i <= number; i++)
    {
        printf("Deposit %d(in Taka): ", i);
        scanf("%lf", &new_user.income[i]);

        total_income += new_user.income[i];

        file1 = fopen("Income_Sheet.txt", "a");
        fprintf(file1, "%s %.2lf\n", new_user.username, new_user.income[i]);
        fclose(file1);
    }
    new_user.balance += total_income;
    write_balance();

    printf("\n");
    printf("Your Deposit Has Been Recorded!\n");
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    clear_screen();
}

void add_expense()
{
    read_balance();
    double total_expense = 0;

    for (i = 1; i <= number; i++)
    {
        printf("Transaction %d(in Taka): ", i);
        scanf("%lf", &new_user.expense[i]);

        total_expense -= new_user.expense[i];

        file2 = fopen("Expense_Sheet.txt", "a");
        fprintf(file2, "%s %.2lf\n", new_user.username, new_user.expense[i]);
        fclose(file2);
    }
    new_user.balance += total_expense;
    write_balance();

    printf("\n");
    printf("Your Transaction Has Been Recorded!\n");
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    clear_screen();
}

int main()
{
    clear_screen();
    printf("╔══════════════════════════════════╗\n");
    printf("║     Welcome to BUDGET BUDDY      ║\n");
    printf("║ Your personal finance companion! ║\n");
    printf("╚══════════════════════════════════╝\n");

    while (1)
    {
        printf("\n");
        printf("╔══════════════════════════════════╗\n");
        printf("║∘₊✧───────✧₊ Home Menu ₊✧──────✧₊∘║\n");
        printf("║ 1. Register User                 ║\n");
        printf("║ 2. Login                         ║\n");
        printf("║ 3. Credits                       ║\n");
        printf("║ 4. Exit                          ║\n");
        printf("╚══════════════════════════════════╝\n");

        printf("\n");
        printf("Pick an option (1 - 4): ");
        scanf("%d", &option);
        printf("\n");

        if (option == 1)
        {
            if (total_user >= max_user)
            {
                printf("Maximum user limit reached!\n");
                return 0;
            }

            file4 = fopen("User_Info.txt", "r");
            if (file4 != 0)
            {
                total_user = 0;

                while (fscanf(file4, "%s\n%s\n", user[total_user].username, user[total_user].password) == 2)
                {
                    total_user++;
                    if (total_user >= max_user)
                    {
                        break;
                    }
                }
                fclose(file4);
            }
            printf("ENTER YOUR USERNAME: ");
            scanf("%s", new_user.username);

            for (i = 0; i < total_user; i++)
            {
                if (strcmp(user[i].username, new_user.username) == 0)
                {
                    printf("USER ALREADY EXISTS!\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    getchar();
                    clear_screen();
                    continue;
                }
            }

            printf("ENTER YOUR PASSWORD: ");
            scanf("%s", new_user.password);
            user[total_user++] = new_user;
            printf("\n");
            printf("USER REGISTERED SUCCESSFULLY!\n");
            save_user();
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            clear_screen();
        }

        if (option == 2)
        {
            char entered_username[max_user];
            char entered_password[max_user];

            printf("ENTER YOUR USERNAME: ");
            scanf("%s", entered_username);

            printf("ENTER YOUR PASSWORD: ");
            scanf("%s", entered_password);

            file4 = fopen("User_Info.txt", "r");

            int login_success = 0;

            while (fscanf(file4, "%s %s", user[total_user].username, user[total_user].password) == 2)
            {
                if (strcmp(user[total_user].username, entered_username) == 0 && strcmp(user[total_user].password, entered_password) == 0)
                {
                    printf("\n");
                    printf("Login Successful!\n");
                    printf("\nPress Enter to continue...");
                    getchar();
                    getchar();
                    clear_screen();
                    login_success = 1;
                    strcpy(new_user.username, entered_username);

                    while (1)
                    {
                        printf("╔══════════════════════════════════╗\n");
                        printf("║∘₊✧──────✧₊ Budget Menu ₊✧─────✧₊∘║\n");
                        printf("║ 1. Add Income                    ║\n");
                        printf("║ 2. Add Expenses                  ║\n");
                        printf("║ 3. Net Worth                     ║\n");
                        printf("║ 4. Logout                        ║\n");
                        printf("╚══════════════════════════════════╝\n");

                        printf("\n");
                        printf("Pick an option (1 - 4): ");
                        scanf("%d", &option);

                        if (option == 1)
                        {
                            clear_screen();
                            printf("How many deposits do you want to make: ");
                            scanf("%d", &number);
                            printf("\n");

                            add_income();
                        }

                        if (option == 2)
                        {
                            clear_screen();
                            printf("How many transactions do you want to record: ");
                            scanf("%d", &number);
                            printf("\n");

                            add_expense();
                        }

                        if (option == 3)
                        {
                            clear_screen();
                            printf("\n");
                            read_balance();
                            printf("NET WORTH: %.2lfTaka\n", new_user.balance);
                            printf("\nPress Enter to continue...");
                            getchar();
                            getchar();
                            clear_screen();
                        }

                        if (option == 4)
                        {
                            printf("\n");
                            printf("Logged out successfully!\n");
                            printf("\nPress Enter to continue...");
                            getchar();
                            getchar();
                            clear_screen();
                            break;
                        }
                    }
                    break;
                }
                total_user++;
            }

            if (login_success == 0)
            {
                printf("\n");
                printf("Invalid username or password!\n");
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                clear_screen();
            }

            fclose(file4);
        }

        if (option == 3)
        {
            clear_screen();
            printf("╔════════════════════════════════════════════════════════════════╗\n");
            printf("║                          Created by:                           ║\n");
            printf("║                                                                ║\n");
            printf("║   Name: Mohammad Ishfaqul Islam   ID: C243021   Section: 1AM   ║\n");
            printf("║   Name: Shajidul Hoque Galib      ID: C243105   Section: 1AM   ║\n");
            printf("║   Name: Sayeed Mohammad Omar      ID: C243004   Section: 1AM   ║\n");
            printf("║                                                                ║\n");
            printf("╚════════════════════════════════════════════════════════════════╝\n");
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            clear_screen();
        }

        if (option == 4)
        {
            clear_screen();
            printf("Thank You For Using Budget Buddy!\n");
            printf("\n");
            break;
        }
    }

    return 0;
}