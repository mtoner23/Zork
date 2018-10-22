#ifndef ZORK_H_
#define ZORK_H_

#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "../include/room.h"
#include "../include/Item.h"
#include "../include/Container.h"
#include "../include/Creature.h"

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork(const char* filename);
	~Zork();
	string usr_input = "";
    Room * curr_room;
	vector<Item*> inventory;
	vector<Room*> rooms;
	vector<Item*> items;
	vector<Container*> containers;
	vector<Creature*> creatures;
	void play(void);
    void process_command();
    Room* find_room(string value);
    Item* find_item(string);
private:
	int setup(void);
};

#endif
