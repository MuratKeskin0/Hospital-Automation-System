#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/patient.h"
#include "../src/patient.c"
#include "../include/doctor.h"
#include "../src/doctor.c"
#include "../include/appointment.h"
#include "../src/appointment.c"
#include "../include/visit.h"
#include "../src/database.c"
#include "../Colors/color.c"
void defaultInformation();
int Display();
int AdminMenu();


int main()
{
    defaultInformation();
    readAllData();
    setAllIdNumbers();
    Display();

    return 0;
}

int Display()
{
    int userType;

    printf("Welcome to the Hospital Management System!\n");
    printf("1. Admin or Patient\n");
    printf("2. Doctor\n");
    printf("3. Exit \n");
    printf("Enter user type (1 for Admin or Patient, 2 for Doctor): ");
    scanf("%d", &userType);

    switch (userType)
    {
    case 1:
        printf("Patient or Admin Menu:\n");
        Patient *account;
        int option;
        int isLoggedIn = 0;

        int newType;
        Date newDate;
        int newConfirmed;
        char newNameDoctor[MAX];
        char newSurnameDoctor[MAX];
        char newSpecialization[MAX];
        char newUsername[MAX];
        char newPasswordDoctor[MAX];
        char newFirstNamePatientt[MAX];
        char newLastNamePatient[MAX];
        int newAge;
        char newGender[MAX];
        char newPasswordPatient[MAX];
        char newPhoneNumber[MAX];

        while (true)
        {
            if (isLoggedIn && account->isAdmin)
            {

                Color_Green();
                printf("\n--------- Welcome Admin --- %s -- %s ---------\n", account->firstName, account->lastName);
                Color_Reset();

                printf("1- Show All Appointments\n");
                printf("2- Update Appointment\n");
                printf("3- Delete Appointment\n");
                printf("4- View Doctors\n");
                printf("5- Update Doctor\n");
                printf("6- Delete Doctor\n");
                printf("7- Add New Doctor\n");
                printf("8- View Patients\n");
                printf("9- Update Patients\n");
                printf("10- Delete Patient\n");
                printf("11- Add New Patient\n");
                printf("12- Total Number of All Appointments\n");
                printf("13- Create Appointments\n");
                printf("14- Change the statue of an Appointment\n");
                printf("15- Logout\n");

                Color_White();
                printf("\nSelect an option : ");
                Color_Reset();

                int choice;
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    showAllAppointments();
                    break;
                case 2:
                    showAllAppointments();
                    Color_White();
                    printf("Please write the ID of the Appointment you want to update :");
                    scanf("%d", &option);
                    Color_Reset();

                    printf("Enter the new type (0 for VISIT_TYPE_CONSULTATION, 1 for VISIT_TYPE_GENERAL): ");
                    int isValidTypeInput = 0;
                    do
                    {
                        scanf("%d", &newType);
                        if (newType == VISIT_TYPE_CONSULTATION || newType == VISIT_TYPE_GENERAL)
                        {
                            isValidTypeInput = 1;
                        }
                        else
                        {
                            printf("Invalid type! Please enter 0 for GENERAL_CHECKUP or 1 for SURGERY: ");
                        }
                    } while (!isValidTypeInput);

                    printf("Enter the new date (day month year): ");
                    scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);

                    printf("Enter the new confirmation status (0 for No, 1 for Yes): ");
                    scanf("%d", &newConfirmed);

                    updateAppointmentInformation(option, newType, newDate, newConfirmed);
                    Color_Green();
                    printf("\nTopic has been updated successfully\n");
                    Color_Reset();
                    break;

                case 3:
                    showAllAppointments();
                    Color_White();
                    printf("\nPlease write the ID of the Appointment you want to delete :");

                    scanf("%d", &option);
                    Color_Reset();
                    deleteAppointment(option);
                    break;

                case 4:
                    showAllDoctors();
                    break;
                case 5:
                    showAllDoctors();
                    Color_White();
                    printf("Please write the ID of the Doctor you want to update :");
                    scanf("%d", &option);
                    Color_Reset();

                    printf("Enter the new first name ");
                    scanf("%s", &newNameDoctor);

                    printf("Enter the new surname ");
                    scanf("%s", &newSurnameDoctor);

                    printf("Enter the new specialization ");
                    scanf("%s", &newSpecialization);

                    printf("Enter the new username ");
                    scanf("%s", &newUsername);

                    printf("Enter the new password ");
                    scanf("%s", &newPasswordDoctor);

                    updateDoctorInformation(option, newNameDoctor, newSurnameDoctor, newSpecialization, newUsername, newPasswordDoctor);
                    Color_Green();
                    printf("\nDoctor has been updated successfully\n");
                    Color_Reset();
                    break;

                case 6:
                    showAllDoctors();
                    Color_White();
                    printf("\nPlease write the ID of the Doctor you want to delete :");

                    scanf("%d", &option);
                    Color_Reset();

                    deleteAppointmentsByDoctor(option);
                    deleteDoctor(option);
                    break;

                case 7:
                    Color_White();
                    printf("\nEnter your firstname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newNameDoctor);

                    Color_White();
                    printf("Enter your lastname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newSurnameDoctor);

                    Color_White();
                    printf("Enter your specialization: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newSpecialization);

                    Color_White();
                    printf("Enter your gender: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newGender);

                    Color_White();
                    printf("Enter your username: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newUsername);

                    bool usernameExists = false;
                    for (int i = 0; i < doctorCount; i++)
                    {
                        if (strcmp(doctors[i].username, newUsername) == 0)
                        {
                            usernameExists = true;
                            break;
                        }
                    }

                    if (usernameExists)
                    {
                        Color_Red();
                        printf("Username already exists. Please choose a different username.\n");
                        Color_Reset();
                        break;
                    }

                    Color_White();
                    printf("Enter your password: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newPasswordDoctor);

                    createDoctor(doctorID, newNameDoctor, newSurnameDoctor, newSpecialization, newGender, newPasswordDoctor);
                    Color_Green();
                    printf("\nDoctor created successfully!\n\n");
                    Color_Green();
                    doctorID++;
                    break;

                case 8:
                    showAllPatients();
                    break;
                case 9:
                    showAllPatients();
                    Color_White();
                    printf("Please write the ID of the Patient you want to update :");
                    scanf("%d", &option);
                    Color_Reset();

                    printf("Enter the new first name ");
                    scanf("%s", &newFirstNamePatientt);

                    printf("Enter the new surname ");
                    scanf("%s", &newLastNamePatient);

                    printf("Enter the new age ");
                    scanf("%d", &newAge);

                    printf("Enter the new gender ");
                    scanf("%s", &newGender);

                    printf("Enter the new phoneNumber ");
                    scanf("%s", &newPhoneNumber);

                    printf("Enter the new password ");
                    scanf("%s", &newPasswordPatient);

                    updatePatientInformation(option, newFirstNamePatientt, newLastNamePatient, newAge, newGender, newPhoneNumber, newPasswordPatient, 0);
                    Color_Green();
                    printf("\nPatient has been updated successfully\n");
                    Color_Reset();
                    break;
                case 10:
                    showAllPatients();
                    Color_White();
                    printf("\nPlease write the ID of the Patient you want to delete :");

                    scanf("%d", &option);
                    Color_Reset();

                    deleteAppointmentsByPatient(option);
                    deletePatient(option);
                    break;
                case 11:
                    Color_White();
                    printf("\nEnter your firstname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newFirstNamePatientt);

                    Color_White();
                    printf("Enter your lastname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newLastNamePatient);

                    Color_White();
                    printf("Enter your age: ");
                    Color_Reset();
                    fflush(stdin);
                    scanf("%d", &newAge);

                    Color_White();
                    printf("Enter your gender: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newGender);

                    Color_White();
                    printf("Enter your phonenumber: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newPhoneNumber);

                    bool phoneNumberExists = false;
                    for (int i = 0; i < patientCount; i++)
                    {
                        if (strcmp(patients[i].phoneNumber, newPhoneNumber) == 0)
                        {
                            phoneNumberExists = true;
                            break;
                        }
                    }

                    if (phoneNumberExists)
                    {
                        Color_Red();
                        printf("Phone number already exists. Please enter a different phone number.\n");
                        Color_Reset();
                        break;
                    }

                    Color_White();
                    printf("Enter your password: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newPasswordPatient);

                    createPatient(patientID, newFirstNamePatientt, newLastNamePatient, newAge, newGender, newPhoneNumber, newPasswordPatient, 0);
                    printf("\nAccount created successfully!\n\n");
                    Color_Green();
                    patientID++;
                    break;

                case 12:
                {
                    int totalAppointments = getTotalNumberOfAppointments();
                    if (totalAppointments >= 0)
                    {
                        Color_Green();
                        printf("Total number of appointments: %d\n", totalAppointments);
                        Color_Reset();
                    }
                    else
                    {
                        Color_Red();
                        printf("Unable to determine the total number of appointments.\n");
                        Color_Reset();
                    }
                }
                break;
                case 13:
                    Color_White();
                    showAllDoctors();
                    int selectedDoctorID;
                    int selectedPatientID;

                    if (doctorCount == 0)
                    {
                        printf("No doctors available.\n");
                        Color_Reset();
                        break;
                    }

                    printf("Enter the ID of the doctor you want to choose: ");
                    Color_Reset();
                    scanf("%d", &selectedDoctorID);

                    int selectedDoctorIndex = -1;
                    for (int i = 0; i < doctorCount; i++)
                    {
                        if (doctors[i].id == selectedDoctorID)
                        {
                            selectedDoctorIndex = i;
                            break;
                        }
                    }

                    if (selectedDoctorIndex == -1)
                    {
                        printf("Invalid doctor ID. Appointment creation failed.\n");
                        break;
                    }

                    showAllPatients();
                    if (patientCount == 0)
                    {
                        printf("No patients available.\n");
                        break;
                    }

                    printf("Enter the ID of the patient you want to choose: ");
                    Color_Reset();
                    scanf("%d", &selectedPatientID);

                    int selectedPatientIndex = -1;
                    for (int i = 0; i < patientCount; i++)
                    {
                        if (patients[i].id == selectedPatientID)
                        {
                            selectedPatientIndex = i;
                            break;
                        }
                    }

                    if (selectedPatientIndex == -1)
                    {
                        printf("Invalid patient ID. Appointment creation failed.\n");
                        break;
                    }
                    printf("Enter the type (0 for VISIT_TYPE_CONSULTATION, 1 for VISIT_TYPE_GENERAL): ");
                    int newType;
                    scanf("%d", &newType);
                    while (newType != VISIT_TYPE_CONSULTATION && newType != VISIT_TYPE_GENERAL)
                    {
                        printf("Invalid type! Please enter 0 for VISIT_TYPE_CONSULTATION or 1 for VISIT_TYPE_GENERAL: ");
                        scanf("%d", &newType);
                    }

                    printf("Enter the date (day month year): ");
                    Date newDate;
                    scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);

                    printf("Enter the confirmation status (0 for No, 1 for Yes): ");
                    int newConfirmed;
                    scanf("%d", &newConfirmed);

                    createAppointment(appointmentCount, &patients[selectedPatientIndex], &doctors[selectedDoctorIndex], newType, newDate, newConfirmed);
                    Color_Green();
                    printf("\nAppointment has been created successfully\n");
                    Color_Reset();
                    appointmentCount++;
                    break;
                case 14:
                    showAllAppointments();
                    Color_White();
                    printf("\nPlease write the ID of the Appointment you want to change its status: ");
                    Color_Reset();

                    int appointmentidd, newStatus;
                    scanf("%d", &appointmentidd);

                    printf("Enter the new confirmation status (0 for No, 1 for Yes): ");
                    scanf("%d", &newStatus);

                    int result = updateAppointmentConfirmation(appointmentidd, newStatus);
                    if (result == 0)
                    {
                        Color_Green();
                        printf("Appointment status updated successfully.\n");
                    }
                    else if (result == 2)
                    {
                        Color_Red();
                        printf("Appointment with the given ID not found.\n");
                    }
                    else
                    {
                        Color_Red();
                        printf("Error updating the appointment.\n");
                    }
                    Color_Reset();
                    break;

                case 15:
                    isLoggedIn = 0;
                    break;
                default:
                    Color_Red();
                    printf("\nInvalid option. Please select [1-12]\n");
                    Color_Reset();
                    while (getchar() != '\n')
                        ; // To prevent it from going into an infinite loop when I enter data of String type.
                    break;
                }
            }
            else if (isLoggedIn && !account->isAdmin)
            {
                int switchOption = 0;
                bool flag = 0;
                char newFirstName[30];
                char newLastName[30];
                char newPassword[30];
                int newAgePatient;
                char newGenderPatient[30];
                char newPhoneNumberPatient[30];

                Color_Green();
                printf("\n--------- Welcome %s -- %s---------\n", account->firstName, account->lastName);
                Color_Reset();

                printf("\n1- Show patient information\n");
                printf("2- Update patient information\n");
                printf("3- Create a new appointment\n");
                printf("4- View your appointments\n");
                printf("5- Delete your appointments\n");
                printf("6- Delete your account\n");
                printf("7- Logout\n");

                Color_White();
                fflush(stdin);
                printf("\nSelect an option : ");
                Color_Reset();
                scanf("%d", &switchOption);

                switch (switchOption)
                {
                case 1:
                    printf("\nFirst Name : %s\n", account->firstName);
                    printf("Last Name : %s\n", account->lastName);
                    printf("Age : %d\n", account->age);
                    printf("Gender : %s\n", account->gender);
                    printf("Phone Number : %s\n", account->phoneNumber);
                    printf("Password : %s\n", account->password);
                    break;
                case 2:
                    Color_White();
                    printf("\nPlease enter your First Name : ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newFirstName);

                    Color_White();
                    printf("Please enter your new Last Name : ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newLastName);

                    Color_White();
                    printf("Please enter your new Age : ");
                    Color_Reset();
                    fflush(stdin);
                    scanf("%d", &newAgePatient);

                    Color_White();
                    printf("Please enter your new Gender : ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newGenderPatient);

                    Color_White();
                    printf("Please enter your new phone number : ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newPhoneNumberPatient);

                    Color_White();
                    printf("Please enter your new password : ");
                    Color_Reset();
                    fflush(stdin);
                    gets(newPassword);

                    updatePatientInformation(account->id, newFirstName, newLastName, newAgePatient, newGenderPatient, newPhoneNumberPatient, newPassword, 0);
                    Color_Green();
                    printf("\nAccount updated successfully\n");
                    Color_Reset();
                    break;
                case 3:
                    Color_White();
                    showAllDoctors();
                    int selectedDoctorID;

                    if (doctorCount == 0)
                    {
                        printf("No doctors available.\n");
                        break;
                    }

                    printf("Enter the ID of the doctor you want to choose: ");
                    Color_Reset();
                    scanf("%d", &selectedDoctorID);

                    int selectedDoctorIndex = -1;
                    for (int i = 0; i < doctorCount; i++)
                    {
                        if (doctors[i].id == selectedDoctorID)
                        {
                            selectedDoctorIndex = i;
                            break;
                        }
                    }

                    if (selectedDoctorIndex == -1)
                    {
                        printf("Invalid doctor ID. Appointment creation failed.\n");
                        break;
                    }

                    printf("Enter the type (0 for VISIT_TYPE_CONSULTATION, 1 for VISIT_TYPE_GENERAL): ");
                    int isValidTypeInput = 0;
                    do
                    {
                        scanf("%d", &newType);
                        if (newType == VISIT_TYPE_CONSULTATION || newType == VISIT_TYPE_GENERAL)
                        {
                            isValidTypeInput = 1;
                        }
                        else
                        {
                            printf("Invalid type! Please enter 0 for GENERAL_CHECKUP or 1 for SURGERY: ");
                        }
                    } while (!isValidTypeInput);

                    printf("Enter the date (day month year): ");
                    scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);

                    printf("Enter the new confirmation status (0 for No, 1 for Yes): ");
                    scanf("%d", &newConfirmed);

                    createAppointment(appointmentCount, account, &doctors[selectedDoctorIndex], newType, newDate, newConfirmed);

                    Color_Green();
                    printf("\nAppointment has been created successfully\n");
                    Color_Reset();
                    appointmentCount++;
                    break;

                case 4:
                    showAppointmentsByPatient(account->id);
                    break;
                case 5:
                    showAppointmentsByPatient(account->id);
                    int optionPat;
                    Color_White();
                    printf("\nPlease write the ID of the Appointment you want to delete :");

                    scanf("%d", &optionPat);
                    Color_Reset();
                    deleteAppointment(optionPat);
                    break;
                case 6:
                    deleteAppointmentsByPatient(account->id);
                    deletePatient(account->id);
                    Color_Green();
                    printf("Account has been deleted successfully.\n");
                    break;
                case 7:
                    isLoggedIn = 0;
                    break;
                default:
                    Color_Red();
                    printf("\nInvalid option. Please select 1, 2, or 3.\n");
                    Color_Reset();
                    while (getchar() != '\n')
                        ; // To prevent it from going into an infinite loop when I enter data of String type.
                    break;
                }
            }
            else
            {
                Color_Green();
                printf("\n--------- WELCOME TO HOSPITAL AUTOMATION SYSTEM ---------\n");
                Color_Reset();
                printf("1- Login\n");
                printf("2- Register\n");
                printf("3- Exit\n");

                Color_White();
                printf("\nSelect an option: ");
                Color_Reset();
                scanf("%d", &option);

                char phonenumber[30];
                char password[30];
                char firstName[50];
                char lastName[50];
                int age;
                char gender[50];

                switch (option)
                {
                case 1:
                    Color_White();
                    printf("\nEnter your phone number: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(phonenumber);

                    Color_White();
                    printf("Enter your password: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(password);

                    Color_Yellow();
                    printf("\nLogging in...\n\n");
                    Color_Reset();
                    account = loginPatients(phonenumber, password);
                    if (account != NULL)
                    {
                        isLoggedIn = 1;
                        break;
                    }
                    else
                    {
                        Color_Red();
                        printf("User not found! Please try again.\n");
                        Color_Reset();
                        continue;
                    }
                    break;

                case 2:
                    Color_White();
                    printf("\nEnter your firstname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(firstName);

                    Color_White();
                    printf("Enter your lastname: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(lastName);

                    Color_White();
                    printf("Enter your age: ");
                    Color_Reset();
                    fflush(stdin);
                    scanf("%d", &age);

                    Color_White();
                    printf("Enter your gender: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(gender);

                    Color_White();
                    printf("Enter your phonenumber: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(phonenumber);

                    Color_White();
                    printf("Enter your password: ");
                    Color_Reset();
                    fflush(stdin);
                    gets(password);

                    account = (createPatient(patientID, firstName, lastName, age, gender, phonenumber, password, 0));
                    Color_Green();
                    printf("\nAccount created succesfully!\n\n");
                    Color_Green();
                    patientID++;
                    isLoggedIn = 1;
                    break;
                case 3:
                    Color_Magenta();
                    printf("\n------------ Goodbye! ------------\n");
                    Color_Reset();
                    return Display();
                default:
                    Color_Red();
                    printf("Invalid option. Please select 1, 2 or 3.\n");
                    Color_Reset();
                    while (getchar() != '\n')
                        ; // To prevent it from going into an infinite loop when I enter data of String type.
                    break;
                }
            }
        }
        break;
    case 2:
        AdminMenu();

        break;
    case 3:
        Color_Blue();
        printf("-----------------BYE---BYE--------------------");
        Color_Reset();
        deleteAllAppointments();
        deleteAllDoctors();
        deleteAllPatients();
        return 0;
    default:
        printf("Invalid user type. Exiting...\n");
        break;
    }

    return 0;
}

int AdminMenu()
{
    Doctor *doctorAccount;
    int isLoggedInDoctor = 0;
    int optionDoctor;
    while (true)
    {
        if (isLoggedInDoctor && doctorAccount)
        {
            int switchOption = 0;
            char newFirstName[30];
            char newLastName[30];
            char newPassword[30];
            char specialization[30];
            char newUsername[30];

            Color_Green();
            printf("\n--------- Welcome %s -- %s---------\n", doctorAccount->firstName, doctorAccount->lastName);
            Color_Reset();

            printf("\n1- Show doctor information\n");
            printf("2- Update doctor information\n");
            printf("3- Delete an appointment\n");
            printf("4- View your appointments\n");
            printf("5- Delete your account\n");
            printf("6- Logout\n");

            Color_White();
            fflush(stdin);
            printf("\nSelect an option : ");
            Color_Reset();
            scanf("%d", &switchOption);

            switch (switchOption)
            {
            case 1:
                printf("\nFirst Name : %s\n", doctorAccount->firstName);
                printf("Last Name : %s\n", doctorAccount->lastName);
                printf("Specialization : %s\n", doctorAccount->specialization);
                printf("Username : %s\n", doctorAccount->username);
                printf("Password: %s\n", doctorAccount->password);
                break;
            case 2:
                Color_White();
                printf("\nPlease enter your First Name : ");
                Color_Reset();
                fflush(stdin);
                gets(newFirstName);

                Color_White();
                printf("Please enter your new Last Name : ");
                Color_Reset();
                fflush(stdin);
                gets(newLastName);

                Color_White();
                printf("Please enter your new Specialization : ");
                Color_Reset();
                fflush(stdin);
                gets(specialization);

                Color_White();
                printf("Please enter your new Username : ");
                Color_Reset();
                fflush(stdin);
                gets(newUsername);

                Color_White();
                printf("Please enter your new password : ");
                Color_Reset();
                fflush(stdin);
                gets(newPassword);

                updateDoctorInformation(doctorAccount->id, newFirstName, newLastName, specialization, newUsername, newPassword);
                Color_Green();
                printf("\nAccount updated successfully\n");
                Color_Reset();
                break;
            case 3:
                Color_White();
                showAllAppointmentsByDoctor(doctorAccount->id);

                if (appointmentCount == 0)
                {
                    printf("No appointments available to delete.\n");
                }
                else
                {
                    int selectedAppointmentID;
                    printf("Enter the ID of the appointment you want to delete: ");
                    Color_Reset();
                    scanf("%d", &selectedAppointmentID);

                    int result = deleteAppointmentsByDoctorandId(doctorAccount->id, selectedAppointmentID);

                    if (result == 0)
                    {
                        Color_Green();
                        printf("Appointment has been deleted successfully.\n");
                    }
                    else
                    {
                        Color_Red();
                        printf("Error deleting the appointment. Please check if the ID is correct.\n");
                    }
                    Color_Reset();
                }
                break;

            case 4:
                showAllAppointmentsByDoctor(doctorAccount->id);
                break;
            case 5:
                deleteAppointmentsByDoctor(doctorAccount->id);
                deleteDoctor(doctorAccount->id);
                Color_Green();
                printf("Account has been deleted successfully.\n");
                break;
            case 6:
                isLoggedInDoctor = 0;
                break;
            default:
                Color_Red();
                printf("\nInvalid option. Please select 1, 2, or 3.\n");
                Color_Reset();
                while (getchar() != '\n')
                    ; // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
        else
        {
            Color_Green();
            printf("\n--------- WELCOME TO HOSPITAL AUTOMATION SYSTEM DOCTOR SIDE ---------\n");
            Color_Reset();
            printf("1- Login\n");
            printf("2- Register\n");
            printf("3- Exit\n");
            int switchDoctor;
            Color_White();
            printf("\nSelect an option: ");
            Color_Reset();
            scanf("%d", &switchDoctor);

            char username[30];
            char password[30];
            char firstName[50];
            char lastName[50];
            char specialization[50];
            char gender[50];

            switch (switchDoctor)
            {
            case 1:
                Color_White();
                printf("\nEnter your username: ");
                Color_Reset();
                fflush(stdin);
                gets(username);

                Color_White();
                printf("Enter your password: ");
                Color_Reset();
                fflush(stdin);
                gets(password);

                Color_Yellow();
                printf("\nLogging in...\n\n");
                Color_Reset();
                doctorAccount = loginDoctors(username, password);
                if (doctorAccount != NULL)
                {
                    isLoggedInDoctor = 1;
                    break;
                }
                else
                {
                    Color_Red();
                    printf("User not found! Please try again.\n");
                    Color_Reset();
                }
                break;

            case 2:
                Color_White();
                printf("\nEnter your firstname: ");
                Color_Reset();
                fflush(stdin);
                gets(firstName);

                Color_White();
                printf("Enter your lastname: ");
                Color_Reset();
                fflush(stdin);
                gets(lastName);

                Color_White();
                printf("Enter your specialization: ");
                Color_Reset();
                fflush(stdin);
                gets(specialization);

                Color_White();
                printf("Enter your gender: ");
                Color_Reset();
                fflush(stdin);
                gets(gender);

                Color_White();
                printf("Enter your username: ");
                Color_Reset();
                fflush(stdin);
                gets(username);

                Color_White();
                printf("Enter your password: ");
                Color_Reset();
                fflush(stdin);
                gets(password);

                doctorAccount = (createDoctor(doctorID, firstName, lastName, specialization, username, password));
                Color_Green();
                printf("\nAccount created succesfully!\n\n");
                Color_Green();
                doctorID++;
                isLoggedInDoctor = 1;
                break;
            case 3:
                Color_Magenta();
                printf("\n------------ Goodbye! ------------\n");
                Color_Reset();
                return Display();
            default:
                Color_Red();
                printf("Invalid option. Please select 1, 2 or 3.\n");
                Color_Reset();
                while (getchar() != '\n')
                    ; // To prevent it from going into an infinite loop when I enter data of String type.
                break;
            }
        }
    }
    return 0;
}

void defaultInformation()
{
    Patient *admin = createPatient(1, "Admin", "Admin", 0, "Admin", "Admin", "Admin", true);
    Patient *user = createPatient(2, "Ahmet", "Ahmet", 25, "male", "123", "123", false);
    Doctor *user1 = createDoctor(1, "Mehmet", "Mehmet", "Eye", "MehmetMehmet", "123");
}
