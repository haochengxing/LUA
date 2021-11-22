local GameLib=require "GameLib"
 
print(GameLib.initDb("127.0.0.1","root","Hao_1987","test_mysql"))
print(GameLib.execSql("select * from user"))
print(GameLib.initRedis("127.0.0.1", 6379))
print(GameLib.execCommand("set foo 123456"))
print(GameLib.execCommand("get foo"))
print(GameLib.releaseRedis())