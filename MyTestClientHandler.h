//
// Created by miri on 18.1.2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include <unistd.h>
using namespace std;

class MyTestClientHandler:public ClientHandler {
 private:
  Solver m_solver;
  CacheManager *m_cm;
 public:
  MyTestClientHandler(Solver solver, CacheManager *cm) {
  this->m_solver = solver;
  this->m_cm = cm;
  }
  virtual void HandleClient(int client_socket, int o) override {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    string line(buffer, valread);
    while (line != "end") {
      //TODO
      if (cm->find(line) != nullptr) {
        cout << cm->find(line) << endl;
      } else {
        cout << solver.solve(line) << endl;
      }
      valread = read(client_socket, buffer, 1024);
      string line(buffer, valread);
    }
  }
};
#endif //EX4__MYTESTCLIENTHANDLER_H_
