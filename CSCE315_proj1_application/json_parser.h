#pragma once
#include "src/json.hpp"
#include <fstream>
#include <iostream>
#include "Database.h"
//#include "Table.h"

using json = nlohmann::json;
using namespace std;

void add_attributes(Table* newTable, vector<string> tableAttributes);

// Find specific table in database
void findTable(Database* db, Table* tableFound, string tableName);

void add_records(Table* newTable, ifstream* jsonStream, vector<string> recordAttributes);

string find_by_attribute(Table* table_search, string attribute, int attributeIndex, int searchIndex);

void print_table(Table printTable);

/*/////////////////////////////////////////////////
Load full json data
/////////////////////////////////////////////////*/

void load_data_to_database(Database* db);

/*/////////////////////////////////////////////////
Users Parser
/////////////////////////////////////////////////*/

void parse_users(Database* db);

// print users table
void print_users(Database db);

/*/////////////////////////////////////////////////
Business Parser
/////////////////////////////////////////////////*/

void parse_businesses(Database* db);
// print businesses table
void print_businesses(Database db);

/*/////////////////////////////////////////////////
Reviews Parser
/////////////////////////////////////////////////*/

void parse_reviews(Database* db);
// print reviews table
void print_reviews(Database db);

/*/////////////////////////////////////////////////
Checkins Parser
/////////////////////////////////////////////////*/

void parse_checkin(Database* db);
// print reviews table
void print_checkin(Database db);

/*/////////////////////////////////////////////////
Photos Parser
/////////////////////////////////////////////////*/

void parse_photos(Database* db);
// print reviews table
void print_photos(Database db);

/*/////////////////////////////////////////////////
Tips Parser
/////////////////////////////////////////////////*/

void parse_tips(Database* db);
// print reviews table
void print_tips(Database db);