#include <fstream>
#include <iostream>
#include "Database.h"
#include "data_processing.h"
#include "json_parser.h"

/*/////////////////////////////////////////////////
User processing
/////////////////////////////////////////////////*/
void get_user_trait(Database* db, string user_id, string trait) {
	Table user_table;
	findTable(db, &user_table, "users");
	string trait_value;
	vector<string> attribute_list = user_table.getAttributes();
	int index = 0;
	// Determine attribute index
	for (auto it = attribute_list.begin(); it != attribute_list.end(); it++){
		if (*it == trait) {
			break;
		}
		index++;
    }

	// find attribute value
	for (auto it = user_table.rec.begin(); it != user_table.rec.end(); it++) {
		if ((*it)[0] == user_id) {
			trait_value = (*it)[index];
			break;
		}
	}
	cout << trait << " for user " << user_id << " : " << trait_value << "\n\n";
}

void get_user_reviews(Database* db, string user_id) {
	Table user_reviews;
	Table review_text;
	Table review_businesses;
	Table review_summary;
	Table business_table;
	Table reviews_table;
	findTable(db, &business_table, "business");
	findTable(db, &reviews_table, "review");
	int index = 0;
	string WHERE = "user_id = " + user_id;

	// get user and business ids
    user_reviews = db->Query("review_id", "review", WHERE);
	WHERE = "user_id == " + user_id;
	review_text = db->Query("text", "review", WHERE);
	review_businesses = db->Query("business_id", "review", WHERE);

	cout << setw(30) << "review_id" << setw(30) << "business_id" << endl;
	for (auto it = reviews_table.rec.begin(); it != reviews_table.rec.end(); it++) {
		cout << (*it)[1] << endl;
		if ((*it)[1] == user_id) {
			string tempAttribute = find_by_attribute(&reviews_table, (*it)[0], 0, 2);
			string tmpName = find_by_attribute(&business_table, tempAttribute, 0, 1);
			cout << setw(30) << (*it)[0] << tempAttribute << tmpName << endl;
			cout << setw(30) << (*it)[0] << tempAttribute << endl;
			tempAttribute = find_by_attribute(&reviews_table, (*it)[0], 0, 5);
			cout << tempAttribute << "\n\n";
		}
	}

}

/*/////////////////////////////////////////////////
Business processing
/////////////////////////////////////////////////*/
void get_business_trait(Database* db, string business_id, string trait) {
	Table business_table;
	findTable(db, &business_table, "businesses");
	string trait_value;
	vector<string> attribute_list = business_table.getAttributes();
	int index = 0;

	for (auto it = attribute_list.begin(); it != attribute_list.end(); it++) {
		if (*it == trait) {
			break;
		}
		index++;
	}
	for (auto it = business_table.rec.begin(); it != business_table.rec.end(); it++) {
		if ((*it)[0] == business_id) {
			trait_value = (*it)[index];
			break;
		}
	}
	cout << trait << " for user " << business_id << " : " << trait_value << "\n\n";
}

void get_business_reviews(Database* db, string business_id) {
	Table user_reviews;
	Table review_text;
	Table review_businesses;
	Table review_summary;
	Table business_table;
	Table reviews_table;
	Table users_table;
	findTable(db, &business_table, "business");
	findTable(db, &users_table, "users");
	findTable(db, &reviews_table, "review");
	int index = 0;
	//Table review_business_names;
	string WHERE = "business_id = " + business_id;
	//cout << "abouta query\n";
	user_reviews = db->Query("review_id", "review", WHERE);

	// get users and reviews
	WHERE = "user_id == " + business_id;
	review_businesses = db->Query("business_id", "review", WHERE);

	cout << setw(30) << "review_id" << setw(30) << "user_id" << endl;
	for (auto it = reviews_table.rec.begin(); it != reviews_table.rec.end(); it++) {
		if ((*it)[2] == business_id) {
			// find user id
			string tempAttribute = find_by_attribute(&reviews_table, (*it)[0], 0, 1);
			string tmpName = find_by_attribute(&users_table, tempAttribute, 0, 1);
			cout << setw(30) << (*it)[0] << tempAttribute << tmpName << endl;
			// find review text
			tempAttribute = find_by_attribute(&reviews_table, (*it)[0], 0, 5);
			cout << tempAttribute << "\n\n";
		}
	}
}
/*{ "text","date","likes","business_id","user_id" };*/
void get_business_tips(Database* db, string business_id) {
	Table business_table;
	Table tips_table;
	//Table users_table;
	findTable(db, &business_table, "business");
	findTable(db, &tips_table, "tip");
	//findTable(db, &reviews_table, "review");

	//cout << setw(30) << "tip_id" << setw(30) << "user_id" << endl;
	for (auto it = tips_table.rec.begin(); it != tips_table.rec.end(); it++) {
		if ((*it)[3] == business_id) {
			// find information about tip
			string tempAttribute = find_by_attribute(&tips_table, business_id, 3, 1);
			cout <<"Date: "<< tempAttribute << "  ";
			tempAttribute = find_by_attribute(&tips_table, business_id, 3, 4);
			cout << "User: " << tempAttribute <<endl;

			// find tip text by business id
			tempAttribute = find_by_attribute(&tips_table, business_id, 3, 0);
			cout << tempAttribute << "\n\n";
		}
	}
}

/*/////////////////////////////////////////////////
Others processing
/////////////////////////////////////////////////*/

void get_business_summary(Database* db, string business_id){
	Table business_table;
	findTable(db, &business_table, "businesses");
	Table checkin_table;
	findTable(db, &checkin_table, "checkin");
	// find business name
 	string tmpAttribute = find_by_attribute(&business_table, business_id, 0, 1);
	cout << "Summary for business "<<tmpAttribute <<" at ";
	// find address
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 3);
	cout << tmpAttribute << ",";
	// find city
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 4);
	cout << tmpAttribute << ",";
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 5);
	cout << tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 13);
	cout << setfill(' ') << setw(10) << "Category:" << setw(30) << tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 9);
	cout <<setfill(' ') <<setw(10) << "Stars:" << setw(30) <<tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 10);
	cout << setfill(' ') << setw(10) << "Reviews:" << setw(30) << tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 11);
	if (tmpAttribute == "1") {
		cout << setfill(' ') << setw(10) << "Open now from: \n";
	}
	else {
		cout << setfill(' ') << setw(10) << "Is currently Closed. Open from:" << setw(30) << tmpAttribute << "\n";
	}
	tmpAttribute = find_by_attribute(&business_table, business_id, 0, 14);
	cout << setfill(' ') << setw(10) << tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&checkin_table, business_id, 1, 0);
	cout << setfill(' ') << setw(10) << "Check-in Times:" << setw(30) << tmpAttribute << "\n\n";
}

void get_user_summary(Database* db, string user_id){
	Table users_table;
	findTable(db, &users_table, "users");
	Table checkin_table;
	findTable(db, &checkin_table, "checkin");

	// find user name
	string tmpAttribute = find_by_attribute(&users_table, user_id, 0, 1);
	cout << "Summary for user " << tmpAttribute << " who has been yelping since ";
	// find start yelping time
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 3);
	cout << tmpAttribute << endl;
	// find review count
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 2);
	cout << setfill(' ') << setw(10) << "Number of Reviews:" << setw(30) << tmpAttribute << "\n";
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 10);
	cout << setfill(' ') << setw(10) << "Average Stars:" << setw(30) << tmpAttribute << "\n";

	// Summary of basic compliments
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 5);
	cout << setfill(' ') << setw(10) << "Useful" << setw(10) << "Funny" << setw(10) << "Cool" << "\n";
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 6);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 7);
	cout << setfill(' ') << setw(10) << tmpAttribute <<"\n\n";

	// Summary of all compliments
	cout << setfill(' ') << setw(10) << "Hot" << setw(10) << "More" << setw(10) 
		 << "Profile" << setw(10)<<"Cute"<<setw(10)<< "List" << setw(10) << "Note" 
		 << setw(10) << "Plain" << setw(10) << "Cool" << setw(10) << "Funny" 
		 << setw(10) << "Writer" << setw(10) << "Photos" << "\n";
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 11);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 12);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 13);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 14);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 15);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 16);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 17);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 18);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 19);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 20);
	cout << setfill(' ') << setw(10) << tmpAttribute;
	tmpAttribute = find_by_attribute(&users_table, user_id, 0, 21);
	cout << setfill(' ') << setw(10) << tmpAttribute << "\n\n";

}

/*/////////////////////////////////////////////////
Join processing
/////////////////////////////////////////////////*/

void all_businesses_summary(Database* db){
	Table businesses_table;
	findTable(db, &businesses_table, "businesses");
	cout << setw(60) << "Name" << setw(90) << "Address" << setw(10) << "Stars" << endl;
	for(auto it = businesses_table.rec.begin(); it != businesses_table.rec.end(); it++) {
		cout << setw(60) << (*it)[1] << setw(90) << (*it)[3] + "," + (*it)[4] + "," + (*it)[5] << setw(10) << (*it)[9] << endl;
    }
	cout << "\n\n";
}

void all_users_summary(Database* db){
	Table users_table;
	findTable(db, &users_table, "users");
	cout << setw(60) << "Name" << setw(20) << "Review Count" << setw(30) << "Yelping Since" << endl;
	for(auto it = users_table.rec.begin(); it != users_table.rec.end(); it++) {
		cout << setw(60) << (*it)[1] << setw(20) << (*it)[2] << setw(30) << (*it)[3] << endl;
	}
	cout << "\n\n";
}