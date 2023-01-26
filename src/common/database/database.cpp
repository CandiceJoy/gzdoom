//
// Created by Candice Neill on 1/16/23.
//

#include "database.h"

static int databaseCallback(void *unused, int rows, char **data, char **colNames)
{
   for(int i = 0; i < rows; i++)
   {
      printf("%s = %s\n", colNames[i], data[i] ? data[i] : "NULL");
   }
   printf("\n");
   return 0;
}

DATABASE_EVENT(wipeDatabase)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(createTable, char* table, FieldDefinition fields[])
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(deleteTable, char* table)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(getAllRows, char* table, char* compareField, CompareType compareType, char* compareValue)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(removeRows, char* table, char* compareField, CompareType compareType, char* compareValue)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(updateRows, char* table, char* compareField, CompareType compareType, char* compareValue)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(insertRow, char* table, TArray<Field> fields)
{
	CREATE_DATABASE_EVENT(event)
}

DATABASE_EVENT(sqlexec, char* sql)
{
	CREATE_DATABASE_EVENT(event)
}