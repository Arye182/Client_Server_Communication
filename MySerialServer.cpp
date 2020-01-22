//
// Created by miri on 21.1.2020.
//

#include "Server.h"
using namespace server_side;

void MySerialServer::open(int port, ClientHandler *c) {
  unsigned short int portl = port;
//create socket
  struct sockaddr_in serv_address{};
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    cerr << "couldnot create socket" << endl;
    exit(1);
  }
//define timeout for connecting client
  int timeout_in_seconds = 12000;
  struct timeval tv;
  tv.tv_sec = timeout_in_seconds;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof(tv));
//bind socket to port
  bzero((char *) &serv_address, sizeof(serv_address));
  serv_address.sin_family = AF_INET;
  serv_address.sin_addr.s_addr = INADDR_ANY;
  serv_address.sin_port = htons(portl);
  if (bind(socketfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) == -1) {
    cerr << "couldnot bind the socket to an IP" << endl;
    exit(1);
  }
  //start listen to port
  if (listen(socketfd, 5) == -1) {
    cerr << "eror during listening to port" << endl;
  } else {
    cout << "listening to port" << endl;
  }
  //open thread to connect clients
  std::thread serial_server_thread(&MySerialServer::start,this,&socketfd, c);
  serial_server_thread.join();
}

void MySerialServer::stop(int socket) {
  close(socket);
}

void *MySerialServer::start(int *socket, ClientHandler *c) {
  struct sockaddr_in client_adress{};
  while (1) {
    int client_length = sizeof(client_adress);
    //accept client
    int client_socket = accept(*socket, (struct sockaddr *) &client_adress, (socklen_t *) &client_length);
    if (client_socket < 0) {
      cerr << "eror accepting client" << endl;
      stop(*socket);
      return nullptr;
    }
    c->HandleClient(client_socket, client_socket);
  }
}