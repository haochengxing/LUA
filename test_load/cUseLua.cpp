//cUseLua
#include <iostream>
#include <string.h>

extern "C"
{
    #include<lua.h>
    #include<lauxlib.h>
    #include<lualib.h>
}

using namespace std;

#if defined(__linux__)
// Linux系统
#include<unistd.h>
#elif defined(_WIN32)
// Windows系统
#include<windows.h>
#endif

/*单位：秒*/
void my_p_sleep(int time) {
#if defined(__linux__)
	// Linux系统
	sleep(time);
#elif defined(_WIN32)
	// Windows系统
	Sleep((time * 1000));
#endif
}

/*单位：毫秒*/
void my_m_sleep(int time) {
#if defined(__linux__)
	// Linux系统
	usleep(time * 1000);
#elif defined(_WIN32)
	// Windows系统
	Sleep(time);
#endif
}

int main()
{
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);    //加载lua库

    if(L == NULL)
    {
        cout<<"Creat Lua State Error !"<<endl;
        return 1;
    }
    int ret = luaL_dofile(L ,"Data.lua");
    if(ret)
    {
        cout<<"Lua doFile Error !"<<endl;
        return 1;
    }


    while (1)
	{

		lua_getglobal(L, "tick");

		if (lua_isfunction(L, -1))
		{
			my_p_sleep(1);

			lua_call(L, 0, 0);
		}

	}

    lua_close(L);
    return 0 ;
}