#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/appointment.h"
#include "../src/database.c"




Appointment *createAppointment(int id, Patient *patient, Doctor *doctor, VisitType type, Date date, bool confirmed)
{
    Appointment *appointment = (Appointment *)malloc(sizeof(Appointment));

    if (appointment == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL; // Return NULL to indicate failure
    }

    appointment->id = id;
    appointment->patient = *patient;
    appointment->doctor = *doctor;
    appointment->type = type;
    appointment->date = date;
    appointment->confirmed = confirmed;

    appointment->findAppointmentDetails = &findAppointmentDetails; // Set the function pointer

    if (insertAppointment(*appointment) != 0)
    {
        free(appointment); // Free the allocated memory in case of an error
        return NULL;       // Return NULL to indicate failure
    }

    appointments[appointmentCount] = *appointment;
    appointmentCount++;

    return appointment;
}

int findAppointmentDetails(Appointment *self)
{
    // Implement your logic to find appointment details
    // For example, you can print or return some information
    printf("Appointment ID: %d\n", self->id);
    printf("Patient: %s %s\n", self->patient.firstName, self->patient.lastName);
    printf("Doctor: %s %s\n", self->doctor.firstName, self->doctor.lastName);
    printf("Type: %s\n", visit_type_names[self->type]);
    printf("Date: %d-%d-%d\n", self->date.day, self->date.month, self->date.year);
    printf("Confirmed: %s\n", self->confirmed ? "Yes" : "No");

    // You can return some value or just return 0 for simplicity
    return 0;
}
