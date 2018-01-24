#include "Table.h"
#include <cstring>
#include <iostream>

using namespace std;

//default constructor
Table::Table() {}

/*constructor with an attribute vector argument, and a name argument that sets the table name*/
Table::Table(vector<string> attr, string name1) {
	name = name1;

	for (int i = 0; i < attr.size(); i++)
	{
		attribute a;
		a.name = attr[i];
		a.isKey = false;
		attributes.push_back(a);
	}

	for (int i = 0; i < attributes.size(); i++)
	{
		attributes[i].columNum = i;
	}
}

/*function addAttribute adds an attribute, creates entries below it containing empty strings*/
void Table::addAttribute(string attrib) {
	attribute a;
	a.name = attrib;
	attributes.push_back(a);

	for (int i = 0; i < rec.size(); i++)
	{
		rec[i].records.push_back("");
	}

	for (int i = 0; i < attributes.size(); i++)
	{
		attributes[i].columNum = i;
	}
}

/*deleteAttribute deletes a specified attrubute, removes every entry below it*/
void Table::deleteAttribute(string attrib)
{
	int columnNum = -1;

	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name == attrib)
		{
			columnNum = i;
			attributes.erase(attributes.begin() + columnNum);
		}
	}

	for (int i = 0; i < rec.size(); i++)
	{
		rec[i].records.erase(rec[i].records.begin() + columnNum);
	}

	for (int i = 0; i < attributes.size(); i++)
	{
		attributes[i].columNum = i;
	}
}

/*insertRecord inserts a record object into the vector of records for the table*/
void Table::insertRecord(Record record) {
	rec.push_back(record);
}

/*getAttributes returns the list of attributes for the able in a vector*/
vector<string> Table::getAttributes() {
	vector<string> attribs;

	for (int i = 0; i < attributes.size(); i++)
	{
		attribs.push_back(attributes[i].name);
	}
	return attribs;
}

/*getNumRecords returns the number of records*/
unsigned int Table::getNumRecords() {
	return (unsigned int)rec.size();
}

/*setKey finds the specified attribute, sets the key to a given table*/
void Table::setKey(string key) {
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name == key)
		{
			attributes[i].isKey = true;
			tableKey = attributes[i].name;
		}
	}
}

/*crossJoin performs a cross join of 2 tables, returns a new table*/
Table Table::crossJoin(Table a, Table b) {
/*the attribute list is assembled for the new table*/
	vector<string> aAttributes = a.getAttributes();
	vector<string> bAttributes = b.getAttributes();
	vector<string> newAttributes;

	for (int i = 0; i < aAttributes.size(); i++)
	{
		newAttributes.push_back(aAttributes[i]);
	}

	for (int i = 0; i < bAttributes.size(); i++)
	{
		newAttributes.push_back(bAttributes[i]);
	}

	int recSize = newAttributes.size();

/*The new table's entries are added given the requirements of cross join*/
	Table newTable(newAttributes, "");

	for (int i = 0; i < a.getNumRecords(); i++)
	{
		for (int j = 0; j < b.getNumRecords(); j++)
		{
			Record r(recSize);

			for (int k = 0; k < aAttributes.size(); k++)
			{
				r[k] = a.rec[i].records[k];
			}

			for (int l = 0; l < bAttributes.size(); l++)
			{
				r[l + aAttributes.size()] = b.rec[j].records[l];
			}
			newTable.insertRecord(r);
		}
	}

	return newTable;
}

/*naturalJoin performs a cross join of 2 tables, returns a new table*/

Table Table::naturalJoin(Table a, Table b) {
/*First, the keys of each table are obtained and checked to see if they match*/
	string aKey = a.tableKey;
	int aKeyCol;
	for (int i = 0; i < a.attributes.size(); i++)
	{
		if (a.attributes[i].isKey)
		{
			aKeyCol = i;
		}
	}
	string bKey = b.tableKey;
	int bKeyCol;
	for (int i = 0; i < b.attributes.size(); i++)
	{
		if (b.attributes[i].isKey)
		{
			bKeyCol = i;
		}
	}
	if (aKey != bKey)
	{
		cout << "Keys do not match\n";
		return Table();
	}
	if (aKey == "" || bKey == "")
	{
		cout << "One of the tables has no key\n";
		return Table();
	}

/*create new table's attribute list*/
	vector<string> newAttributes;
	for (int i = 0; i < a.attributes.size(); i++)
	{
		newAttributes.push_back(a.attributes[i].name);
	}

	for (int i = 0; i < b.attributes.size(); i++)
	{
		if (!b.attributes[i].isKey)
		{
			newAttributes.push_back(b.attributes[i].name);
		}
	}

/*the new table is assembled given the requirements for natural join*/
	Table newTable(newAttributes, "");
	unsigned int newRecordSize = a.attributes.size() + b.attributes.size() - 1;

	for (int i = 0; i < a.rec.size(); i++)
	{
		Record r(newRecordSize);
		for (int j = 0; j < a.rec[i].getRecordSize(); j++)
		{
			r[j] = a.rec[i][j];
		}
		if (r[aKeyCol] != "") newTable.insertRecord(r);
	}

	Table bCopy = b;
	bCopy.deleteAttribute(bKey);

	for (int i = 0; i < newTable.getNumRecords(); i++)
	{
		string thisKey = newTable.rec[i][aKeyCol];

		for (int j = 0; j < b.getNumRecords(); j++)
		{
			if (b.rec[j][bKeyCol] == thisKey)
			{
				for (int k = 0; k < bCopy.rec[j].getRecordSize(); k++)
				{
					newTable.rec[i][a.rec[i].getRecordSize() + k] = bCopy.rec[j][k];
				}
			}
		}
	}
	return newTable;
}

/*numEntries returns the number of non-null entries under an attrubute*/
unsigned int Table::numEntries(string attrib) {
	unsigned int entries = 0;
	int attributeColumn = -1;
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name == attrib)
		{
			attributeColumn = i;
		}
	}

	if (attributeColumn == -1)
	{
		cout << "Attribute does not exist\n";
		return 0;
	}

	for (int i = 0; i < rec.size(); i++)
	{
		if (rec[i][attributeColumn] != "")entries++;
	}
	return entries;
}

/*minimumEntry returns the smallest entry under a given attribute*/
string Table::minimumEntry(string attrib) {
	string min = "";
	int columnNum = -1;
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name == attrib)
		{
			columnNum = i;
		}
	}
	if (columnNum == -1)
	{
		cout << "attribute does not exist!\n";
		return NULL;
	}
	for (int i = 0; i < rec.size(); i++)
	{
		if (i == 0)min = rec[i][columnNum];
		else
		{
			string currentval = rec[i][columnNum];
			if (strcmp(currentval.c_str(), min.c_str()) < 0) min = currentval;
		}
	}

	return min;
}

/*maximumEntry returns the largest entry under a given attribute*/
string Table::maximumEntry(string attrib) {
	string max = "";
	int columnNum = -1;
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name == attrib)
		{
			columnNum = i;
		}
	}
	if (columnNum == -1)
	{
		cout << "attribute does not exist!\n";
		return NULL;
	}

	for (int i = 0; i < rec.size(); i++)
	{
		string currentval = rec[i][columnNum];
		if (strcmp(currentval.c_str(), max.c_str())>0) max = currentval;
	}
	return max;
}