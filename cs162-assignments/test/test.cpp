#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parent
{
private:
	string _thing;

public:
	Parent() {}
	Parent(string thing)
	{
		_thing = thing;
	}
	virtual string get_thing()
	{
		return _thing;
	}
	
};

class ChildOne : public Parent
{
public:
	ChildOne();
	ChildOne(string thing) : Parent(thing) {}
	string get_thing()
	{
		return "Class One: " + Parent::get_thing();
	}
};

class ChildTwo : public Parent
{
public:
	ChildTwo(string thing) : Parent(thing) {}
	string get_thing()
	{
		return "Class Two: " + Parent::get_thing();
	}
};

void printStuff(Parent first, Parent second)
{
	cout << first.get_thing() << endl		//We want this to print "Class One: test" but it prints "test"
			 << second.get_thing() << endl; //We want this to print "Class Two: test" but it prints "test"
}

void add(Parent *thing, Parent **list, int &size){

	// cout << thing << endl;

	Parent ** temp = new Parent*[size + 1];

	for(int i = 0; i < size; i++){
		temp[i] = list[i];
	}
	temp[size++] = thing;

	// delete[] list; //We don't want to delete the inside, because that would delete our objects
	list = temp;
}

int main()
{

	// Parent ** list = new Parent*[0];
	// int size = 0;
	
	// add(new ChildOne("heh"), list, size);
	// add(new ChildTwo("heh2"), list, size);
	// add(new ChildTwo("test2"), list, size);

	// for(int i = 0; i < size; i++){
	// 	cout << list[i]->get_thing() << endl;
	// }

	// for(int i = 0; i < size; i++){
	// 	delete list[i];
	// }
	// delete [] list;

	// Parent **list = new Parent*[2];
	// Parent *test = new ChildOne("test");
	// // Parent *test2 =
	// list[0] = test;
	// list[1] =  new ChildTwo("test2");
	// cout << list[0]->get_thing() << endl << list[1]->get_thing() <<  endl;

	vector<Parent*> first;
	first.push_back(new ChildOne("test"));
	first.push_back(new ChildTwo("test2"));
	for(int i = 0; i < first.size(); i++){
		cout << first.at(i)->get_thing() << endl;
	}

	for(int i = 0; i < first.size(); i++){
		delete first[i];
	}
	


	return 0;
}

