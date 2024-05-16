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

#ifndef SENECA_TRIAGEPATIENT_H_
#define SENECA_TRIAGEPATIENT_H_
#include <iostream>
#include "Patient.h"
using namespace std;

namespace seneca
{
	const int maxSymptomsLen = 512;

	class TriagePatient : public Patient
	{
		char* m_symptoms;
	public:
		TriagePatient();
		TriagePatient(const TriagePatient& source);
		TriagePatient& operator=(const TriagePatient& source);
		virtual ~TriagePatient();
		char type() const;
		ostream& write(ostream& os) const;
		istream& read(istream& is);

	};
}

#endif