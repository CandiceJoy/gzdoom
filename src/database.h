//
// Created by Candice Neill on 1/12/23.
//

#ifndef GZDOOM_DATABASE_H
#define GZDOOM_DATABASE_H

#include <sqlite3.h>

class Database
{
public:
	void init();
	bool query ( char* sql, sqlite3_callback callback , void *, char **errmsg );
	void deinit();
	Database();
private:
	sqlite3* db;
};

//static Database* database = new Database();
static Database *database = new Database();

#endif //GZDOOM_DATABASE_H
