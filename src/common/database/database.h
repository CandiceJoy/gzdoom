//
// Created by Candice Neill on 1/16/23.
//

#ifndef GZDOOM_DATABASE_H
#define GZDOOM_DATABASE_H

#include <sqlite3.h>
#include "../utility/tarray.h"
#include "databasemanager.h"

enum DatabaseScope
{
	GLOBAL, //Never wiped, stored globally
	SAVE, //Never wiped, stored in save
	HUB, //Wiped on hub change, stored in save
	MAP //Wiped on map change, stored in save
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
	NOT_EQUAL
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

struct TableDefinition
{
	TArray<FieldDefinition> fieldDefs;
	char* name;
};

class Database
{
public:
	void wipeDatabase();
	bool createTable(char* table, Field fields[]);
	bool deleteTable(char* table, Field fields[]);
	TArray<TArray<Field>> find(char* table, char* compareField, CompareType compareType, char* compareValue); //find("myTable", "id", EQUAL, "7");
private:
	DatabaseScope scope;
	TArray<TableDefinition> tableDefinitions;
	sqlite3* db;
	char* name;
	int mDefFileNum; //Obj->GetClass()->VMType->mDefFileNo
};

class RawDatabase : Database
{
public:
	TArray<TArray<Field>> query(char*sql); //TODO: Check return value accuracy
};

#endif //GZDOOM_DATABASE_H
