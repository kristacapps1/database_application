#include "Database.h"
#include "Parser.h"

/* Empty database constructor */
Database::Database() {
	/* Empty database */
}
/* Pushes the given table to the vector of tables in the class */
void Database::addTable(Table t) {
	tables.push_back(t);
}

/* Removes a table from the class's table vector */
void Database::dropTable(string name) {
	for (int i = 0; i < tables.size(); i++) {
		if (tables.at(i).name == name) {
			tables.erase(tables.begin() + i);
		}
	}
}

/* makes a copy of the class vector of tables and returns their names */
vector<string> Database::getTableNames() {
	vector<string> names;
	for (int i = 0; i < tables.size(); i++) {
		names.push_back(tables.at(i).name);
	}
	return names;
}
/* makes a copy of the class vector of tables and returns it */
vector<Table> Database::getTables() {
	vector<Table> tablesVec;
	for (int i = 0; i < tables.size(); i++) {
		tablesVec.push_back(tables.at(i));
	}
	return tablesVec;
}

Table Database::Query(string SELECT, string FROM, string WHERE) {
	typedef unordered_map<string, pair<string, string>> myMap;
	Table t;
	Table copyTable;
	myMap m;
	m = whereParser(WHERE);

	/* FROM */
	for (int i = 0; i < tables.size(); i++) {
		if (tables.at(i).name == FROM) {
			t = tables.at(i);
		}
	}

/* WHERE */
	copyTable = t;
	int deciderColumn;
/* checks for each type of comparison and then stores the value and attribute associated with it in a map */
	for (auto&x : m) {
		string val = x.second.second;
	/* first goes through the attirubte list to find the column with the records that we're interested in */
		for (int i = 0; i < copyTable.attributes.size(); i++) {
			if (x.first == copyTable.attributes[i].name) {
				deciderColumn = i;
			}
		}
	/* Each of these loops goes through the vector of records to check if the value stored in the vector is the same as the record in the map */
		if (x.second.first == "=") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (val != copyTable.rec[i][deciderColumn]) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
		else if (x.second.first == "<>") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (val == copyTable.rec[i][deciderColumn]) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
		else if (x.second.first == "<") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (copyTable.rec[i][deciderColumn] >= val) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
		else if (x.second.first == ">") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (copyTable.rec[i][deciderColumn] <= val) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
		else if (x.second.first == "<=") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (copyTable.rec[i][deciderColumn] > val) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
		else if (x.second.first == ">=") {
			for (int i = 0; i < copyTable.rec.size(); i++) {
				if (copyTable.rec[i][deciderColumn] < val) {
					copyTable.rec.erase(copyTable.rec.begin() + i);
				}
			}
		}
	}
/* SELECT */
	vector<string> wantedAttributes;
	wantedAttributes = selectParser(SELECT);
/* Uses a nested for loop to first go through the attributes list */
/* and then the list of attributes given from the SELECT string, */
/* and then compares them to each other to select which attributes to make a table from  */
	for (int i = 0; i < copyTable.attributes.size(); i++) {
		bool match = false;
		for (int j = 0; j < wantedAttributes.size(); j++) {
			if (copyTable.attributes[i].name == wantedAttributes[j]) {
				match = true;
			}
		}
		if (!match) {
			copyTable.deleteAttribute(copyTable.attributes[i].name);
		}
	}

	return copyTable;
}
/* Not used */
Table Database::Query(vector<string> SELECT, string FROM, string WHERE) {
	return{};
}


