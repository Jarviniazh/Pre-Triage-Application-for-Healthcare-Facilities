/***********************************************************************
// Project
//
// File  Utils.cpp
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
// Jarvinia Zhao        2021/3/17      Add validIntInput and strcmp method
// Jarvinia Zhao        2021/3/20      Replace strcmp method with the one in ms4
// Jarvinia Zhao        2021/4/04      Modify the validIntInput method to make it more simple
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "Utils.h"
using namespace std;
namespace seneca {
   // start provided code
   bool debug = false;
   Utils U;
   int Utils::getTime() {
      int mins = -1;
      if (debug) {
         int duration[]{ 3,5,9,20,30 };
         mins = (m_testMins %= 1440);
         m_testMins += duration[m_testIndex++ % 5];
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   void Utils::setDebugTime(int hour, int min) {
      seneca::debug = true;
      m_testMins = hour * 60 + min;
   }

   //A function called "strcmp" is added to the Utils module that works exactly like the strcmp in the <cstring> header file
   int Utils::strcmp(const char* str1, const char* str2)const {
       int i;
       for (i = 0; str1[i] && str2[i] && str1[i] == str2[i]; i++);
       return str1[i] - str2[i];
   }

   //Valid the user input
   int Utils::validIntInput(int min, int max) {
       int input;
       bool isValid = false;

       while (!isValid) {
           cin >> input;
           // Check if the input is an integer
           if (cin.fail())
           {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Bad integer value, try again: ";
           }
           //Check if there is a character after the integer
           else if (cin.peek() != '\n')
           {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Only enter an integer, try again: ";
           }
           else
           {
               // Check the value within the range
               if (input >= min && input <= max)
               {
                   isValid = true;
               }
               else
               {
                   cout << "Invalid value enterd, retry[" << min << " <= value <= " << max << "]: ";
               }
           }
       }
       return input;
   }
}