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

using namespace std;
using namespace rapidxml;

class Container {
public:
	// Constructors & Deconstructors
	Container(xml_node <> * root);
	~Container();
	void print_contents(void);
	// Member variables
	string name;
	string status;
	string description;
	vector <string> accepts;
	vector <string> items;
	vector <Trigger *> triggers;
};

#endif
