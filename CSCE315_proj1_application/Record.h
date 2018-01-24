#ifndef Record_h
#define Record_h

#include "Includes.h"

using namespace std;

class Record {
    
public:
    vector<string> records;
    Record();
    Record(unsigned int size);
    string& operator[](unsigned int i);
    int getRecordSize();
};

#endif /* Record_h*/


