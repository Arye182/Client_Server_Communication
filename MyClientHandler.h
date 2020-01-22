//
// Created by miri on 22.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_
#define CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "Matrix.h"
#include "SearchableMatrix.h"
class MyClientHandler:public ClientHandler{
 private:
  Solver<SearchableMatrix,string>* m_solver;
  CacheManager<SearchableMatrix,string>* m_cm;

 public:
  MyClientHandler(Solver<SearchableMatrix,string>* matrix_solver, CacheManager<SearchableMatrix,string>* cm);
  virtual void HandleClient(int i, int o) override;
};
#endif //CLIENT_SERVER_COMMUNICATION__MYCLIENTHANDLER_H_
