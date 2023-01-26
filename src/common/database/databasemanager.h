//
// Created by Candice Neill on 1/12/23.
//

#ifndef GZDOOM_DATABASEMANAGER_H
#define GZDOOM_DATABASEMANAGER_H

#include <sqlite3.h>
#include "tarray.h"
#include "database.h"

static char* compareTypeToString(CompareType type)
{
	switch(type)
	{
		case EQUAL:
			return "=";
		case GREATER_THAN:
			return ">";
		case LESS_THAN:
			return "<";
		case NOT_EQUAL:
			return "!=";
		case GREATER_THAN_OR_EQUAL:
			return ">=";
		case LESS_THAN_OR_EQUAL:
			return "<=";
	}
}

class DatabaseManager
{
public:
	DatabaseManager();
	bool query(int mFileDef,char* sql, char **errmsg); // Used by VM

	// WARNING: Internal use ONLY; no sanitisation!
	// DO NOT EXPORT.  EVER.
	bool sqlexec(char* sql, char **errmsg);

	void cleanup();
	bool wipeDatabases(DatabaseScope scope);
	sqlite3 openDatabase(char* database);

	//Aggressive sanitisation; removes all ()""'';; etc
	static char* sanitiseSql(char* sql);

	//Less aggressive sanitisation; just make sure they don't try to stray from their namespace
	static char* sanitiseRawSql(char* sql);

	//These are the only DatabaseManager functions that should ONLY ever be called from the VM
	void allocateDatabase(int mFileDef, DatabaseScope scope, char* databaseNamespace);
	void getDatabase(int mFileDef, DatabaseScope scope, char* databaseNamespace);
private:
	TArray<Database> databases;
	bool databasesAllowed;
};

void InitializeDatabaseManager();

extern DatabaseManager * databaseManager;

#endif //GZDOOM_DATABASEMANAGER_H
