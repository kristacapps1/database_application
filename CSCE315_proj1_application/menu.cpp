#pragma once
#include "src/json.hpp"
#include <fstream>
#include <iostream>
#include "Database.h"
#include "menu.h"
#include <sstream>
#include "data_processing.h"

using namespace std;

// Main menu options
void main_menu(Database* db){
	string data_option;
	cout << "Yelp Data Main Menu (Choose a Number)\n";
	cout << left << setw(10) << "\t1. User Data Options\n";
	cout << left << setw(10) << "\t2. Business Data Options\n";
	cout << left << setw(10) << "\t3. Other Retrieval Options\n";
	cout << left << setw(10) << "\t4. Join Options\n";

	cin >> data_option;

	// select option
	if (data_option == "1") {
		users_submenu(db);
	}
	if (data_option == "2") {
		business_submenu(db);
	}
	if (data_option == "3") {
		others_submenu(db);
	}
	if (data_option == "4") {
		joins_submenu(db);
	}

}

// User options
void users_submenu(Database* db){
	string data_option;
	string data_token1;
	vector<string> data_tokens(100);
	int i = 0;
	cout << "User Menu (Choose a Number, use userID to specify)\n";
	cout << "Example: 1 \"-Kv9DMBZGQyf2WSKDR7LwA\" name\n";
	cout << "Example: 2 reviews \"-Kv9DMBZGQyf2WSKDR7LwA\"\n";
	cout << left << setw(10) << "\t1. Get User Trait (name, review_count, ect.)\n";
	cout << left << setw(10) << "\t2. Get Reviews for User\n";

	cin >> data_tokens[0] >> data_tokens[1] >> data_tokens[2];
	cout << endl;
	//cout << "data token1 : " << data_tokens[0] << endl;
	/*cout << "data token2 : " << data_tokens[1] << endl;
	cout << "data token3 : " << data_tokens[2] << endl;*/

	// select activity option
	if (data_tokens[0] == "1") {
		get_user_trait(db, data_tokens[1],data_tokens[2]);
	}
	if (data_tokens[0] == "2") {
		cout << "get reviews from user\n";
		get_user_reviews(db, data_tokens[2]);
	}
}

// Business options
void business_submenu(Database* db){
	string data_option;
	string data_token1;
	vector<string> data_tokens(100);
	int i = 0;
	cout << "Business Menu (Choose a Number, use businessID to specify)\n";
	cout << "Example: 1 \"-Kv9DMBZGQyf2WSKDR7LwA\" address\n";
	cout << "Example: 2 reviews \"-Kv9DMBZGQyf2WSKDR7LwA\"\n";
	cout << left << setw(10) << "\t1. Get Business Trait (name, review_count, ect.)\n";
	cout << left << setw(10) << "\t2. Get Reviews for Businesses\n";
	cout << left << setw(10) << "\t3. Get Tips for Businesses\n";

	cin >> data_tokens[0] >> data_tokens[1] >> data_tokens[2];
	cout << endl;
	/*cout << "data token1 : " << data_tokens[0] << endl;
	cout << "data token2 : " << data_tokens[1] << endl;
	cout << "data token3 : " << data_tokens[2] << endl;*/

	// select activity option
	if (data_tokens[0] == "1") {
		get_business_trait(db, data_tokens[1], data_tokens[2]);
	}
	if (data_tokens[0] == "2") {
		get_business_reviews(db, data_tokens[2]);
	}
	if (data_tokens[0] == "3") {
		get_business_tips(db, data_tokens[2]);
	}
}

// Other data options
void others_submenu(Database* db) {
	string data_option;
	string data_token1;
	vector<string> data_tokens(100);
	int i = 0;
	cout << "Other Options Menu (Choose a Number, use ID to specify)\n";
	cout << "Example: 2 \"lsSiIjAKVl - QRxKjRErBeg\"\n";
	cout << left << setw(10) << "\t1. Business summary\n";
	cout << left << setw(10) << "\t2. User Summary\n";

	cin >> data_tokens[0] >> data_tokens[1];
	cout << endl;
	/*cout << "data token1 : " << data_tokens[0] << endl;
	cout << "data token2 : " << data_tokens[1] << endl;
	cout << "data token3 : " << data_tokens[2] << endl;*/

	// select activity option
	if (data_tokens[0] == "1") {
		get_business_summary(db, data_tokens[1]);
	}
	if (data_tokens[0] == "2") {
		get_user_summary(db, data_tokens[1]);
	}
}

// Join data options
void joins_submenu(Database* db) {
	string data_option;
	string data_token1;
	vector<string> data_tokens(100);
	int i = 0;
	cout << "Join Menu (Choose a Number)\n";
	cout << "Example: 2\n";
	cout << left << setw(10) << "\t1. Ratings summary for all users\n";
	cout << left << setw(10) << "\t2. Ratings summary for all businesses\n";

	cin >> data_tokens[0];
	cout << endl;
	/*cout << "data token1 : " << data_tokens[0] << endl;
	cout << "data token2 : " << data_tokens[1] << endl;
	cout << "data token3 : " << data_tokens[2] << endl;*/

	// select activity option
	if (data_tokens[0] == "1") {
		all_users_summary(db);
	}
	if (data_tokens[0] == "2") {
		all_businesses_summary(db);
	}
}