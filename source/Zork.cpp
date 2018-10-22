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
    curr_room = find_room("Entrance");
}

void Zork::play(void) {
	cout << curr_room->description << endl;
    int out = 0;
	while (out == 0) {
		getline(cin, this->usr_input);
        out = process_command();
	}
    return;
}

int Zork::process_command(){
    if (usr_input == "quit") {
        cout << "Goodbye!!" << endl;
        return 1;
    }else if (usr_input == "n"){
        if(curr_room->north != ""){
            curr_room = find_room(curr_room->north);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go north" << endl;
        }
    }else if (usr_input == "s"){
        if(curr_room->south != ""){
            curr_room = find_room(curr_room->south);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go south" << endl;
        }
    }else if (usr_input == "e"){
        if(curr_room->east != ""){
            curr_room = find_room(curr_room->east);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go east" << endl;
        }
    }else if (usr_input == "w"){
        if(curr_room->west != ""){
            curr_room = find_room(curr_room->west);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go west" << endl;
        }
    }else if (usr_input == "l" || usr_input == "ls"){
        cout << curr_room->description << endl;
        if(curr_room->items.size() != 0){
            int i;
            for(i = 0; i < curr_room->items.size() - 1; i++){
                cout << curr_room->items[i] << ", ";
            }
            cout << curr_room->items[i] << endl;
        }
    }else if (usr_input == "i"){
        if(inventory.size() != 0){
            int i;
            for(i = 0; i < inventory.size() - 1; i++){
                cout << inventory[i]->name << ", ";
            }
            cout << inventory[i]->name << endl;
        }else{
            cout << "Inventory: Empty" << endl;
        }
    }else if(usr_input == "open exit" || usr_input == "exit"){
        if(curr_room->type == "exit"){
            cout << "Game Over" << endl;
            return 1;
        }else{
            cout << "This isn't the exit" << endl;
        }
    }else if(usr_input.substr(0,4) == "take"){
        string item = usr_input.substr(5); // String starting after word take
        bool found = 0;
        for(int i = 0; i < curr_room->items.size(); i ++){
            if(curr_room->items[i] == item){
                curr_room->items.erase(curr_room->items.begin()+i);
                found = 1;
                break;
            }
        }
        if(found){
            inventory.push_back(find_item(item));
            cout << "Taken." << endl;
        }else{
            cout << "There is no item \"" << item << "\" in this room";
        }
    }else{
        cout << "I do not recognize that command" << endl;
    }
    return 0;
}

Item* Zork::find_item(string item) {
    // NOTE: Error if room is not in list (Not sure if it matters)
    for (unsigned int i = 0; i < rooms.size(); i++) {
        if (string(items[i]->name) == item) {
            return items[i];
        }
    }
    cout << "ERROR: Could Not Find room" << endl;
    return NULL;
}

Room* Zork::find_room(string value) {
	// NOTE: Error if room is not in list (Not sure if it matters)
	for (unsigned int i = 0; i < rooms.size(); i++) {
		if (string(rooms[i]->name) == value) {
			return rooms[i];
		}
	}
    cout << "ERROR: Could Not Find room" << endl;
	return NULL;
}
