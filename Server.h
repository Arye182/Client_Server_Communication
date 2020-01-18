//
// Created by miri on 18.1.2020.
//

#ifndef EX4__SERVER_H_
#define EX4__SERVER_H_
#include <iostream>
#include <string>
#include <thread>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;

namespace server_side {
class Server {
public:
  /*
   * @param port
   * open the server and wait to client
   */
  virtual void open(int port);
  /*
   * close the server
   */
  virtual void stop();

};
};

#endif //EX4__SERVER_H_
