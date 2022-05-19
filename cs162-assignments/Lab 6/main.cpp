#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Vehicle
{
  private:
	bool _motorized;
	int _wheels;
	int _speed;

  public:
	static const string _description;
	Vehicle(bool motorized, int wheels, int speed)
	{
		_motorized = motorized;
		_wheels = wheels;
		_speed = speed;
	}
	bool get_motorized() const
	{
		return _motorized;
	}
	string get_description() const
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
};

class Bike : public Vehicle
{
  public:
	static const string _description;
	Bike() : Vehicle(false, 2, 10) {}
};
const string Bike::_description = "Bike";

class Skateboard : public Vehicle
{
  public:
	static const string _description;
	Skateboard() : Vehicle(false, 4, 6) {}
};
const string Skateboard::_description = "Skateboard";

class RaceCar : public Vehicle
{
  public:
	static const string _description;
	RaceCar() : Vehicle(true, 4, 120) {}
};
const string RaceCar::_description = "Race Car";

class Motorcycle : public Vehicle
{
  public:
	static const string _description;
	Motorcycle() : Vehicle(true, 2, 140) {}
};
const string Motorcycle::_description = "Motorcylce";

int main()
{
	srand(time(0));
	Bike testBike;
	Skateboard testSkateboard;
	RaceCar testRaceCar;
	Motorcycle testMotorcycle;

	if (testRaceCar > testMotorcycle)
	{
		cout << "Race car is faster!" << endl;
	}
	else
	{
		cout << "Motorcycle is faster!" << endl;
	}
}