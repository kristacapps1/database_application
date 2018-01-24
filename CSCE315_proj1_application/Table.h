#ifndef Table_h
#define Table_h


#include "Record.h"

using namespace std;


class Table {
	struct attribute
	{
		string name;
		bool isKey;
		int columNum;
	};
public:
	vector<attribute> attributes;
	vector<Record> rec;
	string tableKey;
	string name;

/* constructors */
	Table();
	Table(vector<string> attr, string name1);

/* attribute-related functions */
	void addAttribute(string attrib);
	void deleteAttribute(string attrib);
	vector<string> getAttributes();
	void setKey(string key);
	unsigned int numEntries(string attribute);

/* record-related functions */
	void insertRecord(Record record);
	unsigned int getNumRecords();
	string minimumEntry(string attrib);
	string maximumEntry(string attrib);

/* join functions */
	Table crossJoin(Table a, Table b);
	Table naturalJoin(Table a, Table b);
};


#endif /* Table_h */

