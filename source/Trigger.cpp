#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/Trigger.h"

#define DEBUG_FLAG 0
#if DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Trigger::Trigger(xml_node <> * root) {

	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		DEBUG("Node Name: %s", curr_node->name());
		if (string(curr_node->name()) == string("type")) {
			this->type = curr_node->value();
			DEBUG("Trigger Type: %s\n", this->type.c_str());
		}
		else if (string(curr_node->name()) == string("command")) {
			DEBUG("Trigger Command: %s\n", curr_node->value());
			commands.push_back(curr_node->value());
		}
		else if (string(curr_node->name()) == string("condition")) {
			trigger_condition new_trigger;
			for (xml_node<> * condition_node = curr_node->first_node(); condition_node; condition_node = condition_node->next_sibling()) {
				if (string(condition_node->name()) == string("has")) {
					DEBUG("Trigger Condtion has: %s\n", condition_node->value());
					new_trigger.has = string(condition_node->value());
				}
				else if (string(condition_node->name()) == string("object")) {
					DEBUG("Trigger Condition object: %s\n", condition_node->value());
					new_trigger.object = string(condition_node->value());
				}
				else if (string(condition_node->name()) == string("owner")) {
					DEBUG("Trigger Condition owner: %s\n", condition_node->value());		
					new_trigger.owner = string(condition_node->value());
				}
				else if (string(condition_node->name()) == string("status")) {
					DEBUG("Trigger Condition Status: %s\n", condition_node->value());
					new_trigger.status = string(condition_node->value());
				}
			}
			conditions.push_back(&new_trigger);
		}
		else if (string(curr_node->name()) == string("print")) {
			prints.push_back(curr_node->value());
		}
		else if (string(curr_node->name()) == string("action")) {
			actions.push_back(curr_node->value());
		}
	}
}

Trigger::~Trigger() {}

void Trigger::print_contents(void) {
	for (unsigned int i = 0; i < prints.size(); i++) {
		printf("Print: %s\n", prints[i].c_str());
	}
	for (unsigned int i = 0; i < actions.size(); i++) {
		printf("Action: %s\n", actions[i].c_str());
	}
	for (unsigned int i = 0; i < commands.size(); i++) {
		printf("Command: %s\n", commands[i].c_str());
	}
}
