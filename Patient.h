/* Citation and Sources...
Final Project 
Module: Patient
Filename: Patient.h
Version 1.1
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/20  Preliminary release
2024/3/24  Replaced the macro MAX_NAME_LENGTH with a constant
-----------------------------------------------------------*/


#ifndef SENECA_PATIENT_H_
#define SENECA_PATIENT_H_


#include "IOAble.h"
#include "Ticket.h"


namespace seneca {
    const int max_name_length = 50;

    class Patient : public IOAble
    {
        char* m_name; //Patient name
        int m_ohip; //OHIP number, 9 digits
        Ticket m_ticket; //Ticket object is used to represent the ticket number and time for the lineup.
        //This function initializes a Patient object by copying data from another Patient object.
        void init(const Patient&);
    public:
        //Instantiate a Patient object by providing a ticket number(an integer).This ticket number will be utilized to initialize the Ticket member attribute.
        Patient(int ticketNumber);
        // Copy constructor
    	Patient(const Patient&);
        // Assignment operator overload
    	Patient& operator=(const Patient&);
		// Destructor
    	virtual ~Patient();
        //pure virtual function that returns a character.
    	virtual char type() const= 0;
        // Overload the comparison operator to compare the type of the patient with a character.
    	bool operator==(char) const;
        // Overload the comparison operator to compare the type of the patient with another patient.
    	bool operator==(const Patient&) const;
        // Set the arrival time of the patient to the current time.
    	void setArrivalTime();
        // Return the arrival time of the patient.
        Time time() const;
		// Return the ticket number of the patient.
        int number() const;
        //When a patient is casted to a boolean, return true if the patient is valid, false otherwise.
        operator bool() const;
    	//If a patient is casted to a constant character pointer, return the address of the patient's name.
        operator const char* () const;
        //Write the patient information into the ostream
        ostream& write(std::ostream& os) const;
        //Read the patient information from the istream
    	istream& read(std::istream& is);

    };
}

#endif //MS1_PATIENT_H
