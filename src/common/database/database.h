//
// Created by Candice Neill on 1/16/23.
//

#ifndef GZDOOM_DATABASE_H
#define GZDOOM_DATABASE_H

#include <sqlite3.h>
#include "../utility/tarray.h"
#include "databasemanager.h"

#define CREATE_DATABASE_EVENT(name) DatabaseEvent name = new DatabaseEvent; \
event.identifier = identifier;

#define DATABASE_EVENT_CONCAT(name, params...) name(params)
#define DATABASE_EVENT(name, params...) void Database::DATABASE_EVENT_CONCAT(name, char* identifier, params)

enum DatabaseScope
{
	GLOBAL, //Never wiped, stored globally
	SAVE, //Never wiped, stored in save
	HUB, //Wiped on hub change, stored in save
	MAP //Wiped on map change, stored in save
};

enum DatabaseEventType
{
	ROW_INSERT,
	ROW_UPDATE,
	ROW_REMOVE,
	TABLE_INSERT,
	TABLE_REMOVE,
	DATABASE_ALLOCATE,
	DATABASE_REMOVE,
	RAW
};

enum FieldType
{
	INTEGER,
	REAL,
	TEXT,
	BLOB
};

static enum CompareType
{
	EQUAL,
	GREATER_THAN,
	LESS_THAN,
	NOT_EQUAL,
	GREATER_THAN_OR_EQUAL,
	LESS_THAN_OR_EQUAL
};

struct FieldDefinition
{
	FieldType type;
	char* name;
	bool isKey;
	bool notNullable;
	bool isUnique;
	bool isCheck;
};

struct Field
{
	FieldDefinition* definition;
	char* data;
};

typedef TArray<TArray<Field>> Rowset;

struct TableDefinition
{
	TArray<FieldDefinition> fieldDefs;
	char* name;
};

struct DatabaseEvent
{
	char* identifier;
	DatabaseEventType type;
	Rowset results;
	bool success;
	char* sql;
};

class Database
{
public:
	void wipeDatabase(char* identifier);
	void createTable(char* identifier, char* table, FieldDefinition fields[]);
	void deleteTable(char* identifier, char* table);
	void getAllRows(char* identifier, char* table);
	void getRows(char* identifier, char* table, char* compareField, CompareType compareType, char* compareValue); // find("myTable", "id", EQUAL, "7");
	void removeRows(char* identifier, char* table, char* compareField, CompareType compareType, char* compareValue);
	void updateRows(char* identifier, char* table, char* compareField, CompareType compareType, char* compareValue);
	void insertRow(char* identifier, char* table, TArray<Field>);
	void sqlexec(char* identifier, char* sql);
private:
	DatabaseScope scope;
	TArray<TableDefinition> tableDefinitions;
	sqlite3* db;
	char* name;
	int mDefFileNum; //Obj->GetClass()->VMType->mDefFileNo
};

#endif //GZDOOM_DATABASE_H