/* Citation and Sources...
Final Project 
Module: Menu
Filename: Menu.cpp
Version 1.2
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/10  Preliminary release
2024/3/12  Correct the return type of display and input methods
2024/3/17  Move validIntInput to Utils
-----------------------------------------------------------*/


#include <iostream>
#include <cstring>
#include <cctype>
#include <string>

#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace seneca {
    //Constructor
	Menu::Menu(const char* menuContent, int numberOfTabs) {
		if (menuContent != nullptr && numberOfTabs >= 0) {
            m_text = menuContent;
			m_numTabs = numberOfTabs;
            setNumOfOptions();
		}
        else {
            m_text = nullptr;
            m_numTabs = 0;
            m_numOptions = 0;
        }
	}

    //Get the number of options by reading m_text
    void Menu::setNumOfOptions() {  
        if (m_text == nullptr || m_text[0] == '\0') {
            m_numOptions = 0;
            cout << "Failed to get the number of menu options" << endl;
        }
        else
        {
            m_numOptions = 0;
            for (int i = 0; m_text[i] != '\0'; i++) {
                if (m_text[i] == '\n') {
                    m_numOptions++;
                }
            }            
        }
    }

    //Generate indentation for menu display based on the number of tabs -> "   "(3 space)
    char* Menu::createIndent() const{
        char* indent = new char[m_numTabs * 3 + 1]; 
        for (int i = 0; i < m_numTabs * 3; i++) {
            indent[i] = ' ';
        }
        indent[m_numTabs * 3] = '\0'; 
        return indent;
    }

    //Check if the object in Menu class is empty state
    Menu::operator bool()const {
        if (m_text == nullptr && m_numOptions == 0) {
            return false;
        }
        return true;
    }

    ostream& Menu::display(ostream& os) const{
        if (m_numOptions > 0) {
            char* indent = createIndent();
            os << indent;
            for (int i = 0; m_text[i] != '\0'; i++) {
                os << m_text[i];
                if (m_text[i] == '\n' && m_text[i + 1] != '\0') {
                    os << indent;
                }
            }
            os << "\n";
            os << indent << "0- Exit" << "\n";
            os << indent << "> ";
            delete[] indent;
        }
        else {
        	os << "No option provided" << "\n";
        }
        return os;
    }

    int& Menu::operator>>(int& selection) {
        display();
        selection = U.validIntInput(0, m_numOptions);
        return selection;  
    }
}


