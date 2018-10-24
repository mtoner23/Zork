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
    for(int i = 0; i < rooms.size(); i++){
        if(rooms[i]->north != NULL){
            rooms[i]->north = find_room(rooms[i]->north->name);
        }
        if(rooms[i]->south != NULL){
            rooms[i]->south = find_room(rooms[i]->south->name);
        }
        if(rooms[i]->east != NULL){
            rooms[i]->east = find_room(rooms[i]->east->name);
        }
        if(rooms[i]->west != NULL){
            rooms[i]->west = find_room(rooms[i]->west->name);
        }
        for(int i = 0; i < rooms[i]->items.size(); i ++){
            // Item Allocation
            rooms[i]->items[i] = find_item(items[i]->name);
        }
        for(int j = 0; j < rooms[i]->containers.size(); j++){
            //Container Allocation
            rooms[i]->containers[j] = find_container(rooms[i]->containers[j]->name);
            cout << rooms[i]->containers[j]->name << endl;
            for(int k = 0; k < rooms[i]->containers[j]->items.size(); k++){
                //Container Items allocation
                rooms[i]->containers[j]->items[k] = find_item(rooms[i]->containers[j]->items[k]->name);
            }
        }
        for(int i = 0; i < rooms[i]->creatures.size(); i ++){
            //Creature Allocation
            rooms[i]->creatures[i] = find_creature(items[i]->name);
        }
    }
    
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
        if(curr_room->north != NULL){
            curr_room = find_room(curr_room->north->name);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go north" << endl;
        }
    }else if (usr_input == "s"){
        if(curr_room->south != NULL){
            curr_room = find_room(curr_room->south->name);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go south" << endl;
        }
    }else if (usr_input == "e"){
        if(curr_room->east != NULL){
            curr_room = find_room(curr_room->east->name);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go east" << endl;
        }
    }else if (usr_input == "w"){
        if(curr_room->west != NULL){
            curr_room = find_room(curr_room->west->name);
            cout << curr_room->description << endl;
        }else{
            cout << "You cannot go west" << endl;
        }
    }else if (usr_input == "l" || usr_input == "ls"){
        cout << curr_room->description << endl;
        if(curr_room->items.size() != 0){
            int i;
            for(i = 0; i < curr_room->items.size() - 1; i++){
                cout << curr_room->items[i]->name << ", ";
            }
            cout << curr_room->items[i]->name << endl;
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
        string item_name = usr_input.substr(5); // String starting after word take
        Item* item = NULL;
        for(int i = 0; i < curr_room->items.size(); i ++){
            if(curr_room->items[i]->name == item_name){
                item = curr_room->items[i];
                curr_room->items.erase(curr_room->items.begin()+i);
                break;
            }
        }
        if(item != NULL){
            inventory.push_back(item);
            cout << "Item \"" << item_name << "\" added to inventory"<< endl;
        }else{
            cout << "There is no item \"" << item_name << "\" in this room" << endl;
        }
    }else if(usr_input.substr(0,4) == "drop"){
        string item_name = usr_input.substr(5); // String starting after word take
        Item* item = NULL;
        for(int i = 0; i < inventory.size(); i ++){
            if(inventory[i]->name == item_name){
                item = inventory[i];
                inventory.erase(inventory.begin()+i);
                break;
            }
        }
        if(item != NULL){
            curr_room->items.push_back(item);
            cout << item->name << " dropped." << endl;
        }else{
            cout << "There is no item \"" << item_name << "\" in your inventory" << endl;
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
    cout << "ERROR: Could Not Find Item" << endl;
    return NULL;
}

Creature* Zork::find_creature(string creature) {
    // NOTE: Error if room is not in list (Not sure if it matters)
    for (unsigned int i = 0; i < creatures.size(); i++) {
        if (string(creatures[i]->name) == creature) {
            return creatures[i];
        }
    }
    cout << "ERROR: Could Not Find Creature" << endl;
    return NULL;
}

Container* Zork::find_container(string container) {
    // NOTE: Error if room is not in list (Not sure if it matters)
    for (unsigned int i = 0; i < containers.size(); i++) {
        if (string(containers[i]->name) == container) {
            return containers[i];
        }
    }
    cout << "ERROR: Could Not Find Creature" << endl;
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
