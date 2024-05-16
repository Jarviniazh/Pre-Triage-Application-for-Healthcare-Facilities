/* Citation and Sources...
Final Project 
Module: Patient
Filename: Patient.cpp
Version 1.2
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/20  Preliminary release
2024/3/24  Modified the read function and replaced the macro with a constant
2024/3/29  Improve read method to make it cleaner
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Patient.h"
#include "Utils.h"

using namespace std;

namespace seneca
{
	// This function initializes a Patient object by copying data from another Patient object.
	void Patient::init(const Patient& source)
	{
		if (source.m_name != nullptr)
		{
            m_name = new char[strlen(source.m_name) + 1];
            strcpy(m_name, source.m_name);
		}
		else
		{
			m_name = nullptr;
		}
		m_ohip = source.m_ohip;
	}

	//Instantiate a Patient object by providing a ticket number(an integer).This ticket number will be utilized to initialize the Ticket member attribute.
	Patient::Patient(int ticketNumber): m_ticket(ticketNumber){
        m_name = new char[max_name_length + 1];
		m_ohip = 0;
	}

	// Copy constructor
    /*Patient::Patient(const Patient& source) : m_ticket(source.m_ticket)
	{
		init(source);
	}*/

	Patient::Patient(const Patient& source) : m_ticket(source.m_ticket.number())
	{
		init(source);
	}

	// Assignment operator overload
    Patient& Patient::operator=(const Patient& source)
	{
		if (this != &source)
		{
			delete[] m_name;
			init(source);
			m_ticket = source.m_ticket;
		}
		return *this;
	}

	// Destructor
	Patient::~Patient()
	{
		delete[] m_name;
	}

    // Overload the comparison operator to compare the type of the patient with a character.
    bool Patient::operator==(char rhs) const
	{
		return type() == rhs;
	}

	// Overload the comparison operator to compare the type of the patient with another patient.
    bool Patient::operator==(const Patient& other) const
	{
		return type() == other.type();
	}

	// Set the arrival time of the patient to the current time.
    void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	// Return the time of the patient's ticket.
    Time Patient::time() const
	{
		return m_ticket.time();
	}

	// Return the number of the patient's ticket.
    int Patient::number() const
	{
		return m_ticket.number();
	}

	// Return the type of the patient.
    Patient::operator bool() const
	{
		return m_name != nullptr  && m_ohip > 0; 
	}

    //If a patient is casted to a constant character pointer, return the address of the patient's name.
    Patient::operator const char* () const
	{
		return m_name;
    }

	// Write the patient's information to the output stream.
    ostream& Patient::write(std::ostream& os) const
	{
		if(&os == &clog){
			if (*this)
			{
				int nameWidth = 53;
				int ticketWidth = 5;

				os.setf(ios::left);
				os.width(nameWidth);
				os.fill('.');
				os << m_name;
				os.fill(' ');
				os.unsetf(ios::left);
				os << m_ohip;
				
				os.setf(ios::right);
				os.width(ticketWidth);
				os << m_ticket.number();
				os.unsetf(ios::right);
				//os << m_ticket.number();
				os << " " << m_ticket.time();
				
			}
			else
			{
				os << "Invalid Patient Record";
			}
		}
		else if (&os == &cout)
		{
			if(*this)
			{
				os << m_ticket << "\n";
				os << m_name << ", OHIP: " << m_ohip << "\n";
			}
			else
			{
				os << "Invalid Patient Record" << "\n";
			}
		}
		else
		{
			os << type() << ',' << m_name << ',' << m_ohip << ',';
			m_ticket.write(os);
		}
		return os;
	}

	// Read the patient's information from the input stream.
    istream& Patient::read(std::istream& is)
    {
		char buffer[max_name_length + 1]; // Buffer to store the name input
		if(&is == &cin)
	    {
			cout << "Name: ";
			is.getline(buffer, max_name_length + 1);
	    	delete[] m_name;
		    m_name = new char[max_name_length + 1];
   		    strcpy(m_name, buffer);
		    cout << "OHIP: ";
		    m_ohip = U.validIntInput(100000000, 999999999);
	    }
	    else
	    {
			is.get(buffer, max_name_length + 1, ',');
			is.ignore();
			// Check for an empty input
			if(is.eof())
			{
				return is;
			}
			// Check for a failed input
			if (is.fail()) {
				is.clear();
				// Discard characters until the next comma or EOF
				while (is.get() != ',' && !is.eof());
			}
			//Copy the buffer to the m_name
			delete[] m_name;
			m_name = new char[strlen(buffer) + 1];
			strcpy(m_name, buffer);

			// Read the OHIP number
			is >> m_ohip;
			is.ignore(1000, ',');

			// Read the ticket information
			m_ticket.read(is);
		}
	    return is;
    }
}
