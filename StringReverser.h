//
// Created by miri on 20.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__STRINGREVERSER_H_
#define CLIENT_SERVER_COMMUNICATION__STRINGREVERSER_H_
#include "Solver.h"
#include <string>
using namespace std;
class StringReverser:public Solver<string,string> {
 public:
  virtual string solve(string problem);
};

#endif //CLIENT_SERVER_COMMUNICATION__STRINGREVERSER_H_
