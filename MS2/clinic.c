/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, count = 0;
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            count++;
        }
    }
    printf("\n");
    if (count == 0)
    {
        printf("*** No records found ***");
    }
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{

    int selectionnumber = -1;
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selectionnumber = inputIntRange(0, 2);
        printf("\n");
        switch (selectionnumber)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
            break;
        }
    } while (selectionnumber != 0);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int i = 0, j = 0, counter = 0, patientaddnumber = -1;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            if (counter == 0)
            {
                counter++;
                j = i;
            }
        }
    }
    if (counter == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patientaddnumber = nextPatientNumber(patient, max);
        patient[j].patientNumber = patientaddnumber;
        inputPatient(&patient[j]);
        printf("*** New patient record added ***\n\n");
    }

}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int editnumber = -1, i = -1;
    printf("Enter the patient number: ");
    editnumber = inputIntPositive();
    i = findPatientIndexByPatientNum(editnumber, patient, max);
    if (i > -1)
    {
        putchar('\n');
        menuPatientEdit(&patient[i]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    int patientindex = -1, i = -1;
    char response = 'a';
    printf("Enter the patient number: ");
    patientindex = inputIntPositive();
    printf("\n");
    i = findPatientIndexByPatientNum(patientindex, patient, max);
    if (i > -1)
    {
        displayPatientData(&patient[i], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &response);
        clearInputBuffer();
        if (response == 'y')
        {
            patient[i].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int i = -1, search = -1;
    printf("Search by patient number: ");
    search = inputIntPositive();
    putchar('\n');
    i = findPatientIndexByPatientNum(search, patient, max);
    if (i > -1)
    {
        displayPatientData(&patient[i], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int count = 0, i = -1, searchnumber = 0;
    char Patientphonenumber[10] = { '\0' };
    printf("Search by phone number: ");
    scanf("%s", Patientphonenumber);
    clearInputBuffer();
    for (i = 0; i < max; i++)
    {
        if (strcmp(Patientphonenumber, patient[i].phone.number) == 0)
        {
            searchnumber = i;
            count++;
        }
    }
    if (count == 0)
    {
        printf("\n");
        displayPatientTableHeader();
        printf("\n*** No records found ***\n");
    }
    else if (count > 1)
    {
        printf("\n");
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
            if (strcmp(Patientphonenumber, patient[i].phone.number) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    else
    {
        printf("\n");
        displayPatientTableHeader();
        displayPatientData(&patient[searchnumber], FMT_TABLE);
    }
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i = 0;
    int next = patient[i].patientNumber;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > next)
        {
            next = patient[i].patientNumber;
        }
    }
    next = next + 1;
    return next;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, index = -1;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            index = i;
        }
    }
    return index;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
    int input;
    char phonenumber[PHONE_LEN] = { '\0' };
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    input = inputIntRange(1, 4);
    putchar('\n');
    switch (input)
    {
    case 1:
    {
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        break;
    }
    case 2:
    {
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        break;
    }
    case 3:
    {
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        break;
    }
    case 4:
    {
        strcpy(phone->description, "TBD");
        *phone->number = 0;
        break;
    }
    }
    if (input == 1 || input == 2 || input == 3)
    {
        printf("Number : ");
        inputCString(phonenumber, 1, PHONE_LEN);
        strcpy(phone->number, phonenumber);
        putchar('\n');
    }

}
