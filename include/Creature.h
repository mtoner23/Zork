#ifndef CREATURE_H_
#define CREATURE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>

using namespace std;
using namespace rapidxml;

struct attack_condition {
	string object;
	string status;
};

struct Attack {
	attack_condition condition;
	string print;
	vector <string> actions;
};

class Creature {
public:
	// Constructors & Deconstructors
	Creature(xml_node <> * root);
	~Creature();
	// Member variables
	string name;
	string status;
	string description;
	vector <string> vulnerabilities;
	Attack attack;
	vector <string> triggers;
};

#endif

