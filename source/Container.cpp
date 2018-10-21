#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/Container.h"
#include "../include/Trigger.h"

#define DEBUG_FLAG 0
#if DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(...)
#endif

using namespace std;
using namespace rapidxml;

Container::~Container() {}

void Container::print_contents(void) {
	printf("Container Name: %s\n", (this->name).c_str());
	printf("Container Status: %s\n", this->status.c_str());
	printf("Container Description: %s\n", this->description.c_str());

	for (unsigned int i = 0; i < items.size(); i++) {
		printf("Item: %s\n", items[i].c_str());
	}
	for (unsigned int i = 0; i < accepts.size(); i++) {
		printf("Container Accepts: %s\n", accepts[i].c_str());
	}
	for (unsigned int i = 0; i < triggers.size(); i++) {
		triggers[i]->print_contents();
	}

}

Container::Container(xml_node <> * root) {

	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("name")) {
			this->name = curr_node->value();
			DEBUG("Container Name: %s\n", (this->name).c_str());
		}
		else if (string(curr_node->name()) == string("status")) {
			this->status = curr_node->value();
			DEBUG("Container Status: %s\n", this->status.c_str());
		}
		else if (string(curr_node->name()) == string("description")) {
			this->description = curr_node->value();
			DEBUG("Container Description: %s\n", this->description.c_str());
		}
		else if (string(curr_node->name()) == string("item")) {
			items.push_back(curr_node->value());
			DEBUG("item: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("accept")) {
			accepts.push_back(curr_node->value());
			DEBUG("Accept: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("trigger")) {
			triggers.push_back(new Trigger(curr_node));
		}

	}
}