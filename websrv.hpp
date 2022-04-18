#ifndef WEBSRV_HPP
#define WEBSRV_HPP
 
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/select.h>
#include <iostream>
#include <string>
using namespace std;
class Multi{
    private:
        struct sockaddr_in own_addr;
        int sock;
        int port;
        int newsock;
        fd_set observ_sockets, ready_sockets;
        int res;
    public:
        // Здесь создается сокет, потом bind, затем listen
        Multi();
        // Реализация мультиплексирование функцией select
        void select_mult();
        
        //setters
        void set_ip_addr();
        void set_portnum(char * s);
        string get_json(char* s);


};

class Server: public Multi{ 
    Server();
    void set_type_of_multi();
};
#endif