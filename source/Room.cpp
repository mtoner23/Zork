#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/room.h"
#include "../include/Trigger.h"

//#define DEBUG_FLAG
#ifdef DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Room::~Room(){}

void Room::print_contents(void) {
	printf("Room Name: %s\n", (this->name).c_str());
	printf("Room Status: %s\n", this->status.c_str());
	printf("Room Description: %s\n", this->description.c_str());
	printf("Room Type: %s\n", this->type.c_str());
	printf("NORTH is %s\n", this->north->name.c_str());
	printf("SOUTH is %s\n", this->south->name.c_str());
	printf("EAST is %s\n", this->east->name.c_str());
	printf("WEST is %s\n", this->west->name.c_str());
	
	for (unsigned int i = 0; i < items.size(); i++) {
		printf("Item: %s\n", items[i]->name.c_str());
	}
	for (unsigned int i = 0; i < containers.size(); i++) {
		printf("Container: %s\n", containers[i]->name.c_str());
	}
	for (unsigned int i = 0; i < creatures.size(); i++) {
		printf("Creature: %s\n", creatures[i]->name.c_str());
	}
	for (unsigned int i = 0; i < triggers.size(); i++) {
		triggers[i]->print_contents();
	}
	
}

Room::Room(string name){
    this->name = name;
}

Room::Room(xml_node <> * root) {

	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("name")) {
			this->name = curr_node->value();
			DEBUG("Room Name: %s\n", (this->name).c_str());
		}
		else if (string(curr_node->name()) == string("status")) {
			this->status = curr_node->value();
			DEBUG("Room Status: %s\n", this->status.c_str());
		}
		else if (string(curr_node->name()) == string("description")) {
			this->description = curr_node->value();
			DEBUG("Room Description: %s\n", this->description.c_str());
		}
		else if (string(curr_node->name()) == string("type")) {
			this->type = curr_node->value();
			DEBUG("Room Type: %s\n", this->type.c_str());
		}
		else if (string(curr_node->name()) == string("container")) {
            Container * temp = new Container(curr_node->value());
			containers.push_back(temp);
			DEBUG("container: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("item")) {
            Item * temp = new Item(curr_node->value());
			items.push_back(temp);
			DEBUG("item: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("creature")) {
            Creature * temp = new Creature(curr_node->value());
            creatures.push_back(temp);
			DEBUG("Creature: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("trigger")) {
			triggers.push_back(new Trigger(curr_node));
		}
		else if (string(curr_node->name()) == string("border")) {

			if (string(curr_node->first_node("direction")->value()) == string("north")) {
				this->north = new Room(string(curr_node->first_node("name")->value()));
				DEBUG("NORTH is %s\n", this->north->name.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("south")) {
				this->south = new Room(string(curr_node->first_node("name")->value()));
				DEBUG("SOUTH is %s\n", this->south->name.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("west")) {
				this->west = new Room(string(curr_node->first_node("name")->value()));
				DEBUG("WEST is %s\n", this->west->name.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("east")) {
				this->east = new Room(string(curr_node->first_node("name")->value()));
				DEBUG("EAST is %s\n", this->east->name.c_str());
			}
		}

	}
}
