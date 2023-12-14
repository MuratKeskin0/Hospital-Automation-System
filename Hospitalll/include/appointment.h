
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "patient.h"
#include "doctor.h"
#include "visit.h"
#include <stdbool.h>

extern const char *const visit_type_names[];

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Appointment {
    int id;
    Patient patient;
    Doctor doctor;
    VisitType type;
    Date date;
    bool confirmed;
    int (*findAppointmentDetails)(struct Appointment *);
} Appointment;

Appointment *createAppointment(int id, Patient *patient, Doctor *doctor, VisitType type, Date date, bool confirmed);

int findAppointmentDetails(Appointment *self);

#endif
