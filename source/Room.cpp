#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/room.h"
#include "../include/Trigger.h"

#define DEBUG_FLAG 1
#ifdef DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Room::~Room(){}

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
			containers.push_back(curr_node->value());
			DEBUG("container: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("item")) {
			items.push_back(curr_node->value());
			DEBUG("item: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("creature")) {
			creatures.push_back(curr_node->value());
		}
		else if (string(curr_node->name()) == string("trigger")) {
			triggers.push_back(new Trigger(curr_node));
		}
		else if (string(curr_node->name()) == string("border")) {

			if (string(curr_node->first_node("direction")->value()) == string("north")) {
				this->north = string(curr_node->first_node("name")->value());
				DEBUG("NORTH is %s\n", this->north.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("south")) {
				this->south = string(curr_node->first_node("name")->value());
				DEBUG("SOUTH is %s\n", this->south.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("west")) {
				this->west = string(curr_node->first_node("name")->value());
				DEBUG("WEST is %s\n", this->west.c_str());
			}
			if (string(curr_node->first_node("direction")->value()) == string("east")) {
				this->east = string(curr_node->first_node("name")->value());
				DEBUG("EAST is %s\n", this->east.c_str());
			}
		}

	}
}