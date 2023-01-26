//
// Created by Candice Neill on 1/16/23.
//

#include "db.h"
#include "dbmanager.h"

static int databaseCallback(void *unused, int rows, char **data, char **colNames)
{
   for(int i = 0; i < rows; i++)
   {
      printf("%s = %s\n", colNames[i], data[i] ? data[i] : "NULL");
   }
   printf("\n");
   return 0;
}

DB::DB(const FString& name, DBScope scopeIn)
{
	sqlite3_open(name,&db);
	scope = scopeIn;
}

DB::~DB()
{
	if( db )
	{
		sqlite3_close(db);
		sqlite3_free(db);
	}
}

void DB::wipeDatabase(const FString& identifier)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
}

void DB::createTable(const FString& identifier,const FString& table,FieldDefinition fields[])
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
}

void DB::deleteTable(const FString& identifier,const FString& table)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
}

void DB::getAllRows(const FString& identifier,const FString& table)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
}

void DB::getRows(const FString& identifier,const FString& table,const FString& compareField,CompareType compareType,const FString& compareValue)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
	sanitiseSqlSymbol(compareField);
	sanitiseSqlSymbol(compareValue);
}

void DB::removeRows(const FString& identifier,const FString& table,const FString& compareField,CompareType compareType,const FString& compareValue)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
	sanitiseSqlSymbol(compareField);
	sanitiseSqlSymbol(compareValue);
}

void DB::updateRows(const FString& identifier,const FString& table,const FString& compareField,CompareType compareType,const FString& compareValue)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
	sanitiseSqlSymbol(compareField);
	sanitiseSqlSymbol(compareValue);
}

void DB::insertRow(const FString& identifier,const FString& table,TArray<Result>)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSqlSymbol(table);
}

void DB::sqlexec(const FString& identifier,const FString& sql)
{
	DBEvent* event = nullptr;
	DBManager::createEvent(identifier, event);
	sanitiseSql(sql);
}

void DB::sanitiseSqlSymbol(const FString& sql)
{

}

void DB::sanitiseSql(const FString& sql)
{

}

DBScope DB::getScope ()
{
	return scope;
}

FString DB::getName()
{
	return name;
}
void DB::close ()
{
	if( db )
	{
		close();
	}
}
