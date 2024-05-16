/* Citation and Sources...
Final Project
Module: IOAble
Filename: IOAble.h
Version 1.0
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/13  Preliminary release
-----------------------------------------------------------*/


#ifndef SENECA_IOABLE_H_
#define SENECA_IOABLE_H_

#include <iostream>

using namespace std;
namespace seneca{
	class IOAble
	{
	public:
		//Write. This pure virtual function is for future ostream outputs. 
		virtual ostream& write(std::ostream& os) const = 0;
		//Read. This pure virtual function is for future istream inputs. 
		virtual istream& read(std::istream& is) = 0;
		//Vitual destructor. This class also has an empty virtual destructor.
		virtual ~IOAble() {};
	};

	//Overload the insertion operator to be able to insert the information of an IOAble object into ostream using the IOAble::write function.
	ostream& operator<<(std::ostream&, const IOAble&);

	//Overload the extraction operator to be able to extract information from an istream into an IOAble object using the IOAble::read function.
	istream& operator>>(std::istream&, IOAble&);

}
#endif
