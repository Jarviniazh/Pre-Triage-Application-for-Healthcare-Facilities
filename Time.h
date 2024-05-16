/* Citation and Sources...
Final Project 
Module: Time
Filename: Time.h
Version 1.1
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/10  Preliminary release
2024/3/12  Correct the return type of display and input methods

-----------------------------------------------------------*/


#ifndef SENECA_TIME_H_
#define SENECA_TIME_H_

#include <iostream>
using namespace std;

namespace seneca {
    class Time {
        int m_minutes;
        int m_displayHours;
        int m_displayMins;
        //Convert minute to display as HH:MM
        void convertDisplayFormat();

    public:
        Time(unsigned int min = 0u);
        Time& reset();
        //write
        ostream& display(std::ostream& os = cout) const;

        //read
        istream& read(std::istream& is = cin);

        operator unsigned int()const;
        Time& operator*= (int val);
        Time& operator-= (const Time& D);
        Time operator-(const Time& T) const;

        int getMins() const;

    };

    //Overload the insertion operator to be able to insert a Time object into an ostream object as described in the write method
    ostream& operator<<(std::ostream& os, const Time&);

    //Overload the extraction operator to be able to extract data from an istream object into the Time object as described in the read method.
    istream& operator>>(std::istream& is, Time&);
}
#endif