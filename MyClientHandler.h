//
// Created by miri on 22.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_
#define CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_

#include <string>
#include <sys/socket.h>
#include <thread>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "Matrix.h"
#include "SearchableMatrix.h"

class MyClientHandler : public ClientHandler {
 private:
  Solver<SearchableMatrix, string> *m_solver;
  CacheManager<string, string> *m_cm;
  bool should_stop;

 public:
  MyClientHandler(Solver<SearchableMatrix, string> *matrix_solver,
                  CacheManager<string, string> *cm);
  virtual MyClientHandler *deepCopy() override;
  virtual void HandleClient(int i, int o) override;
  string readFromClient(int socket);
  vector<string> input_vector(string input);
};

#endif //CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_
