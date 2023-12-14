# Hospital Management System Documentation

## Overview
The Hospital Management System (HMS) is designed to efficiently manage hospital operations, including managing patient and doctor profiles, and scheduling appointments.

## Core Components

1. **Patient Management**: Handles creation, authentication, update, and deletion of patient profiles.

2. **Doctor Management**: Manages doctor profiles including creation, authentication, update, and deletion.

3. **Appointment Management**: Facilitates scheduling, updating, and deletion of appointments.

## Functionalities

- **User Authentication**: Separate login mechanisms for patients and doctors.
- **Record Management**: Create, read, update, and delete operations for patient and doctor records.
- **Appointment Handling**: Schedule and manage appointments, with updates on date, type, and confirmation status.

## Complex Rules

- **Appointment Confirmation**: Track and update the confirmation status of appointments.
- **Role-Based Access**: Different access levels based on user roles (patient, doctor, admin).
- **Data Integrity**: Validation of input data and consistent updates across related records.

## System Workflow

1. **Initialization**: Load existing data and set up new record IDs.
2. **User Interaction**: Authenticate users and provide role-specific functionalities.
3. **Data Management**: CRUD operations on patient, doctor, and appointment data.
4. **Termination**: Save changes and clean up resources on exit.

## Conclusion
The HMS streamlines hospital processes, ensuring efficient and secure management of healthcare services.
