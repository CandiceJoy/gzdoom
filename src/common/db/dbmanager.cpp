//
// Created by Candice Neill on 1/12/23.
//

#include "dbmanager.h"

CVAR(Bool, db_allowed, true, CVAR_ARCHIVE);

DBManager * dbManager = nullptr;

int DBManager::systemCallback(void *eventPtr,int rows,char **data,char **colName)
{
	assert(eventPtr != nullptr);
	auto* event = (DBEvent*)eventPtr;
	assert(event->mDefFileNum == SYSTEM_FILENUM);
	auto* rowset = new Resultset;
	event->results = rowset;

	for(int x = 0; x < rows; x++)
	{
		Result result = *new Result;
		result.name = colName[x];
		result.data = data[x];
		rowset->Push( result);
	}

	event->success = true;
	sqlite3_close(event->db);
	sqlite3_free(event->db);
	delete &event->db;
	event->db = nullptr;
	dbManager->eventReturn(*event);

	return 0;
}

DBManager::DBManager()
{
	systemEvents = *new TArray<DBEvent*>();
}

// WARNING: No sanitisation!  DO NOT EXPORT!
void DBManager::sqlexec(const FString& identifier, const FString& name, const FString& sql)
{
	auto* event = new DBEvent;
	systemEvents.Push(event);
	createEvent(identifier, event);
	event->type = RAW;
	event->sql = sql;

	sqlite3 *db;
	event->db = db;
	sqlite3_open(name,&db);
	sqlite3_exec(db,sql.GetChars(),systemCallback,&event,event->err);
}

bool DBManager::wipeDatabases(DBScope scope)
{
	if( !db_allowed )
	{
		return false;
	}

	// Go backwards to avoid modifying the array during iteration
	for( unsigned int x = databases.Size()-1; x >= 0; x-- )
	{
		DB db = databases[x];

		if( db.getScope() == scope )
		{
			FString name = db.getName();
			db.close();
			databases.Delete(x);
			//TODO: Delete file "name"
		}
	}

	return true;
}

void DBManager::allocateDB(int mFileDef,DBScope scope,FString databaseNamespace)
{

}

void DBManager::getDB(int mFileDef,DBScope scope,FString databaseNamespace)
{

}

void DBManager::createEvent(const FString &identifier, DBEvent* event)
{
	char **err;
	event = new DBEvent;
	event->identifier = identifier;
	event->err = err;
}

inline void DBManager::eventReturn (DBEvent event)
{
	systemEvents.Push(&event);
}

DBEvent* DBManager::getEvent(const FString &identifier)
{
	// Go backwards to avoid modifying the array during iteration
	for( unsigned int x = systemEvents.Size()-1; x >= 0; x-- )
	{
		DBEvent* event = systemEvents[x];

		if( event->identifier.Compare(identifier) == 0 )
		{
			systemEvents.Delete(x);
			return event;
		}
	}

	return nullptr;
}

void InitializeDBManager()
{
	if( !dbManager )
	{
		dbManager = new DBManager();
	}
}