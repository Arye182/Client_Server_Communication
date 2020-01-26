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
#include "MyMatrixCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "SearcherObjectAdapter.h"
#include "Solver.h"
#include "AStar.h"
#define INPUT_BUFFER_SIZE 1024

using namespace std;

/**
 *
 */
namespace server_side {

class Server {
 public:
  /*
   * @param port
   * open the server and wait to client
   */
  virtual void open(int port, ClientHandler *c) = 0;
  /*
   * close the server
   */
  virtual void stop(int socket) = 0;
  /**
   * Dtor.
   */
  virtual ~Server() = default;

};

/**
 *
 */
class MySerialServer : public Server {
 public:
  void open(int port, ClientHandler *c) override;
  void stop(int socket) override;
  void *start(int *socket, ClientHandler *c);
};

/**
 *
 */
class MyParallelServer : public Server {
  list<thread> m_threads;
 public:
  MyParallelServer() = default;
  void open(int port, ClientHandler *c) override;
  void acceptClients(int socket, ClientHandler *client_handler);
  void stop(int socket) override;
  void *HandleClientAdapter(ClientHandler *c, int socket);
  void join_threads();
};

/**
 *
 */
namespace boot {
/**
 *
 */
class Main {
 public:
  static void main(char args[]) {
    int port = stod(args);
    auto *server = new MyParallelServer();
    auto *f_cm = new MyMatrixCacheManager();
    AStar<Point> *searcher = new AStar<Point>();
    SearcherObjectAdapter *oa = new SearcherObjectAdapter(searcher);
    MyClientHandler *m = new MyClientHandler(reinterpret_cast<Solver<
        SearchableMatrix, string> *>(oa), f_cm);
    server->open(port, reinterpret_cast<ClientHandler *>(m));
  }
};
}
}


