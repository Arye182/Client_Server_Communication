//
// Created by miri on 22.1.2020.
//

#include "MyClientHandler.h"
#include<sstream>
#define INPUT_BUFFER_SIZE 1024

/**
 * Ctor.
 *
 * @param matrix_solver
 * @param cm
 */
MyClientHandler::MyClientHandler(Solver<SearchableMatrix,
                                        string> *matrix_solver,
                                 CacheManager<string, string> *cm) {
  this->m_solver = matrix_solver;
  this->m_cm = cm;
  this->should_stop = false;
}

/**
 * deep copy method.
 * @return a deep copy of this client handler
 */
MyClientHandler *MyClientHandler::deepCopy() {
  return new MyClientHandler(this->m_solver->deepCopy(), this->m_cm);
}

/**
 *
 * @param i
 * @param o
 */
void MyClientHandler::HandleClient(int i, int o) {
  vector<string> matrix_data;
  string solution;
  //read problem from client
  string str_problem = this->readFromClient(i);
  //check for existing solution
  solution = m_cm->findSolution(str_problem);
  //solve and insert to cache manager
  if (solution == "") {
    matrix_data = input_vector(str_problem);
    SearchableMatrix *problem = new SearchableMatrix(new Matrix(matrix_data));
    solution = m_solver->solve(*problem);
    m_cm->insertSolution(str_problem, solution);
  }
  const char *c_solution = solution.c_str();
  //send to client
  int valwrite = static_cast<int>(write(i, c_solution, strlen(c_solution)));
  if (valwrite == -1) {
    cerr << "couldnot write to client" << endl;
    exit(1);
  }
}

/**
 * reading from client
 * @param socket
 * @return
 */
string MyClientHandler::readFromClient(int socket) {
  char buffer[INPUT_BUFFER_SIZE];
  string full_input = "";
  while (!(should_stop)) {
    int valread = read(socket, buffer, INPUT_BUFFER_SIZE);
    if (valread < 0) {
      cerr << "couldnot read from client" << endl;
      exit(1);
    }
    string line(buffer, valread);
    full_input = full_input + line;
    bzero(buffer, INPUT_BUFFER_SIZE);
    if (line.find("end") < line.size()) {
      this->should_stop = true;
    }
  }
  return full_input;
}

/**
 * gets a string of matrix and returns a vector of strings (rows in matrix)
 * @param input - matrix in string
 * @return matrix in vector of strings
 */
vector<string> MyClientHandler::input_vector(string input) {
  vector<string> matrix_data;
  string temp;
  stringstream input_str_stream(input);
  while (getline(input_str_stream, temp, '\n')) {
    matrix_data.push_back(temp);
  }
  return matrix_data;
}