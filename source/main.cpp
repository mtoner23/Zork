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
#include "../include/Item.h"
#include "../include/Container.h"
#include "../include/Creature.h"
#include "../include/Zork.h"

using namespace std;
using namespace rapidxml;

int main(int argc, const char * argv[]) {
    
	Zork *game = new Zork(argv[1]);
	game->play();

    return 0;
}
