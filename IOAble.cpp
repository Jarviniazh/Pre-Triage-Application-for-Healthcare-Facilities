/* Citation and Sources...
Final Project 
Module: IOAble
Filename: IOAble.cpp
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/13  Preliminary release
-----------------------------------------------------------*/

#include <iostream>
#include "IOAble.h"

using namespace std;

namespace seneca
{
	//Overload operator>>
	istream& operator>>(std::istream& is, IOAble& io)
	{
		io.read(is);
		return is;
	}

	//Overload operator<<
	ostream& operator<<(std::ostream& os, const IOAble& io)
	{
		io.write(os);
		return os;
	}
}
