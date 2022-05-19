/*********************************************************************
** Program Filename: location.h
** Author: Logan Saso
** Date: May 29th
** Description: Location definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef location_h
#define location_h

#include "event.h"

class Location {
	private:
		bool _has_event;
		Event * _event;
	public:
		bool get_has_event();
		Event * get_event();
		Location(Event *);
		Location();
		~Location();
		Location(const Location &);
		void operator=(const Location &);
};

#endif