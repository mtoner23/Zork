#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/trigger.h"

#define DEBUG_FLAG 1
#ifdef DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Trigger::Trigger(xml_node <> * root) {

	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("type")) {
			this->type = curr_node->value();
			DEBUG("Trigger Type: %s\n", this->type.c_str());
		}
		else if (string(curr_node->name()) == string("command")) {
			this->command = curr_node->value();
			DEBUG("Trigger Command: %s\n", this->command.c_str());
		}
		else if (string(curr_node->name()) == string("condition")) {
			for (xml_node<> * condition_node = curr_node->first_node(); condition_node; condition_node = condition_node->next_sibling()) {
				if (string(condition_node->name()) == string("has")) {
					this->condition.has = string(curr_node->value());
					//DEBUG("Trigger Condtion has: %s\n", this->condition.has.c_str());
					DEBUG("Trigger Condtion has: %s\n", curr_node->value());
				}
				if (string(condition_node->name()) == string("object")) {
					this->condition.object = string(curr_node->value());
					DEBUG("Trigger Condition object: %s\n", curr_node->value());
				}
				if (string(condition_node->name()) == string("owner")) {
					this->condition.owner = string(curr_node->value());
					DEBUG("Trigger Condition owner: %s\n", curr_node->value());
				}
			}
		}
		else if (string(curr_node->name()) == string("print")) {
			this->print = curr_node->value();
			DEBUG("Trigger print: %s\n", this->print.c_str());
		}
	}
}

Trigger::~Trigger() {}