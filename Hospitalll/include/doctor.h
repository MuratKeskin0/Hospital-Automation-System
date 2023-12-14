#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct Doctor {
    int id;
    char firstName[50];
    char lastName[50];
    char specialization[50];
    char password[30];
    char username[30];
} Doctor;

Doctor *createDoctor(int id, char *firstName, char *lastName, char *specialization, char *username, char *password);


#endif
