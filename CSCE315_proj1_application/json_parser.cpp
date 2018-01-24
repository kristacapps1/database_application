#include "src/json.hpp"
#include <fstream>
#include <iostream>
#include "Database.h"
#include <string>
#include "json_parser.h"
//#include "Table.h"

using json = nlohmann::json;
using namespace std;

/*/////////////////////////////////////////////////
Parser Helpers
/////////////////////////////////////////////////*/
void add_attributes(Table* newTable, vector<string> tableAttributes) {
	for (auto it = tableAttributes.begin(); it != tableAttributes.end(); it++) {
		newTable->addAttribute(*it);
	}
}

// Find specific table in database
void findTable(Database* db, Table* tableFound, string tableName) {
	for (auto it = db->tables.begin(); it != db->tables.end(); it++) {
		if (it->name == tableName) {
			*tableFound = *it;
			break;
		}
	}
}

// Find specific attribute value in Table by another attribute value
string find_by_attribute(Table* table_search, string attribute, int attributeIndex, int searchIndex) {
	string found_value = "";
	for (auto it = table_search->rec.begin(); it != table_search->rec.end(); it++) {
		if ((*it)[attributeIndex] == attribute) {
			found_value = (*it)[searchIndex];
			break;
		}
	}
	return found_value;
}

void add_records(Table* newTable, ifstream* jsonStream, vector<string> recordAttributes) {
	string jsonStr;
	int count = 0;
	//	double dataNum;

		// add users to table
	while (getline(*jsonStream, jsonStr)) {
		Record userData(recordAttributes.size());
		auto tmpUser = json::parse(jsonStr);
		// add each attribute to the record
		for (int i = 0; i < recordAttributes.size(); i++) {
			string tmpStr = recordAttributes[i];
			//cout << tmpUser[tmpStr].dump() << endl;
			userData[i] = tmpUser[tmpStr].dump();
		}
		newTable->insertRecord(userData);
		count++;
		if (count == 900)
			break;
	}

}

void setup_table(Database* db, Table* newTable, vector<string> attributeNames, 
				ifstream* jis, string tableName, string tableKey) {

	// add attributes to table
	add_attributes(newTable, attributeNames);

	// add records to table
	add_records(newTable, jis, attributeNames);

	// add users table to database
	newTable->name = tableName;
	newTable->setKey(tableKey);
	//std::cout << "table name: " << newTable->name << endl;
	db->addTable(*newTable);
}

void print_table(Database* db, string tableName, Table printTable) {

	// find users table
	findTable(db, &printTable, tableName);

	vector<string> tmpAttributes = printTable.getAttributes();
	cout << "Number ";
	for (auto tmpIt = tmpAttributes.begin(); tmpIt != tmpAttributes.end(); tmpIt++) {
		cout << " " << *tmpIt << " ";
	}
	cout << endl;
	int index = 1;
	for (auto it = printTable.rec.begin(); it != printTable.rec.end(); it++) {
		cout << index << ":";
		//for (auto it1 = it->records.begin(); it1 != it->records.end(); it1++) {
			// exclude friends list
			//if (tableName == "users" && it1 != it->records.begin() + 4) {}
			//else {
		auto it1 = it->records.begin()+1;
				cout << " " << *it1 << " ";
			//}
		//}
		index++;
		cout << endl;
	}
}

void print_table(Table printTable) {

	// find users table
	//findTable(db, &printTable, tableName);

	vector<string> tmpAttributes = printTable.getAttributes();
	cout << "Number ";
	for (auto tmpIt = tmpAttributes.begin(); tmpIt != tmpAttributes.end(); tmpIt++) {
		cout << " " << *tmpIt << " ";
	}
	cout << endl;
	int index = 1;
	for (auto it = printTable.rec.begin(); it != printTable.rec.end(); it++) {
		cout << index << ":";
		for (auto it1 = it->records.begin(); it1 != it->records.end(); it1++) {
			// exclude friends list
			//if (tableName == "users" && it1 != it->records.begin() + 4) {}
			//else {
				cout << " " << *it1 << " ";
			//}
		}
		index++;
		cout << endl;
	}
}

/*/////////////////////////////////////////////////
Load full json data
/////////////////////////////////////////////////*/

void load_data_to_database(Database* db) {
	parse_users(db);
	//print_users(*db);
	parse_businesses(db);
	//print_businesses(*db);
	parse_reviews(db);
	//print_reviews(*db);
	parse_checkin(db);
	//print_checkin(*db);
	parse_photos(db);
	//print_photos(*db);
	parse_tips(db);
	//print_tips(*db);
}


/*/////////////////////////////////////////////////
Users Parser
/////////////////////////////////////////////////*/

void parse_users(Database* db) {
	std::ifstream jis("user.json");
	Table users;
	vector<string> attributeNames = { "user_id", "name" , "review_count" , "yelping_since" , "friends" , "useful" ,
									  "funny" , "cool" , "fans" , "elite" , "average_stars" , "compliment_hot" ,
									  "compliment_more" , "compliment_profile" , "compliment_cute" , "compliment_list" ,
									  "compliment_note" , "compliment_plain", "compliment_cool", "compliment_funny",
									  "compliment_writer", "compliment_photos" };
	//setup users table
	setup_table(db, &users, attributeNames, &jis, "users", "user_id");
}

// print users table
void print_users(Database db) {
	Table users;

	//print users table
	print_table(&db, "users", users);
}

/*/////////////////////////////////////////////////
Business Parser
/////////////////////////////////////////////////*/

void parse_businesses(Database* db) {
	std::ifstream jis("business.json");
	Table businesses;
	vector<string> attributeNames = { "business_id","name", "neighborhood", "address", "city", "state",
									"postal_code", "latitude", "longitude", "stars", "review_count",
									"is_open", "attributes","categories", "hours" };
	//setup businesses table
	setup_table(db, &businesses, attributeNames, &jis, "businesses", "business_id");
}

// print business table
void print_businesses(Database db) {
	Table businesses;

	//print users table
	print_table(&db, "businesses", businesses);
}

/*/////////////////////////////////////////////////
Reviews Parser
/////////////////////////////////////////////////*/

void parse_reviews(Database* db) {
	std::ifstream jis("review.json");
	Table reviews;
	vector<string> attributeNames = { "review_id","user_id" ,"business_id" ,"stars" ,"date" ,"text" ,"useful","funny","cool" };


	//setup users table
	setup_table(db, &reviews, attributeNames, &jis, "review", "review_id");
}

// print reviews table
void print_reviews(Database db) {
	Table reviews;

	//print users table
	print_table(&db, "review", reviews);
}

/*/////////////////////////////////////////////////
Checkins Parser
/////////////////////////////////////////////////*/

void parse_checkin(Database* db) {
	std::ifstream jis("checkin.json");
	Table checkins;
	vector<string> attributeNames = { "time", "business_id"};

	//setup users table
	setup_table(db, &checkins, attributeNames, &jis, "checkin", "business_id");
}

// print checkin table
void print_checkin(Database db) {
	Table checkins;

	//print users table
	print_table(&db, "checkin", checkins);
}

/*/////////////////////////////////////////////////
Photos Parser
/////////////////////////////////////////////////*/

void parse_photos(Database* db) {
	std::ifstream jis("photos.json");
	Table photos;
	vector<string> attributeNames = { "photo_id","business_id" ,"caption","label" };

	//setup users table
	setup_table(db, &photos, attributeNames, &jis, "photo", "photo_id");
}

// print checkin table
void print_photos(Database db) {
	Table photos;

	//print users table
	print_table(&db, "photo", photos);
}

/*/////////////////////////////////////////////////
Tips Parser
/////////////////////////////////////////////////*/

void parse_tips(Database* db) {
	std::ifstream jis("tip.json");
	Table tips;
	vector<string> attributeNames = { "text","date","likes","business_id","user_id" };

	//setup users table
	setup_table(db, &tips, attributeNames, &jis, "tip", "business_id");
}

// print checkin table
void print_tips(Database db) {
	Table tips;

	//print users table
	print_table(&db, "tip", tips);
}

