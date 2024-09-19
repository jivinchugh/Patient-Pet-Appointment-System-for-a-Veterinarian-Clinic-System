/*
*****************************************************************************
						Assignment 1 - Milestone 1
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

#include <stdio.h>
#include "core.h"
#define CRT_SECURE_NO_WARNINGS

void clearInputBuffer(void) 
{ // Discard all remaining char's from the standard input buffer: 
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
int inputInt(void)
{
	char newLine = 'x';
	int value = 0;

	scanf("%d%c", &value, &newLine);
	if (newLine == '\n')
	{
		return value;
	}
	else
	{
		clearInputBuffer();
		printf("Error! Input a whole number: ");
		do
		{
			scanf("%d%c", &value, &newLine);
			if (newLine != '\n')
			{
				clearInputBuffer();
			}
		} while (newLine != '\n');
		return value;
	}
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
	int value, value2;
	char newline = 'x';
	do
	{
		scanf(" %d%c", &value, &newline);
		if (newline == '\n' && (value % 2 == 0 || value % 2 == 1))
			value2 = value;
		else
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (newline != '\n' && (value % 2 == 0 || value % 2 == 1));
	if (value2 >= lowerbound && value2 <= upperbound)
		return value2;
	else
	{
		do
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerbound, upperbound);
			scanf("%d", &value2);
		} while (value2 < lowerbound || value2 > upperbound);
		return value2;
	}
}

char inputCharOption(const char* newstring)
{
	char newchar = '\0';
	char result = '\0';
	int i = 0, j = 0, loop = 1;
	for (j = 1; newstring[j]; j++)
		; // find the length of string using iteration
	do
	{
		scanf("%c%c", &result, &newchar);

		if (newchar == '\n')
		{
			for (i = 0; i < j && loop; i++)
			{
				if (newstring[i] == result)
					loop = 0;
			}
		}
	} while (loop && printf("ERROR: Character must be one of [%s]: ", newstring));
	return result;
}

void inputCString(char* stringvar, int min, int max)
{
	char arrayvariable[999] = { '\0' };
	int flag = 0, i = 0, j = 0;
	do
	{
		scanf("%99[^\n]%*c", arrayvariable);
		for (i = 1; arrayvariable[i]; i++)
			; // this will calculate the length of the string that is required
		if (min == max)
		{
			if (i == min)
			{
				for (j = 0; arrayvariable[j]; stringvar[j] = arrayvariable[j], j++)
					;
				stringvar[j] = '\0';
				flag = 1;
			}
		}
		else
		{
			if (i >= min && i <= max)
			{
				for (j = 0; arrayvariable[j]; stringvar[j] = arrayvariable[j], j++)
					;
				stringvar[j] = '\0';
				flag = 1;
			}
		}
		if (!flag)
		{
			if (min == max)
			{
				printf("ERROR: String length must be exactly %d chars: ", min);
			}
			else if (min == 0 || i > max)
			{
				printf("ERROR: String length must be no more than %d chars: ", max);
			}
			else
			{
				printf("ERROR: String length must be between %d and %d chars: ", min, max);
			}
		}

	} while (!flag);
}

void displayFormattedPhone(char* phonenumber)
{
	int flag = 1, i = 0, rightsize = 10;
	if (phonenumber != NULL)
	{
		for (i = 0; phonenumber[i] && flag; i++)
		{
			if (phonenumber[i] < 48 || phonenumber[i] > 57) //ASCII values for 0 and 9
			{
				flag = 0;
			}
		}
	}
	if (flag && i == rightsize)
	{
		printf("(");
		for (i = 0; i < 3; i++)
		{
			printf("%c", phonenumber[i]);
		}
		printf(")");
		for (i = 3; i < 6; i++)
		{
			printf("%c", phonenumber[i]);
		}
		printf("-");
		for (i = 6; i < rightsize; i++)
		{
			printf("%c", phonenumber[i]);
		}
	}
	else
	{
		printf("(___)___-____");
	}
}