/* Citation and Sources...
Final Project 
Module: TestPatient
Filename: TestPatient.cpp
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/29  Preliminary release
-----------------------------------------------------------*/

#include <iostream>
#include "TestPatient.h"

using namespace std;
namespace seneca{
	static int nextTestTicket = 1;

	TestPatient::TestPatient() : Patient(nextTestTicket)
	{
		nextTestTicket++;
	}
	char TestPatient::type() const
	{
		return 'C';
	}
	//
	ostream& TestPatient::write(std::ostream& os) const
	{
		//If the ostream is cout it will insert "Contagion TEST" into the ostream object and goes to newline.
		if(&os == &cout)
		{
			os << "Contagion TEST" << endl;
		}
		//Then it will call the write() function of the base class Patient.
		Patient::write(os);
		//At end it will return the ostream reference.
		return os;
	}
	//
	istream& TestPatient::read(std::istream& is)
	{
		//It will call the read function of the base class Patient.
		Patient::read(is);
		//If the istream is not cin (reading from a file) then it should set the nextTestTicket to the ticket number of this patient + 1.
		if(&is != &cin)
		{
			nextTestTicket = number() + 1;
		}
		//At end it will return the istream reference.
		return is;
	}
}
