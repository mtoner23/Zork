#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include "../include/Trigger.h"
#include "../include/Item.h"
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

class Container: public ZorkObject {
public:
	// Constructors & Deconstructors
	Container(xml_node <> * root);
    Container(string name);
	~Container();
	void print_contents(void);
	// Member variables
	string name;
	string status;
	string description;
	vector <string> accepts;
	vector <Item *> items;
	vector <Trigger *> triggers;
};

#endif
