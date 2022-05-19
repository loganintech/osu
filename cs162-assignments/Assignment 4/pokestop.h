/*********************************************************************
** Program Filename: pokestop.h
** Author: Logan Saso
** Date: May 29th
** Description: Pokestop definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef pokestop_h
#define pokestop_h

#include "event.h"

class Pokestop : public Event {
	public:
		string get_nearby_string() const;
		void do_event(Trainer &);
}; //int because pokeballs are numbers

#endif