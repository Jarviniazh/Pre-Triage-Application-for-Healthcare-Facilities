/* Citation and Sources...
Final Project 
Module: PreTriage
Filename: PreTriage.cpp
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/4/07  Preliminary release
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "PreTriage.h"
#include "Utils.h"
#include "Menu.h"

using namespace std;

namespace seneca
{
	//A PreTriage class is instantiated using the data file name.
	//The constructor also initializes the two Time attributes, Contagion test and Triage, to 15 and 5 respectively.
	PreTriage::PreTriage(const char* filename): m_avgContagionWait(15), m_avgTriageWait(5)
	{
		m_dataFilename = new char[strlen(filename) + 1];
		strcpy(m_dataFilename, filename);
		m_numLineup = 0;
		//The constructor then loads all the data from the data file, if possible.
		load();
	}

	PreTriage::~PreTriage()
	{
		//Save the data
		save();
		//Iterates through the patient lineup and deletes the elements one by one.
		for (int i = 0; i < m_numLineup; i++)
		{
			delete m_lineup[i];
		}
		//If there are any other dynamically allocated memory, it will delete them as well
		delete[] m_dataFilename;
	}


	Time PreTriage::getWaitTime(const Patient& patient) const
	{
		int numWaiting = 0;
		Time totalWaiting;

		//Find the number of Patients in the lineup that match the type of the received Patient Reference.
		for(int i =0; i < m_numLineup; i++)
		{
			if(m_lineup[i]->type() == patient.type())
			{
				numWaiting++;
			}
		}

		//Returns the product of estimated wait time(for that type of patient) to the number of patients found
		totalWaiting = numWaiting * (patient.type() == 'C' ? m_avgContagionWait : m_avgTriageWait);
		return totalWaiting;

	}

	void PreTriage::setAverageWaitTime(const Patient& patient)
	{
		int currentTime = U.getTime();
		int patientTicketTime = patient.time().getMins();
		int patientTicketNum = patient.number();

		//AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN
		if(patient.type() == 'C')
		{
			m_avgContagionWait = ((currentTime - patientTicketTime) + (patientTicketNum - 1) * m_avgContagionWait) / patientTicketNum;
		}
		else
		{
			m_avgTriageWait = ((currentTime - patientTicketTime) + (patientTicketNum - 1) * m_avgTriageWait) / patientTicketNum;
		}
	}



	int PreTriage::indexOfFirstInLine(char type) const
	{
		//This function iterates over the lineup array of pointers from the beginning.
		for(int i = 0; i < m_numLineup; i++)
		{
			//For each patient, it compares the patient's type with the specified type (using overloaded operator==). 
			if(m_lineup[i]->type() == type)
			{
				// If a match is found, the function returns the found index. 
				return i;
			}
		}
		//If the function iterates over the entire lineup without finding a match, it returns - 1
		return -1;
	}


	void PreTriage::load()
	{
		Patient* temp = nullptr;
		ifstream datafile(m_dataFilename);

		//print "Loading data...", goto newline
		cout << "Loading data..." << endl;

		if (datafile.is_open())
		{
			//read the contagion test average wait time from the data file
			m_avgContagionWait.read(datafile);
			//ignore the comma
			datafile.ignore(1, ',');
			//read the triage average wait time from the data file
			m_avgTriageWait.read(datafile);
			//ignore the newline
			datafile.ignore(1000, '\n');

			char typeChar;
			//In a loop from 0 to the maximum number of patients
			for (int i = 0; i < maxNoOfPatients; i++)
			{
				//datafile.get(typeChar);
				datafile >> typeChar;
				datafile.ignore(1, ',');

				if (datafile.eof())
				{
					break;
				}
				if (typeChar == 'C')
				{
					temp = new TestPatient();
					if (temp)
					{
						temp->read(datafile);
						m_lineup[i] = temp;
						m_numLineup++;
					}
				}
				else if (typeChar == 'T')
				{
					temp = new TriagePatient();
					if (temp)
					{
						temp->read(datafile);
						m_lineup[i] = temp;
						m_numLineup++;
					}
				}
				else
				{
					cout << "Error: Unrecognized character" << endl;
				}
			}
			//At the end print these messages and go to newline:
			//if there are still records left in the file, print the following warning:
			if (m_numLineup == maxNoOfPatients && !datafile.eof())
			{
				cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
				cout << m_numLineup << " Records imported..." << endl;
				cout << endl;
			}
			//if no records were read print 
			else if (m_numLineup == 0)
			{
				cout << "No data or bad data file!" << endl;
				cout << endl;
			}
			else
			{
				cout << m_numLineup << " Records imported..." << endl;
				cout << endl;
			}

			datafile.close();
		}
		else
		{
			cout << "No data or bad data file!" << endl;
			cout << endl;
		}
	}

	void PreTriage::save() const
	{
		int numContaigen = 0;
		int numTriage = 0;

		//Opens the data file for output.
		ofstream datafile(m_dataFilename);
		if (datafile.is_open())
		{
			//Inserts "Saving lineup...", into cout and goes to newline
			cout << "Saving lineup..." << endl;
			//Inserts the average Contaigen Test and Triage wait times, comma-separated into the data file and goes to newline.
			m_avgContagionWait.display(datafile);
			datafile << ',';
			m_avgTriageWait.display(datafile);
			datafile << endl;
			//Iterates through the lineup array of Patient pointers
			for (int i = 0; i < m_numLineup; i++)
			{
				//Inserts them into the data file and goes to newline
				m_lineup[i]->write(datafile) << endl;
				if(m_lineup[i]->type() == 'C')
				{
					numContaigen++;
				}
				else
				{
					numTriage++;
				}
			}
			//Inserts the number of records saved for each type of patient into cout and goes to newline
			cout << numContaigen << " Contagion Tests and " << numTriage << " Triage records were saved!" << endl;
			datafile.close();
		}
		else
		{
			cout << "Fail to save the data file" << endl;
		}
	}

	void PreTriage::reg()
	{
		//Create a Menu object for a sub-menu for patient type selection with one indentation (1 tab) as follows to be displayed later.
		Menu reg("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);

		//If the lineup size has reached the maximum number of patients, print "Line up full!", go to a new line and terminate the function
		if (m_numLineup == maxNoOfPatients)
		{
			cout << "Line up full!" << endl;
			return;
		}
		else
		{
			int selection;
			//display the sub-menu and receive the selection
			reg >> selection;
			cin.ignore();
			switch (selection)
			{
			//if the selection is 1, in the next available lineup pointer instantiate a Contagion Test Patient
			case 1:
				m_lineup[m_numLineup] = new TestPatient();
				break;
			//if the selection is 2, in the next available lineup pointer instantiate a Triage Patient
			case 2:
				m_lineup[m_numLineup] = new TriagePatient();
				break;
			//if the selection is 0, terminate the function
			case 0:
				cout << "Exiting registration..." << endl;
				return;
			}
			//Set the patient's arrival time 
			m_lineup[m_numLineup]->setArrivalTime();
			cout << "Please enter patient information: " << endl;
			//Extract the patient from cin
			m_lineup[m_numLineup]->read(cin);
			//go to newline
			cout << endl;
			cout << "******************************************" << endl;
			m_lineup[m_numLineup]->write(cout);
			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[m_numLineup]) << endl;
			cout << "******************************************" << endl;
			cout << endl;
			//Increase the lineup size
			m_numLineup++;
		}
	}

	void PreTriage::admit()
	{
		int selection;
		char type;
		int patientIndex;

		//Create a Menu object for a sub - menu for patient type selection with one indentation(1 tab) as follows to be displayed later.
		Menu admit("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
		//display the sub-menu and receive the selection to determine the type of patient to admit.
		admit >> selection;
		switch (selection)
		{
		//if the selection is 1, the type is 'C'
		case 1:
				type = 'C';
			break;
		//if the selection is 2, the type is 'T'
		case 2:
				type = 'T';
			break;
		//if the selection is 0, terminate the functi
		case 0:
			cout << "Exiting admission..." << endl;
			return;
		}
		//find the index of the next patient in the line for the type (use indexOfFirstInLine method)
		patientIndex = indexOfFirstInLine(type);
		//if no patient is found, print "Lineup is empty!\n" and terminate the function
		if(patientIndex == -1)
		{
			cout << "Lineup is empty!" << endl;
			return;
		}
		else
		{
			cout << endl;
			cout << "******************************************" << endl;
			cout << "Call time: [" << m_lineup[patientIndex]->time().reset() << "]" << endl;
			cout << "Calling at for ";
			m_lineup[patientIndex]->write(cout);
			cout << "******************************************" << endl;
			cout << endl;
			//set the average wait time for the patient (using setAverageWaitTime method)
			setAverageWaitTime(*m_lineup[patientIndex]);
			//remove the patient from the lineup using the removeDynamicElement function template.
			removeDynamicElement(m_lineup, patientIndex, m_numLineup);
		}
	}

	void PreTriage::lineup() const
	{
		int selection;
		char type;
		int patientIndex;

		//Display the sub-menu
		Menu lineup("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
		lineup >> selection;

		switch (selection)
		{
		case 1:
			type = 'C';
			break;
		case 2:
			type = 'T';
			break;
		case 0:
			cout << "Exiting lineup..." << endl;
			return;
		}

		patientIndex = indexOfFirstInLine(type);
		if (patientIndex == -1)
		{
			//if there are no patients in the lineup print "Line up is empty!\n" instead.
			cout << "Lineup is empty!" << endl;
			return;
		}
		else
		{
			cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			int j = 0;

			//iterate through the lineup array of patient pointers and insert only the type of patents selected by the user into clog.
			for(int i = 0; i < m_numLineup; i++)
			{
				if(m_lineup[i]->type() == type)
				{
					clog.setf(ios::left);
					clog.width(3);
					clog.fill(' ');
					clog << j + 1;
					clog.unsetf(ios::left);
					clog << " - ";
					clog << *m_lineup[i];
					clog << endl;
					j++;
				}
			}
			cout << "-------------------------------------------------------------------------------" << endl;
		}
	}

	void PreTriage::run()
	{
		int selection;
		
		do {
			//Create the Main system menu
			Menu main("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
			//display the menu and get the selection
			main >> selection;
			switch (selection)
			{
			//if the selection is 1 call the register method
			case 1:
				reg();
				break;
			//if the selection is 2 call the admit method
			case 2:
				admit();
				break;
			//if the selection is 3 call the lineup method
			case 3:
				lineup();
				break;
			}
		} while (selection != 0); //if the selection is 0, quit the method
	}
}
