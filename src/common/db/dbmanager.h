//
// Created by Candice Neill on 1/12/23.
//

#ifndef GZDOOM_DBMANAGER_H
#define GZDOOM_DBMANAGER_H

#include "db.h"
#include "c_cvars.h"

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

class DBManager
{
public:
	DBManager();

	// WARNING: Internal use ONLY; no sanitisation!
	// DO NOT EXPORT.  EVER.
	void sqlexec(const FString& identifier, const FString& database, const FString& sql);

	bool wipeDatabases(DBScope scope);

	//These are the only DatabaseManager functions that should ONLY ever be called from the VM
	void allocateDB(int mFileDef,DBScope scope,FString databaseNamespace);
	void getDB(int mFileDef,DBScope scope,FString databaseNamespace);
	static inline void createEvent(const FString& identifier, DBEvent* event);
	void eventReturn(DBEvent event);
	DBEvent* getEvent(const FString& identifier);
private:
	TArray<DB>      databases;
	TArray<DBEvent*> systemEvents;
	static int systemCallback (void *eventPtr,int rows,char **data,char **colName);
};

void InitializeDBManager();
extern DBManager * dbManager;

#endif //GZDOOM_DBMANAGER_H
