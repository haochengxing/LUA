local GameLib=require "GameLib"
 
-- GameLib.initDb("127.0.0.1","root","Hao_1987","test_mysql")
-- local result = GameLib.querySql("select * from user")
-- for i,v in ipairs(result) do
-- 	for k,vv in pairs(v) do
-- 		print(k,vv)
-- 	end
-- end

GameLib.initRedis("127.0.0.1", 6379)
local result = GameLib.execCommand("set foo 123456789")
local result = GameLib.execCommand("get foo")
GameLib.releaseRedis()
