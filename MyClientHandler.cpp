//
// Created by miri on 22.1.2020.
//

#include "MyClientHandler.h"
#define INPUT_BUFFER_SIZE 1024
MyClientHandler::MyClientHandler(Solver<SearchableMatrix,string>* matrix_solver, CacheManager<string,string>* cm){
  this->m_solver = matrix_solver;
  this->m_cm = cm;
  this->should_stop = false;
}
void MyClientHandler::HandleClient(int i, int o) {
  vector<string> matrix_data;
  string solution;
  //read problem from client
  string str_problem = this->readFromClient(i);
  //check for existing solution
  //solution = m_cm->findSolution(str_problem);
  //solve and insert to cache manager
  //if (solution == "not found") {
      matrix_data = input_vector(str_problem);
      SearchableMatrix *problem = new SearchableMatrix(new Matrix(matrix_data));
      solution = m_solver->solve(*problem);
     // m_cm->insertSolution(str_problem, solution);
   // }
    const char *c_solution = solution.c_str();
    //send to client
    int valwrite = static_cast<int>(write(i, c_solution, strlen(c_solution)));
    if (valwrite == -1) {
      cerr << "couldnot write to client" << endl;
      exit(1);
    }
}

string MyClientHandler::readFromClient(int socket) {
  char buffer[INPUT_BUFFER_SIZE];
  string full_input = "";
  while (!(should_stop)) {
    bzero(buffer, INPUT_BUFFER_SIZE);
    int valread = read(socket, buffer, INPUT_BUFFER_SIZE);
    if (valread < 0) {
      cerr << "couldnot read from client" << endl;
      exit(1);
    }
    string line(buffer, valread);
    full_input = full_input + line;
    if (line.find("end") < line.size()) {
      this->should_stop = true;
    }
  }
  cout<<full_input<<endl;
  return full_input;
}
  vector<string> MyClientHandler::input_vector(string input) {
    vector<string> matrix_data;
    int i = 0, index = 0, size;
    string::size_type j;
    size = input.size();
    j = input.find("\n");
    //seperte the input by "\n"
    while (j != string::npos) {
      matrix_data.push_back(input.substr(i, j));
      cout<<matrix_data[index];
      i = j + 2;
      j = input.find("\n", i);
      index++;
    }
    return matrix_data;
}