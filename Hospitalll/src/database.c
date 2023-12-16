#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/appointment.h"
#include "../include/visit.h"

const char *const visit_type_names[] = {
    "General",
    "Consultation",

};

#define MAX 1000

static Patient patients[MAX];
static int patientCount = 0;
static int patientID = 0;
static Doctor doctors[MAX];
static int doctorCount = 0;
static int doctorID = 0;
static Appointment appointments[MAX];
static int appointmentCount = 0;
static int appointmentID = 0;

int insertAppointment(Appointment appointment);

Patient *loginPatients(char *phoneNumber, char *password)
{

    for (int i = 0; i < patientCount; i++)
    {
        if (strcmp(patients[i].phoneNumber, phoneNumber) == 0 && strcmp(patients[i].password, password) == 0)
        {
            return &patients[i];
        }
    }
    Patient *nullP = NULL;
    return nullP;
}

Doctor *loginDoctors(char *username, char *password)
{

    for (int i = 0; i < doctorCount; i++)
    {
        if (strcmp(doctors[i].username, username) == 0 && strcmp(doctors[i].password, password) == 0)
        {
            return &doctors[i];
        }
    }
    Doctor *nullP = NULL;
    return nullP;
}

int insertPatient(Patient patient)
{
    FILE *file = fopen("../database/patient.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", patient.id);
    fprintf(file, "%s\n", patient.firstName);
    fprintf(file, "%s\n", patient.lastName);
    fprintf(file, "%d\n", patient.age);
    fprintf(file, "%s\n", patient.gender);
    fprintf(file, "%s\n", patient.phoneNumber);
    fprintf(file, "%s\n", patient.password);
    fprintf(file, "%d\n", patient.isAdmin);

    fclose(file);
    return 0;
}

int insertDoctor(Doctor doctor)
{
    FILE *file = fopen("../database/doctor.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", doctor.id);
    fprintf(file, "%s\n", doctor.firstName);
    fprintf(file, "%s\n", doctor.lastName);
    fprintf(file, "%s\n", doctor.specialization);
    fprintf(file, "%s\n", doctor.username);
    fprintf(file, "%s\n", doctor.password);

    fclose(file);
    return 0;
}

int insertAppointment(Appointment appointment)
{
    FILE *file = fopen("../database/appointment.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    fprintf(file, "%d\n", appointment.id);
    fprintf(file, "%d\n", appointment.patient.id);
    fprintf(file, "%d\n", appointment.doctor.id);
    fprintf(file, "%d\n", appointment.type);
    fprintf(file, "%d\n", appointment.date.day);
    fprintf(file, "%d\n", appointment.date.month);
    fprintf(file, "%d\n", appointment.date.year);
    fprintf(file, "%d\n", appointment.confirmed);

    fclose(file);
    return 0;
}

int readPatient()
{
    FILE *file = fopen("../database/patient.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Patient *patient;
    char chunk[128];
    int lineNum = 0;
    int patientCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {

        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 8 == 0)
        {
            patient = (Patient *)malloc(sizeof(Patient));
            patient->id = atoi(chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 1)
        {
            strcpy(patient->firstName, chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 2)
        {
            strcpy(patient->lastName, chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 3)
        {
            patient->age = atoi(chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 4)
        {

            if (strlen(chunk) < sizeof(patient->gender))
            {
                strcpy(patient->gender, chunk);
            }
            else
            {

                printf("Error: firstName string is too long!\n");
            }
            lineNum++;
        }
        else if (lineNum % 8 == 5)
        {
            strcpy(patient->phoneNumber, chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 6)
        {
            strcpy(patient->password, chunk);
            lineNum++;
        }
        else if (lineNum % 8 == 7)
        {
            patient->isAdmin = atoi(chunk);
            lineNum++;
            patients[patientCount] = *patient;
            patientCount++;
        }
    }
    patientCount = patientCount;
    fclose(file);

    return 0;
}

int readDoctor()
{
    FILE *file = fopen("../database/doctor.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Doctor *doctor;
    char chunk[128];
    int lineNum = 0;
    int doctorCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 6 == 0)
        {
            doctor = (Doctor *)malloc(sizeof(Doctor));
            doctor->id = atoi(chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            strcpy(doctor->firstName, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            strcpy(doctor->lastName, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            strcpy(doctor->specialization, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            strcpy(doctor->username, chunk);
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            strcpy(doctor->password, chunk);
            lineNum++;
            doctors[doctorCount] = *doctor;
            doctorCount++;
        }
    }

    doctorCount = doctorCount;

    fclose(file);

    return 0;
}

int readAppointment()
{
    FILE *file = fopen("../database/appointment.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Appointment *appointment;
    char chunk[128];
    int lineNum = 0;
    int appointmentCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 8 == 0)
        {
            appointment = (Appointment *)malloc(sizeof(Appointment));
            if (appointment == NULL)
            {
                printf("Memory allocation failed!\n");
                return 1;
            }
            appointment->id = atoi(chunk);
        }
        else if (lineNum % 8 == 1)
        {
            appointment->patient.id = atoi(chunk);
        }
        else if (lineNum % 8 == 2)
        {
            appointment->doctor.id = atoi(chunk);
        }
        else if (lineNum % 8 == 3)
        {
            appointment->type = atoi(chunk);
        }
        else if (lineNum % 8 == 4)
        {
            appointment->date.day = atoi(chunk);
        }
        else if (lineNum % 8 == 5)
        {
            appointment->date.month = atoi(chunk);
        }
        else if (lineNum % 8 == 6)
        {
            appointment->date.year = atoi(chunk);
        }
        else if (lineNum % 8 == 7)
        {
            appointment->confirmed = atoi(chunk);
            appointments[appointmentCount] = *appointment;
            appointmentCount++;
        }

        lineNum++;
    }

    appointmentCount = appointmentCount;

    fclose(file);

    return 0;
}

int deletePatient(int id)
{
    FILE *file = fopen("../database/patient.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Dosya açilirken hata oluştu!\n");
        return 1;
    }

    Patient *patient;
    Patient *tempPatients[patientCount - 1];
    char chunk[128];
    int lineNum = 0;
    int tempPatientCount = 0;
    bool skipPatient = false;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 8 == 0)
        {
            patient = (Patient *)malloc(sizeof(Patient));
            patient->id = atoi(chunk);
            if (patient->id == id)
            {
                skipPatient = true;
            }
            else
            {
                fprintf(temp, "%d\n", patient->id);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 1)
        {
            strcpy(patient->firstName, chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%s\n", patient->firstName);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 2)
        {
            strcpy(patient->lastName, chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%s\n", patient->lastName);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 3)
        {
            patient->age = atoi(chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%d\n", patient->age);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 4)
        {
            strcpy(patient->gender, chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%s\n", patient->gender);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 5)
        {
            strcpy(patient->phoneNumber, chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%s\n", patient->phoneNumber);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 6)
        {
            strcpy(patient->password, chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%s\n", patient->password);
            }
            lineNum++;
        }
        else if (lineNum % 8 == 7)
        {
            patient->isAdmin = atoi(chunk);
            if (!skipPatient)
            {
                fprintf(temp, "%d\n", patient->isAdmin);
                tempPatients[tempPatientCount] = patient;
                tempPatientCount++;
            }
            skipPatient = false;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/patient.txt");
    rename("../database/temp.txt", "../database/patient.txt");

    memset(patients, 0, sizeof(patients));
    for (int i = 0; i < tempPatientCount; i++)
    {
        patients[i] = *tempPatients[i];
    }
    patientCount = tempPatientCount;

    return 0;
}

int deleteDoctor(int id)
{
    FILE *file = fopen("../database/doctor.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Dosya açılırken hata oluştu!\n");
        return 1;
    }

    Doctor *doctor;
    Doctor *tempDoctors[doctorCount - 1];
    char chunk[128];
    int lineNum = 0;
    int tempDoctorCount = 0;
    bool skipDoctor = false;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 6 == 0)
        {
            doctor = (Doctor *)malloc(sizeof(Doctor));
            doctor->id = atoi(chunk);
            if (doctor->id == id)
            {
                skipDoctor = true;
            }
            else
            {
                fprintf(temp, "%d\n", doctor->id);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            strcpy(doctor->firstName, chunk);
            if (!skipDoctor)
            {
                fprintf(temp, "%s\n", doctor->firstName);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            strcpy(doctor->lastName, chunk);
            if (!skipDoctor)
            {
                fprintf(temp, "%s\n", doctor->lastName);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            strcpy(doctor->specialization, chunk);
            if (!skipDoctor)
            {
                fprintf(temp, "%s\n", doctor->specialization);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            strcpy(doctor->username, chunk);
            if (!skipDoctor)
            {
                fprintf(temp, "%s\n", doctor->username);
            }
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            strcpy(doctor->password, chunk);
            if (!skipDoctor)
            {
                fprintf(temp, "%s\n", doctor->password);
                tempDoctors[tempDoctorCount] = doctor;
                tempDoctorCount++;
            }
            skipDoctor = false;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/doctor.txt");
    rename("../database/temp.txt", "../database/doctor.txt");

    memset(doctors, 0, sizeof(doctors));
    for (int i = 0; i < tempDoctorCount; i++)
    {
        doctors[i] = *tempDoctors[i];
    }
    doctorCount = tempDoctorCount;

    return 0;
}

int deleteAppointment(int id)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Appointment appointment;
    char chunk[128];
    int lineNum = 0;
    bool skipAppointment = false;
    int tempAppointmentCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 8 == 0)
        {
            appointment.id = atoi(chunk);
            skipAppointment = (appointment.id == id);
        }

        if (!skipAppointment)
        {
            fprintf(temp, "%s\n", chunk);
        }

        lineNum++;
        if (lineNum % 8 == 0)
        {
            lineNum = 0;
            if (!skipAppointment)
            {
                appointments[tempAppointmentCount++] = appointment;
            }
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/appointment.txt");
    rename("../database/temp.txt", "../database/appointment.txt");

    appointmentCount = tempAppointmentCount;

    return 0;
}

int updatePatientInformation(int id, char *newFirstName, char *newLastName, int newAge, char *newGender, char *newPhoneNumber, char *newPassword, bool newIsAdmin)
{
    FILE *file = fopen("../database/patient.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Patient *patient;
    Patient *tempPatients[patientCount];
    char chunk[128];
    int lineNum = 0;
    int tempPatientCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 8 == 0)
        {
            patient = (Patient *)malloc(sizeof(Patient));
            patient->id = atoi(chunk);

            if (patient->id == id)
            {
                patient->id = id;
                strcpy(patient->firstName, newFirstName);
                strcpy(patient->lastName, newLastName);
                patient->age = newAge;
                strcpy(patient->gender, newGender);
                strcpy(patient->phoneNumber, newPhoneNumber);
                strcpy(patient->password, newPassword);
            }

            fprintf(temp, "%d\n", patient->id);
            lineNum++;
        }
        else if (lineNum % 8 == 1)
        {
            if (patient->id != id)
            {
                strcpy(patient->firstName, chunk);
            }
            fprintf(temp, "%s\n", patient->firstName);
            lineNum++;
        }
        else if (lineNum % 8 == 2)
        {
            if (patient->id != id)
            {
                strcpy(patient->lastName, chunk);
            }
            fprintf(temp, "%s\n", patient->lastName);
            lineNum++;
        }
        else if (lineNum % 8 == 3)
        {
            if (patient->id != id)
            {
                patient->age = atoi(chunk);
            }
            fprintf(temp, "%d\n", patient->age);
            lineNum++;
        }
        else if (lineNum % 8 == 4)
        {
            if (patient->id != id)
            {
                strcpy(patient->gender, chunk);
            }
            fprintf(temp, "%s\n", patient->gender);
            lineNum++;
        }
        else if (lineNum % 8 == 5)
        {
            if (patient->id != id)
            {
                strcpy(patient->phoneNumber, chunk);
            }
            fprintf(temp, "%s\n", patient->phoneNumber);
            lineNum++;
        }
        else if (lineNum % 8 == 6)
        {
            if (patient->id != id)
            {
                strcpy(patient->password, chunk);
            }
            fprintf(temp, "%s\n", patient->password);
            lineNum++;
        }
        else if (lineNum % 8 == 7)
        {
            if (patient->id == id)
            {
                patient->isAdmin = newIsAdmin;
            }
            else
            {
                patient->isAdmin = atoi(chunk);
            }
            fprintf(temp, "%d\n", patient->isAdmin);
            tempPatients[tempPatientCount++] = patient;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/patient.txt");
    rename("../database/temp.txt", "../database/patient.txt");

    memset(patients, 0, sizeof(patients));
    for (int i = 0; i < tempPatientCount; i++)
    {
        patients[i] = *tempPatients[i];
    }
    patientCount = tempPatientCount;

    return 0;
}

int updateDoctorInformation(int id, char *newFirstName, char *newLastName, char *newSpecialization, char *newUsername, char *newPassword)
{
    FILE *file = fopen("../database/doctor.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    Doctor *doctor;
    Doctor *tempDoctors[doctorCount];
    char chunk[128];
    int lineNum = 0;
    int tempDoctorCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        if (lineNum % 6 == 0)
        {
            doctor = (Doctor *)malloc(sizeof(Doctor));
            doctor->id = atoi(chunk);

            if (doctor->id == id)
            {
                doctor->id = id;
                strcpy(doctor->firstName, newFirstName);
                strcpy(doctor->lastName, newLastName);
                strcpy(doctor->specialization, newSpecialization);
                strcpy(doctor->username, newUsername);
                strcpy(doctor->password, newPassword);
            }

            fprintf(temp, "%d\n", doctor->id);
            lineNum++;
        }
        else if (lineNum % 6 == 1)
        {
            if (doctor->id != id)
            {
                strcpy(doctor->firstName, chunk);
            }
            fprintf(temp, "%s\n", doctor->firstName);
            lineNum++;
        }
        else if (lineNum % 6 == 2)
        {
            if (doctor->id != id)
            {
                strcpy(doctor->lastName, chunk);
            }
            fprintf(temp, "%s\n", doctor->lastName);
            lineNum++;
        }
        else if (lineNum % 6 == 3)
        {
            if (doctor->id != id)
            {
                strcpy(doctor->specialization, chunk);
            }
            fprintf(temp, "%s\n", doctor->specialization);
            lineNum++;
        }
        else if (lineNum % 6 == 4)
        {
            if (doctor->id != id)
            {
                strcpy(doctor->username, chunk);
            }
            fprintf(temp, "%s\n", doctor->username);
            lineNum++;
        }
        else if (lineNum % 6 == 5)
        {
            if (doctor->id != id)
            {
                strcpy(doctor->password, chunk);
            }
            fprintf(temp, "%s\n", doctor->password);
            tempDoctors[tempDoctorCount] = doctor;
            tempDoctorCount++;
            lineNum++;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/doctor.txt");
    rename("../database/temp.txt", "../database/doctor.txt");

    memset(doctors, 0, sizeof(doctors));
    for (int i = 0; i < tempDoctorCount; i++)
    {
        doctors[i] = *tempDoctors[i];
    }
    doctorCount = tempDoctorCount;

    return 0;
}

int updateAppointmentInformation(int id, VisitType newType, Date newDate, bool newConfirmed)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp_appointment.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error opening files!\n");
        return 1;
    }

    Appointment appointment;
    int found = 0;

    while (fscanf(file, "%d", &appointment.id) == 1)
    {
        fscanf(file, "%d", &appointment.patient.id);
        fscanf(file, "%d", &appointment.doctor.id);
        fscanf(file, "%d", &appointment.type);
        fscanf(file, "%d", &appointment.date.day);
        fscanf(file, "%d", &appointment.date.month);
        fscanf(file, "%d", &appointment.date.year);
        fscanf(file, "%d", &appointment.confirmed);

        if (appointment.id == id)
        {
            appointment.type = newType;
            appointment.date.day = newDate.day;
            appointment.date.month = newDate.month;
            appointment.date.year = newDate.year;
            appointment.confirmed = newConfirmed;
            found = 1;
        }

        fprintf(temp, "%d\n", appointment.id);
        fprintf(temp, "%d\n", appointment.patient.id);
        fprintf(temp, "%d\n", appointment.doctor.id);
        fprintf(temp, "%d\n", appointment.type);
        fprintf(temp, "%d\n", appointment.date.day);
        fprintf(temp, "%d\n", appointment.date.month);
        fprintf(temp, "%d\n", appointment.date.year);
        fprintf(temp, "%d\n", appointment.confirmed);
    }

    fclose(file);
    fclose(temp);

    if (!found)
    {
        printf("Appointment with ID %d not found.\n", id);
    }

    remove("../database/appointment.txt");
    rename("../database/temp_appointment.txt", "../database/appointment.txt");

    return found ? 0 : 1;
}




void readAllData()
{
    readPatient();
    readDoctor();
    readAppointment();
}

void showAllAppointments()
{
    FILE *file = fopen("../database/appointment.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }

    printf("\n--------------- ALL APPOINTMENTS ---------------\n\n");

    while (fscanf(file, "%d", &appointments[appointmentCount].id) == 1)
    {
        fscanf(file, "%d", &appointments[appointmentCount].patient.id);
        fscanf(file, "%d", &appointments[appointmentCount].doctor.id);
        fscanf(file, "%d", &appointments[appointmentCount].type);
        fscanf(file, "%d", &appointments[appointmentCount].date.day);
        fscanf(file, "%d", &appointments[appointmentCount].date.month);
        fscanf(file, "%d", &appointments[appointmentCount].date.year);
        fscanf(file, "%d", &appointments[appointmentCount].confirmed);

        appointmentCount++;

        printf("Appointment ID: %d\n", appointments[appointmentCount - 1].id);
        printf("Patient ID: %d\n", appointments[appointmentCount - 1].patient.id);
        printf("Doctor ID: %d\n", appointments[appointmentCount - 1].doctor.id);
        printf("Type: %s\n", visit_type_names[appointments[appointmentCount - 1].type]);
        printf("Date: %d-%d-%d\n", appointments[appointmentCount - 1].date.day, appointments[appointmentCount - 1].date.month, appointments[appointmentCount - 1].date.year);
        printf("Confirmed: %s\n", appointments[appointmentCount - 1].confirmed ? "Yes" : "No");
        printf("-------------------------------\n");
    }

    fclose(file);

    if (appointmentCount == 0)
    {
        printf("\nNo appointments found.\n");
    }
}

int updateAppointmentConfirmation(int appointmentID, bool newConfirmationStatus)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    bool updated = false;
    int currentAppointmentId = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        size_t newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 8 == 0)
        {
            currentAppointmentId = atoi(chunk);
        }

        if (lineNum % 8 == 7 && currentAppointmentId == appointmentID)
        {
            fprintf(temp, "%d\n", newConfirmationStatus);
            updated = true;
        }
        else
        {
            fprintf(temp, "%s\n", chunk);
        }

        lineNum++;
        if (lineNum % 8 == 0)
            lineNum = 0;
    }

    fclose(file);
    fclose(temp);

    remove("../database/appointment.txt");
    rename("../database/temp.txt", "../database/appointment.txt");

    return updated ? 0 : 2;
}

void showAllPatients()
{
    FILE *file = fopen("../database/patient.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }

    printf("\n--------------- ALL PATIENTS ---------------\n\n");

    while (fscanf(file, "%d", &patients[patientCount].id) == 1)
    {
        fscanf(file, "%s", patients[patientCount].firstName);
        fscanf(file, "%s", patients[patientCount].lastName);
        fscanf(file, "%d", &patients[patientCount].age);
        fscanf(file, "%s", patients[patientCount].gender);
        fscanf(file, "%s", patients[patientCount].phoneNumber);
        fscanf(file, "%s", patients[patientCount].password);
        fscanf(file, "%d", &patients[patientCount].isAdmin);

        patientCount++;

        printf("Patient ID: %d\n", patients[patientCount - 1].id);
        printf("Name: %s %s\n", patients[patientCount - 1].firstName, patients[patientCount - 1].lastName);
        printf("Age: %d\n", patients[patientCount - 1].age);
        printf("Gender: %s\n", patients[patientCount - 1].gender);
        printf("Phone Number: %s\n", patients[patientCount - 1].phoneNumber);
        printf("Admin: %s\n", patients[patientCount - 1].isAdmin ? "Yes" : "No");
        printf("-------------------------------\n");
    }

    fclose(file);

    if (patientCount == 0)
    {
        printf("\nNo patients found.\n");
    }
}

void showAllDoctors()
{
    FILE *file = fopen("../database/doctor.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }

    printf("\n--------------- ALL DOCTORS ---------------\n\n");

    while (fscanf(file, "%d", &doctors[doctorCount].id) == 1)
    {
        fscanf(file, "%s", doctors[doctorCount].firstName);
        fscanf(file, "%s", doctors[doctorCount].lastName);
        fscanf(file, "%s", doctors[doctorCount].specialization);
        fscanf(file, "%s", doctors[doctorCount].username);
        fscanf(file, "%s", doctors[doctorCount].password);

        doctorCount++;

        printf("Doctor ID: %d\n", doctors[doctorCount - 1].id);
        printf("Name: %s %s\n", doctors[doctorCount - 1].firstName, doctors[doctorCount - 1].lastName);
        printf("Specialization: %s\n", doctors[doctorCount - 1].specialization);
        printf("Username: %s\n", doctors[doctorCount - 1].username);
        printf("-------------------------------\n");
    }

    fclose(file);

    if (doctorCount == 0)
    {
        printf("\nNo doctors found.\n");
    }
}

void setAllIdNumbers()
{

    int maxForPatient = patients[0].id;
    for (int i = 0; i < patientCount; i++)
    {
        if (maxForPatient < patients[i].id)
        {
            maxForPatient = patients[i].id;
        }
    }
    patientID = maxForPatient + 1;

    int maxForDoctor = doctors[0].id;
    for (int i = 0; i < doctorCount; i++)
    {
        if (maxForDoctor < doctors[i].id)
        {
            maxForDoctor = doctors[i].id;
        }
    }
    doctorID = maxForDoctor + 1;

    int maxForAppointment = appointments[0].id;
    for (int i = 0; i < appointmentCount; i++)
    {
        if (maxForAppointment < appointments[i].id)
        {
            maxForAppointment = appointments[i].id;
        }
    }
    appointmentID = maxForAppointment + 1;
}

int deleteAppointmentsByDoctor(int doctorId)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Dosya açılırken hata oluştu!\n");
        return 1;
    }

    Appointment *appointment;
    Appointment *tempAppointments[appointmentCount];
    char chunk[128];
    int lineNum = 0;
    int tempAppointmentCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        appointment = (Appointment *)malloc(sizeof(Appointment));
        appointment->id = atoi(chunk);

        for (int i = 1; i < 7; ++i)
        {
            fgets(chunk, sizeof(chunk), file);

            if (i == 1)
                appointment->patient.id = atoi(chunk);
            else if (i == 2)
                appointment->doctor.id = atoi(chunk);
            else if (i == 3)
                appointment->type = atoi(chunk);
            else if (i == 4)
                appointment->date.day = atoi(chunk);
            else if (i == 5)
                appointment->date.month = atoi(chunk);
            else if (i == 6)
                appointment->date.year = atoi(chunk);
        }

        fgets(chunk, sizeof(chunk), file);
        appointment->confirmed = atoi(chunk);

        if (appointment->doctor.id != doctorId)
        {

            fprintf(temp, "%d\n", appointment->id);
            fprintf(temp, "%d\n", appointment->patient.id);
            fprintf(temp, "%d\n", appointment->doctor.id);
            fprintf(temp, "%d\n", appointment->type);
            fprintf(temp, "%d\n", appointment->date.day);
            fprintf(temp, "%d\n", appointment->date.month);
            fprintf(temp, "%d\n", appointment->date.year);
            fprintf(temp, "%d\n", appointment->confirmed);

            tempAppointments[tempAppointmentCount] = appointment;
            tempAppointmentCount++;
        }
        else
        {

            free(appointment);
        }

        lineNum++;
    }

    fclose(file);
    fclose(temp);

    remove("../database/appointment.txt");
    rename("../database/temp.txt", "../database/appointment.txt");

    memset(appointments, 0, sizeof(appointments));
    for (int i = 0; i < tempAppointmentCount; i++)
    {
        appointments[i] = *tempAppointments[i];
    }
    appointmentCount = tempAppointmentCount;

    return 0;
}

int deleteAppointmentsByPatient(int patientId)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Dosya açılırken hata oluştu!\n");
        return 1;
    }

    Appointment *appointment;
    Appointment *tempAppointments[appointmentCount];
    char chunk[128];
    int lineNum = 0;
    int tempAppointmentCount = 0;

    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if (chunk != NULL)
        {
            size_t newline_pos = strcspn(chunk, "\n");
            chunk[newline_pos] = '\0';
        }

        appointment = (Appointment *)malloc(sizeof(Appointment));
        appointment->id = atoi(chunk);

        for (int i = 1; i < 7; ++i)
        {
            fgets(chunk, sizeof(chunk), file);

            if (i == 1)
                appointment->patient.id = atoi(chunk);
            else if (i == 2)
                appointment->doctor.id = atoi(chunk);
            else if (i == 3)
                appointment->type = atoi(chunk);
            else if (i == 4)
                appointment->date.day = atoi(chunk);
            else if (i == 5)
                appointment->date.month = atoi(chunk);
            else if (i == 6)
                appointment->date.year = atoi(chunk);
        }

        fgets(chunk, sizeof(chunk), file);
        appointment->confirmed = atoi(chunk);

        if (appointment->patient.id != patientId)
        {

            fprintf(temp, "%d\n", appointment->id);
            fprintf(temp, "%d\n", appointment->patient.id);
            fprintf(temp, "%d\n", appointment->doctor.id);
            fprintf(temp, "%d\n", appointment->type);
            fprintf(temp, "%d\n", appointment->date.day);
            fprintf(temp, "%d\n", appointment->date.month);
            fprintf(temp, "%d\n", appointment->date.year);
            fprintf(temp, "%d\n", appointment->confirmed);

            tempAppointments[tempAppointmentCount] = appointment;
            tempAppointmentCount++;
        }
        else
        {

            free(appointment);
        }

        lineNum++;
    }

    fclose(file);
    fclose(temp);

    remove("../database/appointment.txt");
    rename("../database/temp.txt", "../database/appointment.txt");

    memset(appointments, 0, sizeof(appointments));
    for (int i = 0; i < tempAppointmentCount; i++)
    {
        appointments[i] = *tempAppointments[i];
    }
    appointmentCount = tempAppointmentCount;

    return 0;
}

void showAllAppointmentsByDoctor(int doctorId)
{
    FILE *file = fopen("../database/appointment.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }

    printf("\n--------------- DOCTOR'S APPOINTMENTS ---------------\n\n");

    while (fscanf(file, "%d", &appointments[appointmentCount].id) == 1)
    {
        fscanf(file, "%d", &appointments[appointmentCount].patient.lastName);
        fscanf(file, "%d", &appointments[appointmentCount].doctor.username);
        fscanf(file, "%d", &appointments[appointmentCount].type);
        fscanf(file, "%d", &appointments[appointmentCount].date.day);
        fscanf(file, "%d", &appointments[appointmentCount].date.month);
        fscanf(file, "%d", &appointments[appointmentCount].date.year);
        fscanf(file, "%d", &appointments[appointmentCount].confirmed);

        if (appointments[appointmentCount].doctor.id == doctorId)
        {

            printf("Appointment ID: %d\n", appointments[appointmentCount].id);
            printf("Patient ID: %d\n", appointments[appointmentCount].patient.id);
            printf("Doctor ID: %d\n", appointments[appointmentCount].doctor.id);
            printf("Type: %s\n", visit_type_names[appointments[appointmentCount].type]);
            printf("Date: %d-%d-%d\n", appointments[appointmentCount].date.day, appointments[appointmentCount].date.month, appointments[appointmentCount].date.year);
            printf("Confirmed: %s\n", appointments[appointmentCount].confirmed ? "Yes" : "No");
            printf("-------------------------------\n");
        }

        appointmentCount++;
    }

    fclose(file);

    if (appointmentCount == 0)
    {
        printf("\nNo appointments found.\n");
    }
}

void showAppointmentsByPatient(int patientId)
{
    FILE *file = fopen("../database/appointment.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return;
    }

    printf("\n--------------- PATIENT'S APPOINTMENTS ---------------\n\n");

    while (fscanf(file, "%d", &appointments[appointmentCount].id) == 1)
    {
        fscanf(file, "%d", &appointments[appointmentCount].patient.id);
        fscanf(file, "%d", &appointments[appointmentCount].doctor.id);
        fscanf(file, "%d", &appointments[appointmentCount].type);
        fscanf(file, "%d", &appointments[appointmentCount].date.day);
        fscanf(file, "%d", &appointments[appointmentCount].date.month);
        fscanf(file, "%d", &appointments[appointmentCount].date.year);
        fscanf(file, "%d", &appointments[appointmentCount].confirmed);

        if (appointments[appointmentCount].patient.id == patientId)
        {

            printf("Appointment ID: %d\n", appointments[appointmentCount].id);
            printf("Patient ID: %d\n", appointments[appointmentCount].patient.id);
            printf("Doctor ID: %d\n", appointments[appointmentCount].doctor.id);
            printf("Type: %s\n", visit_type_names[appointments[appointmentCount].type]);
            printf("Date: %d-%d-%d\n", appointments[appointmentCount].date.day, appointments[appointmentCount].date.month, appointments[appointmentCount].date.year);
            printf("Confirmed: %s\n", appointments[appointmentCount].confirmed ? "Yes" : "No");
            printf("-------------------------------\n");
        }

        appointmentCount++;
    }

    fclose(file);

    if (appointmentCount == 0)
    {
        printf("\nNo appointments found.\n");
    }
}

int deleteAppointmentsByDoctorandId(int doctorId, int appointmentId)
{
    FILE *file = fopen("../database/appointment.txt", "r");
    FILE *temp = fopen("../database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Dosya açılırken hata oluştu!\n");
        return 1;
    }

    Appointment *tempAppointments[appointmentCount];
    char chunk[128];
    int tempAppointmentCount = 0;

    while (1)
    {
        Appointment *appointment = (Appointment *)malloc(sizeof(Appointment));

        if (fscanf(file, "%d", &appointment->id) != 1)
        {
            free(appointment);
            break;
        }

        for (int i = 1; i < 7; ++i)
        {
            if (fscanf(file, "%s", chunk) != 1)
            {
                free(appointment);
                break;
            }

            if (i == 1)
                appointment->patient.id = atoi(chunk);
            else if (i == 2)
                appointment->doctor.id = atoi(chunk);
            else if (i == 3)
                appointment->type = atoi(chunk);
            else if (i == 4)
                appointment->date.day = atoi(chunk);
            else if (i == 5)
                appointment->date.month = atoi(chunk);
            else if (i == 6)
                appointment->date.year = atoi(chunk);
        }

        if (fscanf(file, "%d", &appointment->confirmed) != 1)
        {
            free(appointment);
            break;
        }

        if (appointment->doctor.id != doctorId || appointment->id != appointmentId)
        {

            fprintf(temp, "%d\n", appointment->id);
            fprintf(temp, "%d\n", appointment->patient.id);
            fprintf(temp, "%d\n", appointment->doctor.id);
            fprintf(temp, "%d\n", appointment->type);
            fprintf(temp, "%d\n", appointment->date.day);
            fprintf(temp, "%d\n", appointment->date.month);
            fprintf(temp, "%d\n", appointment->date.year);
            fprintf(temp, "%d\n", appointment->confirmed);

            tempAppointments[tempAppointmentCount] = appointment;
            tempAppointmentCount++;
        }
        else
        {

            free(appointment);
        }
    }

    fclose(file);
    fclose(temp);

    remove("../database/appointment.txt");
    rename("../database/temp.txt", "../database/appointment.txt");

    memset(appointments, 0, sizeof(appointments));
    for (int i = 0; i < tempAppointmentCount; i++)
    {
        appointments[i] = *tempAppointments[i];
    }
    appointmentCount = tempAppointmentCount;

    return 0;
}

int getTotalNumberOfAppointments()
{
    FILE *file = fopen("../database/appointment.txt", "r");
    int totalAppointments = 0;

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return -1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        totalAppointments++;
    }

    fclose(file);
    return totalAppointments / 8;
}

int deleteAllPatients()
{
    FILE *file = fopen("../database/patient.txt", "w");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    fclose(file);
    patientCount = 0;
    return 0;
}

int deleteAllAppointments()
{
    FILE *file = fopen("../database/appointment.txt", "w");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    fclose(file);
    appointmentCount = 0;
    return 0;
}

int deleteAllDoctors()
{
    FILE *file = fopen("../database/doctor.txt", "w");

    if (file == NULL)
    {
        printf("Error while opening the file!\n");
        return 1;
    }

    fclose(file);
    doctorCount = 0;
    return 0;
}
