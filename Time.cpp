/* Citation and Sources...
Final Project 
Module: Time
Filename: Time.cpp
Version 1.2
Author   Jarvinia Zhao
Revision History
-----------------------------------------------------------
Date      Reason
2024/3/10  Preliminary release
2024/3/12  Correct the return type of display and input methods
2024/3/29  Improve the read method to get the correct input from data file
-----------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <string>


#include "Time.h"
#include "Utils.h"

using namespace std;
namespace seneca {
    //This method resets the Time object to the current time using the U.getTime() method
    Time& Time::reset() {
        return *this = U.getTime();
    }

    //This constructor initializes a Time object.
    Time::Time(unsigned int min)
    {
        m_minutes = min;
        convertDisplayFormat();
    }

    //Calculate HH and MM value of converted time solely in minutes into HH:MM format
    void Time::convertDisplayFormat()
    {
        if (m_minutes == 0)
        {
            m_displayHours = 0;
            m_displayMins = 0;
        }
        else
        {
            m_displayHours = m_minutes / 60;
            m_displayMins = m_minutes % 60;
        }
    }

    //write
    ostream& Time::display(std::ostream& os) const
    {
        os.width(2);
        os.fill('0');
        os << m_displayHours << ":";
        os.width(2);
        os.fill('0');
        os << m_displayMins;
        return os;
    }

    //read
    istream& Time::read(std::istream& is)
    {
        int hour{};
        int mins{};
        do {
            //take the first input to hour
        	is >> hour;
            if (is.fail())
            {
                is.setstate(std::ios::failbit);
                break;
            }
            //Check if there is a clone in input
            if (is.peek() != ':')
            {
                is.setstate(std::ios::failbit);
                break;
            }
            // Ignore the colon 
        	is.ignore();  
            //take the second input to mins
            is >> mins;
            if (is.fail())
            {
                is.setstate(std::ios::failbit);
                break;
            }

            m_minutes = hour * 60 + mins;
            convertDisplayFormat();
        } while (false);

        return is;
    }


    //This operator overloads the cast to unsigned int for the Time class. If a Time object is cast to an unsigned integer, it will return the number of minutes held in the object
    Time::operator unsigned int()const {
        return m_minutes;
    }

    //This operator overloads the multiplication assignment *= for the Time class. It multiplies the number of minutes held in the Time object by val, then returns a reference to the current object.
    Time& Time::operator*= (int val) {
        if (val > 0) {
            m_minutes *= val;
            convertDisplayFormat();
        }
        return *this;
    }

    //This operator overloads the subtraction assignment -= for the Time class. It calculates the time difference between the current Time object and the Time object D passed as an argument.
    Time& Time::operator-= (const Time& D) {
        if (m_minutes < D.m_minutes) {
            m_minutes = (m_minutes + 1440) - D.m_minutes;
        }
        else {
            m_minutes -= D.m_minutes;
        }
        convertDisplayFormat();
        return *this;
    }

    //This operator performs the same calculation as the subtraction assignment -= overload, except that it does not have a side effect (i.e., it does not modify the current object).
    Time Time::operator-(const Time& T)const {
        Time temp;
        if (m_minutes < T.m_minutes) {
            temp.m_minutes = (m_minutes + 1440) - T.m_minutes;
        }
        else {
            temp.m_minutes = m_minutes - T.m_minutes;
        }
        temp.convertDisplayFormat();
        return temp;
    }


    ostream& operator<<(std::ostream& os, const Time& time)
    {
        time.display(os);
        return os;
    }

    istream& operator>>(std::istream& is, Time& time)
    {
        time.read(is);
        return is;
    }


    int Time::getMins() const
    {
	    return m_minutes;
    }

}