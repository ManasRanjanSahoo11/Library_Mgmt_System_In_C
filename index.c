#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct book
{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

struct student
{
    int sRoll;
    char sName[30];
    char sBranch[30];
    char bookName[30];
    char date[20];
} s;

struct time
{
    int day;
    int month;
    int year;
};

FILE *fp;

void addBook();
void removeBook();
void viewBookList();
void issueBook();
void issueBookList();

int main()
{
    printf("##########################################################\n");
    printf("##########################################################\n");
    printf("########                                          ########\n");
    printf("########  Library Management System Project In C  ########\n");
    printf("########                                          ########\n");
    printf("##########################################################\n");
    printf("##########################################################\n");
    printf("\n\n\n");

    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
    printf("**************************************************************\n");
    printf("*                                                            *\n");
    printf("*                                                            *\n");
    printf("*                        WELCOME                             *\n");
    printf("*                          TO                                *\n");
    printf("*                        LIBRARY                             *\n");
    printf("*                       MANAGEMENT                           *\n");
    printf("*                         SYSTEM                             *\n");
    printf("*                                                            *\n");
    printf("*                                                            *\n");
    printf("**************************************************************\n\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n\n");

    printf("Press any key to continue...\n");
    getch();

    int choice;
    while (1)
    {
        printf("\n");
        printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
        printf("**_                     MAIN MENU                          _**\n");
        printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
        printf("1. Add Book \n");
        printf("2. Remove Book \n");
        printf("3. View Book List \n");
        printf("4. Issue Book \n");
        printf("5. View Issued Book List\n");
        printf("0. Exit \n\n");

        printf("Enter Your Choice :\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            viewBookList();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            issueBookList();
            break;
        case 0:
            exit(0);

        default:
            printf("Invalid choice!");
        }
    }

    return 0;
}

void addBook()
{
    printf("\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
    printf("**_                     ADD BOOK                           _**\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
    fp = fopen("mybook.txt", "ab");
    if (fp == NULL)
    {
        printf("File not Found");
        exit(1);
    }

    printf("Enter Book id :\n");
    scanf("%d", &b.id);
    printf("Enter Book Name :\n");
    fflush(stdin);
    gets(b.bookName);
    printf("Enter Author Name :\n");
    fflush(stdin);
    gets(b.authorName);

    char mydate[12];
    time_t cur_time; // for to get current time
    struct tm *lt;   // create structure pointer variable. (lt=localtime)
    time(&cur_time);
    lt = localtime(&cur_time);

    struct time cur_date;
    cur_date.day = lt->tm_mday;
    cur_date.month = lt->tm_mon + 1;    // month is 0-based, so add +1.
    cur_date.year = lt->tm_year + 1900; // years sinces 1900
    sprintf(mydate, "%02d/%02d/%d", cur_date.day, cur_date.month, cur_date.year);
    strcpy(b.date, mydate);

    fprintf(fp, "%d %s %s %s\n", b.id, b.bookName, b.authorName, b.date);
    fclose(fp);

    printf("\nBook Added Sucessfully !\n");

    printf("\npress any key to continue...\n");
    getch();
    return;
}

void removeBook()
{
    printf("\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
    printf("**_                     REMOVE BOOK                        _**\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
    int id, flag = 0;
    printf("Enter Book Id to remove the book:\n");
    scanf("%d", &id);

    FILE *tempFile;

    fp = fopen("mybook.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %s %s", &b.id, b.bookName, b.authorName, b.date) == 4)
    {
        if (id == b.id)
        {
            flag = 1;
            printf("Book deleted successfully...\n");
        }
        else
        {
            fprintf(tempFile, "%d %s %s %s\n", b.id, b.bookName, b.authorName, b.date);
        }
    }

    if (flag == 0)
    {
        printf("Book not found...\n");
    }

    fclose(fp);
    fclose(tempFile);

    remove("mybook.txt");
    rename("temp.txt", "mybook.txt");

    printf("\nPress any key to continue...\n");
    getch();
    return;
}

void viewBookList()
{
    printf("\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
    printf("**_                   VIEW BOOK LIST                       _**\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
    fp = fopen("mybook.txt", "r");
    if (fp == NULL)
    {
        printf("File not Found");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s %s", &b.id, b.bookName, b.authorName, b.date) == 4)
    {
        printf(" %d\t%s\t%s\t%s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);

    printf("\npress any key to continue...\n");
    getch();
    return;
}

void issueBook()
{
    printf("\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
    printf("**_                     ISSUE BOOK                         _**\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");

    fp = fopen("issued.txt", "ab");
    if (fp == NULL)
    {
        printf("File not Found");
        exit(1);
    }

    printf("Enter Roll Number :\n");
    scanf("%d", &s.sRoll);
    printf("Enter student name :\n");
    fflush(stdin);
    gets(s.sName);
    printf("Enter student branch :\n");
    fflush(stdin);
    gets(s.sBranch);
    printf("Enter book name :\n");
    fflush(stdin);
    gets(s.bookName);

    char mydate[12];
    time_t cur_time; // for to get current time
    struct tm *lt;   // create structure pointer variable. (lt=localtime)
    time(&cur_time);
    lt = localtime(&cur_time);

    struct time cur_date;
    cur_date.day = lt->tm_mday;
    cur_date.month = lt->tm_mon + 1;    // month is 0-based, so add +1.
    cur_date.year = lt->tm_year + 1900; // years sinces 1900
    sprintf(mydate, "%02d/%02d/%d", cur_date.day, cur_date.month, cur_date.year);
    strcpy(s.date, mydate);

    fprintf(fp, "%d %s %s %s %s\n", s.sRoll, s.sName, s.sBranch, s.bookName, s.date);
    fclose(fp);

    printf("Book issued sucessfully...");

    printf("\n\npress any key to continue...\n");
    getch();
    return;
}

void issueBookList()
{
    printf("\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n");
    printf("**_             VIEW ISSUE BOOK LIST                       _**\n");
    printf("**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**\n\n");
    fp = fopen("issued.txt", "r");
    if (fp == NULL)
    {
        printf("File not found!");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s %s %s\n", &s.sRoll, s.sName, s.sBranch, s.bookName, s.date) == 5)
    {
        printf("%d %s %s %s %s\n", s.sRoll, s.sName, s.sBranch, s.bookName, s.date);
    }

    fclose(fp);

    printf("\npress any key to continue...\n");
    getch();
    return;
}