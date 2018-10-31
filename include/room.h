#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include "../include/Container.h"
#include "../include/Item.h"
#include "../include/Creature.h"
#include "../include/Trigger.h"
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

class Room: public ZorkObject {
public:
	// Constructors & Deconstructors
	Room(xml_node <> * root);
    Room(string name);
	~Room();
	void print_contents(void);
	void update_status(string status);
	// Member variables
	string name = "";
	string status = "";
	string type = "";
	string description = "";
	Room * north = NULL;
	Room * south = NULL;
    Room * west = NULL;
    Room * east = NULL;
	vector <Container *> containers;
	vector <Item *> items;
	vector <Creature *> creatures;
	vector <Trigger *> triggers;
};

#endif
