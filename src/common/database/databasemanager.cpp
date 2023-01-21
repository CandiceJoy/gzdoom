//
// Created by Candice Neill on 1/12/23.
//

#include "databasemanager.h"
#include <cstdio>

DatabaseManager * databaseManager = nullptr;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void DatabaseManager::openDatabase(char* database)
{
	sqlite3_open( "/Users/candice/Downloads/galaxy-2.0.db" , &this->db );
	char* err;
	query("SELECT name FROM sqlite_schema WHERE type='table' ORDER BY name;",&err);
}

bool DatabaseManager::query (char* sql,char **errmsg )
{
	printf("query exec\n");
	//sqlite3_step()
	return sqlite3_exec(db,sql,callback,0,errmsg );
}

void DatabaseManager::Cleanup ()
{
	sqlite3_close( db );
}

void InitializeDatabaseManager()
{
	if( !databaseManager )
	{
		databaseManager = new DatabaseManager();
	}
}

DatabaseManager::DatabaseManager()
{
	db = nullptr;
}