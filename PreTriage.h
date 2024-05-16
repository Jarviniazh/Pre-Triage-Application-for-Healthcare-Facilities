/* Citation and Sources...
Final Project 
Module: PreTriage
Filename: PreTriage.h
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/4/07  Preliminary release
-----------------------------------------------------------*/


#ifndef SENECA_PRETRIAGE_H_
#define SENECA_PRETRIAGE_H_
#include <iostream>
#include "TestPatient.h"
#include "TriagePatient.h"
using namespace std;
namespace seneca
{
	const int maxNoOfPatients = 100;

	class PreTriage
	{
		//Add two Time object attributes to the class to keep track of the average wait time for the Contaigen test and the Triage patients separately.
		Time m_avgContagionWait;
		Time m_avgTriageWait;
		//Create an array of pointers to Patient objects. 
		Patient* m_lineup[maxNoOfPatients] = { nullptr };
		//A C-string to hold the path and name of the data file.
		char* m_dataFilename;
		//Create an attribute to hold the actual number of patients in the lineup.
		int m_numLineup;

		//Receives a constant Patient Reference and returns the total estimated wait time for that type of Patient
		Time getWaitTime(const Patient&) const;
		//Receives the reference of the admitting patient and adjusts the average wait time of that type of patient based on the admittance time of the patient.
		void setAverageWaitTime(const Patient&);
		//Receives a character representing the type of patient (C for Contaigen, T for Triage).
		int indexOfFirstInLine(char) const;
		//Loads the average wait times and the patient records from the data file and stores them in the lineup array of pointers.
		void load();
		//Saves the patient records to the data file.
		void save() const;
		//Registers a new patient.
		void reg();
		//Calls the next patient in line to be admitted to the contagion test centre or Triage centre
		void admit();
		//Prints a report on patients currently in the lineup.
		void lineup() const; 

	public:
		//A one-argument constructor that receives the name of the data file and initializes the PreTriage object.
		PreTriage(const char* filename);
		//Destructor
		~PreTriage();
		//Runs the PreTriage main application.
		void run();

	};
}

#endif