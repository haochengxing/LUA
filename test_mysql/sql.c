#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
//This is a simle ex.
int main(){
    MYSQL sql;
    mysql_init(&sql);
    printf("MySQL client version : %d \n",mysql_get_client_version());
    if(!mysql_real_connect(&sql,"localhost","root","Hao_1987",NULL,0,NULL,0)){
        puts("Error connecting");
        printf("%s\n",mysql_error(&sql));
    }
    else{
        puts("Success connecting");
    }

  return 0;
}