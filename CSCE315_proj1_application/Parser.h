#pragma once

/* used boost for parser and map that contains three values */
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;

typedef unordered_map<string, pair<string, string>> myMap;

/* Parser for the "WHERE" string */
/* Uses the boost tokenizer to parse the string by spaces, then adds the condition, attribute name, and record name to a boosted map that stores 3 strings */
myMap whereParser(string str) {
	vector<string> tokens;
	char_separator<char> sep{ " " };
	typedef tokenizer<char_separator<char>> tokenizer;
	tokenizer tok{ str, sep };
	myMap m;
/* Puts the parsed "WHERE" statement into a vector of strings for easier traversal */
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
		tokens.push_back(*it);
	}
/* Deletes quotes from strings in the "WHERE" statement to make adding to the map easier */
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens.at(i)[0] == '\'') {
			string str1 = tokens.at(i);
			str1.erase(str1.begin());
			str1.erase(str1.begin() + (str1.length() - 1));
			tokens.at(i) = str1;
		}
	}
/* Traverses the vector of tokens to add the attributes, record names, and conditions to the a map */
	for (int i = 0; i < tokens.size(); i++) {
		string attribute;
		string value;
		string comparison;
	/* The logic for the .at(i..) function is that the attribute is always going to be .at(i - 1), */
	/* the condition will always be .at(i), and the record name will always be .at(i + 1) */
	/* as long as the condition is not AND, OR, or NOT */
	/* Parsing for '=' */
		if (tokens.at(i) == "=") {
			value = tokens.at(i + 1);
			attribute = tokens.at(i - 1);
			comparison = tokens.at(i);
			m.insert({ attribute, make_pair(comparison, value) });			
		}
	/* Parsing for <> */
		else if (tokens.at(i) == "<>") {
			value = tokens.at(i + 1);
			comparison = tokens.at(i);
			attribute = tokens.at(i - 1);
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/* Parsing for <= */
		else if (tokens.at(i) == "<=") {
			value = tokens.at(i + 1);
			comparison = tokens.at(i);
			attribute = tokens.at(i - 1);
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/*  Parsing for '<' */
		else if (tokens.at(i) == "<") {
			value = tokens.at(i + 1);
			attribute = tokens.at(i - 1);
			comparison = tokens.at(i);
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/* Parsing for '>' */
		else if (tokens.at(i) == ">") {
			value = tokens.at(i + 1);
			attribute = tokens.at(i - 1);
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/* Parsing for >= */
		else if (tokens.at(i) == ">=") {
			value = tokens.at(i + 1);
			comparison = tokens.at(i);
			attribute = tokens.at(i - 1);
		}
	/* Parsing for 'OR' */
		else if (tokens.at(i) == "OR") {
			attribute = tokens.at(i + 1);
			if (tokens.at(i + 2) == "<" && tokens.at(i + 3) == "=") {
				comparison = "<=";
				value = tokens.at(i + 4);
			}
			else if (tokens.at(i + 2) == ">" && tokens.at(i + 3) == "=") {
				comparison = ">=";
				value = tokens.at(i + 4);
			}
			else if (tokens.at(i + 2) == "<" && tokens.at(i + 3) == ">") {
				comparison = "<>";
				value = tokens.at(i + 4);
			}
			else {
				comparison = tokens.at(i + 2);
				value = tokens.at(i + 3);
			}
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/* Parsing for 'AND' */
		else if (tokens.at(i) == "AND") {
			attribute = tokens.at(i + 1);
			if (tokens.at(i + 2) == "<" || tokens.at(i + 2) == ">") {
				if (tokens.at(i + 3) == ">") {
					comparison = "<>";
				}
				else if (tokens.at(i + 2) == "<" && tokens.at(i + 3) == "=") {
					comparison = "<=";
				}
				else if (tokens.at(i + 3) == "=") {
					comparison = ">=";
				}
			}
			comparison = tokens.at(i + 2);
			if (tokens.at(i + 3) == ">" || tokens.at(i + 3) == "=") {

				value = tokens.at(i + 4);
			}
			else {
				value = tokens.at(i + 3);
			}
			m.insert({ attribute, make_pair(comparison, value) });
		}
	/* Parsing for 'NOT' */
		else if (tokens.at(i) == "NOT") {
			attribute = tokens.at(i + 1);
			comparison = tokens.at(i + 2);
			value = tokens.at(i + 3);
			m.insert({ attribute, make_pair(comparison, value) });
		}
	}

	return m;
}

vector<string> selectParser(string str) {
	vector<string> attrVec;
	char_separator<char> sep{ ", " };
	typedef tokenizer<char_separator<char>> tokenizer;
	tokenizer tok{ str, sep };
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
		attrVec.push_back(*it);
	}

	return attrVec;
}
