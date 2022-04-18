#ifndef WEBSRV_HPP
#define WEBSRV_HPP
 
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h> 
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/select.h>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include<cstring>
#include <arpa/inet.h>

namespace pt = boost::property_tree;
using namespace std;

class Multi{
    private:
        struct sockaddr_in own_addr;
        int sock;
        int port;
        int newsock;
        fd_set observ_sockets, ready_sockets;
        int res;
        string json;
        string m_file;
        const char * strr;
        uint round;
        char* hash;
    public:
        // Здесь создается сокет, потом bind, затем listen
        Multi(char * adres, char* pt, char * typpe);
        // Реализация мультиплексирование функцией select
        void select_mult();
        
        //setters
        void set_ip_addr();
        void set_portnum(char * s);
        string get_json(char* s);
        int json_handler(string json);
        char * hash_func(uint a, char * j);


};

class Server: public Multi{ 
    Server();
    void set_type_of_multi();
};
#endif