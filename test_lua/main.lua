local WinFeature=require "WinFeature"
 
print(WinFeature.sub2(1,2));
 
local msg=WinFeature.AllSort("123456")
 
for i = 1, #msg.array do
 
    print(msg.array[i])
 
end
 
print(msg);