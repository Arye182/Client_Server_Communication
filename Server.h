//
// Created by miri on 18.1.2020.
//


#include <iostream>
#include <string>
#include <thread>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#define INPUT_BUFFER_SIZE 1024

using namespace std;

namespace server_side {
class ClientHandler {
 public:
  virtual void HandleClient(int i, int o) = 0;
};

class Server {
public:
  /*
   * @param port
   * open the server and wait to client
   */
  virtual void open(int port, ClientHandler* c) = 0;
  /*
   * close the server
   */
  virtual void stop(int socket) = 0;

};

class MySerialServer:public Server {
 public:
  virtual void open(int port, ClientHandler *c) override;
  virtual void stop(int socket) override;
  void *start(int *socket, ClientHandler *c);
};

namespace boot{
  class Main{
   public:
    static void main (char args[]){
      auto* server= new MySerialServer();
      StringReverser* s = new StringReverser();
      //auto* f_cm = new FileCacheManager();
      //MyTestClientHandler* test_client_handler = new MyTestClientHandler(s,f_cm);
      MyClientHandler* m = new MyClientHandler(nullptr, nullptr);
      server->open(5600, reinterpret_cast<ClientHandler*>(m));

    }
  };
};
};


