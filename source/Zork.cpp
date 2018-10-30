#include "../include/rapidxml.hpp"
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "../include/Item.h"
#include "../include/Container.h"
#include "../include/Creature.h"
#include "../include/Zork.h"
#include "../include/ZorkObject.h"
#include "../include/room.h"
#include <sstream>

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
        //TODO fix file handling
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
        for(int j = 0; j < rooms[i]->items.size(); j++){
            // Item Allocation
            //cout << "Room: " << rooms[i]->name << "   Item: " << rooms[i]->items[j]->name << endl;
            rooms[i]->items[j] = find_item(rooms[i]->items[j]->name);
        }
        for(int j = 0; j < rooms[i]->containers.size(); j++){
            //Container Allocation
            rooms[i]->containers[j] = find_container(rooms[i]->containers[j]->name);
            for(int k = 0; k < rooms[i]->containers[j]->items.size(); k++){
                //Container Items allocation
                rooms[i]->containers[j]->items[k] = find_item(rooms[i]->containers[j]->items[k]->name);
            }
        }
        for(int j = 0; j < rooms[i]->creatures.size(); j++){
            //Creature Allocation
            rooms[i]->creatures[j] = find_creature(rooms[i]->creatures[j]->name);
        }
    }
    
}

void Zork::play(void) {
	cout << curr_room->description << endl;
    int out = 0;
    int over = 0;
    string usr_input;
	while (out == 0) {
		getline(cin, usr_input);
        //over = check_override();
        //cout << usr_input << endl;
        if(!over){
            out = process_command(usr_input,0);
        }
        //check_result();
	}
    return;
}

void Zork::check_override(){
    trigger_condition condition;
    for(int i = 0; i < curr_room->triggers.size(); i++){
        condition = curr_room->triggers[i]->condition;
        //TODO:
    }
}

int Zork::process_command(string usr_input, int dev_mode){
    //Dev Mode determines who is calling this command, the player or another object, in which case we can use special commands, add update delete and game over
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
    }else if(usr_input == "open exit" || usr_input == "exit" || (usr_input == "Game Over" && dev_mode)){
        if(dev_mode == 1){
            cout << "Victory!" << endl;
            return 1;
        }else if(curr_room->type == "exit"){
            cout << "Game Over" << endl; //TODO: victory or Game over??
            return 1;
        }else{
            cout << "This isn't the exit" << endl;
        }
    }else if(usr_input.substr(0,4) == "take"){
        string item_name = usr_input.substr(5); //String starting after word take
        Item* item = NULL;
        for(int i = 0; i < curr_room->items.size(); i ++){
            if(curr_room->items[i]->name == item_name){
                item = curr_room->items[i];
                curr_room->items.erase(curr_room->items.begin()+i);
                break;
            }
        }
        for(int i = 0; i < curr_room->containers.size() && item == NULL; i++){
            Container* container = curr_room->containers[i];
            for(int j = 0; j < container->items.size(); j++){
                if(container->items[j]->name == item_name && container->status == "open"){
                    item = container->items[j];
                    container->items.erase(container->items.begin()+j);
                    break;
                }
            }
        }
        if(item != NULL){
            inventory.push_back(item);
            cout << "Item \"" << item_name << "\" added to inventory"<< endl;
        }else{
            cout << "There is no item \"" << item_name << "\" in this room" << endl;
        }
    }else if(usr_input.substr(0,4) == "drop"){
        string item_name = usr_input.substr(5); // String starting after word drop
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
    }else if(usr_input.substr(0,4) == "read"){
        string item_name = usr_input.substr(5); // String starting after word read
        Item* item = NULL;
        for(int i = 0; i < inventory.size(); i ++){
            if(inventory[i]->name == item_name){
                item = inventory[i];
                break;
            }
        }
        if(item != NULL){
            if(item->writing != ""){
                cout << item->writing << endl;
            }else{
                cout << "Nothing Written." << endl;
            }
        }else{
            cout << "No item " << item_name << " in inventory." << endl;
        }
    }else if(usr_input.substr(0,7) == "turn on"){
        string item_name = usr_input.substr(8);
        Item* item = NULL;
        for(int i = 0; i < inventory.size(); i ++){
            if(inventory[i]->name == item_name){
                item = inventory[i];
                break;
            }
        }
        if(item != NULL){
            cout << "You activate the " << item_name << "." << endl;
            if(item->turnon.action == ""){
                cout << "Nothing happened." << endl;
            }
            else{
                string update_text = item->turnon.action.substr(item->turnon.action.rfind("to")+ string("to ").size() );
                item->update_status(update_text);
                //cout << "Updated " << item->name << " to " << item->status << endl;
                cout << item->turnon.print << endl;
            }
        }else{
            cout << item_name << " is not in inventory." << endl;
        }

    
    }else if(usr_input.substr(0,4) == "open"){
        string container_name = usr_input.substr(5);
        Container* container = NULL;
        for(int i = 0; i < curr_room->containers.size(); i++){
            if(curr_room->containers[i]->name == container_name){
                container = curr_room->containers[i];
                break;
            }
        }
        if(container == NULL){
            cout << "Could not find " << container_name << endl;
        }else{
            if(container->accepts.size() == 0){
                if(container->status == ""){
                    container->update_status("open");
                }
                if(container->items.size() == 0){
                    cout << container_name << " is empty" << endl;
                }else if(container->items.size() == 1){
                    cout << container_name << " contains " << container->items[0]->name << endl;
                }else{
                    cout << container_name << " contains ";
                    int i;
                    for(i = 0; i < container->items.size() - 1; i++){
                        cout << container->items[i]->name << ", ";
                    }
                    cout << container->items[i]->name << endl;
                }
            }else{
                cout << "Could not open " << container_name << endl;
            }
        }
    }else if(usr_input.substr(0,3) == "put"){
        stringstream ss(usr_input);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> results(begin, end);
        string item_name = results[1];
        string container_name = results[3];
        Item* item = NULL;
        Container* container = NULL;
        int item_placed = 0;

        for(int i = 0; i < curr_room->containers.size(); i++){
            if(curr_room->containers[i]-> name == container_name){
                container = curr_room->containers[i];
                break;
            }
        }
        if( container == NULL){
            cout << container_name << " is not in " << curr_room->name << endl;
            return 0;
        }
        for(int i = 0; i < inventory.size(); i++){
            if(inventory[i]-> name == item_name){
                item = inventory[i];
                inventory.erase(inventory.begin()+i);
                break;
            }
        }

        if( item == NULL){
            cout << item_name << " is not in inventory" << endl;
            return 0;
        }
        if( container->accepts.size() == 0 && container->status == "open"){
            container->items.push_back(item);
            cout << item_name << " placed in " << container_name << endl;
            item_placed = 1;
        }
        else if(container->accepts.size() == 0 && container->status != "open"){
            cout << item_name << " could not be placed in " << container_name << endl;
        }
        else if(container->accepts.size() != 0){
            for(int i = 0; i < container->accepts.size(); i++){
                if(container->accepts[i] == item_name){
                    container->accepts.erase(container->accepts.begin()+i);
                    cout << item_name << " placed in " << container_name << endl;
                    item_placed = 1;
                    break;
                }
            }
            if( !item_placed ){
                cout << "Could not put " << item_name << " in " << container_name << endl;
            }
        }
        if( !item_placed ){
            inventory.push_back(item);
        }
    }
    else if(usr_input.substr(0,6) == "attack"){
        int idx = (int)usr_input.find(" with ");
        
        string creature_name = usr_input.substr(7,idx - 7);
        string item_name = usr_input.substr(idx+6);
        
        Creature * creature = NULL;
        Item * item = NULL;
        
        
        for (int i = 0; i < curr_room->creatures.size(); i++) {
            if(creature_name == curr_room->creatures[i]->name){
                creature = curr_room->creatures[i];
                break;
            }
        }
        
        if(creature == NULL){
            cout << "There is no creature " << creature_name << " in the room." << endl;
            return 0;
        }
        
        for (int i = 0; i < inventory.size(); i++) {
            if(item_name == inventory[i]->name){
                item = inventory[i];
                break;
            }
        }
        
        if(item == NULL){
            cout << "There is no item " << item_name << " in your inventory." << endl;
            return 0;
        }
        
        cout << "You attack " << creature_name << " with " << item_name << "." << endl;
        
        int success = 0;
        
        for (int i = 0; i < creature->vulnerabilities.size() && success == 0; i++) {
            if(item_name == creature->vulnerabilities[i]){
                //cout << "Vulnerable" << endl;
                for ( int j = 0; j < inventory.size() && success == 0; j ++){
                    //cout << "attack object status: " << creature->attack.condition.status << "our status: " << inventory[j]->status << endl;
                    if((creature->attack.condition.object == "" || creature->attack.condition.object ==  inventory[j]->name) && (creature->attack.condition.status == inventory[j]->status || creature->attack.condition.status == "")){
                        success = 1;
                        if(creature->attack.print != ""){
                            cout << creature->attack.print << endl;
                        }
                    }
                }
            }
        }
        
        if(success){
            for(int i = 0; i < creature->attack.actions.size(); i++){
                //cout << "Action: " << creature->attack.actions[i] << endl;
                process_command(creature->attack.actions[i],1);
            }
        }
        
    } else if(usr_input.substr(0,3) == "Add" && dev_mode){
        int idx = (int)usr_input.find(" to ");
        
        string object_name = usr_input.substr(4,idx - 4);
        string dest_name = usr_input.substr(idx+4);
        
        Item * item = find_item(object_name);
        Creature * creature = find_creature(object_name);
        
        Room * room = find_room(dest_name);
        Container * container = find_container(dest_name);
        
        if(item != NULL){
            if(room != NULL){
                room->items.push_back(item);
            }else{
                container->items.push_back(item);
            }
        }else{
            if(room != NULL){
                room->creatures.push_back(creature);
            }
        }
        
    } else if(usr_input.substr(0,6) == "Delete"){
        // int idx = (int)usr_input.find(" to ");
        
        string object_name = usr_input.substr(7);
        
        int found = 0;
        
        Item * item = find_item(object_name);
        Creature * creature = find_creature(object_name);
        
        for( int i = 0; i < rooms.size() && !found; i++){
            if(item != NULL){
                for(int j = 0; j < rooms[i]->items.size() && !found; j++){
                    if(rooms[i]->items[j] == item){
                        rooms[i]->items.erase(rooms[i]->items.begin() + j);
                        found = 1;
                    }
                }
            } else {
                for(int j = 0; j < rooms[i]->creatures.size() && !found; j++){
                    if(rooms[i]->creatures[j] == creature){
                        rooms[i]->creatures.erase(rooms[i]->creatures.begin() + j);
                        found = 1;
                    }
                }
            }
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
    return NULL;
}

Creature* Zork::find_creature(string creature) {
    // NOTE: Error if room is not in list (Not sure if it matters)
    for (unsigned int i = 0; i < creatures.size(); i++) {
        if (string(creatures[i]->name) == creature) {
            return creatures[i];
        }
    }
    return NULL;
}

Container* Zork::find_container(string container) {
    // NOTE: Error if room is not in list (Not sure if it matters)
    for (unsigned int i = 0; i < containers.size(); i++) {
        if (string(containers[i]->name) == container) {
            return containers[i];
        }
    }
    return NULL;
}

Room* Zork::find_room(string value) {
	// NOTE: Error if room is not in list (Not sure if it matters)
	for (unsigned int i = 0; i < rooms.size(); i++) {
		if (string(rooms[i]->name) == value) {
			return rooms[i];
		}
	}
	return NULL;
}
