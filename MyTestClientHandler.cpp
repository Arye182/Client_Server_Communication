//
// Created by miri on 22.1.2020.
//

#include "MyTestClientHandler.h"

/**
 *
 * @param solver
 * @param cm
 */
MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solver,
                                         CacheManager<string, string> *cm) {
  this->m_solver = solver;
  this->m_cm = cm;
  this->should_stop = false;
}

/**
 *
 * @param input_socket
 * @param output_socket
 */
void MyTestClientHandler::HandleClient(int input_socket, int output_socket) {
  char buffer[INPUT_BUFFER_SIZE] = {0};
  string solution;
  //send to client
  int valread = read(input_socket, buffer, INPUT_BUFFER_SIZE);
  if (valread == -1) {
    cerr << "couldnot read from client" << endl;
    exit(1);
  }
  string line(buffer, valread);
  while (line != "end") {
    if (m_cm->findSolution(line) != "not found") {
      solution = m_cm->findSolution(line);
    } else {
      solution = m_solver->solve(line);
      m_cm->insertSolution(line, solution);
    }
    const char *c_solution = solution.c_str();
    //send to client
    int valwrite =
        static_cast<int>(write(output_socket, c_solution, strlen(c_solution)));
    if (valwrite == -1) {
      cerr << "couldnot write to client" << endl;
      exit(1);
    }
    //receive from client
    valread = read(input_socket, buffer, 1024);
    if (valread == -1) {
      cerr << "couldnot read from client" << endl;
      exit(1);
    }
    string line(buffer, valread);
  }
}


