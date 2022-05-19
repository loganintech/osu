#include <string>
#include <iostream>
#include <cstdlib>
#include "creature.h"
#include "balrog.h"
#include "paladin.h"
using namespace std;

class Vehicle
{
private:
	bool _motorized;
	int _wheels;
	int _speed;
	string _description;
	Creature *_driver;

public:
	Vehicle(bool motorized, int wheels, int speed, string description, Creature *driver)
	{
		_motorized = motorized;
		_wheels = wheels;
		_speed = speed;
		_description = description;
		_driver = driver;
	}
	bool get_motorized() const
	{
		return _motorized;
	}
	string getVehicle() const
	{
		return _description;
	}
	int get_wheels() const
	{
		return _wheels;
	}
	int get_speed() const
	{
		return _speed;
	}
	int get_distance() const
	{
		return _speed * (rand() % 10);
	}
	void set_motorized(const bool motorized)
	{
		_motorized = motorized;
	}
	void set_wheels(const int wheels)
	{
		_wheels = wheels;
	}
	void set_speed(const int speed)
	{
		_speed = speed;
	}
	bool operator<(const Vehicle &other)
	{
		return this->get_distance() < other.get_distance();
	}
	bool operator>(const Vehicle &other)
	{
		return this->get_distance() > other.get_distance();
	}
	Creature *getDriver()
	{
		return _driver;
	}
};

class Bike : public Vehicle
{
public:
	Bike(Creature *driver) : Vehicle(false, 2, 10, "Bike", driver) {}
};

class Skateboard : public Vehicle
{
public:
	Skateboard(Creature *driver) : Vehicle(false, 4, 6, "Skateboard", driver) {}
};

class RaceCar : public Vehicle
{
public:
	RaceCar(Creature *driver) : Vehicle(true, 4, 120, "Race Car", driver) {}
};

class Motorcycle : public Vehicle
{
public:
	Motorcycle(Creature *driver) : Vehicle(true, 2, 140, "Motorcycle", driver) {}
};

#include "race.h"

int main()
{
	Balrog *a_balrog = new Balrog();
	Motorcycle *motorcycle = new Motorcycle(a_balrog);
	Paladin *a_paladin = new Paladin();
	RaceCar *racecar = new RaceCar(a_paladin);
	Creature *winner = execute_race(motorcycle, racecar);
}
