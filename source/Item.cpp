#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/Item.h"
#include "../include/Trigger.h"

#define DEBUG_FLAG 0
#if DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Item::~Item() {}

void Item::print_contents(void) {
	printf("Item Name: %s\n", (this->name).c_str());
	printf("Item Status: %s\n", this->status.c_str());
	printf("Item Description: %s\n", this->description.c_str());
	printf("Item Writing: %s\n", this->writing.c_str());
	printf("Item Turn-on Print is %s\n", this->turnon.print.c_str());
	printf("Item Turn-on Action is %s\n", this->turnon.action.c_str());
	
	for (unsigned int i = 0; i < triggers.size(); i++) {
		triggers[i]->print_contents();
	}

}

Item::Item(xml_node <> * root) {

	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("name")) {
			this->name = curr_node->value();
			DEBUG("Item Name: %s\n", (this->name).c_str());
		}
		else if (string(curr_node->name()) == string("status")) {
			this->status = curr_node->value();
			DEBUG("Item Status: %s\n", this->status.c_str());
		}
		else if (string(curr_node->name()) == string("description")) {
			this->description = curr_node->value();
			DEBUG("Item Description: %s\n", this->description.c_str());
		}
		else if (string(curr_node->name()) == string("writing")) {
			this->writing = curr_node->value();
			DEBUG("Item Writing: %s\n", this->writing.c_str());
		}
		else if (string(curr_node->name()) == string("trigger")) {
			triggers.push_back(new Trigger(curr_node));
		}
		else if (string(curr_node->name()) == string("turnon")) {

			if (curr_node->first_node("print")) {
				this->turnon.print = string(curr_node->first_node("print")->value());
				DEBUG("Item Turn-on Print is %s\n", this->turnon.print.c_str());
			}
			if (curr_node->first_node("action")) {
				this->turnon.action = string(curr_node->first_node("action")->value());
				DEBUG("Item Turn-on Action is %s\n", this->turnon.action.c_str());
			}
			
		}

	}
}