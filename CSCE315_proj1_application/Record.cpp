#include "Record.h"

/* Empty Record constructor */
Record::Record() {
}

/* Sets record size */
Record::Record(unsigned int size) {
    records.resize(size);
}

/* Overloaded [] operator to get records from an object */
string& Record::operator[](unsigned int i) {
    if (i >= records.size()) {
        cout << "sorry this index is larger than the size specified" << endl;
        return records[0];
    }
    return records[i];
}

/* Returns the record size */
int Record::getRecordSize() {
    return (unsigned int)records.size();
}


