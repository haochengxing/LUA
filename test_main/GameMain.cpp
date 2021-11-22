 
 
extern "C" {
 
#include <lua.h>
 
#include <lauxlib.h>
 
#include <lualib.h>
 
};
 
#include <iostream>  
 
#include <vector>
 
#include <set>

#include <hiredis/hiredis.h>


#include <string>
#include <mysql/mysql.h>
 
using namespace std;
 
 
 
static const char* const ERROR_ARGUMENT_COUNT = "error param num!";
 
static const char* const ERROR_ARGUMENT_TYPE = "error param type!";
 
class GameMain {
 
public:
 
	GameMain() {
		conn = mysql_init(NULL);
		if (conn == NULL) {
			cout << "error occurs " << mysql_error(conn);
			exit(1);
		}
	}


	~GameMain() {
		if (conn != NULL) {
			mysql_close(conn);
		}
	}

	bool initDb(string host, string user, string password, string db_name) {
		conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), 0, NULL, 0);
		if (conn == NULL) {
			cout << "error occurs " << mysql_error(conn);
			exit(1);
		}
		return true;
	}


	bool execSql(string sql) {
		if (mysql_query(conn, sql.c_str())) {
			cout << "query error " << mysql_error(conn) << endl;
			return false;
		}
		else {
			result = mysql_use_result(conn);
			if (result) {
				int num_fields = mysql_num_fields(result);
				int num_rows = mysql_field_count(conn);
				printf("%d\n", num_fields);
				printf("%d\n", num_rows);
				for (int i = 0; i < num_rows; i++) {
					row = mysql_fetch_row(result);
					if (row == 0) break;
					for (int j = 0; j < num_fields; j++) {
						cout << row[j] << "\t";
					}
					cout << endl;
				}
			}
			mysql_free_result(result);
		}
		return true;
	}


	bool initRedis(string host, int port) {
		redis_conn = redisConnect(host.c_str(), port);
		if (redis_conn->err) {
			printf("connection error:%s\n", redis_conn->errstr);
			exit(1);
		}
		return true;
	}


	bool execCommand(string command) {
		redisReply* reply = (redisReply*)redisCommand(redis_conn, command.c_str());
		printf("%s\n", reply->str);
		freeReplyObject(reply);
		return true;
	}

	void releaseRedis() {
		redisFree(redis_conn);
	}
 
public:
 
	


	redisContext* redis_conn;


	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
 
};
 
 
 
void ErrorMsg(lua_State* L, const char* const pszErrorInfo)
 
{
 
	lua_pushstring(L, pszErrorInfo);
 
	lua_error(L);
 
}
 
 
 

 
void CheckParamCount(lua_State* L, int paramCount)
 
{
 
	 
 
	if (lua_gettop(L) != paramCount)
 
	{
 
		ErrorMsg(L, ERROR_ARGUMENT_COUNT);
 
	}
 
}
 

GameMain sln;

 
extern "C" int initDb(lua_State* L)
{

	const char* host = luaL_checkstring(L, 1);
	const char* user = luaL_checkstring(L, 2);
	const char* password = luaL_checkstring(L, 3);
	const char* db_name = luaL_checkstring(L, 4);
 
	if (host && user && password && db_name)
	{

		bool result = sln.initDb(host, user, password, db_name);
 
		lua_pushboolean(L, result);
 
	}
	else
	{
 
		ErrorMsg(L, ERROR_ARGUMENT_TYPE);
 
	}
 
	return 1;
}


extern "C" int execSql(lua_State* L)
{

	const char* sql = luaL_checkstring(L, 1);

	if (sql)
	{

		bool result = sln.execSql(sql);

		lua_pushboolean(L, result);

	}
	else
	{

		ErrorMsg(L, ERROR_ARGUMENT_TYPE);

	}

	return 1;
}
 
extern "C" int initRedis(lua_State* L)
{

	const char* host = luaL_checkstring(L, 1);
	int port = (int)luaL_checknumber(L, 2);

	if (host)
	{

		bool result = sln.initRedis(host, port);

		lua_pushboolean(L, result);

	}
	else
	{

		ErrorMsg(L, ERROR_ARGUMENT_TYPE);

	}

	return 1;
}


extern "C" int execCommand(lua_State* L)
{

	const char* command = luaL_checkstring(L, 1);

	if (command)
	{

		bool result = sln.execCommand(command);

		lua_pushboolean(L, result);

	}
	else
	{

		ErrorMsg(L, ERROR_ARGUMENT_TYPE);

	}

	return 1;
}
 

extern "C" int releaseRedis(lua_State* L)
{

	sln.releaseRedis();

	return 1;
}
 

 
 

 
static luaL_Reg luaLibs[] =
 
{
 
	{ "initDb", initDb },

	{ "execSql", execSql },
 
	{ "initRedis", initRedis },

	{ "execCommand", execCommand },

	{ "releaseRedis", releaseRedis },

 
	{ NULL, NULL }
 
};
 
  
 
extern "C" 
 
int luaopen_GameLib(lua_State* L) {   
 
	const char* const LIBRARY_NAME = "GameLib"; 
 
	
 
		lua_newtable(L);
 
		luaL_setfuncs(L,  luaLibs,0);
 
	return 1;
 
}