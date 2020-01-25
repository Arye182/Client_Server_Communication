//
// Created by miri on 18.1.2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
#include <iostream>
#include <cstring>
class ClientHandler {
 public:
  virtual void HandleClient(int i, int o) = 0;
  virtual ClientHandler* deepCopy() = 0;
};
#endif //EX4__CLIENTHANDLER_H_
