#ifndef Database_h
#define Database_h

#include "Table.h"
using namespace std;

class Database {
public:
	/* Members */
	vector<Table> tables;
	/* Methods */
	Database();
	void addTable(Table t);
	void dropTable(string name);
	vector<string> getTableNames();
	vector<Table> getTables();
	Table Query(vector<string> SELECT, string FROM, string WHERE);
	Table Query(string SELECT, string FROM, string WHERE);
};

#endif /* Database_h */