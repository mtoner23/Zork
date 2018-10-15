#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>

using namespace std;
using namespace rapidxml;

class Container {
public:
	// Constructors & Deconstructors
	Container(xml_node <> * root);
	~Container();
	// Member variables
	string name;
	string status;
	string description;
	vector <string> accepts;
	vector <string> items;
	vector <string> triggers;
};

#endif
