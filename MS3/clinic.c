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
#include <stdlib.h>
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientindex, i = -1;
    char response = 'a';
    printf("Enter the patient number: ");
    patientindex = inputIntPositive();
    printf("\n");
    i = findPatientIndexByPatientNum(patientindex, patient, max);
    if (i != -1)
    {
        displayPatientData(&patient[i], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        response = inputCharOption("yn");
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


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    struct Appointment* num = (struct Appointment*)calloc(data->maxAppointments, sizeof(struct Appointment));
    for (i = 0; i < data->maxAppointments; i++)
    {
        num[i].patientNumber = data->appointments[i].patientNumber;
        num[i].date = data->appointments[i].date;
        num[i].time = data->appointments[i].time;
    }
    sortingdata(num, data->maxAppointments);
    displayScheduleTableHeader(&(num->date), 1);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (num[i].patientNumber != 0)
        {
            int index = findPatientIndexByPatientNum(num[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &num[i], 1);
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int year, month, day, i;
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (%d-%d): ",MIN_MONTHS,MAX_MONTHS);
    month = inputIntRange(MIN_MONTHS, MAX_MONTHS);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (%d-%d)  : ",MIN_DAYS,NORMALMONTH);
        day = inputIntRange(MIN_DAYS, NORMALMONTH);
    }
    else
    {
        printf("Day (%d-%d)  : ",MIN_DAYS , LEAPMONTH);
        day = inputIntRange(MIN_MONTHS, LEAPMONTH);
    }
    putchar('\n');
    struct Date enter_date;
    enter_date.year = year;
    enter_date.month = month;
    enter_date.day = day;
    displayScheduleTableHeader(&enter_date, 0);
    struct Appointment* appoint = (struct Appointment*)calloc(data->maxAppointments, sizeof(struct Appointment));
    for (i = 0; i < data->maxAppointments; i++)
    {
        appoint[i].patientNumber = data->appointments[i].patientNumber;
        appoint[i].date = data->appointments[i].date;
        appoint[i].time = data->appointments[i].time;
    }
    sortingdata(appoint, data->maxAppointments);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (appoint[i].patientNumber != 0 && appoint[i].date.year == enter_date.year && appoint[i].date.month == enter_date.month && appoint[i].date.day == enter_date.day)
        {
            int num = findPatientIndexByPatientNum(appoint[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[num], &appoint[i], 0);
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
// Todo:

void addAppointment(struct Appointment* appoint, int maxappointments, struct Patient* patients, int maxpatients)
{
    int patientnumber, year, month, day, hour, min, input, num, i;
    int flag = 0;
    int no_space = 1;
    for (i = 0; i < maxappointments; i++)
    {
        if (appoint[i].patientNumber < 1)
        {
            no_space = 0;
            break;
        }
    }
    if (no_space == 1)
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
        return;
    }
    printf("Patient Number: ");
    patientnumber = inputIntPositive();
    num = findPatientIndexByPatientNum(patientnumber, patients, maxpatients);
    if (num == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        return;
    }
    while (1)
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (%d-%d): ",MIN_MONTHS,MAX_MONTHS);
        month = inputIntRange(MIN_MONTHS, MAX_MONTHS);
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            printf("Day (%d-%d)  : ",MIN_DAYS,NORMALMONTH);
            day = inputIntRange(MIN_DAYS, NORMALMONTH);
        }
        else
        {
            printf("Day (%d-31)  : ",MIN_DAYS);
            day = inputIntRange(MIN_DAYS, LEAPMONTH);
        }
        printf("Hour (%d-23)  : ",MIN_MINS);
        hour = inputIntRange(MIN_MINS, 23);
        printf("Minute (%d-%d): ",MIN_MINS,MAX_MINS);
        min = inputIntRange(MIN_MINS, MAX_MINS);
        for (i = 0; i < maxappointments; i++)
        {
            if (appoint[i].date.year == year && appoint[i].date.month == month && appoint[i].date.day == day && appoint[i].time.hour == hour && appoint[i].time.min == min)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
                flag = 0;
                break;
            }
            flag = 1;
        }
        if (flag == 0)
        {
            continue;
        }
        while (1)
        {
            input = hour * 60 + min;
            if (input % HALFHOUR != 0 || input < FIRSTHOUR * 60 + START_MIN || input > END_HOUR * 60 + END_MIN)
            {
                printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n\n", FIRSTHOUR, START_MIN, END_HOUR, END_MIN, HALFHOUR);
                printf("Hour (%d-23)  : ",MIN_MINS);
                hour = inputIntRange(0, 23);
                printf("Minute (%d-%d): ",MIN_MINS, MAX_MINS);
                min = inputIntRange(0, MAX_MINS);
                flag = 0;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
    for (i = 0; i < maxappointments; i++)
    {
        if (appoint[i].patientNumber < 1)
        {
            appoint[i].patientNumber = patientnumber;
            appoint[i].date.year = year;
            appoint[i].date.month = month;
            appoint[i].date.day = day;
            appoint[i].time.hour = hour;
            appoint[i].time.min = min;
            break;
        }
    }
    printf("\n*** Appointment scheduled! ***\n");
    printf("\n");
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoint, int maxappointments, struct Patient* patients, int maxpatients)
{
    int i, patient_Num, year, month, day;
    char response;
    printf("Patient Number: ");
    patient_Num = inputIntPositive();

    int num = findPatientIndexByPatientNum(patient_Num, patients, maxpatients);
    if (num == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        return;
    }
    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (%d-%d): ",MIN_MONTHS,MAX_MONTHS);
    month = inputIntRange(MIN_MONTHS, MAX_MONTHS);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        printf("Day (%d-%d)  : ",MIN_DAYS, NORMALMONTH);
        day = inputIntRange(MIN_DAYS, NORMALMONTH);
    }
    else
    {
        printf("Day (%d-%d)  : ",MIN_DAYS, NORMALMONTH);
        day = inputIntRange(MIN_DAYS, LEAPMONTH);
    }

    printf("\n");

    printf("Name  : %s\n", patients[num].name);
    printf("Number: %05d\n", patients[num].patientNumber);
    printf("Phone : ");
    displayFormattedPhone(patients[num].phone.number);
    printf(" (%s)\n", patients[num].phone.description);
    printf("Are you sure you want to remove this appointment (y,n): ");
    response = inputCharOption("yn");
    if (response == 'n')
    {
        printf("Operation aborted.\n");
    }
    else
    {
        for (i = 0; i < maxappointments; i++)
        {
            if (appoint[i].patientNumber == patient_Num && appoint[i].date.year == year && appoint[i].date.month == month && appoint[i].date.day == day)
            {
                appoint[i].patientNumber = 0;
                break;
            }
        }
        printf("\nAppointment record has been removed!\n");
    }
    printf("\n");
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
        inputCString(phonenumber, 10, PHONE_LEN);
        strcpy(phone->number, phonenumber);
        putchar('\n');
    }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    FILE* givendata;
    givendata = fopen(datafile, "r");
    while (fscanf(givendata, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
    {
        i++;
        if (i >= max) 
        {
            break;
        }
    }
    fclose(givendata);
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE* givendata;
    givendata = fopen(datafile, "r");
    if (givendata != NULL) 
    {
        while (fscanf(givendata, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF) 
        {
            i++;
            if (i >= max) 
            {
                break;
            }
        }
    }
    return i;
}

void swapping(struct Appointment* app1, struct Appointment* app2)
{
    struct Appointment temp = *app1;
    *app1 = *app2;
    *app2 = temp;
}

void sortingdata(struct Appointment array[], int number)
{
    int i, j;
    for (i = 0; i < number - 1; i++)
    {
        for (j = 0; j < number - i - 1; j++)
        {
            long long data1 = array[j].date.year * 12 * 30 * 24 * 60 + array[j].date.month * 30 * 24 * 60 + array[j].date.day * 24 * 60 + array[j].time.hour * 60 + array[j].time.min;
            long long data2 = array[j + 1].date.year * 12 * 30 * 24 * 60 + array[j + 1].date.month * 30 * 24 * 60 + array[j + 1].date.day * 24 * 60 + array[j + 1].time.hour * 60 + array[j + 1].time.min;
            if (data1 > data2)
            {
                swapping(&array[j], &array[j + 1]);
            }
        }
    }
}
