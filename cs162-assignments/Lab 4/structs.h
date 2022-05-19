#ifndef structs_h
#define structs_h

#include <string>
struct hours {
	int begin_time;
	int end_time;
};

struct book {
	std::string title;
	int num_authors;
	std::string *authors;
	int year;
	int copies;
	bool checked_out;
	int checked_out_num;
};

#endif