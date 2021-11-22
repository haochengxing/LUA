 
 
extern "C" {
 
#include <lua.h>
 
#include <lauxlib.h>
 
#include <lualib.h>
 
};
 
#include <iostream>  
 
#include <vector>
 
#include <set>
 
using namespace std;
 
 
 
static const char* const ERROR_ARGUMENT_COUNT = "error param num!";
 
static const char* const ERROR_ARGUMENT_TYPE = "error param type!";
 
class Solution {
 
public:
 
	vector<string> Permutation(string str, vector<string>&result) {
 
		loc_Permutation(str, 0);
 
		if (str.size() == 0)return result;
 

		for (set<string>::iterator item = all_str.begin(); item != all_str.end(); item++)
		{
			result.push_back(*item);
		}

		//result = all_str;
 
		return result;
 
	}
 
	void loc_Permutation(string str, int loc){
 
		all_str.insert(str);
 
		//all_str.push_back(str);
 
		//cout << str << endl;
 
		int size = str.size();
 
		if (loc == size - 1)return;
 
		//loc_Permutation(str, loc + 1);
 
		for (int idx_swap = loc; idx_swap < size; idx_swap++){
 
			//cout << loc << " " << idx_swap << " ";
 
			swap(str[loc], str[idx_swap]);
 
			loc_Permutation(str, loc + 1);
 
			swap(str[loc], str[idx_swap]);
 
		}
 
 
 
	}
 
public:
 
	set<string> all_str;
 
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
 

 
extern "C" int AllSort(lua_State* L)
 
{
 
	
 
 
 

 
	const char* str= luaL_checkstring(L, 1);
 
 
 
	if (str)
 
	{
 
		Solution sln;
 
		vector<string> strResult;
 
		strResult = sln.Permutation(str, strResult);
 
		
 
		lua_newtable(L);
 
		lua_newtable(L);
 
		int count = 1;
 
		for (int i = 0; i < strResult.size();i++)
 
		{
 
			lua_pushstring(L, strResult[i].c_str());
 
			
 
			lua_rawseti(L, -2, count++);
 
		}
 
		
 
		lua_pushstring(L, "array");
 
		lua_insert(L, -2); /*	school table */
 
		lua_settable(L, -3); /* param.school = school */
 
	
 
	}
 
	else
 
	{
 
		ErrorMsg(L, ERROR_ARGUMENT_TYPE);
 
	}
 
 
 
 
	return 1;
 
}
 
 
 
 
 

 
extern "C" int ShowMsgBox(lua_State* L)
 
{
 
	const char* pszMessage = "hdc";
 
	const char* pszCaption = "hdc";
 
 
 

 
	CheckParamCount(L, 2);
 
 
 

 
	pszMessage = luaL_checkstring(L, 1);
 
	pszCaption = luaL_checkstring(L, 2);
 
 
 
	if (pszCaption && pszMessage)
 
	{
 
		cout << "Hello world from clibs!" << endl;
 
		lua_pushstring(L, "Hello world from clibs!");
 
	}
 
	else
 
	{
 
		ErrorMsg(L, ERROR_ARGUMENT_TYPE);
 
	}
 
 
 

	return 1;
 
}
 
 extern "C" int sub2(lua_State* L)
 
 {
 
	   double op1 = luaL_checknumber(L, 1);
 
	   double op2 = luaL_checknumber(L, 2);
 
	   int temp = op1 - op2;
 
	   lua_pushnumber(L, temp);
 
	   return 1;
 
 }
 
 
 

 
static luaL_Reg luaLibs[] =
 
{
 
	{ "ShowMsgBox", ShowMsgBox },
 
	{ "sub2", sub2 },
 
	{ "AllSort", AllSort },
 
	{ NULL, NULL }
 
};
 
  
 
extern "C" 
 
int luaopen_WinFeature(lua_State* L) {   
 
	const char* const LIBRARY_NAME = "WinFeature"; 
 
	
 
		lua_newtable(L);
 
		luaL_setfuncs(L,  luaLibs,0);
 
	return 1;
 
}