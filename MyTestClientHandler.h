//
// Created by miri on 18.1.2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include <unistd.h>
#include "Solver.h"
#define BUFFER_SIZE 1024

using namespace std;

class MyTestClientHandler:public ClientHandler {
 private:
  Solver<string,string> m_solver;
  CacheManager *m_cm;
 public:
  MyTestClientHandler(Solver<string,string> solver, CacheManager *cm) {
  this->m_solver = solver;
  this->m_cm = cm;
  }
  virtual void HandleClient(int input_socket, int output_socket) override {
    char buffer[BUFFER_SIZE] = {0};
    string solution;
    int valread = read(input_socket, buffer,BUFFER_SIZE);
    if (valread == -1) {
      cerr<<"couldnot read from client"<<endl;
      exit(1);
    }
    string line(buffer, valread);
    while (line != "end") {
      //TODO
      if (cm->find_solutin(line) != nullptr) {
        solution = cm->find_solution(line);
      } else {
        solution = m_solver.solve(line);
      }
        const char* c_solution = solution.c_str();
        int valwrite = static_cast<int>(write(output_socket, c_solution, strlen(c_solution)));
        if (valwrite == -1) {
          cerr<<"couldnot write to client"<<endl;
          exit(1);
        }
      valread = read(input_socket, buffer, 1024);
      if (valread == -1) {
        cerr<<"couldnot read from client"<<endl;
        exit(1);
      }
      string line(buffer, valread);
    }
  }
};
#endif //EX4__MYTESTCLIENTHANDLER_H_
