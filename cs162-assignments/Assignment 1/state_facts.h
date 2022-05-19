#ifndef state_facts_h
#define state_facts_h

struct county {
	std::string name;
	std::string *city;
	int cities;
	int population;
	float avg_income;
	float avg_house;
};
struct state {
	std::string name;
	struct county *c;
	int counties;
	int population;
};

#endif