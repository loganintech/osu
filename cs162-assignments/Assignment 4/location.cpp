/*********************************************************************
** Program Filename: location.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Location functionality
** Input: None
** Output: Functions
*********************************************************************/
#include "event.h"
#include "pokemon_encounter.h"
#include "cave.h"
#include "pokestop.h"
#include "location.h"

bool Location::get_has_event() {
	return _has_event;
}

Event * Location::get_event() {
	return _event;	
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Location::Location(Event * event) {
	_event = event;
	_has_event = true;
}

/*********************************************************************
** Function: Destructor
** Description: Destructs
** Parameters: none
** Pre-Conditions: Object exists
** Post-Conditions: Object destroyed
*********************************************************************/
Location::~Location() {
	delete _event;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Location::Location() {
	_has_event = false;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Location::Location(const Location &other) {
	_has_event = other._has_event;	
	if(_has_event) *_event = *other._event;
}

/*********************************************************************
** Function: Operator=
** Description: Object set
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object set to other object
*********************************************************************/
void Location::operator=(const Location &other) {
	_has_event = other._has_event;	
	if(_has_event) *_event = *other._event;
}

