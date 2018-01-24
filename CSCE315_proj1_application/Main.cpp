#include "Includes.h"
#include "Database.h"
#include "src/json.hpp"
#include <fstream>
#include "json_parser.h"
#include "menu.h"

using json = nlohmann::json;
using namespace std;

int main() {
	Database db;
	cout << "Please wait while database loads...\n";
	load_data_to_database(&db);
	while (true) {
		main_menu(&db);
	}
	return 0;
}