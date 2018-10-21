#ifndef ROOM_H_
#define ROOM_H_

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

class Room: public ZorkObject {
public:
	// Constructors & Deconstructors
	Room(xml_node <> * root);
	~Room();
	void print_contents(void);
	// Member variables
	string name = "";
	string status = "";
	string type = "";
	string description = "";
	string north = "";
	string south = "";
	string west = "";
	string east = "";
	vector <string> containers;
	vector <string> items;
	vector <string> creatures;
	vector <Trigger *> triggers;
};

#endif
