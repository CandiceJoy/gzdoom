//
// Created by Candice Neill on 1/16/23.
//

#ifndef GZDOOM_DB_H
#define GZDOOM_DB_H

#include <sqlite3.h>
#include "tarray.h"
#include "zstring.h"

const int SYSTEM_FILENUM = -1;

enum DBScope
{
	GLOBAL, //Never wiped, stored globally
	SAVE, //Never wiped, stored in save
	HUB, //Wiped on hub change, stored in save
	MAP //Wiped on map change, stored in save
};

enum DBEventType
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

enum CompareType
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
	FString name;
	bool isKey;
	bool notNullable;
	bool isUnique;
	bool isCheck;
};

struct Result
{
	FString name;
	FString data;
};

typedef TArray<Result> Resultset;

struct TableDefinition
{
	TArray<FieldDefinition> fieldDefs;
	FString name;
};

struct DBEvent
{
	FString identifier;
	DBEventType type;
	Resultset * results;
	bool success = false;
	FString sql;
	char** err;
	int mDefFileNum = SYSTEM_FILENUM;
	sqlite3* db = nullptr;
};

class DB
{
public:
	DB(const FString& name, DBScope scopeIn);
	~DB();
	void wipeDatabase(const FString& identifier);
	void createTable(const FString& identifier, const FString& table, FieldDefinition fields[]);
	void deleteTable(const FString& identifier, const FString& table);
	void getAllRows(const FString& identifier, const FString& table);
	void getRows(const FString& identifier, const FString& table, const FString& compareField, CompareType compareType, const FString& compareValue); // find("myTable", "id", EQUAL, "7");
	void removeRows(const FString& identifier, const FString& table, const FString& compareField, CompareType compareType, const FString& compareValue);
	void updateRows(const FString& identifier, const FString& table, const FString& compareField, CompareType compareType, const FString& compareValue);
	void insertRow(const FString& identifier, const FString& table, TArray<Result>);
	void sqlexec(const FString& identifier, const FString& sql);
	DBScope getScope();
	FString getName();
	void close();
private:
	//Aggressive sanitisation; removes all ()""'';; etc
	static void sanitiseSqlSymbol(const FString& sql);

	//Less aggressive sanitisation; just make sure they don't try to stray from their namespace
	static void sanitiseSql(const FString& sql);

	DBScope                 scope;
	TArray<TableDefinition> tableDefinitions;
	sqlite3* db;
	FString name;
	int mDefFileNum; //Obj->GetClass()->VMType->mDefFileNo
};

#endif //GZDOOM_DB_H