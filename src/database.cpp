//
// Created by Candice Neill on 1/12/23.
//

#include <database.h>

void Database::init ()
{
	sqlite3_open( "gzdoom.db" , &db );
}

bool Database::query ( char* sql, sqlite3_callback callback , void *, char **errmsg )
{
	return sqlite3_exec(db,sql,callback,(void *) "",errmsg );
}

void Database::deinit ()
{
	sqlite3_close( db );
}

Database::Database()
{

}