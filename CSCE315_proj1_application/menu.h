#pragma once
#include "src/json.hpp"
#include <fstream>
#include <iostream>
#include "Database.h"

using namespace std;

void main_menu(Database* db);

void users_submenu(Database* db);

void business_submenu(Database* db);

void joins_submenu(Database* db);

void others_submenu(Database* db);

