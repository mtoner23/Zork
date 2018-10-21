#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include "../include/Trigger.h"

using namespace std;
using namespace rapidxml;

struct turn_on {
	string print;
	string action;
};

class Item {
public:
	// Constructors & Deconstructors
	Item(xml_node <> * root);
	~Item();
	void print_contents(void);
	// Member variables
	string name;
	string status;
	string description;
	string writing;
	turn_on turnon;
	vector <Trigger *> triggers;
};

#endif
