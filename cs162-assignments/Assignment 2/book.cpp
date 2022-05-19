/*********************************************************************
** Program Filename: book.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Handles book class
** Input: book string
** Output: Book stuff
*********************************************************************/

#include <string>
#include "book.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

/*********************************************************************
** Function: Non-default constructor
** Description: Takes a string and makes a book object
** Parameters: const string source
** Pre-Conditions: We have a string
** Post-Conditions: We have a book object
*********************************************************************/
Book::Book(const std::string source)
{
	std::string delim = "|";
	int delim_offset = delim.length();
	int previous_delim = -delim_offset;
	int array_location = 0;
	std::string *destination = new std::string[4];

	do
	{
		destination[array_location++] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - 1);
		previous_delim = source.find(delim, previous_delim + delim_offset);
	} while (source.find(delim, previous_delim + delim_offset) != -1);

	destination[array_location++] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - 1);

	set_title(destination[0]);
	set_year(std::atoi(destination[1].c_str()));
	int array_size = 0;
	std::string *authors = split(destination[2], " and ", array_size);
	_authors = NULL;
	_checked_out_ids = new std::string[1];
	set_authors(authors, array_size);
	set_copies(std::atoi(destination[3].c_str()));
}

/*********************************************************************
** Function: Destructor
** Description: Destructs the book
** Parameters: No parameters
** Pre-Conditions: Book object exists
** Post-Conditions: There is no book object
*********************************************************************/
Book::~Book()
{
	if (_checked_out_num != 0)
		delete[] _checked_out_ids;
	delete[] _authors;
}

/*********************************************************************
** Function: Copy Constructor
** Description: Copies a book
** Parameters: Takes a book object to copy
** Pre-Conditions: A book exists
** Post-Conditions: An identical second book exists
*********************************************************************/
Book::Book(const Book &other)
{
	_copies = other.get_copies();
	_year = other.get_year();
	_checked_out_num = other.get_checked_out();
	_num_authors = other.get_num_authors();
	_title = other.get_title();

	//delete[] _authors;

	_authors = new std::string[_num_authors];
	std::string *other_authors = other.get_authors();
	for (int i = 0; i < _num_authors; i++)
	{
		_authors[i] = other_authors[i];
	}

	if (_checked_out_num != 0)
	{
		_checked_out_ids = new std::string[_checked_out_num];
		std::string *other_ids = other.get_checked_out_ids();
		for (int i = 0; i < _checked_out_num; i++)
		{
			_checked_out_ids[i] = other_ids[i];
		}
	}
}

/*********************************************************************
** Function: Default constructor. Doesn't do anything
** Description: Doesn't do anything
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: An empty uninitialized book object exists
*********************************************************************/
Book::Book()
{
}

/*********************************************************************
** Function: get title
** Description: Gets a title of book
** Parameters: none
** Pre-Conditions: title set
** Post-Conditions: title returned
*********************************************************************/
std::string Book::get_title() const
{
	return _title;
}

/*********************************************************************
** Function: get num authors
** Description: Gets the number of authors
** Parameters: None
** Pre-Conditions: Num authors sset
** Post-Conditions: Num authors returned
*********************************************************************/
int Book::get_num_authors() const
{
	return _num_authors;
}

/*********************************************************************
** Function: Get authors
** Description: Gets the number of authors
** Parameters: none
** Pre-Conditions: authors set
** Post-Conditions: authors returned
*********************************************************************/
std::string *Book::get_authors() const
{
	return _authors;
}

/*********************************************************************
** Function: get year
** Description: returns year
** Parameters: none
** Pre-Conditions: year is set
** Post-Conditions: returns year
*********************************************************************/
int Book::get_year() const
{
	return _year;
}

/*********************************************************************
** Function: get copies
** Description: returns copies
** Parameters: none
** Pre-Conditions: copies is set
** Post-Conditions: copies is returned
*********************************************************************/
int Book::get_copies() const
{
	return _copies;
}

/*********************************************************************
** Function: get checked out
** Description: returns checked out
** Parameters: none
** Pre-Conditions: checked out num set
** Post-Conditions: checked out num returned
*********************************************************************/
int Book::get_checked_out() const
{
	return _checked_out_num;
}

/*********************************************************************
** Function: set copies
** Description: sets copies
** Parameters: a copy
** Pre-Conditions: none
** Post-Conditions: copies is set
*********************************************************************/
void Book::set_copies(const int copies)
{
	_copies = copies;
}

/*********************************************************************
** Function: set num authors
** Description: sets num authors
** Parameters: num authors
** Pre-Conditions: none
** Post-Conditions: num authors is set
*********************************************************************/
void Book::set_num_authors(const int num_authors)
{
	_num_authors = num_authors;
}

/*********************************************************************
** Function: set title
** Description: sets titles
** Parameters: title
** Pre-Conditions: none
** Post-Conditions: title is set
*********************************************************************/
void Book::set_title(const std::string title)
{
	_title = title;
}

/*********************************************************************
** Function: set authors
** Description: sets authors
** Parameters: authors array, authors array length
** Pre-Conditions: none
** Post-Conditions: authors are set
*********************************************************************/
void Book::set_authors(const std::string *authors, const int num_authors)
{

	if (_authors != NULL)
	{
		delete[] _authors;
	}
	_authors = new std::string[num_authors];
	for (int i = 0; i < num_authors; i++)
	{
		_authors[i] = authors[i];
	}
	set_num_authors(num_authors);
}

/*********************************************************************
** Function: set year
** Description: set year
** Parameters: year
** Pre-Conditions: none
** Post-Conditions: year set
*********************************************************************/
void Book::set_year(const int year)
{
	_year = year;
}

/*********************************************************************
** Function: increase checked out num
** Description: increase checked out num
** Parameters: none
** Pre-Conditions: checked out num is set
** Post-Conditions: checked out num is one more than it was
*********************************************************************/
void Book::increase_checked_out_num()
{
	_checked_out_num++;
}

/*********************************************************************
** Function: decrease checked out num
** Description: decrease checked out num
** Parameters: none
** Pre-Conditions: checked out num is set
** Post-Conditions: checked out num is one less than it was
*********************************************************************/
void Book::decrease_checked_out_num()
{
	_checked_out_num--;
}

/*********************************************************************
** Function: set checked out num
** Description: set checked out num
** Parameters: num
** Pre-Conditions: none
** Post-Conditions: checked out num = num
*********************************************************************/
void Book::set_checked_out_num(int num)
{
	_checked_out_num = num;
}

/*********************************************************************
** Function: to string
** Description: Returns a stringified book
** Parameters: none
** Pre-Conditions: book exists
** Post-Conditions: returns stringified book like - Title|year|author and another author|copies
*********************************************************************/
std::string Book::to_string()
{
	char buffer[50];
	sprintf(buffer, "%d", _year);
	std::string placeholder = std::string(buffer);

	std::string the_book = _title + "|" + placeholder + "|";
	the_book += _authors[0];
	for (int i = 1; i < _num_authors; i++)
	{
		the_book += " and " + _authors[i];
	}

	char buffer2[50];
	sprintf(buffer2, "%d", _copies);
	std::string placeholder2 = std::string(buffer2);

	the_book += "|" + placeholder2;
	return the_book;
}

/*********************************************************************
** Function: extend array
** Description: Makes an array one longer
** Parameters: string array by reference, array size
** Pre-Conditions: array exists
** Post-Conditions: string array is one longer
*********************************************************************/
void Book::extend_array(std::string *&source, const int size)
{
	std::string *array = new std::string[size + 1];
	for (int i = 0; i < size; i++)
	{
		array[i] = source[i];
	}
	delete[] source;
	source = array;
}

/*********************************************************************
** Function: split
** Description: splits a string into an array
** Parameters: the string souce, string delimiter, and array size by reference
** Pre-Conditions: array size integer is made, source is a thing
** Post-Conditions: returns string array
*********************************************************************/
std::string *Book::split(const std::string source, std::string delim, int &array_size)
{
	int delim_offset = delim.length();
	int previous_delim = -delim_offset;
	int array_location = 0;
	std::string *destination = new std::string[1];
	while (source.find(delim, previous_delim + delim_offset) != -1)
	{
		if (array_location != 0)
		{ //This makes sure the array is the correct size. We have to skip one or else strings with nothing to split segfault
			extend_array(destination, array_location);
		}

		destination[array_location++] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - delim_offset);
		previous_delim = source.find(delim, previous_delim + delim_offset);
	}
	extend_array(destination, array_location);
	destination[array_location] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - delim_offset);

	array_size = array_location + 1;
	return destination;
}

/*********************************************************************
** Function: operator=
** Description: Like a copy constructor, but using the equalsign
** Parameters: a book by reference
** Pre-Conditions: a book exists
** Post-Conditions: a duplicate book exists
*********************************************************************/
Book &Book::operator=(const Book &other)
{
	_copies = other.get_copies();
	_year = other.get_year();
	_checked_out_num = other.get_checked_out();
	_num_authors = other.get_num_authors();
	_title = other.get_title();

	//delete[] _authors;

	_authors = new std::string[_num_authors];
	std::string *other_authors = other.get_authors();
	for (int i = 0; i < _num_authors; i++)
	{
		_authors[i] = other_authors[i];
	}

	if (_checked_out_num != 0)
	{
		_checked_out_ids = new std::string[_checked_out_num];
		std::string *other_ids = other.get_checked_out_ids();
		for (int i = 0; i < _checked_out_num; i++)
		{
			_checked_out_ids[i] = other_ids[i];
		}
	}

	return *this;
}

/*********************************************************************
** Function: set checked out ids
** Description: sets checked out ids array
** Parameters: string array ids
** Pre-Conditions: checked out ids exists
** Post-Conditions: checked out ids set
*********************************************************************/
void Book::set_checked_out_ids(const std::string *ids)
{

	if (_checked_out_ids != NULL && _checked_out_num != 0)
	{
		delete[] _checked_out_ids;
	}
	if (_checked_out_num == 0)
	{
		_checked_out_ids = new std::string[1];
	}
	else
	{
		_checked_out_ids = new std::string[_checked_out_num];
	}

	for (int i = 0; i < _checked_out_num; i++)
	{
		_checked_out_ids[i] = ids[i];
	}
}

/*********************************************************************
** Function: get checked out ids
** Description: returns checked out ids
** Parameters: none
** Pre-Conditions: checked out ids exists
** Post-Conditions: returns checked out ids
*********************************************************************/
std::string *Book::get_checked_out_ids() const
{
	return _checked_out_ids;
}