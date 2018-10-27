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
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

struct turn_on {
	string print = "";
	string action = "";
};

class Item: public ZorkObject {
public:
	// Constructors & Deconstructors
	Item(xml_node <> * root);
    Item(string name);
	~Item();
	void print_contents(void);
	void update_status(string status);
	// Member variables
	string name = "";
	string status = "";
	string description = "";
	string writing = "";
	turn_on turnon;
	vector <Trigger *> triggers;
};

#endif
