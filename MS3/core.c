/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Jivin Chugh
Student ID#: 156056210
Email      : jchugh@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
int inputInt(void)
{
    char newLine = 'x';
    int value;

    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    } while (newLine != '\n');
    return value;
}

int inputIntPositive(void)
{
    int value = 0;
    do
    {
        value = inputInt();
        if (value < 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value < 0);
    return value;
}

int inputIntRange(int lowerbound, int upperbound)
{
    int value2 = lowerbound - 1;
    do
    {
        value2 = inputInt();
        if (value2<lowerbound || value2>upperbound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerbound, upperbound);
        }
    } while (value2<lowerbound || value2>upperbound);
    return value2;
}

char inputCharOption(char newstring[7])
{
    char input, newLine;
    int i, flag;
    do
    {
        flag = 0;
        scanf("%c%c", &input, &newLine);
        if (newLine == '\n')
        {
            for (i = 0; i < 7; i++)
            {
                if (input == newstring[i])
                {
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                printf("ERROR: Character must be one of [%s]: ", newstring);
            }
        }
    } while (flag == 0);
    return input;
}
void inputCString(char* stringvar, int min, int max)
{
    char resultstr[100];
    while (1) 
    {
        scanf(" %[^\n]%*c", resultstr);
        if (min == max)
        {
            if (strlen(resultstr) != min) 
            {
                printf("Invalid %d-digit number! Number: ", min);
            }
            else 
            {
                break;
            }
        }
        else 
        {
            if (strlen(resultstr) > max) 
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else if (strlen(resultstr) < min) 
            {
                printf("Error! String length must be between %d and %d chars: ", min, max);
            }
            else
            {
                break;
            }
        }
    }
    strcpy(stringvar, resultstr);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

void displayFormattedPhone(const char* phonenumber)
{
    int flag = 0;
    int i = 0;

    if (phonenumber != NULL)
    {
        for (i = 0; phonenumber[i]; i++)
        {

            if (phonenumber[i] < 48 || phonenumber[i] > 57)//ASCII CODE VALUES OF 0-9
            {
                flag = 1;
            }
        }
    }
    if (flag == 0 && i == 10)
    {
        printf("(");
        for (i = 0; i < 3; i++)
            printf("%c", phonenumber[i]);
        printf(")");
        for (i = 3; i < 6; i++)
            printf("%c", phonenumber[i]);
        printf("-");
        for (i = 6; i < 10; i++)
            printf("%c", phonenumber[i]);
    }
    else
    {
        printf("(___)___-____");
    }
}



