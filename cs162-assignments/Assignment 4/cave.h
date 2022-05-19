/*********************************************************************
** Program Filename: cave.h
** Author: Logan Saso
** Date: May 29th
** Description: Cave definitions
** Input: None
** Output: Definition
*********************************************************************/

#ifndef cave_h
#define cave_h

#include "event.h"

class Cave : public Event  {
	public:
		string get_nearby_string() const;
		void do_event(Trainer &);

}; //int because stones are numbers

#endif