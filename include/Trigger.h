#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>

using namespace std;
using namespace rapidxml;

struct trigger_condition {
	string has = "";
	string object = "";
	string owner = "";
	string status = "";
};

class Trigger {
public:
	Trigger(xml_node <> * root);
	~Trigger();
	void print_contents(void);
	string type = "";
	string command = "";
    trigger_condition condition;
    //vector <trigger_condition *> condition;
	string print = "";
	string action = "";
};

#endif
