#ifndef PATIENT_H
#define PATIENT_H

typedef struct {
    int id;
    char firstName[50];
    char lastName[50];
    char gender[50];  
    int age;
    char phoneNumber[15]; 
    char password[30];
    bool isAdmin;
} Patient;

Patient *createPatient(int id, char *firstName, char *lastName, int age, char *gender, char *phoneNumber, char *password, bool isAdmin);

#endif

