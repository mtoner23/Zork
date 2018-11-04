#ifndef CREATURE_H_
#define CREATURE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include "../include/Trigger.h"
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

struct attack_condition {
	string object = "";
	string status = "";
};

struct Attack {
	attack_condition condition;
	string print = ""; //TODO maybe multiple prints
	vector <string> actions;
};

class Creature: ZorkObject{
public:
	// Constructors & Deconstructors
	Creature(xml_node <> * root);
    Creature(string name);
	~Creature();
	void print_contents(void);
	void update_status(string status);
	// Member variables
	string name = "";
	string status = "";
	string description = "";
	vector <string> vulnerabilities;
	Attack attack;
	vector <Trigger *> triggers;
    
};

#endif

