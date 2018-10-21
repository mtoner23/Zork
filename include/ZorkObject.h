#ifndef ZORKOBJECT_H_
#define ZORKOBJECT_H_

#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace rapidxml;

class ZorkObject {
public:
	ZorkObject(void);
	~ZorkObject();
	virtual void print_contents(void);
	string name = "";
};

#endif