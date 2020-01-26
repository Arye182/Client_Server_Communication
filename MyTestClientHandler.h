//
// Created by miri on 18.1.2020.
//

#include <string>
#include <sys/socket.h>
#include <thread>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

#define INPUT_BUFFER_SIZE 1024
using namespace std;

class MyTestClientHandler : public ClientHandler {
 private:
  Solver<string, string> *m_solver;
  CacheManager<string, string> *m_cm;
  bool should_stop;

 public:
  MyTestClientHandler(Solver<string, string> *solver,
                      CacheManager<string, string> *cm);
  void HandleClient(int input_socket, int output_socket) override;
};