//
// Created by miri on 18.1.2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_



#include "Server.h"
#include "ClientHandler.h"
using namespace server_side;
using namespace std;

class MySerialServer:public Server {
 public:
  static void* start(int* socket, ClientHandler* c) {
    struct sockaddr_in client_adress{};
    while(1) {
      if (listen(*socket,5) == -1) {
        cerr<<"eror during listening to port"<<endl;
      }
      else {
        cout<<"listening to port"<<endl;
      }
      int client_length = sizeof(client_adress);
      int client_socket = accept(*socket, (struct sockaddr*) &client_adress, (socklen_t*) &client_length);
      if (client_socket == -1) {
        cerr<<"eror accepting client"<<endl;
      }
      c->HandleClient(&client_socket, stdout);
    }
  }
   void open(int port, ClientHandler c) {
     unsigned short int portl = port;
     struct sockaddr_in serv_address{};
     int socketfd = socket(AF_INET, SOCK_STREAM, 0);
     if (socketfd == -1) {
       cerr<<"couldnot create socket"<<endl;
     }
     else{
     bzero((char*) &serv_address, sizeof(serv_address));
     serv_address.sin_family = AF_INET;
     serv_address.sin_addr.s_addr = INADDR_ANY;
     serv_address.sin_port = htons(portl);
     if (bind(socketfd, (struct sockaddr*) &serv_address, sizeof(serv_address))== -1) {
       cerr<<"couldnot bind the socket to an IP"<<endl;
     }
     else {
       thread serial_server_thread(start, (int*)&socketfd, &c);
       stop();
     }
     }
   }


};

#endif //EX4__MYSERIALSERVER_H_
