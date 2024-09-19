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
#pragma once

// Clear the standard input buffer 
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue 
void suspend(void);

int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int lowerbound, int upperbound);

char inputCharOption(const char* newstring);

void inputCString(char* stringvar, int min, int max);

void displayFormattedPhone(char* phonenumber);
