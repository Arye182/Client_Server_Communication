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
#include "FileCacheManager.h"
#define INPUT_BUFFER_SIZE 1024

using namespace std;

namespace server_side {
class ClientHandler {
 public:
  virtual void HandleClient(int i, int o) = 0;
};

class Server {
public:
  /*
   * @param port
   * open the server and wait to client
   */
  virtual void open(int port, ClientHandler* c) = 0;
  /*
   * close the server
   */
  virtual void stop() = 0;

};

class MySerialServer:public Server {
 public:
  MySerialServer(){}
  static void* start(int* socket, ClientHandler* c) {
    struct sockaddr_in client_adress{};
    while(1) {
      if (listen(*socket,5) == -1) {
        cerr<<"eror during listening to port"<<endl;
      }
      else {
        cout<<"listening to port"<<endl;
      }
      int client_length = sizeof(client_adress);
      int client_socket = accept(*socket, (struct sockaddr*) &client_adress, (socklen_t*) &client_length);
      if (client_socket == -1) {
        cerr<<"eror accepting client"<<endl;
      }
      c->HandleClient(client_socket, client_socket);
    }
  }
  virtual void open(int port, ClientHandler* c) override {
    unsigned short int portl = port;
    struct sockaddr_in serv_address{};
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      cerr<<"couldnot create socket"<<endl;
    }
    else{
      bzero((char*) &serv_address, sizeof(serv_address));
      serv_address.sin_family = AF_INET;
      serv_address.sin_addr.s_addr = INADDR_ANY;
      serv_address.sin_port = htons(portl);
      if (bind(socketfd, (struct sockaddr*) &serv_address, sizeof(serv_address))== -1) {
        cerr<<"couldnot bind the socket to an IP"<<endl;
      }
      else {
        thread serial_server_thread(start, &socketfd, c);
        stop();
      }
    }
  }
  virtual void stop(){}

};

class MyTestClientHandler:public ClientHandler {
 private:
  Solver<string,string>* m_solver;
  CacheManager<string, string> *m_cm;
 public:
  MyTestClientHandler(Solver<string,string>* solver, CacheManager<string,string> *cm) {
    this->m_solver = solver;
    this->m_cm = cm;
  }
  virtual void HandleClient(int input_socket, int output_socket) override {
    char buffer[INPUT_BUFFER_SIZE] = {0};
    string solution;
    int valread = read(input_socket, buffer,INPUT_BUFFER_SIZE);
    if (valread == -1) {
      cerr<<"couldnot read from client"<<endl;
      exit(1);
    }
    string line(buffer, valread);
    while (line != "end") {
      //TODO
      if (m_cm->findSolution(line)!="not found") {
        solution = m_cm->findSolution(line);
      } else {
        solution = m_solver->solve(line);
        m_cm->insertSolution(line, solution);
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
namespace boot{
  class Main{
   public:
    static void main (char args[]){
      server_side::MySerialServer* server= new MySerialServer();
      server->open(5600,new MyTestClientHandler(new StringReverser(),new FileCacheManager()));
    }
  };
};
};


