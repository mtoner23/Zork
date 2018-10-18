//
//  main.cpp
//  Zork
//
//  Created by Michael Toner on 10/3/18.
//  Copyright © 2018 Michael Toner. All rights reserved.
//

#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "../include/room.h"

using namespace std;
using namespace rapidxml;

int main(int argc, const char * argv[]) {
    // insert code here...
	if (argc < 2) {
		cout << "Not enough inputs\nUsage: ./main [filename]" << endl;
		return 0;
	}

	xml_document<> doc;
	xml_node<>* root;
	vector<Room*> rooms;

	//ifstream theFile (argv[1]);
	ifstream theFile("sample.txt.xml");
	//ifstream theFile("roomsample.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root = doc.first_node("map");

	for (xml_node<>* curr_node = root->first_node(); curr_node; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("room")) {
			rooms.push_back(new Room(curr_node));
		}
	}
	//xml_node<>* curr_node = root->first_node();
	//rooms.push_back(new Room(curr_node));
	//curr_node
    return 0;
}
