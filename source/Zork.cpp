#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "../include/room.h"
#include "../include/Item.h"
#include "../include/Container.h"
#include "../include/Creature.h"
#include "../include/Zork.h"
#include "../include/ZorkObject.h"

using namespace std;
using namespace rapidxml;

// Function Declarations
Room* find_room(vector<Room*> list, string value);

Zork::~Zork(void){}

Zork::Zork(const char* filename) {
	xml_document<> doc;
	xml_node<>* root;
	ifstream theFile(filename);

	if (theFile.fail()) {
		cout << "FILE: " << filename << " failed to open." << endl;
		// Possible to indicate failure???
	}
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root = doc.first_node("map");

	for (xml_node<>* curr_node = root->first_node(); curr_node != NULL; curr_node = curr_node->next_sibling()) {
		if (string(curr_node->name()) == string("room")) {
			Room* temp = new Room(curr_node);
			//temp->print_contents();
			rooms.push_back(temp);
		}
		if (string(curr_node->name()) == string("item")) {
			Item* temp = new Item(curr_node);
			//temp->print_contents();
			items.push_back(temp);
		}
		if (string(curr_node->name()) == string("container")) {
			Container* temp = new Container(curr_node);
			//temp->print_contents();
			containers.push_back(temp);
		}
		if (string(curr_node->name()) == string("creature")) {
			Creature* temp = new Creature(curr_node);
			//temp->print_contents();
			creatures.push_back(temp);
		}
	}
}

void Zork::play(void) {
	Room* room_ptr = find_room(rooms, "Entrance");
	cout << room_ptr->description << endl;
	while (true) {
		getline(cin, this->usr_input);
		if (usr_input == "quit") {
			cout << "Goodbye!!" << endl;
			return;
		}
	}
}

Room* find_room(vector<Room*> list, string value) {
	// NOTE: Error if room is not in list (Not sure if it matters)
	for (unsigned int i = 0; i < list.size(); i++) {
		if (string(list[i]->name) == value) {
			return list[i];
		}
	}
	return NULL;
}