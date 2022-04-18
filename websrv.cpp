

#include "websrv.hpp"

 Multi::Multi(){
     // создаем сокет 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        perror("can't create socket\n");
        exit(-1);
    }
    own_addr.sin_family = AF_INET; 
    own_addr.sin_addr.s_addr = INADDR_ANY;
    own_addr.sin_port = htons(8083);
    // закрепляем адресс за сокетом
    if (bind(sock, (struct sockaddr *) &own_addr,sizeof(own_addr)) < 0)
    {
        perror("can't bind socket!");
        exit(-1);
    }
    // начинаем обработку запросов на соединение 
    if (listen(sock, 5) < 0)
    {
        printf("can't listen socket!");
        exit(-1);
    }
 }

 void Multi::set_portnum(char* s){
     port = atoi(s);
     cout<< port<<endl;
 }

 void Multi::select_mult(){
     FD_ZERO(&observ_sockets);
     FD_SET(sock,&observ_sockets);
     while(1){
         cout<< "waiting for connection..."<<endl;
         if((res = select(sock+1,&observ_sockets,NULL,NULL,NULL))<0){
             perror("select problem");
             exit(-1);
         }
         if(res == 0){
             continue;
         }
         if( res > 0){
             if((newsock = accept(sock, NULL, NULL))<0)
             {
                perror(" cant accept\n");  
                exit(-1);
             }
             if(fork() ==0){
                 char  str[60000] = {0};
                 read(newsock ,str, 60000);
                 cout<< str<< endl;
                 cout<< endl<< get_json(str);
                 write(newsock, str, 60000);
                 exit(0);
             }

         }
         
        

     }
 }
 string Multi:: get_json(char* s){
     string json;
     int fl = 0;
     while(1){
         if(fl){
             json.push_back(*s);
         }
         if(*s == '\n'){
             if(*(s+1) == '{') fl = 1;
         }
         if(fl && (*s == '}')) break;
         s++;
     }
     return json;
     

 }