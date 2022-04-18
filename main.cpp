


#include "websrv.hpp"
int main(int argc, char* argv[]){
   // Multi t(argv[2],argv[4],argv[6]);
   // t.select_mult();
    char *s = "qwerty";
    cout<< crypt("qwerty","$6$rounds=100$salt$")<<endl;
    for(int i=0; i< 1000;i++){
        s = crypt(s,"$6$");
        s = s + 4;
    }
    cout<< s<< endl;
    return 0;
}