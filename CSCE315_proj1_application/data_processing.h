#pragma once
#include <fstream>
#include <iostream>
#include "Database.h"

/*/////////////////////////////////////////////////
User processing
/////////////////////////////////////////////////*/

void get_user_trait(Database* db, string user_id, string trait);

void get_user_reviews(Database* db, string user_id);

/*/////////////////////////////////////////////////
Business processing
/////////////////////////////////////////////////*/

void get_business_trait(Database* db, string business_id, string trait);

void get_business_reviews(Database* db, string business_id);

void get_business_tips(Database* db, string business_id);

/*/////////////////////////////////////////////////
Others processing
/////////////////////////////////////////////////*/

void get_business_summary(Database* db, string business_id);

void get_user_summary(Database* db, string user_id);

/*/////////////////////////////////////////////////
Join processing
/////////////////////////////////////////////////*/

void all_businesses_summary(Database* db);

void all_users_summary(Database* db);