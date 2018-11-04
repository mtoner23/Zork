#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/Creature.h"
#include "../include/Trigger.h"

#define DEBUG_FLAG 0
#if DEBUG_FLAG
#	define DEBUG(...) printf(__VA_ARGS__)
#else
#	define DEBUG(x,...)
#endif

using namespace std;
using namespace rapidxml;

Creature::~Creature() {}

void Creature::print_contents(void) {
	printf("Creature Name: %s\n", (this->name).c_str());
	printf("Creature Status: %s\n", this->status.c_str());
	printf("Creature Description: %s\n", this->description.c_str());

	for (unsigned int i = 0; i < vulnerabilities.size(); i++) {
		printf("Creature Vulnerabilities: %s\n", vulnerabilities[i].c_str());
	}
	for (unsigned int i = 0; i < triggers.size(); i++) {
		triggers[i]->print_contents();
	}
	printf("Creature Attack Condition Object: %s\n", this->attack.condition.object.c_str());
	printf("Creature Attack Condition Status: %s\n", this->attack.condition.status.c_str());
	//printf("Creature Attack Print: %s\n", this->attack.prints.c_str());
	
	for (unsigned int i = 0; i < this->attack.actions.size(); i++) {
		printf("Creature Attack Action: %s\n", this->attack.actions[i].c_str());
	}
}

Creature::Creature(string name){
    this->name = name;
}

Creature::Creature(xml_node <> * root) {
	for (xml_node<> * curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("name")) {
			this->name = curr_node->value();
			DEBUG("Creature Name: %s\n", (this->name).c_str());
		}
		else if (string(curr_node->name()) == string("status")) {
			this->status = curr_node->value();
			DEBUG("Creature Status: %s\n", this->status.c_str());
		}
		else if (string(curr_node->name()) == string("description")) {
			this->description = curr_node->value();
			DEBUG("Creature Description: %s\n", this->description.c_str());
		}
		else if (string(curr_node->name()) == string("vulnerability")) {
			vulnerabilities.push_back(curr_node->value());
			DEBUG("Creature Vulnerabilities: %s\n", curr_node->value());
		}
		else if (string(curr_node->name()) == string("trigger")) {
			triggers.push_back(new Trigger(curr_node));
		}
		else if (string(curr_node->name()) == string("attack")) {
            
            for(xml_node<>* attack_node = curr_node->first_node(); attack_node; attack_node=attack_node->next_sibling()){
                if (string(attack_node->name()) == "print") {
                    this->attack.prints.push_back(string(curr_node->first_node("print")->value()));
                }
                if (string(attack_node->name()) == "condition") {
                    //xml_node<> * temp_node = curr_node->first_node("condition");
                    for(xml_node<>* cond_node = attack_node->first_node(); cond_node; cond_node = cond_node->next_sibling()){
                        if (string(cond_node->name()) == "object") {
                            this->attack.condition.object = string(cond_node->value());
                            DEBUG("Attack Condition Object is %s\n", this->attack.condition.object.c_str());
                        }
                        if (string(cond_node->name()) == "status") {
                            this->attack.condition.status = string(cond_node->value());
                            DEBUG("Attack Condition Status is %s\n", this->attack.condition.status.c_str());
                        }
                    }
                    
                }
            }
			
			
			for (xml_node<>* action_node = curr_node->first_node("action"); action_node; action_node = action_node->next_sibling()) {
				if (string(action_node->name()) != string("action")) {
					continue;
				}
				this->attack.actions.push_back(action_node->value());
			}

		}

	}
}

void Creature::update_status(string status){
	this->status = status;
}
