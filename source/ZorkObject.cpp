#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

ZorkObject::~ZorkObject(void) {}

ZorkObject::ZorkObject(void) {
	this->name = "DEFAULT";
}

void ZorkObject::print_contents(void) {
	printf("ZorkObject name: %s", this->name.c_str());
}