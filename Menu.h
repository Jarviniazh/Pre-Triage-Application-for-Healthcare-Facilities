/* Citation and Sources...
Final Project
Module: Menu
Filename: Menu.h
Version 1.2
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/10  Preliminary release
2024/3/12  Correct the return type of display and input methods
2024/3/17  Move validIntInput to Utils
-----------------------------------------------------------*/


#ifndef SENECA_MENU_H_
#define SENECA_MENU_H_

#include <iostream>
namespace seneca {
	class Menu {
		const char* m_text;
		int m_numOptions;
		int m_numTabs;

		//Get the number of options from content m_text
		void setNumOfOptions();
		void setIndexOfOption();
		char* createIndent() const;
		//Check empty state
		operator bool() const;

	public: 
		Menu(const char* menuContent, int numberOfTabs = 0);

		//Menu can not be copied or assigned to another Menu object
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

		//The display method is responsible for presenting the Menu content to the user.
		std::ostream& display(std::ostream& os = std::cout) const;

		int& operator>>(int& selection);
	};
}
#endif