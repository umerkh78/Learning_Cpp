#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

void test(){
    int c_sock;
    c_sock = socket(AF_INET,SOCK_DGRAM,0); //Last param is for raw sockets since we ain't using one nothing to mention
    if(c_sock>0){
        //if the socket created successfully it returns non negative num
        std::cout<<"Socket created successfully 1"<<std::endl;
        struct sockaddr_in serv_address;
        serv_address.sin_addr.s_addr = inet_addr("10.0.2.15");
        serv_address.sin_family = AF_INET;
        serv_address.sin_port = htons(8000);
        connect(c_sock,(const sockaddr*)&serv_address,sizeof(serv_address));
        
        while(1){
            char msg[255]= "Hello from client 1";
            sendto(c_sock,msg,sizeof(msg),0,(const sockaddr*)&serv_address,sizeof(serv_address));
            char reply[255];
            if (recv(c_sock,reply,sizeof(reply),0)<1)
            {
                std::cout<<"Waiting for server to respond for 1...."<<std::endl;
            }
            else{
                std::cout<<reply<<std::endl;
                break;
            }

        }
        std::cout<<"Done sending"<<std::endl;
        close(c_sock);
    }
    else{
        std::cout<<"Socket creation failed"<<std::endl;
    }
    
}
void test1(){
    int c_sock;
    c_sock = socket(AF_INET,SOCK_DGRAM,0); //Last param is for raw sockets since we ain't using one nothing to mention
    if(c_sock>0){
        //if the socket created successfully it returns non negative num
        std::cout<<"Socket created successfully 2"<<std::endl;
        struct sockaddr_in serv_address;
        serv_address.sin_addr.s_addr = inet_addr("10.0.2.15");
        serv_address.sin_family = AF_INET;
        serv_address.sin_port = htons(8000);
        connect(c_sock,(const sockaddr*)&serv_address,sizeof(serv_address));
        
        while(1){
            char msg[255]= "Hello from client 2";
            sendto(c_sock,msg,sizeof(msg),0,(const sockaddr*)&serv_address,sizeof(serv_address));
            char reply[255];
            if (recv(c_sock,reply,sizeof(reply),0)<1)
            {
                std::cout<<"Waiting for server to respond for 2..."<<std::endl;
            }
            else{
                std::cout<<reply<<std::endl;
                break;
            }

        }
        std::cout<<"Done sending"<<std::endl;
        close(c_sock);
    }
    else{
        std::cout<<"Socket creation failed"<<std::endl;
    }
    
}
int main(){
    std::thread th1(&test);
    std::thread th2(&test1);
    th1.join();
    th2.join();
    std::cout<<"Done"<<std::endl;
    return 0;
}