#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/patient.h"
#include "database.c"

int insertPatient(Patient patient);

Patient *createPatient(int id, char *firstName, char *lastName, int age, char *gender, char *phoneNumber, char *password, bool isAdmin){
    Patient *patient = (Patient *)malloc(sizeof(Patient));
    patient->id =id;
    strcpy(patient->firstName, firstName);
    strcpy(patient->lastName, lastName);
    patient->age =age;
    strcpy(patient->gender, gender);
    strcpy(patient->phoneNumber, phoneNumber);
    strcpy(patient->password, password);
    patient->isAdmin = isAdmin;
    insertPatient(*patient);
    patients[patientCount] = *patient;
    patientCount++;
    return patient;
}

