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

#ifndef SENECA_TESTPATIENT_H_
#define SENECA_TESTPATIENT_H_
#include <iostream>
#include "Patient.h"
using namespace std;
namespace seneca
{
	

	class TestPatient : public Patient
   {
	public:
		TestPatient();
		char type() const;
		ostream& write(std::ostream& os) const;
		istream& read(std::istream& is);
		   
   };
}

#endif