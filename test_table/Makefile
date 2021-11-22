GameLib.so : GameMain.cpp
	g++ -g -Wall --shared -fPIC -llua GameMain.cpp -o GameLib.so  -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lhiredis
clean :
	rm *.so