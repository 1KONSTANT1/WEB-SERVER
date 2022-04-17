

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
    own_addr.sin_port = htons(port);
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
        return 0; 
    }
 }

 void Multi::set_portnum(){
     port = atoi(argv[3]);
 }

 void select_mult(){
     while(1){
         newsock = accept(sock, NULL, NULL);
         if(newsock == -1){
                perror(" cant accept\n");  
                exit(-1);
            }
     }
 }