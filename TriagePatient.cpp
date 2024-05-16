/* Citation and Sources...
Final Project 
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/29  Preliminary release
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TriagePatient.h"

using namespace std;
namespace seneca
{
	static int nextTriageTicket = 1;

	TriagePatient::TriagePatient() : Patient(nextTriageTicket)
	{
		m_symptoms = nullptr;
		nextTriageTicket ++;
	}
	TriagePatient::TriagePatient(const TriagePatient& source) : Patient(source)
	{
		if (source.m_symptoms != nullptr)
		{
			m_symptoms = new char[maxSymptomsLen + 1];
			strcpy(m_symptoms, source.m_symptoms);
		}
		else
		{
			m_symptoms = nullptr;
		}
	}
	TriagePatient& TriagePatient::operator=(const TriagePatient& source)	
	{
		if (this != &source)
		{
			Patient::operator=(source);
			delete[] m_symptoms;
			m_symptoms = new char[strlen(source.m_symptoms) + 1];
			strcpy(m_symptoms, source.m_symptoms);
		}
		else
		{
			m_symptoms = nullptr;
		}
		return *this;
	}
	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
	}
	char TriagePatient::type() const
	{
		return 'T';
	}
	ostream& TriagePatient::write(ostream& os) const
	{
		//If the ostream reference is cout, it prints a "TRIAGE" label, inserts the patient, and displays the symptoms.
		if(&os == &cout)
		{
			os << "TRIAGE" << endl;
			Patient::write(os);
			os << "Symptoms: " << m_symptoms << endl;
		}	
		// If it is clog, it only prints the patient information in a linear format with no symptoms.
		else if (&os == &clog)
		{
			Patient::write(os);

		}
		// If it is neither cout nor clog, it inserts the information in a comma-separated format.
		else
		{
			Patient::write(os);
			os << "," << m_symptoms;
		}
		return os;
	}
	istream& TriagePatient::read(istream& is)
	{
		char buffer[maxSymptomsLen + 1];
		delete[] m_symptoms;
		Patient::read(is);

		if (&is != &cin)
		{
			//ignore the comma
			is.ignore();
			is.getline(buffer, maxSymptomsLen, '\n');
			if (is.fail())
			{
				is.clear();
				//delete[] m_symptoms;
				m_symptoms = nullptr;
			}
			else
			{
				m_symptoms = new char[strlen(buffer) + 1];
				strcpy(m_symptoms, buffer);
				nextTriageTicket = number() + 1;
			}
		}
		else
		{
			is.ignore();
			cout << "Symptoms: ";
			is.getline(buffer, maxSymptomsLen, '\n');
			if (is.fail())
			{
				is.clear();
				//delete[] m_symptoms;
				m_symptoms = nullptr;
			}
			else
			{
				m_symptoms = new char[strlen(buffer) + 1];
				strcpy(m_symptoms, buffer);
			}

		}
		return is;
	}
}