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
#include "../include/Item.h"
#include "../include/Container.h"
#include "../include/Creature.h"
#include "../include/room.h"

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork(const char* filename);
	~Zork();
    Room * curr_room;
	vector<Item*> inventory;
	vector<Room*> rooms;
	vector<Item*> items;
	vector<Container*> containers;
	vector<Creature*> creatures;
	void play(void);
    int process_command(string,int);
    int check_override(string);
    Room* find_room(string value);
    Item* find_item(string);
    Item* search_inventory(string);
    Creature* find_creature(string);
    Container* find_container(string);
private:
	int setup(void);
};

#endif
