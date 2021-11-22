#include <iostream>
#include "MyDB.h"
using namespace std;
int main(){
    MyDB db;
    db.initDb("127.0.0.1","root","Hao_1987","test_mysql");
    db.execSql("select * from user");
    return 0;
}