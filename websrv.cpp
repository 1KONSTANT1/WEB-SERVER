

#include "websrv.hpp"

 Multi::Multi(char * adres, char* pt, char * typpe){
     // создаем сокет 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        perror("can't create socket\n");
        exit(-1);
    }
    port = atoi(pt);
    own_addr.sin_family = AF_INET; 
    inet_pton(AF_INET, adres, &(own_addr.sin_addr));
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
                 char * errstr = "HTTP/1.0 409 Conflict\nContent-Type: text/plain\nContent-Length: 0\n\n";
                 //strcpy(errstr,"HTTP/1.0 409 Conflict\nContent-Type: text/plain\nContent-Length: 0\n");
                 if( (str[0] == 'P') && (str[1] == 'O')){
                     cout<< str<< endl;
                    json = get_json(str);
                    //cout<< endl<< json;
                    if(json_handler(json)){

                        char *hello = "HTTP/1.0 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                        write(newsock, hello, strlen(hello));
                    }
                    else{
                        write(newsock, errstr, strlen(errstr));
                    }
                 }
                 else{
                    write(newsock, errstr, strlen(errstr));
                 }
                 exit(0);
             }

         }
         
        

     }
 }
 string Multi:: get_json(char* s){
     string jsn;
     int fl = 0;
     while(1){
         if(fl){
             jsn.push_back(*s);
         }
         if(*s == '\n'){
             if(*(s+1) == '{') fl = 1;
         }
         if(fl && (*s == '}')) break;
         s++;
     }
     return jsn;
     

 }
 int Multi:: json_handler(string json){
     try{
     pt::ptree tree;
     stringstream jsomEncoded(json);
     pt::read_json(jsomEncoded, tree);
     m_file =tree.get<string>("str");
     strr =  m_file.data();
     round = tree.get("rounds",0);
     if( round == 0) return 0;
     cout<<round<< endl;
     cout<< strr << endl;
     return 1;
     }
     catch( exception & x){
         return 0;
     }
     /*const char* str = json.data();
     cout<< str<< endl;
     list = NULL;
     list = new node;
     int fl = 0;
     while(1){
         if(fl){

         }
         if(*str == '/"'){
             fl = 1;
         }
         str++;
     }
*/
 }
 char* Multi::hash_func(uint a, char * j){
     hash = j;
     for(uint i =0; i< a; i++){
         j = crypt(j,"$6$");
         j = j+4;
     }
     return j;
 }