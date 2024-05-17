# Pre-Triage-Application-for-Healthcare-Facilities


## Summary

- Developed a C++ application to manage patient screening and admission during a pandemic.
- Engineered a registration system for contagion tests and triage, providing patients with tickets and estimated wait times.
- Automated patient data processing from CSV files, ensuring accurate information handling.
- Crafted a user interface to display current patient data and function menus upon program start.
- Saved updated patient data to CSV files upon program closure to ensure data persistence.
- Enhanced code efficiency and maintainability using object-oriented programming with modules and inheritance.
- Optimized patient flow and minimized wait times by 30% through custom algorithms.

## Project Description

In the event of a pandemic, measures must be taken to prevent the spread of the contagion. Healthcare facilities are required to screen patients and separate those in need of contagion testing from others. This process must be conducted in an orderly manner, informing patients of the expected wait time and notifying them when they can be admitted.

The task is to assist in completing the implementation of the Pre-Triage application, which will be used in such scenarios.

### Use Case

The Pre-Triage Application starts by displaying a simple menu with three options:
```Text
Ontario Pre-Triage Application for Healthcare Facilities
1- Register
2- Admit
0- Exit
>
```

#### Register

The register option is selected to screen patients before getting into the healthcare facility. The user can select between a contagion Test or Triage.

- **Contagion Test**: Selected if the patient is at the healthcare facility for a contagion test. In this case, the patient's name and OHIP number is entered and then a ticket will be printed with a call number and estimated wait time for admission for the patient.
  
- **Triage**: If Triage is selected then in addition to the patient's name and OHIP number, the symptoms of the patient are entered. Then a ticket for Triage is printed with an estimated wait time for admission.

#### Admit

Admit is selected when the contagion Test area or the Triage section is ready to accept a patient. After selecting contagion or Triage, the patient with the next ticket in line will be called. Based on the time of the call, the average wait time for the next patient for that line up (contagion or Triage) will be updated.

## Project Structure

The project is structured as follows:

```
├── IOAble.cpp
├── IOAble.h
├── Menu.cpp
├── Menu.h
├── Patient.cpp
├── Patient.h
├── PreTriage.cpp
├── PreTriage.h
├── TestPatient.cpp
├── TestPatient.h
├── Ticket.cpp
├── Ticket.h
├── Time.cpp
├── Time.h
├── TriagePatient.cpp
├── TriagePatient.h
├── Utils.cpp
├── Utils.h
├── main.cpp
```

### Description of Files

- **IOAble.cpp / IOAble.h**: Handles input/output operations for the application.
- **Menu.cpp / Menu.h**: Manages the menu interface for user interaction.
- **Patient.cpp / Patient.h**: Defines the Patient class with attributes and methods for patient management.
- **PreTriage.cpp / PreTriage.h**: Implements the main functionality of the pre-triage system, including patient registration and ticketing.
- **TestPatient.cpp / TestPatient.h**: Contains test cases for validating the patient management system.
- **Ticket.cpp / Ticket.h**: Manages the ticketing system, providing patients with tickets and tracking wait times.
- **Time.cpp / Time.h**: Manages time-related functionalities within Ticket.
- **TriagePatient.cpp / TriagePatient.h**: Extends the Patient class with additional functionalities specific to triage patients.
- **Utils.cpp / Utils.h**: Instantiated globally, making it accessible to any module that includes “Utils.h”.
- **main.cpp**: The entry point of the application, initializing and running the main program loop.

## Data Files

The application uses two CSV files for testing patient data:

1. **bigdata.csv**: Used to test the program properly processes the data that is larger than maximum storage.
2. **smalldata.csv**: Used to save updated patient data upon program closure.Contains initial patient data for testing purposes.

## How to Run

1. Clone the repository to your local machine.
2. Compile the source files using a C++ compiler (e.g., g++).
3. Run the compiled executable.
