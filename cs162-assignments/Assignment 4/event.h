/*********************************************************************
** Program Filename: event.h
** Author: Logan Saso
** Date: May 29th
** Description: Event definition
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef event_h
#define event_h


#include <string>
#include "trainer.h"

using namespace std;

class Event {
	public:
		virtual string get_nearby_string() const = 0;
		virtual void do_event(Trainer &) = 0;
};

#endif