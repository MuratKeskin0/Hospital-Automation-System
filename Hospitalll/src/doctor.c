#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/doctor.h"
#include "../src/database.c"

int insertDoctor(Doctor doctor);

Doctor *createDoctor(int id, char *firstName, char *lastName, char *specialization, char *username, char *password){
    Doctor *doctor = (Doctor *)malloc(sizeof(Doctor));
    doctor->id =id;
    strcpy(doctor->firstName, firstName);
    strcpy(doctor->lastName, lastName);
    strcpy(doctor->specialization, specialization);
    strcpy(doctor->username, username);
    strcpy(doctor->password, password);
    insertDoctor(*doctor);
    doctors[doctorCount] = *doctor;
    doctorCount++;
    return doctor;
}

