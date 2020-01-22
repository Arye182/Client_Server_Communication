//
// Created by miri on 22.1.2020.
#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver<string,string>* solver, CacheManager<string,string> *cm) {
this->m_solver = solver;
this->m_cm = cm;
this->should_stop = false;
}

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
    //TODO
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
