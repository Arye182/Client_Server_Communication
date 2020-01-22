//
// Created by miri on 22.1.2020.
//

#include "MyClientHandler.h"

MyClientHandler::MyClientHandler(Solver<SearchableMatrix,string>* matrix_solver, CacheManager<SearchableMatrix,string>* cm){
  this->m_solver = matrix_solver;
  this->m_cm = cm;
}
void MyClientHandler::HandleClient(int i, int o) {
  vector<string> matrix_data;
  string solution;
  //send to client
  int valread = read(input_socket, buffer, INPUT_BUFFER_SIZE);
  if (valread == -1) {
    cerr << "couldnot read from client" << endl;
    exit(1);
  }
  string line(buffer, valread);
  while (line != "end") {
    //TODO
    matrix_data.push_back(line);

    if (m_cm->findSolution(line) != "not found") {
      solution = m_cm->findSolution(line);
    } else {
      solution = m_solver->solve(line);
      m_cm->insertSolution(line, solution);
    }
    const char *c_solution = solution.c_str();
    //send to client
    int valwrite = static_cast<int>(write(output_socket, c_solution, strlen(c_solution)));
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