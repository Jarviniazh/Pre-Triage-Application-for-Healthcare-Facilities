#ifndef SENECA_TICKET_H_
#define SENECA_TICKET_H_
#include <iostream>
#include "Time.h"
#include "IOAble.h"
namespace seneca {
   class Ticket:public IOAble{
      Time m_time;
      int m_number; //The ticket number; A sequential integer, starting from one and unique for each lineup.
   public:
      Ticket(int number);
      Time time()const; //Getter, A query that returns the time when the ticket was issued.
      int number()const; //Getter, A query returning the number of the ticket
      void resetTime(); //Sets the Ticket time to the current time.
      std::ostream& write(std::ostream& ostr )const;
      std::istream& read(std::istream& istr);
   };
}
#endif // !SENECA_TICKET_H_
